/*************************************************
Infinite-Gaming.com Presents:
Real Vehicle Lights v.2 by Cyber_Punk

DO NOT REMOVE CREDITS
If you borrow bits of code would be nice to..
credit the original authors

NEW - Public vehicles - Police, FBI, FIRE, Medic have flashing lights with the siren button (horn)
NEWv2 - Fixed a couple bugs, reworked the blinker system PRESS Look Left or Look Right to activate blinker
If you turn the wheel in the opposite direction than the blinker it will auto shut off. Just like a real car :P

Know issues (not script bugs)
Lights still will not flash in the day time,
Rear lights do not flash......
Hope for a samp fix in 0.3b code should still work
*************************************************/
#include <a_samp>

#define BLINK_RATE  	400 // This is the rate of flash (also rate of timer in milliseconds, same for pflash)
#define PFLASH_RATE     300 // This controls the rate of flash for public vehicle lights, works for all police, fire, ambulance vehicles
#define LIGHT_KEY		KEY_SUBMISSION // Set this to whatever key you want to turn the lights on

#define COLOR_YELLOW 0xFFFF00AA                   // Took this random color from another GM of mine. Change as you wish

new Tinted [MAX_VEHICLES] = 0;                    // OnFilterScriptInit vehicles won't be tinted
new Text3D: vehicle3dtext [MAX_VEHICLES];         // 3D text that will be above window tinted vehicle
new PlVehID[MAX_VEHICLES];                        // Used in OnPlayerStateChange to check from which vehicle player's exiting

forward TintWindows ();                           // Forwarded this function for the timer

//Put MAX PLAYERS HERE (sorry its for the timer..)
#undef MAX_PLAYERS
	#define MAX_PLAYERS 50
	
// Macro from SAMP wiki Credits to the author
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

new BlinkTime[MAX_PLAYERS];

public OnFilterScriptInit ()
{
	printf (" Filterscript Tint system ");
	printf (" made by Srdjan loaded  ");

    SetTimer ("TintWindows", 1500, 1);

	for (new i = 1; i <= MAX_VEHICLES; i++)
	{
		vehicle3dtext[i] = Create3DTextLabel (" ", COLOR_YELLOW, 0.0, 0.0, -50.0, 300.0, 0, 1);  // Creating 3dtext labels for every potential vehicle
	}

	return 1;
}

