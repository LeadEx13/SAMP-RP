/********************************************
*       Programmers: Xtreme, SharkyKH       *
*       Include: XtremeAdmin.inc            *
*       Purpose: Xtreme Admin Functions     *
********************************************/
 
#if defined _XtremeAdmin_included
  #endinput
#endif
#define _XtremeAdmin_included
#pragma library XtremeAdmin
 
#include "xadmin/DFiles.inc"
#include "xadmin/XRegistration.inc"
#define dcmd(%1,%2,%3) if(!(strcmp((%3)[1],#%1,true,(%2)))&&((((%3)[(%2)+1]==0)&&(dcmd_%1(playerid,"")))||(((%3)[(%2)+1]==32)&&(dcmd_%1(playerid,(%3)[(%2)+2]))))) return 1
#define GetStringArg(%1,%2) for(new x = 0; getarg(%1,x) != '\0'; x++) %2[x] = getarg(%1,x)
 
enum ConfigData {
        Float:TeleportZOffset,                          // Offset Z for when you use goto or gethere.
        MinimumPasswordLength,                          // Minimum password length for registration.
        DisplayServerMessage,              // Boolean to display the server message.
        SlapDecrement,                      // The amount to subract with the command /SLAP.
        MutedWarnings,                      // The amount of warnings a player has when they are Muted.
        GodWeapons,                         // Do you get weapons when you type /GOD?
        MaxLevel,                           // The maximum admin level possible.
        DisplayConnectMessages,             // Display connect and disconnect messages?
        MaxPing,                            // The maximum ping allowed for the ping kicker.
        AdminImmunity,                      // Allow admin immunity for ping kicks?
        PingSecondUpdate,                   // The amount of seconds to check pings.
        ForbidData,                         // What action to commit if a player joins with a forbidden name (0 = Nothing, 1 = Kick, 2 = Ban)
        DisableJailCommands                // Disable player commands whilst they are jailed?
};
enum PlayerData {
        Level,                                                  // Stores the integer value for the player's level.
        Registered,                         // Determines whether or not the player has registered.
        bool:LoggedIn,       // Determines whether or not the player has logged in.
        Muted,                              // Determins whether or not the player has been muted.
        MutedWarnings,                      // The amount of warnings that the player currently has.
        Jailed,                              // Has the player been jailed?
        Commands,                              // Do you want to see player commands (for admins)?
        ACommands,                              // Do you want to see admin commands (for admins)?
        PPMS,                              // Do you want to see player private messages (for admins)?
        Frozen                       // Determines whether or not the player is frozen.
};
enum SpectateData {
        bool:Spectating,                    // Determine whether the player is spectating.
        SpectateID                          // Store the ID that the player is spectating.
}
stock Variables[MAX_PLAYERS][PlayerData], Config[ConfigData], Spec[MAX_PLAYERS][SpectateData], ForbidNames[100][256];
//=====================[DYNAMIC CONFIGURATION SYSTEM]===========================
stock CreateLevelConfig({Float,_}:...) {
        new tmp[256],file[256]; file = "/xadmin/Configuration/Variables.ini";
        if(dini_Exists(file)) dini_Remove(file); dini_Create(file); dini_IntSet(file,"Count",0);
        new Count = dini_Int(file,"Count"), string[256];
        for(new i = 0; i < numargs(); i++) { ClearString(256,string); GetStringArg(i,string); valstr(tmp,Count); dini_Set(file,tmp,string); Count++; dini_IntSet(file,"Count",Count); }
}
stock CreateCommandConfig({Float,_}:...) {
        new i = 0,key[256],value,file[256]; file = "/xadmin/Configuration/Commands.ini";
        if(!dini_Exists(file)) dini_Create(file);
        while(i < numargs()) { ClearString(256,key); GetStringArg(i,key); value = getarg(i+1,0); if(!dini_Isset(file,key)) dini_IntSet(file,key,value); i += 2; }
}
stock CreateCommandConfigEx({Float,_}:...) {
        new i = 0,key[256],value,file[256]; file = "/xadmin/Configuration/Commands.ini";
        while(i < numargs()) { ClearString(256,key); GetStringArg(i,key); value = getarg(i+1,0); if(!dini_Isset(file,key)) dini_IntSet(file,key,value); i += 2; }
}
stock CreateUserConfigFile(playerid) {
        new file[256],name[24],config[256],tmp[256],tmp2[256]; config = "/xadmin/Configuration/Variables.ini"; GetPlayerName(playerid,name,24); format(file,256,"/xadmin/Users/%s.ini",udb_encode(name));
        if(!dini_Exists(file)) dini_Create(file); if(!dini_Exists(config)) dini_Create(config);
        for(new i = 0; i < dini_Int(config,"Count"); i++) { valstr(tmp,i); tmp2 = dini_Get(config,tmp); if(!dini_Isset(file,tmp2)) dini_IntSet(file,tmp2,0); }
}
stock GetPlayerFileVar(playerid,var[]) {
        new file[256]; file = GetPlayerFile(playerid);
        return (!dini_Exists(file)) ? 0 : dini_Int(file,var);
}
stock CreateForbiddenNames({Float,_}:...) {
        new Temp[256],i; while(i < numargs()) { GetStringArg(i,Temp); ForbidNames[i] = Temp; printf(ForbidNames[i]); i += 1; }
}
stock SetUserString(playerid,var[],value[]) { new file[256]; file = GetPlayerFile(playerid); if(!dini_Exists(file)) dini_Create(file); dini_Set(file,var,value); }
stock SetUserInt(playerid,var[],value) { new file[256]; file = GetPlayerFile(playerid); if(!dini_Exists(file)) dini_Create(file); dini_IntSet(file,var,value); return 1; }
stock SetConfigInt(var[],value) { new file[256] = "/xadmin/Configuration/Variables.ini"; if(!dini_Isset(file,var)) return 0; dini_IntSet(file,var,value); return 1; }
stock UpdateConfigurationVariables() {
        new ConfigFile[256]; ConfigFile = "/xadmin/Configuration/Configuration.ini";
        if(!dini_Exists(ConfigFile)) dini_Create(ConfigFile);
        // Make sure required variables exist.
        if(!dini_Isset(ConfigFile,"ServerMessage")) dini_Set(ConfigFile,"ServerMessage","None");
        if(!dini_Isset(ConfigFile,"Teleport_Z_Offset")) dini_FloatSet(ConfigFile,"Teleport_Z_Offset",1.0);
        if(!dini_Isset(ConfigFile,"MinimumPasswordLength")) dini_IntSet(ConfigFile,"MinimumPasswordLength",3);
        if(!dini_Isset(ConfigFile,"DisplayServerMessage")) dini_IntSet(ConfigFile,"DisplayServerMessage",0);
        if(!dini_Isset(ConfigFile,"SlapDecrement")) dini_IntSet(ConfigFile,"SlapDecrement",20);
        if(!dini_Isset(ConfigFile,"MutedWarnings")) dini_IntSet(ConfigFile,"MutedWarnings",5);
        if(!dini_Isset(ConfigFile,"GodWeapons")) dini_IntSet(ConfigFile,"GodWeapons",0);
        if(!dini_Isset(ConfigFile,"MaxLevel")) dini_IntSet(ConfigFile,"MaxLevel",12);
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
stock IsPlayerCommandLevel(playerid,command[]) {
        if(!dini_Isset("/xadmin/Configuration/Commands.ini",command)) return false;
        return (IsPlayerConnected(playerid) && Variables[playerid][LoggedIn] && (Variables[playerid][Level] >= dini_Int("/xadmin/Configuration/Commands.ini",command) || dini_Int("/xadmin/Configuration/Commands.ini",command) == 0)) ? true : false;
}
stock GetPlayerFile(playerid) { new string[256], PlayerName[24]; GetPlayerName(playerid,PlayerName,24); format(string,256,"/xadmin/Users/%s.ini",udb_encode(PlayerName)); return string; }
stock SendLevelErrorMessage(playerid,command[]) { if(IsPlayerXAdmin(playerid)) { new string[256]; format(string,256,"ERROR: You must be administrator level %d to use this command.",dini_Int("/xadmin/Configuration/Commands.ini",command)); return SendClientMessage(playerid,red,string); } else return 0; }
stock ReturnPlayerID(PlayerName[]) {
        for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i)) { new name[24]; GetPlayerName(i,name,24); if(strfind(name,PlayerName,true)!=-1) return i; }
        return INVALID_PLAYER_ID;
}
stock ReturnPlayerName(playerid) { new name[24]; GetPlayerName(playerid, name, 24); return name; }
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

