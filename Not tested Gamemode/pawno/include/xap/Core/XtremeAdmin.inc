/************************************************
*	Programmers: Xtreme, SharkyKH		*
*	Include: XtremeAdmin.inc		*
*	Purpose: Xtreme Admin Functions		*
*************************************************/
 
#if defined _XtremeAdmin_included
  #endinput
#endif
#define _XtremeAdmin_included
#pragma library XtremeAdmin

#include "xap/Core/DFiles.inc"
#include "xap/Core/XRegistration.inc"
#include "xap/Core/MD5.inc"
#define dcmd(%1,%2,%3) if(!(strcmp((%3)[1],#%1,true,(%2)))&&((((%3)[(%2)+1]==0)&&(dcmd_%1(playerid,"")))||(((%3)[(%2)+1]==32)&&(dcmd_%1(playerid,(%3)[(%2)+2]))))) return 1
#define GetStringArg(%1,%2) for(new x = 0; getarg(%1,x) != '\0'; x++) %2[x] = getarg(%1,x)
 
enum ConfigData
{
	Float:TeleportZOffset,			// Offset Z for when you use goto or gethere.
	MinimumPasswordLength,			// Minimum password length for registration.
	DisplayServerMessage,			// Boolean to display the server message.
	SlapDecrement,				// The amount to subract with the command /SLAP.
	MutedWarnings,				// The amount of warnings a player has when they are Muted.
	GodWeapons,				// Do you get weapons when you type /GOD?
	MaxLevel,				// The maximum admin level possible.
	DisplayConnectMessages,			// Display connect and disconnect messages?
	MaxPing,				// The maximum ping allowed for the ping kicker.
	AdminImmunity,				// Allow admin immunity for ping kicks?
	PingSecondUpdate,			// The amount of seconds to check pings.
	ForbidData,				// What action to commit if a player joins with a forbidden name (0 = Nothing, 1 = Kick, 2 = Ban)
	DisableJailCommands			// Disable player commands whilst they are jailed?
};
enum PlayerData
{
	Level,			// Stores the integer value for the player's level.
	Registered,		// Determines whether or not the player has registered.
	bool:LoggedIn,		// Determines whether or not the player has logged in.
	Muted,			// Determins whether or not the player has been muted.
	MutedWarnings,		// The amount of warnings that the player currently has.
	Jailed,			// Has the player been jailed?
	Commands,		// Do you want to see player commands (for admins)?
	ACommands,		// Do you want to see admin commands (for admins)?
	PPMS,			// Do you want to see player private messages (for admins)?
	Frozen			// Determines whether or not the player is frozen.
};
enum SpectateData
{
	bool:Spectating,	// Determine whether the player is spectating.
	SpectateID		// Store the ID that the player is spectating.
}
stock Variables[MAX_PLAYERS][PlayerData], Config[ConfigData], Spec[MAX_PLAYERS][SpectateData], ForbidNames[100][24];
//new CMDSFile[64] = "/xap/Configuration/Commands.ini";
//=====================[DYNAMIC CONFIGURATION SYSTEM]===========================
stock CreateLevelConfig({Float,_}:...)
{
	new tmp[128],file[64]; file = "/xap/Configuration/Variables.ini";
	if(dini_Exists(file)) dini_Remove(file); dini_Create(file); dini_IntSet(file,"Count",0);
	new Count = dini_Int(file,"Count"), string[128];
	for(new i = 0; i < numargs(); i++) { ClearString(128,string); GetStringArg(i,string); valstr(tmp,Count); dini_Set(file,tmp,string); Count++; dini_IntSet(file,"Count",Count); }
}
/*stock AddCommandToCommandConfig(command[], level)
{
	if(!dini_Exists(CMDSFile)) dini_Create(CMDSFile);
	if(!dini_Isset(CMDSFile,command)) dini_IntSet(CMDSFile,command,level);
}*/
stock CreateUserConfigFile(playerid)
{
	new file[64],name[24],config[64],tmp[128],tmp2[128]; config = "/xap/Configuration/Variables.ini";
	GetPlayerName(playerid,name,24); format(file,64,"/xap/Users/%s.ini",udb_encode(name));
	if(!dini_Exists(file)) dini_Create(file); if(!dini_Exists(config)) dini_Create(config);
	for(new i = 0; i < dini_Int(config,"Count"); i++) { valstr(tmp,i); tmp2 = dini_Get(config,tmp); if(!dini_Isset(file,tmp2)) dini_IntSet(file,tmp2,0); }
}
stock GetPlayerFileVar(playerid,var[])
{
	new file[64]; file = GetPlayerFile(playerid);
	return (!dini_Exists(file)) ? 0 : dini_Int(file,var);
}
stock CreateForbiddenNames({Float,_}:...)
{
	new Temp[128],i; while(i < numargs()) { GetStringArg(i,Temp); ForbidNames[i] = Temp; i += 1; }
}
stock SetUserString(playerid,var[],value[]) { new file[64]; file = GetPlayerFile(playerid); if(!dini_Exists(file)) dini_Create(file); dini_Set(file,var,value); }
stock SetUserInt(playerid,var[],value) { new file[64]; file = GetPlayerFile(playerid); if(!dini_Exists(file)) dini_Create(file); dini_IntSet(file,var,value); return 1; }
stock SetConfigInt(var[],value) { new file[64] = "/xap/Configuration/Variables.ini"; if(!dini_Isset(file,var)) return 0; dini_IntSet(file,var,value); return 1; }
stock UpdateConfigurationVariables()
{
	new ConfigFile[64]; ConfigFile = "/xap/Configuration/Configuration.ini";
	if(!dini_Exists(ConfigFile)) dini_Create(ConfigFile);
	// Make sure required variables exist.
	if(!dini_Isset(ConfigFile,"ServerMessage")) dini_Set(ConfigFile,"ServerMessage","None");
	if(!dini_Isset(ConfigFile,"Teleport_Z_Offset")) dini_FloatSet(ConfigFile,"Teleport_Z_Offset",1.0);
	if(!dini_Isset(ConfigFile,"MinimumPasswordLength")) dini_IntSet(ConfigFile,"MinimumPasswordLength",3);
	if(!dini_Isset(ConfigFile,"DisplayServerMessage")) dini_IntSet(ConfigFile,"DisplayServerMessage",0);
	if(!dini_Isset(ConfigFile,"SlapDecrement")) dini_IntSet(ConfigFile,"SlapDecrement",20);
	if(!dini_Isset(ConfigFile,"MutedWarnings")) dini_IntSet(ConfigFile,"MutedWarnings",5);
	if(!dini_Isset(ConfigFile,"GodWeapons")) dini_IntSet(ConfigFile,"GodWeapons",0);
	if(!dini_Isset(ConfigFile,"MaxLevel")) dini_IntSet(ConfigFile,"MaxLevel",10);
	if(!dini_Isset(ConfigFile,"DisplayConnectMessages")) dini_IntSet(ConfigFile,"DisplayConnectMessages",1);
	if(!dini_Isset(ConfigFile,"MaxPing")) dini_IntSet(ConfigFile,"MaxPing",600);
	if(!dini_Isset(ConfigFile,"AdminImmunity")) dini_IntSet(ConfigFile,"AdminImmunity",1);
	if(!dini_Isset(ConfigFile,"PingSecondUpdate")) dini_IntSet(ConfigFile,"PingSecondUpdate",5);
	if(!dini_Isset(ConfigFile,"ForbidData")) dini_IntSet(ConfigFile,"ForbidData",0);
	if(!dini_Isset(ConfigFile,"DisableJailCommands")) dini_IntSet(ConfigFile,"DisableJailCommands",1);
	// Update to array.
	Config[TeleportZOffset] = dini_Float(ConfigFile,"Teleport_Z_Offset");
	Config[MinimumPasswordLength] = dini_Int(ConfigFile,"MinimumPasswordLength");
	Config[DisplayServerMessage] = dini_Bool(ConfigFile,"DisplayServerMessage");
	Config[SlapDecrement] = dini_Bool(ConfigFile,"SlapDecrement");
	Config[MutedWarnings] = dini_Int(ConfigFile,"MutedWarnings");
	Config[GodWeapons] = dini_Int(ConfigFile,"GodWeapons");
	Config[MaxLevel] = dini_Int(ConfigFile,"MaxLevel");
	Config[DisplayConnectMessages] = dini_Int(ConfigFile,"DisplayConnectMessages");
	Config[MaxPing] = dini_Int(ConfigFile,"MaxPing");
	Config[AdminImmunity] = dini_Int(ConfigFile,"AdminImmunity");
	Config[PingSecondUpdate] = dini_Int(ConfigFile,"PingSecondUpdate");
	Config[ForbidData] = dini_Int(ConfigFile,"ForbidData");
	Config[DisableJailCommands] = dini_Int(ConfigFile,"DisableJailCommands");
}
//==========================[CUSTOM FUNCTIONS]==================================
stock ClearString(MaxLength,string[]) for(new i = 0; i < MaxLength; i++) format(string[i],1,"");
stock ReturnCommandID(cmd[])
{
	for (new i = 0; i < COMMANDS_COUNT; ++i)
		if (!strcmp(CommandsList[i][CL_CMD], cmd, true))
			return i;
	return -1;
}
stock ReturnCommandLevel(cmd[])
{
	for (new i = 0; i < COMMANDS_COUNT; ++i)
		if (!strcmp(CommandsList[i][CL_CMD], cmd, true))
			return CommandsList[i][CL_LVL];
	return -1;
}
stock IsPlayerCommandLevel(playerid,command[]) {
	new cmdlvl = ReturnCommandLevel(command);
	if (cmdlvl < 0) cmdlvl = 0;
	return (IsPlayerConnected(playerid) && Variables[playerid][LoggedIn]
		&& (Variables[playerid][Level] >= cmdlvl || cmdlvl == 0)) ? true : false;
}
stock GetPlayerFile(playerid) {
	new string[64], PlayerName[24]; GetPlayerName(playerid,PlayerName,24);
	format(string,64,"/xap/Users/%s.ini",udb_encode(PlayerName));
	return string;
}
stock SendLevelErrorMessage(playerid,command[])
{
	if (Variables[playerid][Level])
	{
		new string[128];
		new cmdlvl = ReturnCommandLevel(command);
		if (cmdlvl < 0) cmdlvl = 0;
		if (Variables[playerid][LoggedIn])
			format(string, 128, "ERROR: You must be administrator level %d to use this command.", cmdlvl);
		else
			format(string, 128, "ERROR: You must be logged in to your admin account to do admin commands.");
		return SendClientMessage(playerid, red, string);
	}
	else return false;
}
stock ReturnPlayerID(PlayerName[]) {
	for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i)) { new name[24]; GetPlayerName(i,name,24); if(strfind(name,PlayerName,true)!=-1) return i; }
	return INVALID_PLAYER_ID;
}
stock ReturnPlayerName(playerid) {
	new name[24]; GetPlayerName(playerid, name, 24);
	return name;
}
stock IsPlayerInServer(PlayerName[])
{
	for (new i = 0; i < GetMaxPlayers(); i++)
	{
		if(IsPlayerConnected(i))
		{
			new name[24];
			GetPlayerName(i,name,24);
			if (!strcmp(name,PlayerName,false)) return true;
		}
	}
	return false;
}
stock ReturnWeaponID(WeaponName[])
{
	if(strfind("molotov",WeaponName,true)!=-1) return 18;
	for(new i = 0; i <= 46; i++) {
		switch(i) {
			case 0,19,20,21,44,45: continue;
			default: { new name[24]; GetWeaponName(i,name,24); if(strfind(name,WeaponName,true)!=-1) return i; }
		}
	}
	return -1;
}
stock IsPlayerXAdmin(playerid) return (Variables[playerid][LoggedIn] && Variables[playerid][Level]) ? true:false;
stock GetConnectedPlayers() {
	new Players;
	for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i)) Players++;
	return Players;
}
stock IsSkinValid(SkinID) return ((SkinID >= 0 && SkinID <= 1)||(SkinID == 2)||(SkinID == 7)||(SkinID >= 9 && SkinID <= 41)
||(SkinID >= 43 && SkinID <= 85)||(SkinID >=87 && SkinID <= 118)||(SkinID >= 120 && SkinID <= 148)||(SkinID >= 150 && SkinID <= 207)
||(SkinID >= 209 && SkinID <= 272)||(SkinID >= 274 && SkinID <= 288)||(SkinID >= 290 && SkinID <= 299)) ? true:false;
stock IsNumeric(string[]) {
	for (new i = 0, j = strlen(string); i < j; i++) if (string[i] > '9' || string[i] < '0') return 0;
	return 1;
}
stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance) {
	new Float:a; GetPlayerPos(playerid, x, y, a); GetPlayerFacingAngle(playerid, a);
	if (GetPlayerVehicleID(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	x += (distance * floatsin(-a, degrees)); y += (distance * floatcos(-a, degrees));
}
stock Wait(time) {
	new stamp = tickcount();
	while (tickcount() - stamp < time) { }
	return 1;
}