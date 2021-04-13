/* MyGameText By RoiKy */
#include <a_samp>
new Text: MyText[4];
new Text: MyTextPlayer[MAX_PLAYERS][4];

forward GameTextForAllDestroy1();
forward GameTextForAllDestroy2();
forward GameTextForAllDestroy3();
forward GameTextForAllDestroy4();
forward GameTextForPlayerDestroy1(playerid);
forward GameTextForPlayerDestroy2(playerid);
forward GameTextForPlayerDestroy3(playerid);
forward GameTextForPlayerDestroy4(playerid);

public GameTextForAllDestroy1() return TextDrawDestroy(MyText[0]);
public GameTextForAllDestroy2() return TextDrawDestroy(MyText[1]);
public GameTextForAllDestroy3() return TextDrawDestroy(MyText[2]);
public GameTextForAllDestroy4() return TextDrawDestroy(MyText[3]);
public GameTextForPlayerDestroy1(playerid) return TextDrawDestroy(MyTextPlayer[playerid][0]);
public GameTextForPlayerDestroy2(playerid) return TextDrawDestroy(MyTextPlayer[playerid][1]);
public GameTextForPlayerDestroy3(playerid) return TextDrawDestroy(MyTextPlayer[playerid][2]);
public GameTextForPlayerDestroy4(playerid) return TextDrawDestroy(MyTextPlayer[playerid][3]);

