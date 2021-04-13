/*
	[[==========================================================]]
        [[   		   *FAC - AntiCheat System*                 ]]
	[[  Script Created By.yoNi | StricT - All Rights Reserved©  ]]
	[[                   System Version - 1.0                   ]]
	[[==========================================================]]
*/


/*[[====================[Includes]====================]]*/
	#include <a_samp>
	//#include <dini>

/*[[====================[Functions]====================]]*/
stock PlayerACFile(playerid)
{
    new f[256];
    format(f,sizeof(f),"AntiCheat/%d.ini",playerid);
    return f;
}
stock CreateACFile(playerid)
{
    dini_Create(PlayerACFile(playerid));
    dini_IntSet(PlayerACFile(playerid),"Money",0);
    return 1;
}

stock FAC_GivePlayerMoney(playerid,money)
{
dini_IntSet(PlayerACFile(playerid),"Money",money);
return GivePlayerMoney(playerid,money);
}

/*
	[[==========================================================]]
        [[                    *End of File*                         ]]
	[[  Script Created By.yoNi | StricT - All Rights Reserved©  ]]
	[[        [FAC - AntiCheat System - Version - 1.0]          ]]
	[[==========================================================]]
*/

