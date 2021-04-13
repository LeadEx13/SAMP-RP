stock ShowCommandsForAdmin(playerid)
{
	new lvl = Variables[playerid][Level];
	new CList[14][COMMANDS_PER_LEVEL_COUNT][16], count[14] = 0;
	for (new i = 0; i < COMMANDS_COUNT; ++i)
	{
		new level = CommandsList[i][CL_LVL];
		if (count[level-1] > COMMANDS_PER_LEVEL_COUNT-1)
		{
			new string[128];
			format(string,128,"FATAL ERROR: The number of commands in level %d (count[%d]) is higher than %d!",level,level-1,COMMANDS_PER_LEVEL_COUNT);
			return SendClientMessage(playerid,red,string);
		}
		format(CList[level-1][count[level-1]], 16, CommandsList[i][CL_CMD]);
		count[level-1]++;
	}
	
	new bool:First[14], LineSum[9], LineIndex = 0, InfoString[1024];
	for (new i = 0; i < lvl; ++i)
	{
		First[i] = true;
		for (new j = 0; j < COMMANDS_PER_LEVEL_COUNT; ++j)
		{
			if (strlen(CList[i][j]))
			{
				if (First[i])
				{
					if (LineSum[LineIndex]+5+strlen(CList[i][j]) > 128)
					{
						format(InfoString, 1024, "%s\r\n[%d] %s", InfoString, i+1, CList[i][j]);
						LineIndex++;
						LineSum[LineIndex] += (5+strlen(CList[i][j]));
					}
					else
					{
						if (!strlen(InfoString)) format(InfoString, 1024, "%s[%d] %s", InfoString, i+1, CList[i][j]);
						else format(InfoString, 1024, "%s [%d] %s", InfoString, i+1, CList[i][j]);
						LineSum[LineIndex] += (6+strlen(CList[i][j]));
					}
					First[i] = false;
				}
				else
				{
					if (LineSum[LineIndex]+5+strlen(CList[i][j]) > 128)
					{
						format(InfoString, 1024, "%s\r\n[%d] %s", InfoString, i+1, CList[i][j]);
						LineIndex++;
						LineSum[LineIndex] += (5+strlen(CList[i][j]));
					}
					else
					{
						format(InfoString, 1024, "%s,%s", InfoString, CList[i][j]);
						LineSum[LineIndex] += (1+strlen(CList[i][j]));
					}
				}
			}
		}
	}
	new caption[64]; format(caption,64,"Commands List: (Level: %d)",lvl);
	ShowPlayerDialog(playerid, 30423, DIALOG_STYLE_MSGBOX, caption, InfoString, "OK", "");
	return 1;
}