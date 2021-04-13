/*
=======================
This Include Is Made By
=======>Sandra<========
=======================
*/

#include <a_samp>

//CountdownSinc
new IsCountdownSincStarted;
new IsPlayerCountdownSincStarted[MAX_PLAYERS];
new PlayerCountdownSincCount[MAX_PLAYERS];
new CountdownSincCount;
new PlayerCountdownSincTimer[MAX_PLAYERS];
new CountdownSincTimer;

//PocketMoney:
new IsPocketMoneyEnabled;
new IsPocketMoneyMessageEnabled = 1;
new PocketMoneyAmount;
new PocketMoneyTimer;

/*
native ======CountdownSinc==============
native CreateCountdownSinc(time, sound);
native CreatePlayerCountdownSinc(playerid, time, sound);
native StopCountdownSinc();
native StopPlayerCountdownSinc(playerid);
native ======PocketMoney==============
native EnablePocketMoney(amount, frequency);
native DisablePocketMoney();
native SetPocketMoneyAmount(amount);
native SetPocketMoneyFrequency(frequency);
native TogglePocketMoneyMessage(toggle);
*/


stock CreateCountdownSinc(time, sound)
{
	if(IsCountdownSincStarted == 0)
	{
	    for(new i; i<MAX_PLAYERS; i++)
	    {
	        if(IsPlayerConnected(i))
	        {
		        if(IsPlayerCountdownSincStarted[i] == 1)
		        {
		            KillTimer(PlayerCountdownSincTimer[i]);
		            PlayerCountdownSincCount[i] = 0;
		            IsPlayerCountdownSincStarted[i] = 0;
				}
			}
		}
		CountdownSincTimer = SetTimerEx("CountdownSinc", 1000, 1, "d", sound);
		CountdownSincCount = time;
		IsCountdownSincStarted = 1;
	}
}
stock CreatePlayerCountdownSinc(playerid, time, sound)
{
	if(IsPlayerCountdownSincStarted[playerid] == 0 && IsCountdownSincStarted == 0)
	{
		PlayerCountdownSincTimer[playerid] = SetTimerEx("PlayerCountdownSinc", 1000, 1, "id", playerid, sound);
		PlayerCountdownSincCount[playerid] = time;
		IsPlayerCountdownSincStarted[playerid] = 1;
	}
}
stock StopCountdownSinc()
{
	KillTimer(CountdownSincTimer);
	GameTextForAll(" ", 10, 3);
    CountdownSincCount = 0;
    IsCountdownSincStarted = 0;
}
stock StopPlayerCountdownSinc(playerid)
{
	KillTimer(PlayerCountdownSincTimer[playerid]);
	GameTextForPlayer(playerid, " ", 10, 3);
    PlayerCountdownSincCount[playerid] = 0;
    IsPlayerCountdownSincStarted[playerid] = 0;
}

stock EnablePocketMoney(amount, frequency)
{
	if(IsPocketMoneyEnabled==0)
	{
	    PocketMoneyTimer = SetTimer("PocketMoney", (frequency*1000), 1);
	    IsPocketMoneyEnabled = 1;
	    PocketMoneyAmount = amount;

	}
}
stock DisablePocketMoney()
{
	if(IsPocketMoneyEnabled==1)
	{
	    KillTimer(PocketMoneyTimer);
	    IsPocketMoneyEnabled = 0;
    }
}
stock SetPocketMoneyAmount(amount)
{
    PocketMoneyAmount = amount;
}

stock SetPocketMoneyFrequency(frequency)
{
	KillTimer(PocketMoneyTimer);
	PocketMoneyTimer = SetTimer("PocketMoney", (frequency*1000), 1);
}

stock TogglePocketMoneyMessage(toggle)
{
    IsPocketMoneyMessageEnabled = toggle;
}

forward CountdownSinc(sound);
public CountdownSinc(sound)
{
    if(CountdownSincCount == 0)
	{
	    if(sound == 1)
		{
		    for(new i; i<MAX_PLAYERS; i++)
		    {
		        if(IsPlayerConnected(i))
		        {
		            PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
				}
			}
		}
	    GameTextForAll("~r~GoGoGo", 2000, 3);
	    KillTimer(CountdownSincTimer);
	    IsCountdownSincStarted = 0;
	}
	else
	{
	    if(sound == 1)
		{
		    for(new i; i<MAX_PLAYERS; i++)
		    {
		        if(IsPlayerConnected(i))
		        {
		            PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
				}
			}
		}
		new cdstring[128];
		format(cdstring, sizeof(cdstring), "~y~%d", CountdownSincCount);
		GameTextForAll(cdstring, 1500, 3);
		CountdownSincCount--;
	}
}

forward PlayerCountdownSinc(playerid, sound);
public PlayerCountdownSinc(playerid, sound)
{
    if(PlayerCountdownSincCount[playerid] == 0)
	{
	    if(sound == 1) PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	    GameTextForPlayer(playerid,"~n~~n~~r~GoGoGo", 2000, 3);
	    KillTimer(PlayerCountdownSincTimer[playerid]);
	    IsPlayerCountdownSincStarted[playerid] = 0;
	}
	else
	{
	    if(sound == 1) PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
		new pcdstring[128];
	    format(pcdstring, sizeof(pcdstring), "~n~~g~%d", PlayerCountdownSincCount[playerid]);
		GameTextForPlayer(playerid, pcdstring, 1500, 3);
		PlayerCountdownSincCount[playerid]--;
	}
}

forward PocketMoney();
public PocketMoney()
{
    if(IsPocketMoneyMessageEnabled == 1)
    {
		new pmstring[128];
		format(pmstring, sizeof(pmstring), "You received $%d,- pocketmoney!",PocketMoneyAmount);
		SendClientMessageToAll(0xFFFF66AA, pmstring);
	}
	for(new i; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GivePlayerMoney(i,  PocketMoneyAmount);
		}
	}
}
