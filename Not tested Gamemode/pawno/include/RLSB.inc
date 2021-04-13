/*
	dEzIRE's Login*Register*Stats*Bank Script include
	~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Programmer: dEzIRE & Some Amit_B's Functions
	Creation Data: 19/09/2008
	Version: 0.1
	Compatibility: SanAndreas:MultiPlayer 0.2.X

	Contact:
	~~~~~~~~
	ICQ: 392015283
	Messanger: dezire@dezire.net
*/

//=[IncludeDefines]=============================================================
#include "a_samp.inc"
#include "dini.inc"
#include "file.inc"
// Colors:
#define COLOR_LIGHTGREEN 0x24FF0AB9
#define COLOR_GREEN 0x33FF33AA
#define COLOR_BRIGHTRED 0xFF000096
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_PINK 0xFF66FFAA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_BLUE 0x0B6F6FF
#define COLOR_LIGHTBLUEGREEN 0x0F66AFF
// Funcations:
#define ReadCMD(%1); Config[CL_%1] = dini_Int("RLSB/Config.cfg",#%1);
#define ReadOption_Int(%1); Config[%1] = dini_Int("RLSB/Config.cfg",#%1);
#define CheckPlayerCMDLevel(%1,%2); if(PlayerInfo[%1][Level] < Config[CL_%2]) \
{ \
	new cmdstring[256]; \
	format(cmdstring,sizeof(cmdstring),"Level Error: You must be level %d to use this command.",Config[CL_%2]); \
	SendClientMessage(%1,COLOR_BRIGHTRED,cmdstring); \
	return 1; \
}
//=[Enums]======================================================================
enum PlayerInfoData
{
	Level,
	Logged,
	Tag,
	FL,
	Kills,
	Deaths,
	Money,
	Bank,
	Saved,
	Float:SPX,
	Float:SPY,
	Float:SPZ,
	SPI,
	SkinSavedId,
	SkinSaved,
	SaveSkin 
};
enum ConfigEnum 
{
	// Options (3):
	MinPasswordLength,
	MaxPasswordLength,
	MaxFailedLogins,
	// Commands (2):
	CL_register,
	CL_login,
        CL_changenick,
        CL_changepass
};
//=[Variables]==================================================================
stock
	PlayerInfo[MAX_PLAYERS][PlayerInfoData],
	Config[ConfigEnum]
	;
