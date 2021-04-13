/*
 ==========================================
||         Fux-c.co.il Mode Inc.          ||
||     Mode & Include Created By Naor.    ||
||       Msn: NaorDesign@Hotmail.com      ||
||         Naor Copyright (c) 2009.       ||
 ==========================================
*/
//============ [ Settings ] ================
#include <a_samp>
#tryinclude <dini>
#pragma tabsize 0

//============ [ Colors ] ==================

#define COLOR_INV 0xFFFFFF00
#define WHITE 0xFFFFFFAA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_SPAWN 0xFF8C55FF
#define COLOR_LIGHTBLUE 0x6DC5F3FF
#define COLOR_ADMIN 0xFF0000FF
#define COLOR_SAY 0x2986CEFF
#define COLOR_SYSGREY 0xC6BEBDFF
#define COLOR_BLACK 0x000000FF
#define COLOR_JOIN 0x74E80099
#define COLOR_WARN 0xBE615099
#define COLOR_RACE 0x00BBBB99
#define COLOR_KRED 0xFF0000FF
#define COLOR_LIGHTGREEN 0x24FF0AB9
#define COLOR_PURPLE 0x330066AA
#define COLOR_PINK 0xFF66FFAA
#define COLOR_BLUE 0x0000BBAA
#define COLOR_LIGHTRED 0xFF99AADD
#define COLOR_DARKGREY 0x333333AA 
#define COLOR_DARKRED 0x990000AA
#define COLOR_INDIGO 0x4B00B0AA 
#define COLOR_AQUA 0x7CFC00AA 
#define COLOR_BRIGHTRED 0xDC143CAA 
#define COLOR_SYSTEM 0xEFEFF7AA 
#define COLOR_GRAY 0xAFAFAFAA 
#define COLOR_BLUEGREEN 0x46BBAA00 
#define COLOR_CYAN 0x00FFFFAA 
#define COLOR_VIOLET 0x9955DEEE 
#define COLOR_LEMON 0xDDDD2357 
#define COLOR_BLUEWHITE 0x99FFFFAA
#define COLOR_LIGHTCYAN 0xAAFFCC33
#define COLOR_DARKBLUE 0x300FFAAB 
#define COLOR_BROWN 0x993300AA
#define COLOR_GRAYWHITE 0xEEEEFFC4
#define COLOR_DARKGREEN 0x12900BBF
#define COLOR_PEACH 0xEECFA1AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_SPAWN 0xFF8C55FF
#define COLOR_ADMIN 0xFF0000FF
#define COLOR_SAY 0x2986CEFF
#define COLOR_SYSGREY 0xC6BEBDFF
#define COLOR_BLACK 0x000000FF
#define COLOR_JOIN 0x74E80099
#define COLOR_WARN 0xBE615099
#define COLOR_RACE 0x00BBBB99
#define COLOR_KRED 0xFF0000FF
#define COLOR_LCY 0xAAFFCC33
#define COLOR_CYAN 0x00FFFFAA 
#define green	0x16EB43FF
#define green2	0x008D00AA
#define green3	0x006400AA
#define blue	0x005EECAA
#define cblue	0x6495EDAA
#define red		0xFF0000AA
#define orange	0xFF9900AA
#define lblue	0x00FFFFAA
#define yellow	0xFFFF00AA
#define green	0x16EB43FF
#define green2	0x008D00AA
#define green3	0x006400AA
#define lgreen	0x2CCC99FF
#define red		0xFF0000AA
#define darkred	0x800000FF
#define white	0xFFFFFFAA
#define pink	0xCCFF00FFAA
#define purple	0x8B00A0FF
#define grey	0xC0C0C0AA
#define ppmsc	0xA448FFFF
//============ [ Stocks ] ==================
//
 stock rgba2hex(r,g,b,a) return (r*16777216) + (g*65536) + (b*256) + a;
//
//==============================================================================
/* native TeleportPlayer(playerid, telename[], Float:Vx, Float:Vy, Float:Vz, Float:Va, Float:Px, Float:Py, Float:Pz, Float:Pa, interior);  */
//==============================================================================

