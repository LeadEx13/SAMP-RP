#include <a_samp>
#include <audio>

main()
{
	print("FS Online radio in cars loaded.");
	print("Author: SDraw");
}

forward PlayVehicleRadioForPlayer(playerid,online,volume);
forward NonChangeRadio(playerid);
forward SetVolume(playerid,volume);

new VehRadio[MAX_VEHICLES];
new PassengerInCar[MAX_VEHICLES][4];
new VehVolume[MAX_VEHICLES];

new HandleidForPlayer[MAX_PLAYERS];
new bool:WaitForBuf[MAX_PLAYERS];
new PassengerSeat[MAX_PLAYERS];
new OldCar[MAX_PLAYERS];

new Stations[10][2][32] = {
	{"http://72.26.204.18:6006","DI Trance FM"},
	{"http://85.214.146.14:8118","RS Culture FM"},
	{"http://64.202.109.61:80","GotRadio"},
	{"http://85.17.62.97:8036","Radio Totaal FM"},
	{"http://74.63.47.82:8506","Street Lounge FM"},
	{"http://213.133.120.70:8050","Techno4ever Radio"},
	{"http://193.42.152.215:8018","Radio Redhill"},
	{"http://46.105.109.142:9062","pLayTecH Studio"},
	{"http://72.26.204.18:6696","Classic R&H Sky FM"},
	{"http://194.50.90.55:10005","Real Wales Radio"}/*,
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=674096","Real Wales Radio1"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280356","Real Wales Radio2"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=301250","Real Wales Radio3"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=614375","Real Wales Radio4"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280855","Real Wales Radio5"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1026951","Real Wales Radio6"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=9463","Real Wales Radio7"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1377212","Real Wales Radio8"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1281016","Real Wales Radio9"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275071","Real Wales Radio10"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280610","Real Wales Radio11"},
 	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275743","Real Wales Radio12"},
 	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1193516","Real Wales Radio13"},
 	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=9054","Real Wales Radio14"},
	{"http://yp.shoutcast.com/sbin/tunein-station.pls?id=702448","Real Wales Radio15"}*/
};

public OnFilterScriptInit()
{
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		VehRadio[i] = 1;
		VehVolume[i] = 30;
		PassengerInCar[i][1] = INVALID_PLAYER_ID;
		PassengerInCar[i][2] = INVALID_PLAYER_ID;
		PassengerInCar[i][3] = INVALID_PLAYER_ID;
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
    HandleidForPlayer[playerid] = 0;
    WaitForBuf[playerid] = false;
    OldCar[playerid] = INVALID_VEHICLE_ID;
    return 0;
}

public OnPlayerStateChange(playerid,newstate,oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
	    if(Audio_IsClientConnected(playerid))
	    {
	        if(HandleidForPlayer[playerid] == 0)
	        {
				Audio_StopRadio(playerid);
			    new veh = GetPlayerVehicleID(playerid);
			    new seat = GetPlayerVehicleSeat(playerid);
			    if(seat != 0)
				{
					PassengerInCar[veh][seat] = playerid;
					PassengerSeat[playerid] = seat;
					OldCar[playerid] = veh;
				}
			    PlayVehicleRadioForPlayer(playerid,VehRadio[veh],VehVolume[veh]);
			}
		}
 	}
 	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
 	{
 	    if(Audio_IsClientConnected(playerid))
 	    {
 	        if(HandleidForPlayer[playerid] != 0)
	        {
		 		Audio_Stop(playerid,HandleidForPlayer[playerid]);
		 		HandleidForPlayer[playerid] = 0;
		 		if(OldCar[playerid] != INVALID_VEHICLE_ID)
		 		{
		 		    PassengerInCar[OldCar[playerid]][PassengerSeat[playerid]] = INVALID_PLAYER_ID;
		 		    OldCar[playerid] = INVALID_VEHICLE_ID;
				}
			}
		}
	}
 	return 0;
}

