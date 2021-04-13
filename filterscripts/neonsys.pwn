

#include <a_samp>
#include <dini>

#define COLOR_WHITE 0xFFFFFFFF


forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
forward GateOpenn();
forward CloseGate();
forward CheckForNeonPos(playerid);
forward LoadNeon();
forward SaveNeon();



new gatemover;
new openedgate = 0;
new ObjectSelect[MAX_VEHICLES][4];
new NeonObject[MAX_VEHICLES][2];


public OnFilterScriptInit()
{
	Create3DTextLabel("Neon Save system{899eff}\nNeon price: 30000${1cd24c}\nLights price: 10000$",COLOR_WHITE,690.54302979,-1182.41369629,17.17897415,15.0,0,1);
	gatemover = CreateObject(980,690.54302979,-1182.41369629,17.17897415,0.00000000,0.00000000,240.00000000); //gate move
 	CreatePickup(3096,23,697.2826,-1183.6445,15.5834,0);
	CreateObject(980,702.30810547,-1189.30163574,16.47109413,0.00000000,0.00000000,62.00000000); //object(airportgate) (1)
	CreateObject(14826,696.31774902,-1190.84143066,15.19145679,0.00000000,0.00000000,0.00000000); //object(int_kbsgarage2) (1)
	CreateObject(1076,700.62005615,-1181.23803711,16.35316849,0.00000000,0.00000000,238.00000000); //object(wheel_lr4) (1)
	CreateObject(1079,699.29327393,-1180.47265625,16.30689621,0.00000000,0.00000000,242.00000000); //object(wheel_sr1) (1)
	CreateObject(1084,697.94982910,-1179.69775391,16.30231857,0.00000000,0.00000000,236.00000000); //object(wheel_lr5) (1)
	CreateObject(1076,698.55499268,-1180.04687500,17.40899658,0.00000000,0.00000000,246.00000000); //object(wheel_lr4) (2)
	CreateObject(1079,699.87243652,-1180.80676270,17.35228539,0.00000000,0.00000000,240.00000000); //object(wheel_sr1) (2)
	SetTimer("SaveNeon",100000,1);
	SetTimer("CheckForNeonPos",6000,1);
	LoadNeon();
}

public OnFilterScriptExit()
{
	SaveNeon();
	SendRconCommand("reloadfs neonsys");
	return 1;
}


main()
{
	print("\n----------------------------------");
	print(" Neon SAVE System by Misha_Konsta");
	print("----------------------------------\n");
}


