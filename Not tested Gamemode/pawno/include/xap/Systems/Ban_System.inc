forward CheckTempBans();
public CheckTempBans()
{
	new data[1024], load[9][64], string[128],
	ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_name[24], ban_ip[15], ban_reason[64],
	year, month, day, hour, minute, second;
	getdate(year, month, day); gettime(hour, minute, second);
	new File:file = fopen("/xap/Bans/TempBans.ban",io_read);
	if (file)
	{
		while (fread(file, data, sizeof data))
		{
			StripNewLine(data);
			split(data, load, '|');
			ban_day = strval(load[0]);
			ban_month = strval(load[1]);
			ban_year = strval(load[2]);
			ban_hour = strval(load[3]);
			ban_minute = strval(load[4]);
			strmid(ban_name, load[5], 0, strlen(load[5]), 24);
			strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
			strmid(ban_reason, load[8], 0, strlen(load[8]), 64);
			if (year >= ban_year && month >= ban_month && day >= ban_day && hour >= ban_hour && minute >= ban_minute)
			{
				UnTempBan(ban_name, 1);
				format(string,128,"Server un-temp-banned %s [Reason: %s] {IP: %s}\r\n",ban_name,ban_reason,ban_ip);
				WriteToLog("unbans",string);
			}
		}
	}
	return true;
}

/**
 *  Checks if 'string' has a ban.
 *  type = 1 is by name, type = 2 is by IP.
 *  @param   string
 *           type
 */

stock BanCheck(string[], type)
{
	if (type == 1)
	{
		new BanFile[128];
		format(BanFile, 128, "xap/Bans/Names/%s.ini", string);
		if (!dini_Exists(BanFile)) return false;
	}
	else
	{
		new IpBanFile[128];
		format(IpBanFile, 128, "xap/Bans/IP/%s.ini", string);
		if (!dini_Exists(IpBanFile)) return false;
	}
	return true;
}

/**
 *  Unbans 'string' if he has a temp-ban.
 *  type = 1 is by name, type = 2 is by IP.
 *  @param   string
 *           type
 */
stock UnTempBan(string[], type)
{
	if (!TempBanCheck(string, type)) return false;
	new data[1024], load[10][64], tmp[128], ban_name[24], ban_ip[15], File:fhandle[2], fname[2][64];
	fname[0] = "/xap/Bans/TempBans.ban";
	fname[1] = "/xap/Bans/TempBans.ban.part";
	if (!fexist(fname[0])) return false;
	fhandle[0] = fopen(fname[0],io_read);
	if (fexist(fname[1])) fremove(fname[1]);
	fhandle[1] = fopen(fname[1],io_write);
	
	if (fhandle[0] && fhandle[1])
	{
		while (fread(fhandle[0], data, sizeof data))
		{
		    StripNewLine(data);
		    if (strlen(data))
		    {
				split(data, load, '|');
				strmid(ban_name, load[5], 0, strlen(load[5]), 24);
				strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
				if ((type == 1 && strcmp(ban_name, string, false))
				|| (type == 2 && strcmp(ban_ip, string, false)))
				{
					format(tmp, 128, "%s\n", data);
					fwrite(fhandle[1], tmp);
				}
			}
		}
		fclose(fhandle[0]); fremove(fname[0]);
		fcopytextfile(fname[1], fname[0]);
	}
	fclose(fhandle[1]); fremove(fname[1]);
	return true;
}

/**
 *  Returnes the ban info of 'string' requested in 'getwhat'.
 *  type = 1 is by name, type = 2 is by IP.
 *  @param   string
 *           type
 *           getwhat
 */