stock MyGameTextForAll(Message[],Seconds,Style)
{
	switch(Style)
	{
	    case 1:
	    {

			MyText[0] = TextDrawCreate(296.000000, 380.000000, Message);
			TextDrawBackgroundColor(MyText[0], 255);
			TextDrawFont(MyText[0], 2);
			TextDrawLetterSize(MyText[0], 0.539999, 2.100000);
			TextDrawColor(MyText[0], -1);
			TextDrawSetOutline(MyText[0], 0);
			TextDrawSetProportional(MyText[0], 1);
			TextDrawSetShadow(MyText[0], 1);
			TextDrawShowForAll(MyText[0]);
			SetTimer("GameTextForAllDestroy1",Seconds*1000,0);
	    }
	    case 2:
	    {
			MyText[1] = TextDrawCreate(62.000000, 425.000000, Message);
			TextDrawBackgroundColor(MyText[1], 255);
			TextDrawFont(MyText[1], 1);
			TextDrawLetterSize(MyText[1], 0.519999, 1.500000);
			TextDrawColor(MyText[1], -1);
			TextDrawSetOutline(MyText[1], 0);
			TextDrawSetProportional(MyText[1], 1);
			TextDrawSetShadow(MyText[1], 1);
			TextDrawShowForAll(MyText[1]);
			SetTimer("GameTextForAllDestroy2",Seconds*1000,0);
	    }
	    case 3:
	    {
			MyText[2] = TextDrawCreate(505.000000, 110.000000, Message);
			TextDrawBackgroundColor(MyText[2], 255);
			TextDrawFont(MyText[2], 0);
			TextDrawLetterSize(MyText[2], 1.039999, 2.999999);
			TextDrawColor(MyText[2], -1);
			TextDrawSetOutline(MyText[2], 0);
			TextDrawSetProportional(MyText[2], 1);
			TextDrawSetShadow(MyText[2], 1);
			TextDrawShowForAll(MyText[2]);
			SetTimer("GameTextForAllDestroy3",Seconds*1000,0);
	    }
	    case 4:
	    {
			MyText[3] = TextDrawCreate(285.000000, 166.000000, Message);
			TextDrawBackgroundColor(MyText[3], 255);
			TextDrawFont(MyText[3], 3);
			TextDrawLetterSize(MyText[3], 0.699999, 2.799999);
			TextDrawColor(MyText[3], -1);
			TextDrawSetOutline(MyText[3], 0);
			TextDrawSetProportional(MyText[3], 1);
			TextDrawSetShadow(MyText[3], 1);
			TextDrawShowForAll(MyText[3]);
			SetTimer("GameTextForAllDestroy4",Seconds*1000,0);
	    }
	}
	return true;
}
stock MyGameTextForPlayer(playerid,Message[],Seconds,Style)
{
	switch(Style)
	{
	    case 1:
	    {

			MyTextPlayer[playerid][0] = TextDrawCreate(296.000000, 380.000000, Message);
			TextDrawBackgroundColor(MyTextPlayer[playerid][0], 255);
			TextDrawFont(MyTextPlayer[playerid][0], 2);
			TextDrawLetterSize(MyTextPlayer[playerid][0], 0.539999, 2.100000);
			TextDrawColor(MyTextPlayer[playerid][0], -1);
			TextDrawSetOutline(MyTextPlayer[playerid][0], 0);
			TextDrawSetProportional(MyTextPlayer[playerid][0], 1);
			TextDrawSetShadow(MyTextPlayer[playerid][0], 1);
			TextDrawShowForPlayer(playerid,MyTextPlayer[playerid][0]);
			SetTimerEx("GameTextForPlayerDestroy1",Seconds*1000,0,"i",playerid);
	    }
	    case 2:
	    {
			MyTextPlayer[playerid][1] = TextDrawCreate(62.000000, 425.000000, Message);
			TextDrawBackgroundColor(MyTextPlayer[playerid][1], 255);
			TextDrawFont(MyTextPlayer[playerid][1], 1);
			TextDrawLetterSize(MyTextPlayer[playerid][1], 0.519999, 1.500000);
			TextDrawColor(MyTextPlayer[playerid][1], -1);
			TextDrawSetOutline(MyTextPlayer[playerid][1], 0);
			TextDrawSetProportional(MyTextPlayer[playerid][1], 1);
			TextDrawSetShadow(MyTextPlayer[playerid][1], 1);
			TextDrawShowForPlayer(playerid,MyTextPlayer[playerid][1]);
			SetTimerEx("GameTextForPlayerDestroy2",Seconds*1000,0,"i",playerid);
	    }
	    case 3:
	    {
			MyTextPlayer[playerid][2] = TextDrawCreate(505.000000, 110.000000, Message);
			TextDrawBackgroundColor(MyTextPlayer[playerid][2], 255);
			TextDrawFont(MyTextPlayer[playerid][2], 0);
			TextDrawLetterSize(MyTextPlayer[playerid][2], 1.039999, 2.999999);
			TextDrawColor(MyTextPlayer[playerid][2], -1);
			TextDrawSetOutline(MyTextPlayer[playerid][2], 0);
			TextDrawSetProportional(MyTextPlayer[playerid][2], 1);
			TextDrawSetShadow(MyTextPlayer[playerid][2], 1);
			TextDrawShowForPlayer(playerid,MyTextPlayer[playerid][2]);
			SetTimerEx("GameTextForPlayerDestroy3",Seconds*1000,0,"i",playerid);
	    }
	    case 4:
	    {
			MyTextPlayer[playerid][3] = TextDrawCreate(285.000000, 166.000000, Message);
			TextDrawBackgroundColor(MyTextPlayer[playerid][3], 255);
			TextDrawFont(MyTextPlayer[playerid][3], 3);
			TextDrawLetterSize(MyTextPlayer[playerid][3], 0.699999, 2.799999);
			TextDrawColor(MyTextPlayer[playerid][3], -1);
			TextDrawSetOutline(MyTextPlayer[playerid][3], 0);
			TextDrawSetProportional(MyTextPlayer[playerid][3], 1);
			TextDrawSetShadow(MyTextPlayer[playerid][3], 1);
			TextDrawShowForPlayer(playerid,MyTextPlayer[playerid][3]);
			SetTimerEx("GameTextForPlayerDestroy4",Seconds*1000,0,"i",playerid);
	    }
	}
	return true;
}
/* MyGameText By RoiKy */