//=[GetName]====================================================================
/*
	native GetName(playerid);
*/
stock GetName(playerid)
{
	new Name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,Name,sizeof(Name));
	return Name;
}
//=[IsPlayerLogged]=============================================================
/*
	native IsPlayerLogged(playerid);
*/
stock IsPlayerLogged(playerid) return (PlayerInfo[playerid][Logged]? 1 : 0);
//=[GetIP]======================================================================
/*
	native GetIP(playerid);
*/
stock GetIP(playerid)
{
	new IP[16];
	GetPlayerIp(playerid,IP,sizeof(IP));
	return IP;
}
//=[GetPlayerFile]==============================================================
/*
	native GetPlayerFile(playerid);
*/
stock GetPlayerFile(playerid)
{
	new string[256];
	format(string,sizeof(string),"RLSB/Users/%s.ini",GetName(playerid));
	return string;
}
//=[CreateLoadConfig]===========================================================
/*
	native CreateLoadConfig();
*/
stock CreateLoadConfig()
{
	#define ConfigFile "RLSB/Config.cfg"
	if(!dini_Exists(ConfigFile))
	{
		dini_Create(ConfigFile);
		dini_IntSet(ConfigFile,"MinPasswordLength",3);
		dini_IntSet(ConfigFile,"MaxPasswordLength",15);
		dini_IntSet(ConfigFile,"MaxFailedLogins",3);
		dini_IntSet(ConfigFile,"register",0);
		dini_IntSet(ConfigFile,"login",0);
                dini_IntSet(ConfigFile,"changenick",0);
                dini_IntSet(ConfigFile,"changepass",0);
	}
	#undef ConfigFile
	ReadOption_Int(MinPasswordLength);
	ReadOption_Int(MaxPasswordLength);
	ReadOption_Int(MaxFailedLogins);
	ReadCMD(register);
	ReadCMD(login);
	ReadCMD(changenick);
	return 1;
}
//=[IsNumeric]==================================================================
/*
	native IsNumeric(string[]);
*/
stock IsNumeric(string[])
{
	for(new i=0;i<strlen(string);i++)
		if(string[i] > '9' || string[i] < '0')
			return 0;
	return 1;
}
//=[ReturnID]===================================================================
/*
	native ReturnID(text[], playerid = INVALID_PLAYER_ID);
	* "utils.inc" programmers's "ReturnUser" funcation (with changes)
*/
stock ReturnID(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while(text[pos] < 0x21)
	{
		if(text[pos] == 0)
			return INVALID_PLAYER_ID;
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if(IsNumeric(text[pos]))
	{
		userid = strval(text[pos]);
		if(userid >= 0 && userid < GetMaxPlayers())
		{
			if(!IsPlayerConnected(userid))
				userid = INVALID_PLAYER_ID;
			else
				return userid;
		}
	}
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerName(i,name,sizeof(name));
			if(strcmp(name,text[pos],true,len) == 0)
			{
				if(len == strlen(name))
					return i;
				else
					count++, userid = i;
			}
		}
	}
	if(count != 1)
	{
		if(playerid != INVALID_PLAYER_ID)
		{
			if(count)
				SendClientMessage(playerid,COLOR_BRIGHTRED,"Multiple users found, please narrow earch.");
			else
				SendClientMessage(playerid,COLOR_BRIGHTRED,"No matching user found.");
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid;
}
//=[RegisterPlayer]================================================================
/*
	native RegisterPlayer(playerid,password[]);
*/
RegisterPlayer(playerid,password[])
{
	new File:f, date[3], time[3], string[256];
	if(fexist(GetPlayerFile(playerid)))
	{
		getdate(date[0],date[1],date[2]);
		gettime(time[0],time[1],time[2]);
		f = fopen(GetPlayerFile(playerid),io_append);
		format(string,sizeof(string),"// ===== %s's file: =====\r\n",GetName(playerid)); fwrite(f,string);
		fwrite(f,"// Account:\r\n");
		format(string,sizeof(string),"Password=%s\r\n",password); fwrite(f,string);
		format(string,sizeof(string),"Level=%d\r\n",PlayerInfo[playerid][Level]); fwrite(f,string);
 		format(string,sizeof(string),"Tag=%s\r\n","Begginer"); fwrite(f,string);
                format(string,sizeof(string),"Logged=%d\r\n",PlayerInfo[playerid][Logged]); fwrite(f,string);
		fwrite(f,"// Misc:\r\n");
		format(string,sizeof(string),"IP=%s\r\n",GetIP(playerid)); fwrite(f,string);
		format(string,sizeof(string),"LastConnectIP=%s\r\n",GetIP(playerid)); fwrite(f,string);
		format(string,sizeof(string),"State=%s\r\n","Online"); fwrite(f,string);
		fwrite(f,"// Times & Dates:\r\n");
		format(string,sizeof(string),"RegisterationYear=%d\r\n",date[0]); fwrite(f,string);
		format(string,sizeof(string),"RegisterationMonth=%d\r\n",date[1]); fwrite(f,string);
		format(string,sizeof(string),"RegisterationDay=%d\r\n",date[2]); fwrite(f,string);
		format(string,sizeof(string),"RegisterationHour=%d\r\n",time[0]); fwrite(f,string);
		format(string,sizeof(string),"RegisterationMinute=%d\r\n",time[1]); fwrite(f,string);
		format(string,sizeof(string),"LastConnectYear=%d\r\n",date[0]); fwrite(f,string);
		format(string,sizeof(string),"LastConnectMonth=%d\r\n",date[1]); fwrite(f,string);
		format(string,sizeof(string),"LastConnectDay=%d\r\n",date[2]); fwrite(f,string);
		format(string,sizeof(string),"LastConnectHour=%d\r\n",time[0]); fwrite(f,string);
		format(string,sizeof(string),"LastConnectMinute=%d\r\n",time[1]); fwrite(f,string);
		fwrite(f,"// Stats:\r\n");
		format(string,sizeof(string),"Kills=%d\r\n",PlayerInfo[playerid][Kills]); fwrite(f,string);
		format(string,sizeof(string),"Deaths=%d\r\n",PlayerInfo[playerid][Deaths]); fwrite(f,string);
		format(string,sizeof(string),"Money=%d\r\n",PlayerInfo[playerid][Money]); fwrite(f,string);
                format(string,sizeof(string),"Bank=%d\r\n",PlayerInfo[playerid][Bank]); fwrite(f,string);
		fwrite(f,"// Pos & Skin:\r\n");
		format(string,sizeof(string),"SavePos=%d\r\n",PlayerInfo[playerid][Saved]); fwrite(f,string);
		format(string,sizeof(string),"SavePosX=%.4f\r\n",PlayerInfo[playerid][SPX]); fwrite(f,string);
		format(string,sizeof(string),"SavePosY=%.4f\r\n",PlayerInfo[playerid][SPY]); fwrite(f,string);
		format(string,sizeof(string),"SavePosZ=%.4f\r\n",PlayerInfo[playerid][SPZ]); fwrite(f,string);
		format(string,sizeof(string),"SavePosI=%d\r\n",PlayerInfo[playerid][SPI]); fwrite(f,string);
		format(string,sizeof(string),"Saved=%d\r\n",PlayerInfo[playerid][Saved]); fwrite(f,string);
		format(string,sizeof(string),"SkinSavedId=%d\r\n",PlayerInfo[playerid][SkinSavedId]); fwrite(f,string);
		format(string,sizeof(string),"SaveSkin=%d\r\n",PlayerInfo[playerid][SaveSkin]); fwrite(f,string);
		format(string,sizeof(string),"SkinSaved=%d\r\n",PlayerInfo[playerid][SkinSaved]); fwrite(f,string);
		fwrite(f,"// ===== End Of File =====");
		fclose(f);
	}
	return 1;
}
//=[LoginPlayer]================================================================
/*
	native LoginPlayer(playerid);
*/
stock LoginPlayer(playerid)
{
	new date[3], time[3];
	if(dini_Exists(GetPlayerFile(playerid)))
	{
		PlayerInfo[playerid][Logged] = 1;
		PlayerInfo[playerid][FL] = 0;
		getdate(date[0],date[1],date[2]);
		gettime(time[0],time[1],time[2]);
		PlayerInfo[playerid][Level] = dini_Int(GetPlayerFile(playerid),"Level");
		dini_Set(GetPlayerFile(playerid),"LastConnectIP",GetIP(playerid));
		dini_Set(GetPlayerFile(playerid),"State","Online");
		dini_IntSet(GetPlayerFile(playerid),"LastConnectYear",date[0]);
		dini_IntSet(GetPlayerFile(playerid),"LastConnectMonth",date[1]);
		dini_IntSet(GetPlayerFile(playerid),"LastConnectDay",date[2]);
		dini_IntSet(GetPlayerFile(playerid),"LastConnectHour",time[0]);
		dini_IntSet(GetPlayerFile(playerid),"LastConnectMinute",time[1]);
		PlayerInfo[playerid][Kills] = dini_Int(GetPlayerFile(playerid),"Kills");
		PlayerInfo[playerid][Deaths] = dini_Int(GetPlayerFile(playerid),"Deaths");
		PlayerInfo[playerid][Money] = dini_Int(GetPlayerFile(playerid),"Money");
                PlayerInfo[playerid][Bank] = dini_Int(GetPlayerFile(playerid),"Bank");
		GivePlayerMoney(playerid,PlayerInfo[playerid][Money]);
		PlayerInfo[playerid][Saved] = dini_Int(GetPlayerFile(playerid),"SavePos");
		PlayerInfo[playerid][SPX] = dini_Float(GetPlayerFile(playerid),"SavePosX");
		PlayerInfo[playerid][SPY] = dini_Float(GetPlayerFile(playerid),"SavePosY");
		PlayerInfo[playerid][SPZ] = dini_Float(GetPlayerFile(playerid),"SavePosZ");
		PlayerInfo[playerid][SPI] = dini_Int(GetPlayerFile(playerid),"SavePosI");
		PlayerInfo[playerid][SkinSavedId] = dini_Int(GetPlayerFile(playerid),"SkinSavedId");
		PlayerInfo[playerid][SkinSaved] = dini_Int(GetPlayerFile(playerid),"SkinSaved");
	        PlayerInfo[playerid][SaveSkin] = dini_Int(GetPlayerFile(playerid),"SaveSkin");
	}
	return 1;
}