stock KickPlayer(playerid, adminid, reason[])
{
	new string[128],name[24],ActionName[24],fileline[128]; GetPlayerName(playerid,ActionName,24);
	if (adminid == -1) { // Server
		format(string,128,"\"%s\" has been Kicked from the server. (Reason: %s)",ActionName,reason);
		format(fileline,128,"Server kicked %s (%d) [Reason: %s]\r\n",ActionName,playerid,reason);
		SendClientMessageToAll(yellow,string);
	} else if (adminid == -2) { // RCON
		format(string,128,"\"%s\" has been Kicked from the server. (Reason: %s)",ActionName,reason);
		format(fileline,128,"RCON kicked %s (%d) [Reason: %s]\r\n",ActionName,playerid,reason);
		SendClientMessageToAll(yellow,string);
	} else { // Normal
		GetPlayerName(adminid,name,24);
		format(string,128,"\"%s\" has been Kicked from the server by Administrator \"%s\". (Reason: %s)",ActionName,name,reason);
		format(fileline,128,"%s (%d) kicked %s (%d) [Reason: %s]\r\n",name,adminid,ActionName,playerid,reason);
		SendClientMessageToAll(yellow,string);
	}
	WriteToLog("kicks",fileline);
	TogglePlayerControllable(playerid,false);
	Kick(playerid);
	return 1;
}

stock BanPlayer(playerid, adminid, reason[], days = 0)
{
	new string[128],name[24],ActionName[24],ip[20],fileline[128]; GetPlayerName(playerid,ActionName,24); GetPlayerIp(playerid,ip,20);
	if (adminid == -1) // Server
	{
		if (days)
		{
			format(string,128,"\"%s\" has been Temp-Banned by the server for %d %s. (Reason: %s)",ActionName,days,(days==1)?("day"):("days"),reason);
			format(fileline,128,"Server temp-banned %s (%d) for %d %s [Reason: %s] {IP: %s}\r\n",ActionName,playerid,days,(days==1)?("day"):("days"),reason,ip);
		}
		else
		{
			format(string,128,"\"%s\" has been Banned by the server. (Reason: %s)",ActionName,reason);
			format(fileline,128,"Server banned %s (%d) [Reason: %s] {IP: %s}\r\n",ActionName,playerid,reason,ip);
		}
		SendClientMessageToAll(yellow,string);
	}
	else if (adminid == -2) // RCON
	{
	    if (days)
	    {
			format(string,128,"\"%s\" has been Temp-Banned by the server for %d %s. (Reason: %s)",ActionName,days,(days==1)?("day"):("days"),reason);
			format(fileline,128,"RCON temp-banned %s (%d) for %d %s [Reason: %s] {IP: %s}\r\n",ActionName,playerid,days,(days==1)?("day"):("days"),reason,ip);
			SendClientMessageToAll(yellow,string);
			format(string,128,"You have been Banned by the server for %d %s. (Reason: %s)",days,(days==1)?("day"):("days"),reason);
			SendClientMessage(playerid,yellow,string);
		}
		else
		{
			format(string,128,"\"%s\" has been Banned by the server. (Reason: %s)",ActionName,reason);
			format(fileline,128,"RCON banned %s (%d) [Reason: %s] {IP: %s}\r\n",ActionName,playerid,reason,ip);
			SendClientMessageToAll(yellow,string);
			format(string,128,"You have been Banned by the server. (Reason: %s)",reason);
			SendClientMessage(playerid,yellow,string);
		}
	}
	else // Normal
	{
	    if (days)
	    {
			GetPlayerName(adminid,name,24);
			new fdays[16]; FormatDays(days, fdays);
			format(string,128,"\"%s\" has been Temp-Banned by Administrator \"%s\" for %s. (Reason: %s)",ActionName,name,fdays,reason);
			format(fileline,128,"%s (%d) temp-banned %s (%d) for %d %s [Reason: %s] {IP: %s}\r\n",name,adminid,ActionName,playerid,days,(days==1)?("day"):("days"),reason,ip);
		}
		else
		{
			GetPlayerName(adminid,name,24);
			format(string,128,"\"%s\" has been Banned by Administrator \"%s\". (Reason: %s)",ActionName,name,reason);
			format(fileline,128,"%s (%d) banned %s (%d) [Reason: %s] {IP: %s}\r\n",name,adminid,ActionName,playerid,reason,ip);
		}
		SendClientMessageToAll(yellow,string);
	}
	if (days) WriteToLog("tempbans",fileline);
	else WriteToLog("bans",fileline);
	format(string,128,"Ban Info: (Time & Date: %s) (IP: %s)",TND("ban"),ip);
	SendClientMessage(playerid,lblue,string);
	if (days)
	{
		new File:tempban = (fexist("/xap/Bans/TempBans.ban"))?fopen("/xap/Bans/TempBans.ban",io_append):fopen("/xap/Bans/TempBans.ban",io_write);
		new year, month, day; getdate(year, month, day);
		day += days;
		CorrectDate(day, month, year);
		format(fileline, 128, "%d|%d|%d|%s|%s|%s|%s|%s|%s|%s\n",
		day, month, year, TND("hour"), TND("minute"), ActionName, ip, TND("tempban"), (adminid < 0)?("*Server*"):(name), reason);
		fwrite(tempban, fileline);
		fclose(tempban);
	}
	else
	{
		new IpBanFile[128], BanFile[128];
		format(BanFile, 128, "/xap/Bans/Names/%s.ini", ActionName); format(IpBanFile, 128, "/xap/Bans/IP/%s.ini", ip);
		if (dini_Exists(BanFile) || dini_Exists(IpBanFile)) return false;
		dini_Create(BanFile);
		if (adminid < 0) dini_Set(BanFile, "Admin", "*Server*");
		else dini_Set(BanFile, "Admin", name);
		dini_Set(BanFile, "IP", ip);
		dini_Set(BanFile, "Reason", reason);
		dini_Set(BanFile, "TND", TND("ban"));
		dini_Create(IpBanFile);
		if (adminid < 0) dini_Set(IpBanFile, "Admin", "*Server*");
		else dini_Set(IpBanFile, "Admin", name);
		dini_Set(IpBanFile, "PlayerName", ActionName);
		dini_Set(IpBanFile, "Reason", reason);
		dini_Set(IpBanFile, "TND", TND("ban"));
	}
	TogglePlayerControllable(playerid,false);
	Kick(playerid);
	return 1;
}
