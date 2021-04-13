/*  TINT system made by Srdjan
	Today's date 28/08/2011   */

#include <a_samp>

#define COLOR_YELLOW 0xFFFF00AA                   // Took this random color from another GM of mine. Change as you wish

new Tinted [MAX_VEHICLES] = 0;                    // OnFilterScriptInit vehicles won't be tinted
new Text3D: vehicle3dtext [MAX_VEHICLES];         // 3D text that will be above window tinted vehicle
new PlVehID[MAX_VEHICLES];                        // Used in OnPlayerStateChange to check from which vehicle player's exiting

forward TintWindows ();                           // Forwarded this function for the timer

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

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!strcmp (cmdtext, "/buytint"))
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

public OnPlayerStateChange (playerid, newstate, oldstate)
{
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
