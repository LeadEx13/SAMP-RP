//--------------[INCLUDE]-------------------------
#include a_samp
//-------------[stock's]-------------------------------
stock HGiveMoney(playerid,money)
return
CallRemoteFunction("HGiveMoney","ii",playerid,money);
stock HResetMoney(playerid)
return CallRemoteFunction("HResetMoney","i",playerid);