stock TempBanGet(string[], type, getwhat[])
{
	new data[1024], load[10][64], returnstr[128], id = -1,
	ban_name[24], ban_ip[15], ban_tnd[20], ban_admin[24], ban_reason[64];
	
	if (!strcmp(getwhat, "day", true)) id = 0;
	else if (!strcmp(getwhat, "month", true)) id = 1;
	else if (!strcmp(getwhat, "year", true)) id = 2;
	else if (!strcmp(getwhat, "hour", true)) id = 3;
	else if (!strcmp(getwhat, "minute", true)) id = 4;
	else if (!strcmp(getwhat, "name", true)) id = 5;
	else if (!strcmp(getwhat, "ip", true)) id = 6;
	else if (!strcmp(getwhat, "tnd", true)) id = 7;
	else if (!strcmp(getwhat, "admin", true)) id = 8;
	else if (!strcmp(getwhat, "reason", true)) id = 9;
	
	new File:file = fopen("/xap/Bans/TempBans.ban",io_read);
	if (file)
	{
		while (fread(file, data, sizeof data))
		{
			StripNewLine(data);
			split(data, load, '|');
			strmid(ban_name, load[5], 0, strlen(load[5]), 24);
			strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
			strmid(ban_reason, load[7], 0, strlen(load[7]), 20);
			strmid(ban_admin, load[8], 0, strlen(load[8]), 24);
			strmid(ban_reason, load[9], 0, strlen(load[9]), 64);
			if ((type == 1 && !strcmp(ban_name, string, false)) || (type == 2 && !strcmp(ban_ip, string, false)))
			{
				switch (id)
				{
					case 0 .. 2: format(returnstr, 128, "%d", strval(load[id]));
					case 3 .. 4: format(returnstr, 128, "%s", CorrectTime(strval(load[id])));
					case 5: format(returnstr, 128, ban_name);
					case 6: format(returnstr, 128, ban_ip);
					case 7: format(returnstr, 128, ban_tnd);
					case 8: format(returnstr, 128, ban_admin);
					case 9: format(returnstr, 128, ban_reason);
					default: format(returnstr, 128, "");
				}
			}
		}
	}
	return returnstr;
}

/**
 *  Checks if 'string' has a temp-ban.
 *  type = 1 is by name, type = 2 is by IP.
 *  @param   string
 *           type
 */
stock TempBanCheck(string[], type)
{
	new data[1024], load[10][64];
	new ban_name[24], ban_ip[15];
	new File:file = fopen("/xap/Bans/TempBans.ban",io_read);
	if (file)
	{
		while (fread(file, data, sizeof data))
		{
			StripNewLine(data); split(data, load, '|');
			strmid(ban_name, load[5], 0, strlen(load[5]), 24);
			strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
			if (type == 1 && !strcmp(ban_name, string, false)) return true;
			else if (type == 2 && !strcmp(ban_ip, string, false)) return true;
		}
	}
	return false;
}

/**
 *  Updating 'bannedname' 's IP to 'newip' in TempBans.ban
 *  @param   bannedname
 *           newip
 */
stock UpdateTempBan(bannedname[], newip[])
{
	if (!TempBanCheck(bannedname, 1)) return false;
	new data[1024], load[10][64], tmp[128], File:fhandle[2], fname[2][64],
	ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_name[24], ban_ip[15], ban_tnd[20], ban_admin[24], ban_reason[64];
	fname[0] = "/xap/Bans/TempBans.ban";
	fname[1] = "/xap/Bans/TempBans.ban.part";
	fhandle[0] = fopen(fname[0],io_read);
	if (fexist(fname[1])) fremove(fname[1]);
	fhandle[1] = fopen(fname[1],io_write);
	
	if (fhandle[0] && fhandle[1])
	{
		while (fread(fhandle[0], data, sizeof data))
		{
		    StripNewLine(data);
		    if (strlen(data))
		    {
				split(data, load, '|');
				ban_day = strval(load[0]);
				ban_month = strval(load[1]);
				ban_year = strval(load[2]);
				ban_hour = strval(load[3]);
				ban_minute = strval(load[4]);
				strmid(ban_name, load[5], 0, strlen(load[5]), 24);
				strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
				strmid(ban_tnd, load[7], 0, strlen(load[7]), 20);
				strmid(ban_admin, load[8], 0, strlen(load[8]), 24);
				strmid(ban_reason, load[9], 0, strlen(load[9]), 64);
				if (strcmp(ban_name, bannedname, false))
					format(tmp, 128, "%d|%d|%d|%s|%s|%s|%s|%s|%s|%s\n", ban_day, ban_month, ban_year, ban_hour, ban_minute,
					ban_name, newip, ban_tnd, ban_admin, ban_reason);
				else format(tmp, 128, "%s\n\n", data);
				fwrite(fhandle[1], tmp);
			}
		}
		fclose(fhandle[0]); fremove(fname[0]);
		fcopytextfile(fname[1], fname[0]);
	}
	fclose(fhandle[1]); fremove(fname[1]);
	return true;
}

