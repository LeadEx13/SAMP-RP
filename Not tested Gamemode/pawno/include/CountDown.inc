//============================================================//
//* CountDownForPlayer & CountDownForAll
//* Version: 1.0
//============================================================//
//* Created by:
//* Biesmen
//============================================================//
//* Foreach Include by:
//* Y_Less
//============================================================//

#include <a_samp>
#include <Foreach>

#undef MAX_PLAYERS
#define MAX_PLAYERS 500 // Change 500 to your server's slots.

enum CountStuff
{
	cdc[2],
	cdem[30],
	cds,
	CDUsed,
};
new CD[MAX_PLAYERS][CountStuff];

new CDTimer[MAX_PLAYERS];
new CDTimerA;

	
forward CountD();
forward CountDP(playerid);

stock AvailableColors(TColor[])
{
	if(strcmp(TColor,"r", true) == 0) return 1;
	if(strcmp(TColor,"g", true) == 0) return 1;
	if(strcmp(TColor,"b", true) == 0) return 1;
	if(strcmp(TColor,"w", true) == 0) return 1;
	if(strcmp(TColor,"y", true) == 0) return 1;
	if(strcmp(TColor,"p", true) == 0) return 1;
	if(strcmp(TColor,"l", true) == 0) return 1;
	if(strcmp(TColor,"h", true) == 0) return 1;
	else return 0;
}

stock CountDownForAll(Color[2], EndMessage[30], Seconds)
{
	foreach(Player, i)
	{
		if(CD[i][CDUsed] == 1) return print("CountDown ERROR: There's a player still having the Countdown messages!");
		if(strlen(Color) > 1 || !AvailableColors(Color)) return print("CountDown ERROR: Invalid color used!");
		if(strlen(EndMessage) > 30) return print("CountDown ERROR: End Message is too long!");
		if(Seconds < 0 ) return print("CountDown ERROR: Negative amount of seconds.");
		CD[i][cdc] = Color;
		CD[i][cdem] = EndMessage;
		CD[i][cds] = Seconds;
		CDTimerA = SetTimer("CountD", 1000, true);
		CD[i][CDUsed] = 1;
	}
	return 1;
}

stock CountDownForPlayer(playerid, Color[2], EndMessage[30], Seconds)
{
	if(CD[playerid][CDUsed] == 1) return print("CountDown ERROR: The function is already being used for this player!");
	if(strlen(Color) > 1 || !AvailableColors(Color)) return print("CountDown ERROR: Invalid color used!");
	if(strlen(EndMessage) > 30) return print("CountDown ERROR: End Message is too long!");
	if(Seconds < 0 ) return print("CountDown ERROR: Negative amount of seconds.");
	CD[playerid][cdc]= Color;
	CD[playerid][cdem] = EndMessage;
	CD[playerid][cds] = Seconds;
	CDTimer[playerid] = SetTimerEx("CountDP", 1000, true, "i", playerid);
	CD[playerid][CDUsed] = 1;
	return 1;
}

public CountD()
{
	foreach(Player, i)
	{
		new string[35];
		if(CD[i][cds] != 0)
		{
			format(string, sizeof(string), "~%s~%d", CD[i][cdc], CD[i][cds]);
			GameTextForPlayer(i,string, 1000, 4);
			CD[i][cds]--;
		}
		else
		{
			format(string, sizeof(string), "~%s~%s", CD[i][cdc], CD[i][cdem]);
			GameTextForPlayer(i, string, 2000, 4);
			KillTimer(CDTimerA);
			CD[i][CDUsed] = 0;
		}
	}
	return 1;
}

public CountDP(playerid)
{
	new string[35];
	if(CD[playerid][cds] != 0)
	{
		format(string, sizeof(string), "~%s~%d", CD[playerid][cdc], CD[playerid][cds]);
		GameTextForPlayer(playerid,string, 1000, 4);
		CD[playerid][cds]--;
	}
	else
	{
		format(string, sizeof(string), "~%s~%s", CD[playerid][cdc], CD[playerid][cdem]);
		GameTextForPlayer(playerid, string, 2000, 4);
		KillTimer(CDTimer[playerid]);
		CD[playerid][CDUsed] = 0;
	}
	return 1;
}
		