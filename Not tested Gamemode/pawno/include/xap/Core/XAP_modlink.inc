#include <dudb>
#include <dini>

stock IsPlayerXAdmin(playerid)
{
	new file[64], name[24]; GetPlayerName(playerid, name, 24);
	format(file, 64, "xap/Users/%s.ini", udb_encode(name));
	if(dini_Int(file, "Level") >= 1 && dini_Int(file, "LoggedIn") == 1) return true;
	else return false;
}

stock xLevel(playerid)
{
	new file[64], name[24]; GetPlayerName(playerid, name, 24);
	format(file, 64, "xap/Users/%s.ini", udb_encode(name));
	return dini_Int(file, "Level");
}