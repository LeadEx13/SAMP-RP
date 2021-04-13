forward RestorePlayerPosition(playerid);
public RestorePlayerPosition(playerid)
{
	if (!xPlayer[playerid][SpecLastInfo][sSaved]) return false;
	if (xPlayer[playerid][SpecLastInfo][sVehicleID])
	{
		if (IsVehicleOccupied(xPlayer[playerid][SpecLastInfo][sVehicleID])) PutPlayerInVehicle(playerid, xPlayer[playerid][SpecLastInfo][sVehicleID], 1);
		else PutPlayerInVehicle(playerid, xPlayer[playerid][SpecLastInfo][sVehicleID], 0);
		LinkVehicleToInterior(xPlayer[playerid][SpecLastInfo][sVehicleID], xPlayer[playerid][SpecLastInfo][sInterior]);
	}
	else SetPlayerPos(playerid, xPlayer[playerid][SpecLastInfo][sX], xPlayer[playerid][SpecLastInfo][sY], xPlayer[playerid][SpecLastInfo][sZ]);
	SetPlayerInterior(playerid, xPlayer[playerid][SpecLastInfo][sInterior]);
	xPlayer[playerid][SpecLastInfo][sSaved] = false; xPlayer[playerid][SpecLastInfo][sVehicleID] = 0; xPlayer[playerid][SpecLastInfo][sInterior] = 0;
	xPlayer[playerid][SpecLastInfo][sX] = 0; xPlayer[playerid][SpecLastInfo][sY] = 0; xPlayer[playerid][SpecLastInfo][sZ] = 0;
	return true;
}

stock Spectate(playerid, id, bool:toggle)
{
	if (id == -1 && toggle) return false;
	if (toggle)
	{
		new Float:X, Float:Y, Float:Z;
		if (!Spec[playerid][Spectating])
		{
			if (!IsPlayerInAnyVehicle(playerid)) GetPlayerPos(playerid, X, Y, Z);
			else
			{
				xPlayer[playerid][SpecLastInfo][sVehicleID] = GetPlayerVehicleID(playerid);
				GetVehiclePos(xPlayer[playerid][SpecLastInfo][sVehicleID], X, Y, Z);
			}
			xPlayer[playerid][SpecLastInfo][sX] = X;
			xPlayer[playerid][SpecLastInfo][sY] = Y;
			xPlayer[playerid][SpecLastInfo][sZ] = Z;
			xPlayer[playerid][SpecLastInfo][sInterior] = GetPlayerInterior(playerid);
			xPlayer[playerid][SpecLastInfo][sSaved] = true;
		}
		Spec[playerid][Spectating] = true;
		Spec[playerid][SpectateID] = id;
		SetPlayerInterior(playerid, GetPlayerInterior(id));
		TogglePlayerSpectating(playerid, true);
		if (!IsPlayerInAnyVehicle(id)) PlayerSpectatePlayer(playerid, id);
		else PlayerSpectateVehicle(playerid, GetPlayerVehicleID(id));
		new string[128], name[24], ActionName[24]; GetPlayerName(playerid, name, 24); GetPlayerName(id, ActionName, 24);
		format(string, 128, "~y~~h~~h~~h~Spectator Mode:~n~~r~%d ~g~%s", id, ActionName);
		GameTextForPlayer(playerid, string, 10000, 4);
		format(string, 128, "You are now spectating player \"%s\".", ActionName); SendClientMessage(playerid, lgreen, string);
		format(string, 128, "\"%s\" is now spectating player \"%s\".", name, ActionName); SendMessageToAdminsEx(playerid, lgreen, string);
	}
	else
	{
		if (!Spec[playerid][Spectating]) return SendClientMessage(playerid,red,"ERROR: You must be spectating.");
		Spec[playerid][Spectating] = false;
		Spec[playerid][SpectateID] = INVALID_PLAYER_ID;
		TogglePlayerSpectating(playerid, false);
		SetTimerEx("RestorePlayerPosition", 250, 0, "i", playerid);
		GameTextForPlayer(playerid,"~y~~h~~h~~h~Spectator Mode:~n~~r~OFF",5000,4);
		new string[128], name[24]; GetPlayerName(playerid, name, 24);
		SendClientMessage(playerid, lgreen, "You have turned your spectator mode off.");
		format(string, 128, "\"%s\" has turned his spectator mode off.", name); SendMessageToAdminsEx(playerid, lgreen, string);
	}
	return true;
}

public ResetReportedID(playerid)
{
	xPlayer[playerid][LastReportedID] = -1;
	xPlayer[playerid][TimerReport] = -1;
}