stock TeleportPlayer(playerid, telename[], Float:Vx, Float:Vy, Float:Vz, Float:Va, Float:Px, Float:Py, Float:Pz, Float:Pa, interior){
    new Message[128];
    format(Message, sizeof(Message), "%s", telename);
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        SetVehiclePos(GetPlayerVehicleID(playerid),Vx,Vy,Vz);
	SetVehicleZAngle(GetPlayerVehicleID(playerid),Va);
	SetCameraBehindPlayer(playerid);
	LinkVehicleToInterior(GetPlayerVehicleID(playerid),interior);
	}else{
	SetPlayerPos(playerid,Px,Py,Pz);
	SetPlayerFacingAngle(playerid,Pa);
	SetCameraBehindPlayer(playerid);
	}
	SetPlayerInterior(playerid, interior);
        SendClientMessage(playerid,COLOR_YELLOW,Message);
        PlayerPlaySound(playerid,1056, 0.0, 0.0, 0.0);
	return 1;
}
//==============================================================================
/* native TeleportPlayerNoV(playerid,telename[],Float:Plx, Float:Ply, Float:Plz, Float:Pla,interior); */
//==============================================================================

stock TeleportPlayerNoV(playerid,telename[],Float:Plx, Float:Ply, Float:Plz, Float:Pla,interior){
    new Message[128];
    format(Message, sizeof(Message), "%s", telename);
    SetPlayerPos(playerid,Plx,Ply,Plz);
    if(Pla != -1)SetPlayerFacingAngle(playerid,Pla);
    SetCameraBehindPlayer(playerid);
    SetPlayerInterior(playerid, interior);
    SendClientMessage(playerid,COLOR_YELLOW,Message);
    PlayerPlaySound(playerid,1056, 0.0, 0.0, 0.0);
    return 1;
}
//==============================================================================
/* native HqTeleport(playerid, Float:Vx, Float:Vy, Float:Vz, Float:Va, Float:Px, Float:Py, Float:Pz, Float:Pa, interior); */
//==============================================================================

stock HqTeleport(playerid, Float:Vx, Float:Vy, Float:Vz, Float:Va, Float:Px, Float:Py, Float:Pz, Float:Pa, interior){
    new Message[128],name[24];
    GetPlayerName(playerid,name, sizeof(name));

    format(Message,sizeof(Message),".%s - ברוך הבא אל מפקדת הקלאן שלך",dini_Get(PlayerFile(name),"Clan"));
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
        SetVehiclePos(GetPlayerVehicleID(playerid),Vx,Vy,Vz);
        SetVehicleZAngle(GetPlayerVehicleID(playerid),Va);
	SetCameraBehindPlayer(playerid);
	LinkVehicleToInterior(GetPlayerVehicleID(playerid),interior);
	}else{
	SetPlayerPos(playerid,Px,Py,Pz);
	SetPlayerFacingAngle(playerid,Pa);
	SetCameraBehindPlayer(playerid);
	}
	SetPlayerInterior(playerid, interior);
	SendClientMessage(playerid,COLOR_ORANGE, Message);
	format(Message,sizeof(Message),"~R~Welcome To - ~G~~H~%s ~R~Hq!",dini_Get(PlayerFile(name),"Clan"));
        GameTextForPlayer(playerid,Message,2500,4);
	return 1;
}
//=========================================================================================================================================================
/* native ReturnPlayerID(PlayerName[]); */
//==============================================================================

stock ReturnPlayerID(PlayerName[]) {
    for(new i = 0; i < GetMaxPlayers(); i++) if(IsPlayerConnected(i)) { new name[24]; GetPlayerName(i,name,24); if(strfind(name,PlayerName,true)!=-1) return i; }
    return INVALID_PLAYER_ID;
}

//==============================================================================
/* native ClanError(playerid,level); */ 
//==============================================================================

stock ClanError(playerid,level)
{
    if(level == 3)return SendClientMessage(playerid, COLOR_WHITE," [Clan Error] פקודה זו החל מרמת קלאן 3");
    if(level == 2)return SendClientMessage(playerid, COLOR_WHITE," [Clan Error] פקודה זו החל מרמת קלאן 2");
    return SendClientMessage(playerid, COLOR_WHITE," [Clan Error] .אינך מורשה לפקודה זו");
}
//==============================================================================
/* native LevelError(playerid,level); */ 
//==============================================================================

stock LevelError(playerid,level)
{
    new lString[256];  
    format(lString, sizeof(lString),".%d פקודה זו ניתנת לשימוש החל מרמה #",level);
    return SendClientMessage(playerid,COLOR_KRED,lString);
}

//==============================================================================
/* native PlayerFile(playerid); */
//==============================================================================

stock PlayerFile(name[]) {
    new string[256];
    format(string,sizeof(string),"/Users/%s.txt",name);
    return string;
}
//==============================================================================
/* GetPlayerLevel(playerid); */
//==============================================================================

