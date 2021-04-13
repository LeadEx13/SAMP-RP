#define APS_MAX_TRYS 3
#define APS_LOGINTIME 60
forward APS_LoginKick(playerid);
new APS_Login[MAX_PLAYERS], APS_Timer[MAX_PLAYERS] = -1;

public APS_LoginKick(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	SendClientMessage(playerid, yellow, "APS: Login time exceeded, Kicked.");
	return KickPlayer(playerid, -1, "APS");
}