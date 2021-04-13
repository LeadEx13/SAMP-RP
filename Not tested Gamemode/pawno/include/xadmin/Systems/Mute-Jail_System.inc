stock MutePlayer(playerid, time, reason[])
{
	if(!IsPlayerConnected(playerid)||Variables[playerid][Muted]) return 1;
	new string[128],ActionName[24]; GetPlayerName(playerid,ActionName,24);
	Variables[playerid][Muted] = true, Variables[playerid][MutedWarnings] = Config[MutedWarnings];
	format(xPlayer[playerid][MuteInfo][mReason], 32, reason);
	xPlayer[playerid][MuteInfo][mTime] = time;
	xPlayer[playerid][MuteInfo][mTimeLeft] = time;
	new nTime[16];
	FormatTime(time, nTime);
	xPlayer[playerid][TimerUnMute] = SetTimerEx("UnMutePlayer", (time*1000), 0, "d", playerid);
	format(string,128,"\"%s\" has been muted by the server for %s. (Reason: %s)",ActionName,nTime,reason);
	SendClientMessageToAll(yellow,string);
	return 1;
}

public UnMutePlayer(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Muted]) {
		new string[128],string2[128],name[24]; GetPlayerName(playerid, name, 24);
		format(string,128,"You have been auto-unmuted by the server.");
		format(string2,128,"\"%s\" has been auto-unmuted by the server.",name);
		for(new i=0; i<MAX_PLAYERS; ++i) if(IsPlayerConnected(i)) if(i!=playerid) SendClientMessage(i, yellow, string2); else SendClientMessage(i, yellow, string);
		Variables[playerid][Muted] = false; Variables[playerid][MutedWarnings] = Config[MutedWarnings];
		ClearString(32, xPlayer[playerid][MuteInfo][mReason]);
		xPlayer[playerid][MuteInfo][mTime] = 0;
		xPlayer[playerid][MuteInfo][mTimeLeft] = 0;
		xPlayer[playerid][TimerUnMute] = -1;
	}
	return 1;
}

stock MuteDisconnect(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Muted]) {
		Variables[playerid][Muted] = false;
		Variables[playerid][MutedWarnings] = Config[MutedWarnings];
		ClearString(32, xPlayer[playerid][MuteInfo][mReason]);
		xPlayer[playerid][MuteInfo][mTime] = 0;
		xPlayer[playerid][MuteInfo][mTimeLeft] = 0;
		xPlayer[playerid][TimerUnMute] = -1;
		SendClientMessage(playerid, yellow, "You have been auto-unmuted by the server.");
	}
	return 1;
}

stock MuteUnload(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Muted]) {
		Variables[playerid][Muted] = false;
		Variables[playerid][MutedWarnings] = Config[MutedWarnings];
		ClearString(32, xPlayer[playerid][MuteInfo][mReason]);
		xPlayer[playerid][MuteInfo][mTime] = 0;
		xPlayer[playerid][MuteInfo][mTimeLeft] = 0;
		KillTimer(xPlayer[playerid][TimerUnMute]);
		xPlayer[playerid][TimerUnMute] = -1;
		SendClientMessage(playerid, yellow, "You have been auto-unmuted by the server.");
	}
	return 1;
}

public Mute_Time_Ticker()
{
	for (new i = 0; i < MAX_PLAYERS; ++i)
		if (IsPlayerConnected(i) && Variables[i][Muted] && xPlayer[i][MuteInfo][mTime] > 0 && xPlayer[i][MuteInfo][mTimeLeft] > 0)
			xPlayer[i][MuteInfo][mTimeLeft]--;
	return 1;
}