stock SendMessageToAdmins(color, text[]) { for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i) && IsPlayerXAdmin(i)) SendClientMessage(i,color,text); return 1; }
stock SendPMMessageToAdmins(playerid,recieverid,text[]) { new string[256],name[24],toname[24]; GetPlayerName(playerid,name,24); GetPlayerName(recieverid,toname,24); format(string,256,"*** PM: %s [%d] to %s [%d]: %s",name,playerid,toname,recieverid,text); for(new i=0;i<GetMaxPlayers();i++) if(IsPlayerConnected(i)&&i!=playerid&&i!=recieverid&&IsPlayerXAdmin(i)&&Variables[i][PPMS]) SendClientMessage(i,ppmsc,string); }
stock SendMessageToAdminsEx(playerid, color, text[]) { for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid) SendClientMessage(i,color,text); return 1; }
stock SendMessageToAdminsEx2(playerid1, playerid2, color, text[]) { for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid1 && i != playerid2) SendClientMessage(i,color,text); return 1; }
stock IsPlayerXAdmin(playerid) return (Variables[playerid][LoggedIn] && Variables[playerid][Level]) ? true:false;
stock GetConnectedPlayers() { new Players; for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i)) Players++; return Players; }
stock IsSkinValid(SkinID) return ((SkinID >= 0 && SkinID <= 1)||(SkinID == 2)||(SkinID == 7)||(SkinID >= 9 && SkinID <= 41)||(SkinID >= 43 && SkinID <= 85)||(SkinID >=87 && SkinID <= 118)||(SkinID >= 120 && SkinID <= 148)||(SkinID >= 150 && SkinID <= 207)||(SkinID >= 209 && SkinID <= 272)||(SkinID >= 274 && SkinID <= 288)||(SkinID >= 290 && SkinID <= 299)) ? true:false;
stock IsNumeric(string[]) { for (new i = 0, j = strlen(string); i < j; i++) if (string[i] > '9' || string[i] < '0') return 0; return 1; }
stock SendPlayerCommandToAdmins(playerid, command[]) { if (!IsPlayerXAdmin(playerid)) { new string[256], pName[24]; GetPlayerName(playerid, pName, 24); format(string, 256, "*** %d) %s: %s", playerid, pName, command); SendPCommandMessageToAdmins(playerid, string); } else SendModeACommandMessageToAdmins(playerid, command); }
stock SendPCommandMessageToAdmins(playerid, text[]) { for(new i = 0; i < GetMaxPlayers(); i++) if (IsPlayerConnected(i) && IsPlayerXAdmin(i) && Variables[i][Commands] && i != playerid) { SendClientMessage(i, cblue, text); } }
stock SendACommandMessageToAdmins(playerid, command[], params[]) {
if(dini_Int("/xadmin/Configuration/Commands.ini",command) >= 1 || !strcmp(command,"xcmds",true)) if (Variables[playerid][Level] > 0) {
new playerlog[256]; format(playerlog,256,"/%s %s\r\n",command,params); WriteToLog("admin", playerlog, playerid); }
for(new i = 0; i < GetMaxPlayers(); i++) if (IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid && Variables[i][ACommands]) { new string[256], pName[24]; GetPlayerName(playerid, pName, 24); format(string, 256, "[Admin] %d) %s: /%s %s", playerid, pName, command, params); SendClientMessage(i, cblue, string); } }
stock SendModeACommandMessageToAdmins(playerid, command[]) { for(new i = 0; i < GetMaxPlayers(); i++) if (IsPlayerConnected(i) && i != playerid && Variables[i][ACommands]) { new string[256], pName[24]; GetPlayerName(playerid, pName, 24); format(string, 256, "[Admin] %d) %s: %s", playerid, pName, command); SendClientMessage(i, cblue, string); } }
stock BanCheckName(pName[]) { new BanFile[128], IpBanFile[128]; format(BanFile, 128, "xadmin/Bans/Names/%s.ini", pName); if (!dini_Exists(BanFile)) return false; format(IpBanFile, 128, "xadmin/Bans/IP/%s.ini", dini_Get(BanFile, "IP")); if (!dini_Exists(IpBanFile)) return false; return true; }
stock BanCheckIP(IP[]) { new IpBanFile[128]; format(IpBanFile, 128, "xadmin/Bans/IP/%s.ini", IP); if (!dini_Exists(IpBanFile)) return false; return true; }
stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance) { new Float:a; GetPlayerPos(playerid, x, y, a); GetPlayerFacingAngle(playerid, a); if (GetPlayerVehicleID(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), a); x += (distance * floatsin(-a, degrees)); y += (distance * floatcos(-a, degrees)); }
stock Wait(time) { new stamp = tickcount(); while (tickcount() - stamp < time) { } return 1; }
stock SendMessageToPlayers(color, text[]) { for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i) && !IsPlayerXAdmin(i)) SendClientMessage(i,color,text); return 1; }
stock IsVehicleExist(vehicleid) return (GetVehicleModel(vehicleid))?true:false;
stock IsVehicleOccupied(vehicleid) {
for(new i=0; i<GetMaxPlayers(); i++) if(IsPlayerConnected(i)&&GetPlayerState(i)==2 &&GetPlayerVehicleID(i)==vehicleid) return true;
return false; }
stock TogglePlayerControllableEx(playerid,bool:toggle) { TogglePlayerControllable(playerid,toggle); Variables[playerid][Frozen] = toggle; }
stock SendClientMessageToAllEx(playerid, color ,text[]) { for(new i=0;i<GetMaxPlayers();i++) if(IsPlayerConnected(i)&&i!=playerid) SendClientMessage(i,color,text); }
stock HigherLevelWarning(playerid, id, command[]) { new string[256],name[24]; GetPlayerName(playerid, name, 24); SendClientMessage(playerid,red,"ERROR: You can not use this on player which is higher level then you."); format(string,256,"[NOTE] \"%s\" has tried to %s you, but failed.",name,command); SendClientMessage(id,red,string); return 1; }
stock IsChargedNumeric(const string[]) {
new length=strlen(string); if (length==0) return false; for (new i = 0; i < length; i++) {
if ((string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+') || (string[i]=='-' && i!=0) || (string[i]=='+' && i!=0)) return false; }
if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
return true; }
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
stock ReturnVehicleModel(vname[]) {
        new VehicleNames[212][] = {
        {"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},{"Firetruck"},{"Trashmaster"},{"Stretch"},
        {"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},{"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},
        {"Washington"},{"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},{"Banshee"},{"Predator"},
        {"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Trailer 1"},{"Previon"},{"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},
        {"Romero"},{"Packer"},{"Monster"},{"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Trailer 2"},{"Turismo"},{"Speeder"},
        {"Reefer"},{"Tropic"},  {"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},{"Skimmer"},{"PCJ-600"},{"Faggio"},
        {"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},{"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},
        {"Dinghy"},{"Hermes"},{"Sabre"},{"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
        {"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},{"Jetmax"},{"Hotring"},
        {"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},{"Mesa"},{"RC Goblin"},{"Hotring Racer A"},
        {"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},{"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},
        {"Cropdust"},{"Stunt"},{"Tanker"},{"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},{"NRG-500"},
        {"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},{"Willard"},{"Forklift"},{"Tractor"},{"Combine"},
        {"Feltzer"},{"Remington"},{"Slamvan"},{"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
        {"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},{"Utility"},{"Nevada"},{"Yosemite"},
        {"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},{"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},
        {"Tahoma"},{"Savanna"},{"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},{"Broadway"},
        {"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},{"Tug"},{"Trailer 3"},{"Emperor"},{"Wayfarer"},
        {"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},{"Trailer 3"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police Car (LSPD)"},
        {"Police Car (SFPD)"},{"Police Car (LVPD)"},{"Police Ranger"},  {"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
        {"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},{"Utility Trailer"}
        };
        for(new i = 0; i < 212; i++) {
                if (strfind(VehicleNames[i], vname, true) != -1) {
                        return i + 400;
                }
        }
        return -1;
}