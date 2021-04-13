	/************************************
	* Amit_B's Define Functions         *
	* Created by Amit Barami "Amit_B"   *
	* Creation Data: 13/5/2008          *
	* Version: 1.0                      *
	************************************/
#include <a_samp>
#if defined adf_included
	#endinput
#endif
new File:adfCreateFile;
#pragma unused adfCreateFile
#define adf_included
#pragma library adf
#define Your_IsPlayerAdmin_Function AdminLevel < 1
#define OP(%0) new %0 = 0; %0 < MAX_PLAYERS; %0 ++) if(IsPlayerConnected(%0)
#define OA(%0) new %0 = 0; %0 < MAX_PLAYERS; %0 ++) if(IsPlayerConnected(%0) && IsPlayerAdmin(%0)
#define OA2(%0) new %0 = 0; %0 < MAX_PLAYERS; %0 ++) if(IsPlayerConnected(%0) && Your_IsPlayerAdmin_Function(%0)
#define OA3(%0) new %0 = 0; %0 < MAX_PLAYERS; %0 ++) if(IsPlayerConnected(%0) && (Your_IsPlayerAdmin_Function(%0) || IsPlayerAdmin(%0))
#define K *1000
#define pFormat(%0,%1,%2,%3,%4) new %2[128]; format(%2,sizeof(%2),%3,%4); SendClientMessage(%0,%1,%2)
#define AllFormat(%0,%1,%2,%3) new %1[128]; format(%1,sizeof(%1),%2,%3); SendClientMessageToAll(%0,%1)
#define PlaySound(%0,%1) PlayerPlaySound(%0,%1,0.0,0.0,0.0)
#define fcreate(%0) adfCreateFile = fopen(%0,io_write); fclose(%0)
#define dexist(%0) fexist("/" %0 "/")
#define equal(%0,%1) !strcmp(%0,%1,true)
// sleep function by Xalphox, improved by me
#define sleep sleep2
stock sleep(s)
{
	assert s > 0 && s < cellmax;
	new nt[4], ot[4];
	gettime(ot[0],ot[1],ot[2]);
	ot[3] = ot[2] + (ot[1]*60) + (ot[0]*600);
	while(nt[3] != (ot[3]+seconds))
	{
	 	gettime(nt[0],nt[1],nt[2]);
		nt[3] = nt[2] + (nt[1]*60) + (nt[0]*600);
	}
}