public OnPlayerRequestClass(playerid, classid)
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(strcmp(cmdtext,"/neongate",true)==0)
	{
		if(PlayerToPoint(8,playerid,690.1254,-1181.9131,15.3945))
		{
			GateOpenn();
		}
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(PlayerToPoint(8,playerid,690.1254,-1181.9131,15.3945))
		{
			GateOpenn();
		}
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 9010)
    {
        if(!response) return 1;
		ShowPlayerDialog(playerid, 9011, DIALOG_STYLE_LIST, "What interests you? "," Neon lights (30,000) \nLights - backlight (10.000) "," Next","Back");
    }
  	else if(dialogid == 9011)
    {
        if(!response) return 1;
        switch(listitem)
        {
            case 0:ShowPlayerDialog(playerid, 9012, DIALOG_STYLE_LIST, "Select COLOR", "Blue neon\nRed neon\nGreen neon\nWhite neon\nPink neon\nYellow neon", "Buy!", "Cancel");
            case 1:ShowPlayerDialog(playerid, 9013, DIALOG_STYLE_LIST, "Select COLOR", "White lights\nRed lights\nGreen lights\nBlue lights\nLights beacons\nPolice lights", "Buy!", "Cancel");
        }
    }
   	else if(dialogid == 9012)
    {
        if(response==0)
		{
			ShowPlayerDialog(playerid, 9011, DIALOG_STYLE_LIST, "What interests you? "," Neon lights (30,000) \nLights - backlight (10.000) "," Next","Back");
			return 1;
		}
		if(IsValidObject(ObjectSelect[GetPlayerVehicleID(playerid)][0]) || IsValidObject(ObjectSelect[GetPlayerVehicleID(playerid)][1]))
		{
			DestroyObject(ObjectSelect[GetPlayerVehicleID(playerid)][0]);
			DestroyObject(ObjectSelect[GetPlayerVehicleID(playerid)][1]);
		}
		switch(listitem)
        {
            case 0:NeonObject[GetPlayerVehicleID(playerid)][0]=18648;
			case 1:NeonObject[GetPlayerVehicleID(playerid)][0]=18647;
            case 2:NeonObject[GetPlayerVehicleID(playerid)][0]=18649;
            case 3:NeonObject[GetPlayerVehicleID(playerid)][0]=18652;
            case 4:NeonObject[GetPlayerVehicleID(playerid)][0]=18651;
            case 5:NeonObject[GetPlayerVehicleID(playerid)][0]=18650;
        }
        if(GetPlayerMoney(playerid) > 10000)
  		{
  			ObjectSelect[GetPlayerVehicleID(playerid)][0] = CreateObject(NeonObject[GetPlayerVehicleID(playerid)][0],0,0,0,0,0,0);
        	ObjectSelect[GetPlayerVehicleID(playerid)][1] = CreateObject(NeonObject[GetPlayerVehicleID(playerid)][0],0,0,0,0,0,0);
        	AttachObjectToVehicle(ObjectSelect[GetPlayerVehicleID(playerid)][0], GetPlayerVehicleID(playerid), -0.8, 0.0, -0.55, 0.0, 0.0, 0.0);
        	AttachObjectToVehicle(ObjectSelect[GetPlayerVehicleID(playerid)][1], GetPlayerVehicleID(playerid), 0.8, 0.0, -0.55, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1133, 0, 0, 0);
        	GivePlayerMoney(playerid, -30000);
			SendClientMessage(playerid,COLOR_WHITE,"Neon on cars has been successfully installed, price 30.000$");
		}
		else
		{
			SendClientMessage(playerid,COLOR_WHITE,"Money?!");
		}
    }
   	else if(dialogid == 9013)
    {
        if(response==0)
		{
			ShowPlayerDialog(playerid, 9011, DIALOG_STYLE_LIST, "What interests you? "," Neon lights (30,000) \nLights - backlight (10.000) "," Next","Back");
			return 1;
		}
        if(IsValidObject(ObjectSelect[GetPlayerVehicleID(playerid)][2]) || IsValidObject(ObjectSelect[GetPlayerVehicleID(playerid)][3]))
		{
			DestroyObject(ObjectSelect[GetPlayerVehicleID(playerid)][2]);
			DestroyObject(ObjectSelect[GetPlayerVehicleID(playerid)][3]);
		}
		switch(listitem)
        {
            case 0:NeonObject[GetPlayerVehicleID(playerid)][1]=19281;
            case 1:NeonObject[GetPlayerVehicleID(playerid)][1]=19282;
            case 2:NeonObject[GetPlayerVehicleID(playerid)][1]=19283;
            case 3:NeonObject[GetPlayerVehicleID(playerid)][1]=19284;
            case 4:NeonObject[GetPlayerVehicleID(playerid)][1]=19285;
            case 5:NeonObject[GetPlayerVehicleID(playerid)][1]=19293;
		}
		if(GetPlayerMoney(playerid) > 10000)
  		{
			ObjectSelect[GetPlayerVehicleID(playerid)][2] = CreateObject(NeonObject[GetPlayerVehicleID(playerid)][1],0,0,0,0,0,0);
	        ObjectSelect[GetPlayerVehicleID(playerid)][3] = CreateObject(NeonObject[GetPlayerVehicleID(playerid)][1],0,0,0,0,0,0);
			AttachObjectToVehicle(ObjectSelect[GetPlayerVehicleID(playerid)][2], GetPlayerVehicleID(playerid), -0.8, 2.25, 0.0, 0.0, 0.0, 180.0);
	        AttachObjectToVehicle(ObjectSelect[GetPlayerVehicleID(playerid)][3], GetPlayerVehicleID(playerid), 0.8, 2.25, 0.0, 0.0, 0.0, 180.0);
			PlayerPlaySound(playerid, 1133, 0, 0, 0);
	        GivePlayerMoney(playerid, -10000);
	        SendClientMessage(playerid,COLOR_WHITE,"Lights on cars has been successfully installed, price 10.000$");
		}
		else
		{
			SendClientMessage(playerid,COLOR_WHITE,"Money?!");
		}
    }
	return 1;
}

