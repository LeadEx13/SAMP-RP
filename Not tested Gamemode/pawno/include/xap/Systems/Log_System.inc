stock FormatTime(sec, time[16])
{
    if (sec == 0)
	{
		time = "0 seconds";
		return time;
	}
    new fdecimal[16];
	new fmin[6]; format(fmin, 6, "%.1f", floatdiv(sec,60));
	new minute = (sec/60);
	new sep = strfind(fmin, ".");
	strmid(fdecimal, fmin, sep+1, strlen(fmin), 16);
	if (sec < 60) format(time, 16, "%d second%s", sec, (sec != 1)?("s"):(""));
	else
	{
		if (strval(fdecimal) == 0) format(time, 16, "%d minute%s", minute, (minute > 1)?("s"):(""));
		else format(time, 16, "%s mintue%s", fmin, (floatstr(fmin) > 1.0)?("s"):(""));
	}
	return time;
}

stock FormatDate(day, month, year)
{
	new date[32];
	new monthNames[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	format(date, 32, "%s %d, %d", monthNames[month - 1], day, year);
	return date;
}

stock TND(usage[])
{
	new tnd[128],day,month,year,hour,minute,second,hour_tf[3],minute_tf[3],second_tf[3];
	getdate(year,month,day); gettime(hour,minute,second);
	if (hour <= 9) format(hour_tf,3,"0%d",hour); else format(hour_tf,3,"%d",hour);
	if (minute <= 9) format(minute_tf,3,"0%d",minute); else format(minute_tf,3,"%d",minute);
	if (second <= 9) format(second_tf,3,"0%d",second); else format(second_tf,3,"%d",second);
	if (!strcmp(usage, "ban", true)) format(tnd,128,"%d.%d.%d | %s:%s:%s",day,month,year,hour_tf,minute_tf,second_tf);
	else if (!strcmp(usage, "logins", true)) format(tnd,128,"%s:%s",hour_tf,minute_tf);
	else if (!strcmp(usage, "hour", true)) format(tnd,128,"%s",hour_tf);
	else if (!strcmp(usage, "minute", true)) format(tnd,128,"%s",minute_tf);
	else if (!strcmp(usage, "tempban", true)) format(tnd,128,"%d/%d/%d, %s:%s",day,month,year,hour_tf,minute_tf);
	return tnd;
}

stock WriteToLog(category[], string[], playerid = -1)
{
	new tnd[128],name[24],day,month,year,hour,minute,second; GetPlayerName(playerid,name,24);
	new hour_tf[3],minute_tf[3],second_tf[3]; getdate(year,month,day); gettime(hour,minute,second);
	if (hour <= 9) format(hour_tf,3,"0%d",hour); else format(hour_tf,3,"%d",hour);
	if (minute <= 9) format(minute_tf,3,"0%d",minute); else format(minute_tf,3,"%d",minute);
	if (second <= 9) format(second_tf,3,"0%d",second); else format(second_tf,3,"%d",second);
	format(tnd,128,"[%d.%d.%d | %s:%s:%s]",day,month,year,hour_tf,minute_tf,second_tf);
	new line[128],file[128];
	if (!strcmp(category,"admin",true)) { // Admin Commands
		if(playerid == -1) return print("XAP ERROR: Can not save admin log! (invalid player ID)");
		format(file,128,"/xap/Logs/Commands/%s.log",name);
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"adminchat",true)) { // Admin Chat
	    if(playerid == -1) return print("XAP ERROR: Can not save admin chat! (invalid player ID)");
		file = "/xap/Logs/System/adminchat.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s (%d): %s\r\n",tnd,ReturnPlayerName(playerid),playerid,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"kicks",true)) { // Kicks
		file = "/xap/Logs/System/kicks.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"bans",true)) { // Bans
		file = "/xap/Logs/System/bans.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"tempbans",true)) { // Temp-Bans
		file = "/xap/Logs/System/tempbans.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"unbans",true)) { // Unbans
		file = "/xap/Logs/System/unbans.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"logins",true)) { // Logins
		file = "/xap/Logs/System/logins.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"[%d.%d.%d] %s",day,month,year,string);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"iplog",true)) { // IP Log
		new nick[128],ipadd[128],idx; nick = strtok(string,idx); ipadd = strtok(string,idx);
		format(file,128,"/xap/Logs/IP/%s.log",nick);
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s\r\n",tnd,ipadd);
		fwrite(handle,line); fclose(handle);
	} else if (!strcmp(category,"reports",true)) { // Report
		file = "/xap/Logs/System/reports.log";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,256,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
	} else printf("XAP ERROR: Can not find the log category named \"%s\"!",category);
	return true;
}