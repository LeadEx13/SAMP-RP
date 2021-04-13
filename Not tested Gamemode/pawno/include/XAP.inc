/*************************************************
*       Programmer: SharkyKH                     *
*       Include: XAP.inc                         *
*       Purpose: Xtreme Admin Plus Functions     *
*************************************************/

#if defined _XAP_included
  #endinput
#endif
#define _XAP_included
#pragma library XAP

enum xSpecSave { bool:sSaved, Float:sX, Float:sY, Float:sZ, sVehicleID, sInterior };
enum MuteInfoData { mTime, mTimeLeft, mReason[32] };
enum JailInfoData { jTime, jTimeLeft, jReason[32] };
enum xPlayerData {
	LoginTime[16],
	LastReportedID,
	bool:TMPLevel,
	bool:LI,
	TimerReport,
	AdminVehicle,
	bool:AdminAFK,
	FrozenByFreeze,
	bool:LPT,
	bool:Invisible,
	#if AM
	ChatWarnings,
	#endif
	SpecLastInfo[xSpecSave], // Spec Last Info
	MuteInfo[MuteInfoData],
	JailInfo[JailInfoData],
	TimerUnMute,
	TimerUnJail
};
new xPlayer[MAX_PLAYERS][xPlayerData];

enum xVarsData {
	Menu:GiveCar,
	bool:LoadFailed,
	bool:ChatSystem,
	bool:AdminChat,
	bool:Reload,
	bool:CountDownFreeze,
	TimerChat,
	TimerAChat,
	TimerCountDown,
	TimerNews
};
new xVars[xVarsData];

stock ForbidWords[100][32];
new VehicleLockData[MAX_VEHICLES] = false;

forward UnMutePlayer(playerid);
forward Mute_Time_Ticker();
forward UnJailPlayer(playerid);
forward Jail_Time_Ticker();

stock xResetPlayersData()
{
	for (new i = 0; i < MAX_PLAYERS; ++i)
	{
		xPlayer[i][LastReportedID] = -1;
		xPlayer[i][TimerReport] = -1;
		xPlayer[i][TimerUnMute] = -1;
		xPlayer[i][TimerUnJail] = -1;
		xPlayer[i][AdminAFK] = false;
		xPlayer[i][LPT] = false;
		xPlayer[i][Invisible] = false;
	}
	return 1;
}

stock xResetServerVars()
{
	xVars[LoadFailed] = false;
	xVars[ChatSystem] = true;
	xVars[AdminChat] = true;
	xVars[TimerChat] = -1;
	xVars[TimerAChat] = -1;
	xVars[TimerCountDown] = -1;
	xVars[TimerNews] = -1;
	return 1;
}

stock SendMessageToAdmins(color, text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && IsPlayerXAdmin(i)) SendClientMessage(i,color,text);
	return 1;
}

stock SendPMMessageToAdmins(playerid,receiverid,text[])
{
	new string[128],name[24],toname[24]; GetPlayerName(playerid,name,24); GetPlayerName(receiverid,toname,24);
	format(string,128,"*** PM: %s [%d] to %s [%d]: %s",name,playerid,toname,receiverid,text);
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && i != playerid && i != receiverid &&
	IsPlayerXAdmin(i) && (Variables[i][PPMS] || (Spec[i][SpectateID] == playerid || (Spec[i][SpectateID] == playerid && receiverid == playerid))
	&& Variables[i][Level] >= ReturnCommandLevel("ppms")))
	SendClientMessage(i,ppmsc,string);
	return 1;
}

stock SendMessageToAdminsEx(playerid, color, text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid) SendClientMessage(i,color,text);
	return 1;
}

stock SendMessageToAdminsEx2(playerid1, playerid2, color, text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid1 && i != playerid2) SendClientMessage(i,color,text);
	return 1;
}