public PlayVehicleRadioForPlayer(playerid,online,volume)
{
	if(HandleidForPlayer[playerid] != 0)
	{
	    Audio_Stop(playerid,HandleidForPlayer[playerid]);
		HandleidForPlayer[playerid] = 0;
	}
	HandleidForPlayer[playerid] = Audio_PlayStreamed(playerid,Stations[online - 1][0],false,false,false);
	Audio_SetVolume(playerid,HandleidForPlayer[playerid],volume);
	new str[64];
	format(str,sizeof(str),"~n~~n~~n~~n~~n~~n~~n~~n~~y~%s",Stations[online - 1][1]);
	GameTextForPlayer(playerid,str,3500,5);
	WaitForBuf[playerid] = true;
	SetTimerEx("NonChangeRadio",5000,false,"i",playerid);
	return 1;
}

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	if(newkeys == KEY_ACTION)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        {
		        if(Audio_IsClientConnected(playerid))
		        {
		            if(WaitForBuf[playerid]) return SendClientMessage(playerid,0xFF0000FF,"* –адио нельз€ сменить в течении 5-ти секунд");
			        new veh = GetPlayerVehicleID(playerid);
			        VehRadio[veh]++;
					if(VehRadio[veh] == 11) VehRadio[veh] = 1;
		 			PlayVehicleRadioForPlayer(playerid,VehRadio[veh],VehVolume[veh]);
      				if(PassengerInCar[veh][1] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][1],VehRadio[veh],VehVolume[veh]);
      				if(PassengerInCar[veh][2] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][2],VehRadio[veh],VehVolume[veh]);
      				if(PassengerInCar[veh][3] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][3],VehRadio[veh],VehVolume[veh]);
				}
			}
		}
	}
	if(newkeys == 132)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        {
		        if(Audio_IsClientConnected(playerid))
		        {
		            if(WaitForBuf[playerid]) return SendClientMessage(playerid,0xFF0000FF,"* –адио нельз€ сменить в течении 5-ти секунд");
			        new veh = GetPlayerVehicleID(playerid);
			        VehRadio[veh]--;
					if(VehRadio[veh] == 0) VehRadio[veh] = 10;
		 			PlayVehicleRadioForPlayer(playerid,VehRadio[veh],VehVolume[veh]);
		 			if(PassengerInCar[veh][1] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][1],VehRadio[veh],VehVolume[veh]);
      				if(PassengerInCar[veh][2] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][2],VehRadio[veh],VehVolume[veh]);
      				if(PassengerInCar[veh][3] != INVALID_PLAYER_ID) PlayVehicleRadioForPlayer(PassengerInCar[veh][3],VehRadio[veh],VehVolume[veh]);
				}
			}
		}
	}
	if(newkeys == KEY_ANALOG_UP)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        {
		        if(Audio_IsClientConnected(playerid))
		        {
					new veh = GetPlayerVehicleID(playerid);
					if(VehVolume[veh] >= 0 && VehVolume[veh] < 100)
					{
					    VehVolume[veh] += 5;
					    SetVolume(playerid,VehVolume[veh]);
					    if(PassengerInCar[veh][1] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][1],VehVolume[veh]);
      					if(PassengerInCar[veh][2] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][2],VehVolume[veh]);
      					if(PassengerInCar[veh][3] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][3],VehVolume[veh]);
					}
				}
			}
		}
	}
	if(newkeys == KEY_ANALOG_DOWN)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        {
		        if(Audio_IsClientConnected(playerid))
		        {
					new veh = GetPlayerVehicleID(playerid);
					if(VehVolume[veh] > 0 && VehVolume[veh] <= 100)
					{
					    VehVolume[veh] -= 5;
					    SetVolume(playerid,VehVolume[veh]);
					    if(PassengerInCar[veh][1] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][1],VehVolume[veh]);
      					if(PassengerInCar[veh][2] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][2],VehVolume[veh]);
      					if(PassengerInCar[veh][3] != INVALID_PLAYER_ID) SetVolume(PassengerInCar[veh][3],VehVolume[veh]);
					}
				}
			}
		}
	}
	return 0;
}

public SetVolume(playerid,volume)
{
    Audio_SetVolume(playerid,HandleidForPlayer[playerid],volume);
    new str[64];
    format(str,sizeof(str),"~n~~n~~n~~n~~n~~n~~n~~n~~g~Volume: ~y~%d%%",volume);
    GameTextForPlayer(playerid,str,3500,5);
    return 1;
}

public NonChangeRadio(playerid)
{
    WaitForBuf[playerid] = false;
    return 1;
}
