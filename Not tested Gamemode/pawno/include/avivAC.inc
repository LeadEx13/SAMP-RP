/*
           * VGames.co.il      Aviv Anti Cheat
        * © Copyright 2009, Aviv Balali (AAvivB')
        * Support Version:        SanAndreas:MultiPlayer 0.2X
        * Version:                        0.2.0
        * Creation Date:        12/7/2009
        * Credits To        Omer Horev (N1trO)

        native AC_OnPlayerSpawn(playerid);
        native AC_OnPlayerDisconnect(playerid);
        native AC_GivePlayerMoney(playerid,money);
        native AC_ResetPlayerMoney(playerid);

*/


#include <a_samp>
#if defined _avivAC_included
#endinput
        #endif
#define _avivAC_included
#pragma library avivAC

static
        Money[MAX_PLAYERS],
        timer2[MAX_PLAYERS];

forward Set(playerid);
forward AC_Check(playerid);
forward AC_U(playerid);
stock AC_OnPlayerSpawn(playerid){SetTimerEx("AC_U",3000,0,"d",playerid);AC_Set(playerid);EnableStuntBonusForAll(false);}
stock AC_OnPlayerDisconnect(playerid){KillTimer(timer2[playerid]);}
stock AC_GivePlayerMoney(playerid,money){GivePlayerMoney(playerid,money);Money[playerid] += money;return 1;}
stock AC_Set(playerid){ResetPlayerMoney(playerid);GivePlayerMoney(playerid,Money[playerid]);return 1;}
stock AC_ResetPlayerMoney(playerid){ResetPlayerMoney(playerid);Money[playerid]=0;return 1;}
public AC_Check(playerid)
        if(GetPlayerMoney(playerid) > Money[playerid])
        {
                new string[128],name[MAX_PLAYER_NAME+1];
                GetPlayerName(playerid, name, sizeof(name));
                format(string,sizeof(string),"%s Has been kicked by AAC (Money Cheat %d)",name,Money[playerid]-=GetPlayerMoney(playerid));
                SendClientMessageToAll(0xFF0000FF,string);
                Kick(playerid);
                KillTimer(timer2[playerid]);
        }
public AC_U(playerid){timer2[playerid] = SetTimerEx("AC_Check",100,1,"d",playerid);return 1;}