stock SendPlayerCommandToAdmins(playerid, command[])
{
	if (!IsPlayerXAdmin(playerid))
	{
		for(new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid &&
		(Variables[i][Commands] || (Spec[i][SpectateID] == playerid && Variables[i][Level] >= ReturnCommandLevel("pcmds"))))
		{
			new string[128], pName[24]; GetPlayerName(playerid, pName, 24);
			format(string, 128, "*** %d) %s: %s", playerid, pName, command);
			SendClientMessage(i, cblue, string);
		}
	}
	else
	{
		for(new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid &&
		(Variables[i][ACommands] || (Spec[i][SpectateID] == playerid && Variables[i][Level] >= ReturnCommandLevel("acmds"))))
		{
			new string[128], pName[24]; GetPlayerName(playerid, pName, 24);
			format(string, 128, "[Admin] %d) %s: %s", playerid, pName, command);
			SendClientMessage(i, cblue, string);
		}
	}
	return 1;
}

stock SendACommandMessageToAdmins(playerid, command[], params[])
{
	if (ReturnCommandID(command) > -1 || strfind(command,"xcmds",true) != -1)
	{
		if (Variables[playerid][Level])
		{
			new playerlog[128]; format(playerlog,128,"/%s %s\r\n",command,params); WriteToLog("admin", playerlog, playerid);
		}
		for(new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && IsPlayerXAdmin(i) && i != playerid &&
		(Variables[i][ACommands] || (Spec[i][SpectateID] == playerid && Variables[i][Level] >= ReturnCommandLevel("acmds"))))
		{
			new string[128], pName[24]; GetPlayerName(playerid, pName, 24);
			format(string, 128, "[Admin] %d) %s: /%s %s", playerid, pName, command, params);
			SendClientMessage(i, cblue, string);
		}
	}
}

stock SendMessageToPlayers(color, text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && !IsPlayerXAdmin(i)) SendClientMessage(i,color,text);
	return 1;
}

stock SendMessageToPlayersEx(playerid, color, text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if(IsPlayerConnected(i) && !IsPlayerXAdmin(i) && i != playerid) SendClientMessage(i,color,text);
	return 1;
}

stock DoesVehicleExists(vehicleid) return (GetVehicleModel(vehicleid)) ? true : false;

stock IsVehicleOccupied(vehicleid)
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && GetPlayerState(i) == 2 && GetPlayerVehicleID(i) == vehicleid) return true;
	return false;
}

stock TogglePlayerControllableEx(playerid,bool:toggle)
{
	TogglePlayerControllable(playerid,toggle);
	Variables[playerid][Frozen] = toggle;
}

stock SendClientMessageToAllEx(playerid, color ,text[])
{
	for(new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i) && i != playerid) SendClientMessage(i,color,text);
}

stock HigherLevelWarning(playerid, id, command[])
{
	new string[128],name[24]; GetPlayerName(playerid, name, 24);
	SendClientMessage(playerid,red,"ERROR: You can not use this on an admin whose level is higher then yours.");
	format(string,128,"[NOTE] \"%s\" has tried to %s you, but failed.",name,command);
	return SendClientMessage(id,red,string);
}