public SaveNeon()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		new vehicleid = GetPlayerVehicleID(i);
		{
			if(IsValidObject(ObjectSelect[vehicleid][0]) || IsValidObject(ObjectSelect[vehicleid][1]))
			{
				new DiniString[16];
			 	format(DiniString, 16, "Neon_%d", vehicleid);
				dini_IntSet("CarNeon.ini", DiniString, NeonObject[vehicleid][0]);
			}
			if(IsValidObject(ObjectSelect[vehicleid][2]) || IsValidObject(ObjectSelect[vehicleid][3]))
			{
				new DiniString[16];
				format(DiniString, 16, "Lights_%d", vehicleid);
				dini_IntSet("CarNeon.ini", DiniString, NeonObject[vehicleid][1]);
			}
		}
	}
	return 1;
}
public LoadNeon()
{
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		new DiniString[16];
		format(DiniString, 16, "Neon_%d", i);
		NeonObject[i][0]=dini_Int("CarNeon.ini", DiniString);
		if(NeonObject[i][0])
		{
			ObjectSelect[i][0] = CreateObject(NeonObject[i][0],0,0,0,0,0,0);
			ObjectSelect[i][1] = CreateObject(NeonObject[i][0],0,0,0,0,0,0);
			AttachObjectToVehicle(ObjectSelect[i][0], i, -0.8, 0.0, -0.55, 0.0, 0.0, 0.0);
			AttachObjectToVehicle(ObjectSelect[i][1], i, 0.8, 0.0, -0.55, 0.0, 0.0, 0.0);
		}
		format(DiniString, 16, "Lights_%d", i);
		NeonObject[i][1]=dini_Int("CarNeon.ini", DiniString);
		if(NeonObject[i][1])
		{
			ObjectSelect[i][2] = CreateObject(NeonObject[i][1],0,0,0,0,0,0);
			ObjectSelect[i][3] = CreateObject(NeonObject[i][1],0,0,0,0,0,0);
			AttachObjectToVehicle(ObjectSelect[i][2], i, -0.8, 2.25, 0.0, 0.0, 0.0, 180.0);
			AttachObjectToVehicle(ObjectSelect[i][3], i, 0.8, 2.25, 0.0, 0.0, 0.0, 180.0);
		}
	}
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	if(IsValidObject(ObjectSelect[vehicleid][0]) || IsValidObject(ObjectSelect[vehicleid][1]))
	{
		DestroyObject(ObjectSelect[vehicleid][0]);
		DestroyObject(ObjectSelect[vehicleid][1]);
	}
	if(IsValidObject(ObjectSelect[vehicleid][2]) || IsValidObject(ObjectSelect[vehicleid][3]))
	{
		DestroyObject(ObjectSelect[vehicleid][2]);
		DestroyObject(ObjectSelect[vehicleid][3]);
	}
	return 1;
}
public GateOpenn()
{
	if(openedgate == 0)
	{
		MoveObject(gatemover,690.54302979,-1182.41369629,10.17897415,2);
 		SetTimer("CloseGate",7000,0);
 		openedgate = 1;
 	}
}
public CloseGate()
{
	MoveObject(gatemover,690.54302979,-1182.41369629,17.17897415,2);
	openedgate = 0;
}
public CheckForNeonPos(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(PlayerToPoint(4, playerid, 697.2826,-1183.6445,15.5834))
		{
			ShowPlayerDialog(playerid, 9010, DIALOG_STYLE_MSGBOX, "Pimp my car > Tuning", "{FFFFFF}You stopped at a saloon car leveling {ffb449}'Los Santos'\n{0bcd5a}You wish to purchase an additional tuning?", "Buy", "Cancel");
		}
	}
}
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}