/**
 *  Checks if 'playerid' has a temp-ban. (OnPlayerConnect)
 *  @param   playerid
 */
stock Connect_TempBanCheck(playerid)
{
	new name[24], ip[16], string[128], data[1024], load[10][64];
	new ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_name[24], ban_ip[15], ban_tnd[20], ban_admin[24], ban_reason[64];
	GetPlayerName(playerid, name, 24); GetPlayerIp(playerid, ip, 16);
	new year, month, day, hour, minute, second;
	getdate(year, month, day); gettime(hour, minute, second);
	new File:file = fopen("/xap/Bans/TempBans.ban",io_read);
	if (file)
	{
		while (fread(file, data, sizeof data))
		{
			StripNewLine(data);
			split(data, load, '|');
			ban_day = strval(load[0]);
			ban_month = strval(load[1]);
			ban_year = strval(load[2]);
			ban_hour = strval(load[3]);
			ban_minute = strval(load[4]);
			strmid(ban_name, load[5], 0, strlen(load[5]), 24);
			strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
			strmid(ban_tnd, load[7], 0, strlen(load[7]), 20);
			strmid(ban_admin, load[8], 0, strlen(load[8]), 24);
			strmid(ban_reason, load[9], 0, strlen(load[9]), 64);
			if (!strcmp(ban_ip, ip, false) || !strcmp(ban_name, name, false))
			{
				if (!(year >= ban_year && month >= ban_month && day >= ban_day && hour >= ban_hour && minute >= ban_minute))
				{
					if (strcmp(ban_ip, ip, false)) UpdateTempBan(ban_name, ip);
					SendClientMessage(playerid,red,"You are banned from this server.");
					format(string, 128, "Ban Info: (Admin: %s) (Player: %s) (IP: %s) (Date & Time: %s)", ban_admin, name, ip, ban_tnd);
					SendClientMessage(playerid,lblue,string);
					format(string, 128, "Ban Info: (Unban Date & Time: %d/%d/%d, %s:%s) (Reason: %s)",
					ban_day, ban_month, ban_year, CorrectTime(ban_hour), CorrectTime(ban_minute), ban_reason);
					SendClientMessage(playerid,lblue,string);
					Kick(playerid);
					return 1;
				}
				else if (year >= ban_year && month >= ban_month && day >= ban_day && hour >= ban_hour && minute >= ban_minute)
					UnTempBan(ban_name, 1);
			}
		}
	}
	return true;
}

/**
 *  Sends ban info on 'string' to 'playerid'.
 *  type = 1 is by name, type = 2 is by IP.
 *  @param   playerid
 *           string
 *           type
 */
