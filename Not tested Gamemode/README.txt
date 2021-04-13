+---------------------------+
¦ How to install JunkBuster ¦
+---------------------------+

>>> To install JunkBuster correctly, you must follow these 10 easy steps. <<<

Step 1)
	Copy the downloaded folder "JunkBuster" into your folder "scriptfiles".

Step 2)
	Copy "JunkBuster.pwn" into your "filterscripts" folder.
	Add "JunkBuster" to "filterscripts" in your "server.cfg" file.
	
	IMPORTANT:
		Write "JunkBuster" in front of all other filterscripts! JunkBuster must be loaded first!!!
		It must look like this: filterscripts JunkBuster FS1 FS2 FS3 ETC
		
	Copy all includes in "pawno/includes" into YOUR folder "include" located in
	the folder "pawno".

Step 3)
	Include "JunkBuster.inc" (this is the client script) in your GAMEMODE and ALL your FILTERSCRIPTS!
	Just use #include <JunkBuster>. If you do not do this, JunkBuster will not work properly and probably kick/ban innocent players.

Step 4)
	You are using a custom admin system with for example levels? Not only RCON?
	You can link this admin system with JunkBuster.
	JunkBuster can't recognize your adminsystem so you must add a function.

	Function (This is only an EXAMPLE!):

		public IsPlayerAdminCall(playerid)
		{
			if(PlayerInfo[playerid][pAdmin] >= 1)
				return 1;
			else
				return 0;
		}

	IMPORTANT:
		If you haven't understood yet: This function depends on YOUR admin system. 
		The function above is ONLY FOR GODFATHER so you may have to customize this function.
		If you do not add this function admin immunity will only work for RCON-admins!!!
		
	TEMPLATE (copy this function into your admin script/gamemode and fill in the missing part [this was just for the bloody noobs]):
		
		public IsPlayerAdminCall(playerid)
		{
			if(/* Missing part: Is playerid admin? */)
				return 1; // If yes, return 1.
			else
				return 0; // If no, return 0.
		}
	
	PS:
		JunkBuster is compatible with the default Godfather gamemode! (Tested)
		
	PPS:
		JunkBuster is actually compatible with nearly every script! (It's designed to be)
	
Step 5)
	Remove/comment the error lines (#error) at the beginning and the end of the "JunkBuster.pwn" filterscript.
	
	IMPORTANT: 
		Decide if you want to use the new SQLite Ban System by uncommenting the line where #define USE_DATABASE is.
		I do not recommend using it because it's experimental. So you probably should just compile JunkBuster without editing it.
	
	Compile "JunkBuster.pwn".
	Compile all your other gamemodes/filterscripts and check for errors. If there are any errors or warnings and you
	don't know how to fix it, post them in the JunkBuster topic on forum.sa-mp.com.
	(But there shouldn't be any errors in update 10.)

Step 6)
	Start your gamemode, go ingame and login as RCON-admin. 
	Now type /jbcfg. A dialog will appear.
	Choose the listitem "Set a var". After you have done this
	you will see all JunkBuster variables with the current values. 
	It's the best you choose every variable. Double-click on a variable and a new
	dialog will appear where you can set the variable. There will be a description for every variable, too. 
	Read description for the chosen variable before you change it.
	After you have customized the JunkBuster configuration. Go back to the main dialog (/jbcfg) and 
	choose "Save configuration to file".
	
Step 7)
	Add more bad words and forbidden weapons (or don't). 
	To do this open "BadWords.cfg" in the folder "scriptfiles/JunkBuster".
	Add or remove bad words. Now open "ForbiddenWeapons.cfg" and add or remove weapon IDs. 
	Minigun (38), both rocket launchers (35,36) and flamethrower (37) are forbidden by default.
	Go ingame again, tpye /jbcfg and choose "Load configuration from file" to load the forbidden weapons and bad words.
	Now open "JunkBuster.cfg" in the folder "scriptfiles/JunkBuster" and change the value "Homepage". 
	(If you don't have a homepage... hm... I don't know what to write there.
	Maybe write the homepage of a server you hate so the admins there will get annoyed by the cheaters?)

Step 8) 
	Type ingame /jbcmds for more administration commands (RCON only).

Step 9)
	JunkBuster is now ready to protect your server from spammers, hackers, cheaters and other noobs.
	If you find a bug, REPORT it in SA-MP forums in the JunkBuster topic.

Step 10)
	Have fun and feel saver. 
	So, was it that hard? 
	
	
	
	
	
	
	
	
	
	
	[...]
	
	
	
	
	
	
	
	
	
	
	OK, it was probably harder than Justin Bieber's Willy...
	
	
	
	
	
	
	
	
	
	[...]
	
	
	
	
	
	
	
	
	Oh... wait! This must mean it was not hard at all!
	