stock GetPlayerLevel(name[])return dini_Int(PlayerFile(name),"Level");

//==============================================================================
/* native SetPlayerPosEx(playerid,Float:X,Float:Y,Float:Z,Float:A); */ 
//==============================================================================

stock SetPlayerPosEx(playerid,Float:X,Float:Y,Float:Z,Float:A)return SetPlayerPos(playerid,X,Y,Z),SetPlayerFacingAngle(playerid,A);

//==============================================================================
/* native WriteToServerLog(category[], string[]); */
//==============================================================================

stock WriteToServerLog(category[], string[]) {
	new tnd[128],day,month,year,hour,minute,second;
	new hour_tf[3],minute_tf[3],second_tf[3]; getdate(year,month,day); gettime(hour,minute,second);
	if (hour <= 9) format(hour_tf,3,"0%d",hour); else format(hour_tf,3,"%d",hour);
	if (minute <= 9) format(minute_tf,3,"0%d",minute); else format(minute_tf,3,"%d",minute);
	if (second <= 9) format(second_tf,3,"0%d",second); else format(second_tf,3,"%d",second);
	format(tnd,128,"[%d.%d.%d | %s:%s:%s]",day,month,year,hour_tf,minute_tf,second_tf);
	new line[512],file[128];
	if (!strcmp(category,"Commands",true)) {
		file = "/ServerFiles/Commands.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"Pms",true)) {
		file = "/ServerFiles/Pms.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"Gangs",true)) {
		file = "/ServerFiles/Gangs.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
        } else if (!strcmp(category,"Clans",true)) {
		file = "/ServerFiles/Clans.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"Phone",true)) {
		file = "/ServerFiles/Phones.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"Chat",true)) {
		file = "/ServerFiles/Chat.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"Kills&Deaths",true)) {
		file = "/ServerFiles/Kills&Deaths.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else if (!strcmp(category,"BoughtCars",true)) {
		file = "/ServerFiles/BoughtCars.txt";
		new File:handle = (fexist(file))?fopen(file,io_append):fopen(file,io_write);
		format(line,512,"%s %s",tnd,string);
		fwrite(handle,line); fclose(handle);
		
	} else printf("ERROR: Can not find the log category named \"%s\"!",category);
	return 1;
}

//==============================================================================
/* native Wait(time) */
//==============================================================================

stock Wait(time) { new stamp = tickcount(); while (tickcount() - stamp < time) { } return 1; }

//==============================================================================
/* native SendClientMessageToAllEx(playerid, color ,text[]); */
//==============================================================================

stock SendClientMessageToAllEx(playerid, color ,text[]) { for(new i=0;i<GetMaxPlayers();i++) if(IsPlayerConnected(i)&&i!=playerid) SendClientMessage(i,color,text); }

//==============================================================================
/* native IsNickVaild(const nick[]); */
//==============================================================================
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

//==============================================================================
/* native IsXAdmin(playerid); */
//==============================================================================
stock IsPlayerXAdmin(playerid)
{
	new file[64], name[24]; GetPlayerName(playerid, name, 24);
	format(file, 64, "xadmin/Users/%s.ini", udb_encode(name));
	if(dini_Int(file, "Level") >= 1 && dini_Int(file, "LoggedIn") == 1) return true;
	else return false;
}
//==============================================================================
/* native xLevel(playerid) */
//==============================================================================
stock xLevel(playerid)
{
	new file[64], name[24]; GetPlayerName(playerid, name, 24);
	format(file, 64, "xaadmin/Users/%s.ini", udb_encode(name));
	return dini_Int(file, "Level");
}
//==============================================================================
/* native SetAlpha(color, alpha ); */
//==============================================================================

stock SetAlpha( color, alpha ) // Set the alpha intensity on a colour.
{
	if ( alpha > 0xFF )
	    alpha	= 0xFF;
	else if ( alpha < 0x00 )
	    alpha	= 0x00;

	return ( color & 0xFFFFFF00 ) | alpha;
}