stock TempBanInfo(playerid, string[], type)
{
	new str[128], data[1024], load[10][64];
	new ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_name[24], ban_ip[15], ban_tnd[20], ban_admin[24], ban_reason[64];
	new File:file = fopen("/xap/Bans/TempBans.ban",io_read);
	if (file)
	{
		while (fread(file, data, sizeof data))
		{
			StripNewLine(data);
			split(data, load, '|');
			ban_day = strval(load[0]);
			ban_month = strval(load[1]);
			ban_year = strval(load[2]);
			ban_hour = strval(load[3]);
			ban_minute = strval(load[4]);
			strmid(ban_name, load[5], 0, strlen(load[5]), 24);
			strmid(ban_ip, load[6], 0, strlen(load[6]), 15);
			strmid(ban_tnd, load[7], 0, strlen(load[7]), 20);
			strmid(ban_admin, load[8], 0, strlen(load[8]), 24);
			strmid(ban_reason, load[9], 0, strlen(load[9]), 64);
			if (type == 1 && !strcmp(ban_name, string, false))
			{
				format(str, 128, "Ban Info: (Player: %s) (Admin: %s) (IP: %s) (Date & Time: %s)", ban_name, ban_admin, ban_ip, ban_tnd);
				SendClientMessage(playerid,lblue,str);
				format(str, 128, "Ban Info: (Unban Date & Time: %d/%d/%d, %d:%d) (Reason: %s)",
				ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_reason);
				return SendClientMessage(playerid,lblue,str);
			}
			else if (type == 2 && !strcmp(ban_ip, string, false))
			{
				format(str, 128, "Ban Info: (Player: %s) (Admin: %s) (IP: %s)", ban_name, ban_admin, ban_ip);
				SendClientMessage(playerid,lblue,string);
				format(str, 128, "Ban Info: (Unban Date & Time: %d/%d/%d, %d:%d) (Reason: %s)",
				ban_day, ban_month, ban_year, ban_hour, ban_minute, ban_reason);
				return SendClientMessage(playerid,lblue,str);
			}
			else return SendClientMessage(playerid, red, "This player is not banned.");
		}
	}
	return true;
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li, aNum, len;
	while (i <= strlen(strsrc))
	{
		if (strsrc[i] == delimiter || i == strlen(strsrc))
		{
			len = strmid(strdest[aNum], strsrc, li, i, 128);
			strdest[aNum][len] = 0;
			li = i+1;
			aNum++;
		}
		i++;
	}
	return 1;
}

stock CorrectDate(&day, &month, &year)
{
	if (IsMonth31(month))
	{
		if (day > 31)
		{
			month += 1;
			if (month > 12)
			{
				year += 1;
				while(day > 31) day -= 31;
			}
			else while(day > 31) day -= 31;
		}
	}
	else if (!IsMonth31(month))
	{
		if (day > 30)
		{
			month += 1;
			if (month > 12)
			{
				year += 1;
				while(day > 30) day -= 30;
			}
			else while(day > 30) day -= 30;
		}
	}
	else if (!IsMonth31(month) && IsMonth29(year) && month == 2)
	{
		if (day > 29)
		{
			month += 1;
			if (month > 12)
			{
				year += 1;
				while(day > 29) day -= 29;
			}
			else while(day > 29) day -= 29;
		}
	}
	else if (!IsMonth31(month) && !IsMonth29(year) && month == 2)
	{
		if (day > 28)
		{
			month += 1;
			if (month > 12)
			{
				year += 1;
				while(day > 28) day -= 28;
			}
			else while(day > 28) day -= 28;
		}
	}
	return true;
}

stock IsMonth31(month)
{
	switch (month)
	{
		case 1, 3, 5, 7, 8, 10, 12: return 1;
		default: return 0;
	}
	return 0;
}

stock IsMonth29(year)
{
        new y = 2000;
        for(new i = 4; i < 3000; i += 4) if ((y+i) == year) return 1;
        return 0;
}

stock CorrectTime(value)
{
	new value_tf[3];
	if (value <= 9) format(value_tf,3,"0%d",value); else format(value_tf,3,"%d",value);
	return value_tf;
}

stock FormatDays(days, output[16])
{
	new weeks, daysafterweeks;
	if (days == 0)
	{
		output = "0 days";
		return output;
	}
	else if (days == 1)
	{
		output = "1 day";
		return output;
	}
	else if (days > 1)
	{
		format(output, 16, "%d days", days);
		return output;
	}
	else if (days % 7 == 0)
	{
		weeks = (days / 7);
		format(output, 16, "%d week%s", weeks, (weeks > 1)?("s"):(""));
	}
	else
	{
		weeks = (days / 7);
		daysafterweeks = (days - ((days / 7) * 7));
		format(output, 16, "%d week%s and %d day%s", weeks, (weeks > 1)?("s"):(""), daysafterweeks, (daysafterweeks > 1)?("s"):(""));
	}
	return output;
}