stock JailPlayer(playerid, time, reason[])
{
	if(!IsPlayerConnected(playerid)||Variables[playerid][Jailed]) return 1;
	new string[128],ActionName[24]; GetPlayerName(playerid,ActionName,24);
	Variables[playerid][Jailed] = true;
	new nTime[16]; FormatTime(time, nTime);
	new cell = random(sizeof(JailPositions));
	SetPlayerPos(playerid,JailPositions[cell][j_x],JailPositions[cell][j_y],JailPositions[cell][j_z]);
	SetPlayerInterior(playerid,JailPositions[cell][j_int]);
	SetPlayerFacingAngle(playerid,0);
	SetPlayerHealth(playerid, 100000);
	TogglePlayerControllable(playerid,false);
	xPlayer[playerid][TimerUnJail] = SetTimerEx("UnJailPlayer", (time*1000), 0, "d", playerid);
	format(string,128,"\"%s\" has been jailed by the server for %s. (Reason: %s)",ActionName,nTime,reason);
	format(xPlayer[playerid][JailInfo][jReason], 32, reason);
	xPlayer[playerid][JailInfo][jTime] = time;
	xPlayer[playerid][JailInfo][jTimeLeft] = time;
	for (new i=0; i<MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && Spec[i][Spectating] && Spec[i][SpectateID] == playerid) {
	TogglePlayerSpectating(i,false);
	Spec[i][Spectating] = false;
	Spec[i][SpectateID] = INVALID_PLAYER_ID;
	GameTextForPlayer(i,"~y~~h~~h~~h~Spectator Mode: ~r~OFF~n~~b~The player has been ~r~jailed",200,4);
	SetTimerEx("RestorePlayerPosition",500,0,"i",i); }
	SendClientMessageToAll(yellow,string);
	return 1;
}

public UnJailPlayer(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Jailed]) {
		new string[128],string2[256],name[24]; GetPlayerName(playerid, name, 24);
		format(string,128,"You have been auto-unjailed by the server.");
		format(string2,128,"\"%s\" has been auto-unjailed by the server.",name);
		SetPlayerHealth(playerid,100);
		for(new i=0; i<MAX_PLAYERS; i++) if(IsPlayerConnected(i)) if(i!=playerid) SendClientMessage(i, yellow, string2); else SendClientMessage(i, yellow, string);
		ClearString(32, xPlayer[playerid][JailInfo][jReason]);
		xPlayer[playerid][JailInfo][jTime] = 0;
		xPlayer[playerid][JailInfo][jTimeLeft] = 0;
		TogglePlayerControllable(playerid,false);
		Variables[playerid][Jailed] = false;
		SetPlayerInterior(playerid, 0);
		xPlayer[playerid][TimerUnJail] = -1;
		for (new i=0; i<MAX_PLAYERS; i++) if (IsPlayerConnected(i) && Spec[i][Spectating] && Spec[i][SpectateID] == playerid) {
		TogglePlayerSpectating(playerid,false); Spec[playerid][Spectating] = false; Spec[playerid][SpectateID] = INVALID_PLAYER_ID;
		GameTextForPlayer(playerid," ",200,4); SetTimerEx("RestorePlayerPosition",500,0,"i",playerid); }
		SpawnPlayer(playerid);
	}
	return 1;
}

stock JailDisconnect(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Jailed]) {
		SetPlayerHealth(playerid,100);
		Variables[playerid][Jailed] = false;
		TogglePlayerControllable(playerid,false);
		xPlayer[playerid][TimerUnJail] = -1;
		ClearString(32, xPlayer[playerid][JailInfo][jReason]);
		xPlayer[playerid][JailInfo][jTime] = 0;
		xPlayer[playerid][JailInfo][jTimeLeft] = 0;
		SendClientMessage(playerid, yellow, "You have been auto-unjailed by the server.");
	}
	return 1;
}

stock JailUnload(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(Variables[playerid][Jailed]) {
		SetPlayerHealth(playerid,100);
		Variables[playerid][Jailed] = false;
		TogglePlayerControllable(playerid,false);
		KillTimer(xPlayer[playerid][TimerUnJail]);
		xPlayer[playerid][TimerUnJail] = -1;
		ClearString(32, xPlayer[playerid][JailInfo][jReason]);
		xPlayer[playerid][JailInfo][jTime] = 0;
		xPlayer[playerid][JailInfo][jTimeLeft] = 0;
		SendClientMessage(playerid, yellow, "You have been auto-unjailed by the server.");
	}
	return 1;
}

public Jail_Time_Ticker()
{
	for (new i = 0; i < MAX_PLAYERS; ++i)
		if (IsPlayerConnected(i) && Variables[i][Jailed] && xPlayer[i][JailInfo][jTime] > 0 && xPlayer[i][JailInfo][jTimeLeft] > 0)
			xPlayer[i][JailInfo][jTimeLeft]--;
	return 1;
}