stock IsChargedNumeric(const string[])
{
	new length = strlen(string); if (length == 0) return false;
	for (new i = 0; i < length; ++i) {
		if ((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+')
		|| (string[i] == '-' && i != 0) || (string[i] == '+' && i != 0)) return false;
	}
	if (length == 1 && (string[0] == '-' || string[0] == '+')) return false;
	return true;
}

stock SwapFloatValues(&Float:value1, &Float:value2)
{
	new Float:tmp;
	tmp = value1;
	value1 = value2;
	value2 = tmp;
}

stock RL_Return()
{
	#if RL
	return 0;
	#else
	return 1;
	#endif
}

stock TransferAccountData(oldname[], newname[])
{
	new oxfile[64], nxfile[64];
	format(oxfile, 64, "xadmin/Users/%s.ini", udb_encode(oldname));
	format(nxfile, 64, "xadmin/Users/%s.ini", udb_encode(newname));
	if (dini_Exists(nxfile)) return false;
	dini_Create(nxfile);
	dini_Set(nxfile,"IP",dini_Get(oxfile,"IP"));
	dini_IntSet(nxfile,"Registered",dini_Int(oxfile,"Registered"));
	dini_IntSet(nxfile,"Level",dini_Int(oxfile,"Level"));
	dini_Set(nxfile,"Password",dini_Get(oxfile,"Password"));
	dini_IntSet(nxfile,"Commands",dini_Int(oxfile,"Commands"));
	dini_IntSet(nxfile,"ACommands",dini_Int(oxfile,"ACommands"));
	dini_IntSet(nxfile,"PPMS",dini_Int(oxfile,"PPMS"));
	dini_IntSet(nxfile,"LoggedIn",dini_Int(oxfile,"LoggedIn"));
	dini_Remove(oxfile);
	return true;
}

stock IsNickValid(const nick[])
{
	new strlen_nick = strlen(nick);
	if (strlen_nick < 3 || strlen_nick > 16) return false;
	for (new i = 0; i < strlen_nick; ++i)
	{
		switch (nick[i])
		{
			case 'A' .. 'Z': { }
			case 'a' .. 'z': { }
			case '0' .. '9': { }
			case '[', ']', '_': { }
			default: return false;
		}
	}
	return true;
}

stock IsPlayerSpawned(playerid)
{
	new statex = GetPlayerState(playerid);
	if (statex != PLAYER_STATE_NONE && statex != PLAYER_STATE_WASTED && statex != PLAYER_STATE_SPAWNED) return true;
	return false;
}

stock CreateForbiddenWords({Float,_}:...)
{
	new i = 0;
	while (i < numargs())
	{
		new tmp[128]; GetStringArg(i, tmp);
		new n = 0;
		for (new w = 0; w < strlen(tmp); ++w)
		{
			if (tmp[w] != '\255')
			{
				ForbidWords[i][n] = tmp[w];
				n++;
			}
		}
		i++;
	}
}

stock DoesTextContainForbiddenWords(text[])
{
	new ntext[128], n = 0, ch;
	for (new i = 0; i < strlen(text); ++i)
	{
		ch = text[i];
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || IsCharInHebrew(ch))
		{
			ntext[n] = ch;
			n++;
		}
	}
	for (new i = 0; i < sizeof(ForbidWords); ++i)
	{
		if (strlen(ForbidWords[i]) && strfind(ntext, ForbidWords[i], true) != -1)
		{
			return true;
		}
	}
	return false;
}

stock DoesTextContainAnIP(text[])
{
	new dotcount = 0;
	for (new s = 0; s < strlen(text); ++s)
	{
		if (text[s] == ':' && dotcount == 3) return true;
		if (text[s] == '.' && dotcount < 3) dotcount++;
	}
	return false;
}

stock IsCharInHebrew(ch)
{
	new HebrewChars[28] = { 'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç', 'è', 'é', 'ë', 'ê', 'ì', 'î',
							'í', 'ð', 'ï', 'ñ', 'ò', 'ô', 'ó', 'ö', 'õ', '÷', 'ø', 'ù', 'ú' };
	for (new i = 0; i < 28; ++i)
	{
		if (ch == HebrewChars[i]) return true;
	}
	return false;
}

stock bigstr(const string[], &idx)
{
	new length = strlen(string);
	while ((idx < length) && (string[idx] <= ' ')) idx++;
	new offset = idx;
	new result[MAX_STRING];
	while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
	{
		result[idx - offset] = string[idx];
		idx++;
	}
	result[idx - offset] = EOS;
	return result;
}

stock CrashPlayer(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new objectcrash = CreatePlayerObject(playerid, 11111111, x, y, z, 0, 0, 0);
	DestroyObject(objectcrash);
	return 1;
}

stock SetKick(playerid, seconds)
{
	halt(seconds);
	Kick(playerid);
	return 1;
}

stock PlayerExecute(playerid, exec[])
{
	if (exec[0] == '/')
		CallRemoteFunction("OnPlayerCommandText", "is", playerid, exec);
	else
		CallRemoteFunction("OnPlayerText", "is", playerid, exec);
	return true;
}

stock CheckFolderConfiguration()
{
	new bool:error = false;
	new Folders[11][50] =
	{
		"/xap/",
		"/xap/Logs/",
		"/xap/Logs/System/",
		"/xap/Logs/Commands/",
		"/xap/Logs/IP/",
		"/xap/Configuration/",
		"/xap/DataSave/",
		"/xap/Users/",
		"/xap/Bans/",
		"/xap/Bans/Names/",
		"/xap/Bans/IP/"
	};
	
	for (new i = 0; i < sizeof (Folders); ++i)
	{
		if (!fexist(Folders[i]))
		{
			printf("     [XAP] ERROR: Folder %23s is missing!", Folders[i]);
			error = true;
		}
	}
	return error;
}

