/*
--------------------------------
ViP System include by.yoNi | SyticT
Fux-c.co.il
----------------------------------
*/
#include <a_samp>

//Colors

#define color_white 0xFFFFFFAA
#define color_main 0x33CCFFAA
#define color_bg 0x46BBAA00
#define color_r 0xAA3333AA

/*
native ViPFile(playerid);
*/
stock ViPFile(playerid)
{
    new name[MAX_PLAYER_NAME],VFile[50];
    GetPlayerName(playerid,name,sizeof(name));
    format(VFile,sizeof(VFile),"ViP/%s.ini",name);
    return VFile;
}
/*
native IsPlayerViP(playerid);
*/

stock IsPlayerViP(playerid)return dini_Exists(ViPFile(playerid))? true:false;

/*
native GetPlayerViPLevel(playerid);
*/

stock GetPlayerViPLevel(playerid)return dini_Int(ViPFile(playerid),"Level");

/*
native IsPlayerInArea(playerid, Float:max_x, Float:min_x, Float:max_y, Float:min_y);
*/

stock IsPlayerInViPArea(playerid, Float:max_x, Float:min_x, Float:max_y, Float:min_y)
{
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	if(X <= max_x && X >= min_x && Y <= max_y && Y >= min_y) return 1;
	return 0;
}

/*
native SendClientMessageToViP(color,const message[]);
*/

stock SendClientMessageToViP(color,const message[]){
for(new i; i < MAX_PLAYERS; i++)if(IsPlayerConnected(i) && IsPlayerViP(i))SendClientMessage(i,color,message);
return 1;
}