//==============================================================================
/* native IsVaidText(text[]); */
//==============================================================================
stock IsVaildText(text[])
{
    new Check[2] = 0,len = strlen(text);
    for(new text_leg = 0; text_leg < len; text_leg++)
	{
      if(text[text_leg] == '.' || text[text_leg] == ':' || text[text_leg] == ' '
      || text[text_leg] == '*' || text[text_leg] == '/' || text[text_leg] == '''
      || text[text_leg] == '_' || text[text_leg] == '-' || text[text_leg] == '!'
      || text[text_leg] == '@' || text[text_leg] == '#' || text[text_leg] == '$'
      || text[text_leg] == '%' || text[text_leg] == '^' || text[text_leg] == '&'
	  || text[text_leg] == '(' || text[text_leg] == ')' || text[text_leg] == '~'
	  || text[text_leg] == '`' || text[text_leg] == '<' || text[text_leg] == '>'
	  || text[text_leg] == ',' || text[text_leg] == '|' || text[text_leg] == ';'
	  || text[text_leg] == '?' || text[text_leg] == '=' || text[text_leg] == '['
	  || text[text_leg] == ']' || text[text_leg] == '{' || text[text_leg] == '}')
	  {
	  Check[0]++;
	  }

      if(text[text_leg] == '0' || text[text_leg] == '1' || text[text_leg] == '2' || text[text_leg] == '3'
      || text[text_leg] == '4' || text[text_leg] == '5' || text[text_leg] == '6' || text[text_leg] == '7'
      || text[text_leg] == '8' || text[text_leg] == '9')
	  {
      Check[1]++;
      }

    }
    if(Check[0]  >= 3 && Check[1] >= 8)return false;   
    return true;
}
/*
stock IsVaildText(text[])
{
    new Check[2] = 0;
    new len = strlen(text);
    for(new text_leg = 0; text_leg < len; text_leg++)
	{

    if(text[text_leg] == '.' || text[text_leg] == ':' || text[text_leg] == ' ' || text[text_leg] == '*' 
      || text[text_leg] == '/' || text[text_leg] == '_' || text[text_leg] == '-'
      || text[text_leg] == 'X' || text[text_leg] == '@' || text[text_leg] == '!'
      || text[text_leg] == '#' || text[text_leg] == '|' || text[text_leg] == '~' ||){ Check[0]++; }

    if(text[text_leg] == '0' || text[text_leg] == '1' || text[text_leg] == '2' || text[text_leg] == '3' || text[text_leg] == '4'
       || text[text_leg] == '5' || text[text_leg] == '6' || text[text_leg] == '7' || text[text_leg] == '8' || text[text_leg] == '9'){ Check[1]++; }

    }
    if(Check[0]  >= 3 && Check[1] >= 8)return 0;
    return 1;
}
*/

//==============================================================================
/* native PlayerPlaySoundToAll(soundid); */
//==============================================================================

stock PlayerPlaySoundToAll(soundid){
for(new i = 0; i < GetMaxPlayers(); i++)if(IsPlayerConnected(i))PlayerPlaySound(i,soundid, 0.0, 0.0, 0.0);
return 1;
}

//==============================================================================
/* native GetName(playerid); */
//==============================================================================

stock GetName(playerid)
{
	new pName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pName, sizeof(pName));
	return pName;
}

//==============================================================================
/* native strval_fix(string[]); */
//==============================================================================

stock strval_fix(string[]) return strlen(string) > 49? 0 : strval(string);

//==============================================================================
/* native fsearch(filename[], search[], bool:caps = false); */
//==============================================================================

stock fsearch(filename[], search[], bool:caps = false)
{
new File:fhandle = fopen(filename, io_read);
new temp[255];
while(fread(fhandle, temp))
{
StripNewLine(temp);
if (equal(temp, search, caps)) return true;
}
return false;
}

//==============================================================================
/* native RemoveAllPlayersFromVehicle(vehicleID); */
//==============================================================================

stock RemoveAllPlayersFromVehicle(vehicleID){for(new i; i<MAX_PLAYERS; i++){ if(IsPlayerConnected(i)){ if(IsPlayerInVehicle(i, vehicleID)){RemovePlayerFromVehicle(i);}}}}

//==============================================================================
/* native IsPlayerInArea2(playerid, Float:minx, Float:miny, Float:maxx, Float:maxy);
//==============================================================================
stock IsPlayerInArea2(playerid, Float:minx, Float:miny, Float:maxx, Float:maxy)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if (x > minx && x < maxx && y > miny && y < maxy) return 1;
    return 0;
}


stock GetHealth(playerid)
{
new Float:PlayerHealth;
GetPlayerHealth(playerid,PlayerHelath);
return PlayerHealth;
}

stock GetArmour(playerid)
{
new Float:PlayerArmour;
GetPlayerHealth(playerid,PlayerArmour);
return PlayerArmour;
}