public OnFilterScriptExit()
{
	print("\n--------------------------------------");
	print(" Real Vehicle Lights UNLOADED");
	print("--------------------------------------\n");
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	KillTimer(BlinkTime[playerid]);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new panels, doors, lights, tires;
		new carid = GetPlayerVehicleID(playerid);
		GetVehicleDamageStatus(carid, panels, doors, lights, tires);
		lights = encode_lights(1, 1, 1, 1);
		SetPVarInt(playerid, "vMainOn", 0);
		UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
	}
	else if(newstate == PLAYER_STATE_ONFOOT)
	{
		KillTimer(BlinkTime[playerid]);
		SetPVarInt(playerid, "CopFlash", 0);
	}
	if ((oldstate == PLAYER_STATE_ONFOOT) && (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER))  // When player enters vehicle
	{
	    PlVehID[playerid] = GetPlayerVehicleID (playerid);  // Writing the vehicle ID for further usage
	}
	if ((newstate == PLAYER_STATE_ONFOOT) && (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER))  // When player exits vehicle
	{
		if (Tinted[PlVehID[playerid]])      // If the vehicle's windows were tinted (not necessary, but I've added)
		{
			for (new i=0; i < MAX_PLAYERS; i++)
		    {
				ShowPlayerNameTagForPlayer (i, playerid, 1);   // It will show the players name tag to everyone
		    }
		}
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(LIGHT_KEY))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0)
		{
			if(GetPVarInt(playerid, "CopFlash") == 0)
			{
		 		new panels, doors, lights, tires;
		 		new carid = GetPlayerVehicleID(playerid);
				GetVehicleDamageStatus(carid, panels, doors, lights, tires);
				switch(GetPVarInt(playerid, "vMainOn"))
				{
				    case 0:{
				        lights = encode_lights(0, 0, 0, 0);
		      			SetPVarInt(playerid, "vMainOn", 1);
					}
					case 1:{
						lights = encode_lights(1, 1, 1, 1);
						SetPVarInt(playerid, "vMainOn", 0);
					}
				}
				UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
			}
		}
	}
	if(PRESSED(KEY_CROUCH))
	{
	    if(IsPublicService(GetPlayerVehicleID(playerid)) && GetPlayerVehicleSeat(playerid) == 0)
		{
			switch(GetPVarInt(playerid, "CopFlash"))
			{
				case 0:{
				    KillTimer(BlinkTime[playerid]);
					BlinkTime[playerid] = SetTimerEx("vBlinker", PFLASH_RATE, 1, "i", playerid);
					SetPVarInt(playerid, "CopFlash", 1);
				}
				case 1:{
		   			KillTimer(BlinkTime[playerid]);
   					new panels, doors, lights, tires;
   					new carid = GetPlayerVehicleID(playerid);
					GetVehicleDamageStatus(carid, panels, doors, lights, tires);
					lights = encode_lights(1, 1, 1, 1);
					UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
					SetPVarInt(playerid, "CopFlash", 0);
				}
			}
		}
	}
	if(PRESSED(KEY_LOOK_LEFT))
	{
		if(GetPlayerVehicleSeat(playerid) == 0)
		{
			if(GetPVarInt(playerid, "vBLeft") == 0)
			{
				KillTimer(BlinkTime[playerid]);
				BlinkTime[playerid] = SetTimerEx("vBlinker", BLINK_RATE, 1, "i", playerid);
	   			SetPVarInt(playerid, "vBLeft", 1);
	   			SetPVarInt(playerid, "vBRight", 0);
			}else{
			    KillTimer(BlinkTime[playerid]);
				new panels, doors, lights, tires;
				new carid = GetPlayerVehicleID(playerid);
				GetVehicleDamageStatus(carid, panels, doors, lights, tires);
			    switch(GetPVarInt(playerid, "vMainOn")){
			        case 0:{
			        	lights = encode_lights(1, 1, 1, 1);
					}
					case 1:{
	                    lights = encode_lights(0, 0, 0, 0);
					}
				}
				UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
			    SetPVarInt(playerid, "vBLeft", 0);
			}
		}
	}
	if(PRESSED(KEY_LOOK_RIGHT))
	{
		if(GetPlayerVehicleSeat(playerid) == 0)
		{
			if(GetPVarInt(playerid, "vBRight") == 0)
			{
				KillTimer(BlinkTime[playerid]);
				BlinkTime[playerid] = SetTimerEx("vBlinker", BLINK_RATE, 1, "i", playerid);
	   			SetPVarInt(playerid, "vBRight", 1);
	   			SetPVarInt(playerid, "vBLeft", 0);
			}else{
			    KillTimer(BlinkTime[playerid]);
				new panels, doors, lights, tires;
				new carid = GetPlayerVehicleID(playerid);
				GetVehicleDamageStatus(carid, panels, doors, lights, tires);
			    switch(GetPVarInt(playerid, "vMainOn")){
			        case 0:{
			        	lights = encode_lights(1, 1, 1, 1);
					}
					case 1:{
	                    lights = encode_lights(0, 0, 0, 0);
					}
				}
				UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
			    SetPVarInt(playerid, "vBRight", 0);
			}
		}
	}
	return 1;
}

forward vBlinker(playerid);
public vBlinker(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPVarInt(playerid, "CopFlash") != 1)
	{
	    new Keys, ud, lr, panels, doors, lights, tires;
	    new carid = GetPlayerVehicleID(playerid);
	    GetPlayerKeys(playerid, Keys, ud, lr);
		GetVehicleDamageStatus(carid, panels, doors, lights, tires);

		if(lr > 0)
		{
			if(GetPVarInt(playerid, "vBLeft") == 1)
			{
			    KillTimer(BlinkTime[playerid]);
			    switch(GetPVarInt(playerid, "vMainOn")){
			        case 0:{
			        	lights = encode_lights(1, 1, 1, 1);
					}
					case 1:{
	                    lights = encode_lights(0, 0, 0, 0);
					}
				}
				UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
			    SetPVarInt(playerid, "vBLeft", 0);
			    return 1;
			}
		}
		else if(lr < 0)
		{
			if(GetPVarInt(playerid, "vBRight") == 1)
			{
			    KillTimer(BlinkTime[playerid]);
			    switch(GetPVarInt(playerid, "vMainOn")){
			        case 0:{
			        	lights = encode_lights(1, 1, 1, 1);
					}
					case 1:{
	                    lights = encode_lights(0, 0, 0, 0);
					}
				}
				UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
			    SetPVarInt(playerid, "vBRight", 0);
			    return 1;
			}
		}

		if(GetPVarInt(playerid, "vBRight") == 1)
		{
			switch(GetPVarInt(playerid, "vMainOn")){
			    case 0:{
	      			switch(GetPVarInt(playerid, "vBlinkOn")){
	      			    case 0:{
			        		lights = encode_lights(1, 1, 0, 0);
	      					SetPVarInt(playerid, "vBlinkOn", 1);
	      			    }
	      			    case 1:{
							lights = encode_lights(1, 1, 1, 1);
							SetPVarInt(playerid, "vBlinkOn", 0);
	      			    }
					}
				}
				case 1:{
      				switch(GetPVarInt(playerid, "vBlinkOn")){
	      			    case 0:{
			        		lights = encode_lights(0, 0, 1, 1);
	      					SetPVarInt(playerid, "vBlinkOn", 1);
	      			    }
	      			    case 1:{
							lights = encode_lights(0, 0, 0, 0);
							SetPVarInt(playerid, "vBlinkOn", 0);
	      			    }
					}
				}
			}
		}
		
		if(GetPVarInt(playerid, "vBLeft") == 1)
		{
			switch(GetPVarInt(playerid, "vMainOn")){
			    case 0:{
	      			switch(GetPVarInt(playerid, "vBlinkOn")){
	      			    case 0:{
			        		lights = encode_lights(0, 0, 1, 1);
	      					SetPVarInt(playerid, "vBlinkOn", 1);
	      			    }
	      			    case 1:{
							lights = encode_lights(1, 1, 1, 1);
							SetPVarInt(playerid, "vBlinkOn", 0);
	      			    }
					}
				}
				case 1:{
      				switch(GetPVarInt(playerid, "vBlinkOn")){
	      			    case 0:{
			        		lights = encode_lights(1, 1, 0, 0);
	      					SetPVarInt(playerid, "vBlinkOn", 1);
	      			    }
	      			    case 1:{
							lights = encode_lights(0, 0, 0, 0);
							SetPVarInt(playerid, "vBlinkOn", 0);
	      			    }
					}
				}
			}
		}
		UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
	}
	else if(GetPVarInt(playerid, "CopFlash") == 1)
	{
	    new d[4];
	    new carid = GetPlayerVehicleID(playerid);
		GetVehicleDamageStatus(carid, d[0], d[1], d[2], d[3]);

		switch(GetPVarInt(playerid, "vBlinkOn"))
		{
		   case 0:{
				d[2] = encode_lights(1, 1, 0, 0);
				SetPVarInt(playerid, "vBlinkOn", 1);
		   }
		   case 1:{
				d[2] = encode_lights(0, 0, 1, 1);
				SetPVarInt(playerid, "vBlinkOn", 0);
		   }
		}
		UpdateVehicleDamageStatus(carid, d[0], d[1], d[2], d[3]);
		return 1;
	}
	return 1;
}
// Thanks to JernejL (RedShirt)
encode_lights(light1, light2, light3, light4) {

	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);

}

