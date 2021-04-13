#if defined _vgames_included
  #endinput
#endif

#define _vgames_included
#pragma library fxp

#include <a_samp>

/*
	New Functions:
	
	* isPlayerInArea(playerID, Float:data[4]) - Do commands to player in area [Not created by me]
	* PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash) - Give money in area [Not created by me]
	* Float:GetDistanceBetweenPlayers(p1,p2) - Get distance between players [Not created by me]
	* SoundForAll(sound) - Use sound for all players [Created by me]
	* SetHealthForAll(health) - [Set all health [Created by me]
	* SetArmorForAll(armor) - Set all armor [Created by me]
	* SetAllFacingAngle(ang) - Set all facing angle [Created by me]
	* GiveAllMoney(money) - Give money to all [Created by me]
	* SetAllSkin(skinid) - Set all skin [Created by me]
	* SetAllWantedLevel(level) - Set all wanted level [Created by me]
	* SetAllPos(X,Y,Z) - Set all position [Created by me]
*/

forward isPlayerInArea(playerID, Float:data[4]);
forward PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash);
forward Float:GetDistanceBetweenPlayers(p1,p2);
forward SoundForAll(sound);
forward SetHealthForAll(health);
forward SetArmorForAll(armor);
forward SetAllFacingAngle(ang);
forward GiveAllMoney(money);
forward SetAllSkin(skinid);
forward SetAllWantedLevel(level);
forward SetAllPos(X,Y,Z);

/*
native isPlayerInArea(playerID, Float:data[4]);
native PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash);
native Float:GetDistanceBetweenPlayers(p1,p2);
native SoundForAll(sound);
native SetHealthForAll(health);
native SetArmorForAll(armor);
native SetAllFacingAngle(ang);
native GiveAllMoney(money);
native SetAllSkin(skinid);
native SetAllWantedLevel(level);
native SetAllPos(X,Y,Z);
*/

//=isPlayerInArea===============================================================
public isPlayerInArea(playerID, Float:data[4])
{
	new Float:X, Float:Y, Float:Z;

	GetPlayerPos(playerID, X, Y, Z);
	if(X >= data[0] && X <= data[2] && Y >= data[1] && Y <= data[3]) {
		return 1;
	}
	return 0;
}
//=PayPlayerInArea==============================================================
public PayPlayerInArea(playerID, Float:x1, Float:y1, Float:x2, Float:y2, cash)
{

	if(IsPlayerConnected(playerID))
	{
		new Float:X, Float:Y, Float:Z;

		GetPlayerPos(playerID, X, Y, Z);
		if(X >= x1 && X <= x2 && Y >= y1 && Y <= y2)
		{
			GivePlayerMoney(playerID, cash);
			return 1;
		}
	}
	return 0;
}
//=GetDistanceBetweenPlayers====================================================
public Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;

	if (!IsPlayerConnected(p1) || !IsPlayerConnected(p2)){
	return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));

}
//=SoundForAll==================================================================
public SoundForAll(sound)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) PlayerPlaySound(i,sound,0.0,0.0,0.0);
    }
    return 1;
}
//=SetHealthForAll==============================================================
public SetHealthForAll(health)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerHealth(i,health);
    }
    return 1;
}
//=SetArmorForAll===============================================================
public SetArmorForAll(armor)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerArmour(i,armor);
    }
    return 1;
}
//=SetAllFacingAngle============================================================
public SetAllFacingAngle(ang)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerFacingAngle(i,ang);
    }
    return 1;
}
//=GiveAllMoney=================================================================
public GiveAllMoney(money)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) GivePlayerMoney(i,money);
    }
    return 1;
}
//=SetAllSkin===================================================================
public SetAllSkin(skinid)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerSkin(i,skinid);
    }
    return 1;
}
//=SetAllWantedLevel============================================================
public SetAllWantedLevel(level)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerWantedLevel(i,level);
    }
    return 1;
}
//=SetAllPos====================================================================
public SetAllPos(X,Y,Z)
{
    for (new i = 0, j = MAX_PLAYERS; i < j; i ++)
    {
        if (IsPlayerConnected(i)) SetPlayerPos(i,X,Y,Z);
    }
    return 1;
}