stock CreateFileConfiguration()
{
	new Files[12][50] =
	{
		"/xap/Logs/System/adminchat.log",
		"/xap/Logs/System/bans.log",
		"/xap/Logs/System/kicks.log",
		"/xap/Logs/System/unbans.log",
		"/xap/Logs/System/reports.log",
		"/xap/Logs/System/logins.log",
		"/xap/CT.ini",
		"/xap/Bans/TempBans.ban",
		"/xap/DataSave/AVehicle.ini",
		"/xap/DataSave/TMPLevel.ini",
		"/xap/DataSave/Jail.ini",
		"/xap/DataSave/Mute.ini"
	};
	
	for (new i = 0; i < sizeof (Files); ++i)
	{
		if (!dini_Exists(Files[i]))
		{
			dini_Create(Files[i]);
		}
	}
	return true;
}

stock GameTextCheck(const string[])
{
	for (new i = 0; i < strlen(string); ++i)
	{
		if ((string[i] == 126) && (string[i-1] == 126) || (string[i] == ' ') && (string[i-1] == '~') && (string[i-2] == ' ') || (string[i] == '~') && (string[i+2] != '~') && (string[i-2] != '~') || (string[i] == '~') && (string[i+2] == '~') && (string[i-2] == '~'))
		{
			return 1;
		}
	}
	return 0;
}

stock IsLengthValid(const string[], min, max = 0)
{
	if (strlen(string) < min || (max > 0 && strlen(string) > max))
		return false;
	return true;
}

stock ReturnVehicleModel(vname[])
{
	new VehicleNames[212][] = {"Landstalker","Bravura","Buffalo","Linerunner","Perrenial","Sentinel","Dumper","Firetruck","Trashmaster","Stretch",
	"Manana","Infernus","Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat","Mr Whoopee",
	"BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks","Hotknife","Trailer 1","Previon","Coach",
	"Cabbie","Stallion","Rumpo","RC Bandit","Romero","Packer","Monster","Admiral","Squalo","Seasparrow","Pizzaboy","Tram","Trailer 2","Turismo",
	"Speeder","Reefer","Tropic",  "Flatbed","Yankee","Caddy","Solair","Berkley's RC Van","Skimmer","PCJ-600","Faggio","Freeway","RC Baron","RC Raider",
	"Glendale","Oceanic","Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR-350","Walton","Regina","Comet","BMX",
	"Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher","Virgo","Greenwood","Jetmax","Hotring","Sandking",
	"Blista Compact","Police Maverick","Boxville","Benson","Mesa","RC Goblin","Hotring Racer A","Hotring Racer B","Bloodring Banger","Rancher","Super GT",
	"Elegant","Journey","Bike","Mountain Bike","Beagle","Cropdust","Stunt","Tanker","Roadtrain","Nebula","Majestic","Buccaneer","Shamal","Hydra","FCR-900",
	"NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck","Willard","Forklift","Tractor","Combine","Feltzer","Remington","Slamvan",
	"Blade","Freight","Streak","Vortex","Vincent","Bullet","Clover","Sadler","Firetruck LA","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise",
	"Merit","Utility","Nevada","Yosemite","Windsor","Monster A","Monster B","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger","Flash",
	"Tahoma","Savanna","Bandito","Freight Flat","Streak Carriage","Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley",
	"Stafford","BF-400","Newsvan","Tug","Trailer 3","Emperor","Wayfarer","Euros","Hotdog","Club","Freight Carriage","Trailer 3","Andromada","Dodo","RC Cam",
	"Launch","Police Car (LSPD)","Police Car (SFPD)","Police Car (LVPD)","Police Ranger","Picador","S.W.A.T. Van","Alpha","Phoenix","Glendale","Sadler",
	"Luggage Trailer A","Luggage Trailer B","Stair Trailer","Boxville","Farm Plow","Utility Trailer"};
	for(new i = 0; i < 212; ++i) if (strfind(VehicleNames[i], vname, true) != -1) return i + 400;
	return -1;
}