IsPublicService(carid)
{
    new PS[11] = { 416, 427, 490, 528, 407, 544, 596, 598, 597, 599, 601 };
    for(new i = 0; i < sizeof(PS); i++)
	{
		if(GetVehicleModel(carid) == PS[i]) return 1;
	}
	return 0;
}
//tint
public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!strcmp (cmdtext, "/v tint"))
	{
	    if (IsPlayerInAnyVehicle (playerid))
		{
		    new vehid = GetPlayerVehicleID (playerid);
		    if (GetPlayerVehicleSeat (playerid) != 0)
		    {
		        SendClientMessage (playerid, COLOR_YELLOW, "You need to be the driver to use this command.");
		    }
		    else
		    {
		        if (Tinted[vehid])
		        {
		            SendClientMessage (playerid, COLOR_YELLOW, "Your windows are tinted already.");
		        }
		        else
		        {
		            Tinted[vehid] = 1;
		            Update3DTextLabelText (vehicle3dtext[vehid], COLOR_YELLOW, "Vehicle's windows are tinted");
                    SendClientMessage (playerid, COLOR_YELLOW, "Your windows have been tinted.");
      	        }
		    }
		}
		else
		{
		    SendClientMessage (playerid, COLOR_YELLOW, "You need to be in the vehicle to use this command.");
		}
		return 1;
	}
	return 0;
}


public TintWindows ()
{
	for (new id = 1; id <= MAX_VEHICLES; id++)         // Going through every vehicle
	{
		if (Tinted[id])                                // Making sure their windows are tinted
		{
		    Attach3DTextLabelToVehicle (vehicle3dtext[id], id, 0.0, 0.0, 1.2);   // If they are, 3dtext label will apear above the car
		    for (new i = 0; i < MAX_PLAYERS; i++)      // Going through every player
		    {
				if (IsPlayerInVehicle (i, id))         // Making sure he is sitting in the vehicle
				{
				    for (new j = 0; j < MAX_PLAYERS; j++) // Another loop
				    {
     					if (!IsPlayerInVehicle (j, id))   // Making sure the other person is not in the vehicle
				       	{
     	  					ShowPlayerNameTagForPlayer (j, i, 0);  // The person out of the vehicle won't be able to see the nametag of the one inside
				       	}
				    }
				}
		    }
		}
	}
	return 1;
}

public OnVehicleDeath (vehicleid)
{
	if (Tinted [vehicleid])
	{
	    Update3DTextLabelText (vehicle3dtext[vehicleid], COLOR_YELLOW, " ");             // Changing the 3dtext label accordingly
	    Attach3DTextLabelToVehicle (vehicle3dtext[vehicleid], vehicleid, 0.0, 0.0, 1.2);
	    Tinted[vehicleid] = 0; // When the car's destroyed, that veh ID won't have windows tinted
	}
	return 1;
}

