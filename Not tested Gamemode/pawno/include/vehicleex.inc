/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Global
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#if defined __vehicleex__included
#endinput
#endif

//**-----Cars------**
#define MAX_BIKES 11
#define MAX_BMX 3
#define MAX_BOAT 10
#define MAX_HELI 11
#define MAX_CARS 144
#define MAX_MONSTER 5
#define MAX_PLANES 13

new VehicleBikesmodel[MAX_BIKES] =    {
581,
523,
462,
521,
463,
522,
461,
448,
468,
586,
471
};

new VehicleBikesnames[MAX_BIKES][36] =    {
{"BF400"},
{"HPV-1000"},
{"Faggio"},
{"FCR900"},
{"Freeway"},
{"Nrg-500"},
{"Pcj600"},
{"Pizzaboy"},
{"Sanchez"},
{"WayFarer"},
{"Quad"}};

new VehicleBmxmodel[MAX_BMX] =  {
509,
481,
510
};

new VehicleBmxnames[MAX_BMX][36] =  {
{"Bike"},
{"BMX"},
{"Mountain Bike"}
};

new VehicleBoatmodel[MAX_BOAT] =    {
472,
473,
493,
595,
484,
430,
453,
452,
446,
454,
};

new VehicleBoatnames[MAX_BOAT][36] =    {
{"Coastg"},
{"Dinghy"},
{"Jetmax"},
{"Launch"},
{"Marquis"},
{"Predator"},
{"Reefer"},
{"Speeder"},
{"Squalo"},
{"Tropic"}
};

new VehicleHelimodel[MAX_HELI] =    {
548,
425,
417,
487,
497,
563,
501,
465,
447,
469,
488
};

new VehicleHelinames[MAX_HELI][36] =    {
{"Cargobob"},
{"Hunter"},
{"Leviathn"},
{"Maveric"},
{"Polmav"},
{"Raindance"},
{"Rcgoblin"},
{"Rcraider"},
{"Seasparow"},
{"Sparrow"},
{"Vcnmav"}
};

new VehicleCarmodel[MAX_CARS] = {
445,
602,
416,
485,
568,
429,
433,
499,
424,
536,
496,
504,
422,
609,
498,
401,
575,
518,
402,
541,
482,
431,
438,
457,
527,
483,
524,
415,
542,
589,
437,
532,
480,
596,
599,
597,
598,
578,
486,
507,
562,
585,
427,
419,
587,
490,
528,
533,
544,
407,
565,
455,
530,
526,
466,
604	,
492	,
474	,
588	,
434	,
502	,
503	,
494	,
579	,
545	,
411	,
546	,
559	,
508	,
571	,
400	,
403	,
517	,
410	,
551	,
500	,
418	,
572	,
423	,
414	,
516	,
582	,
467	,
443	,
470	,
404	,
514,
603	,
600	,
413	,
426	,
436,
547	,
489	,
441	,
594	,
564	,
515	,
479	,
534	,
432	,
505,
442,
440	,
475	,
543	,
605	,
495	,
567	,
428,
405	,
535	,
458	,
580	,
439	,
561	,
409	,
560	,
550	,
506	,
601	,
574	,
566	,
549	,
420	,
459	,
576	,
525	,
531	,
408	,
583	,
451	,
558	,
552	,
540	,
491	,
412	,
478	,
421	,
529	,
555	,
456	,
554	,
477
};

new VehicleCarnames[MAX_CARS][34] = {
{"Admiral"},
{"Alpha"},
{"Ambulan"},
{"Baggage"},
{"Bandito"},
{"Banshee"},
{"Barracks"},
{"Benson"},
{"Bf-inject"},
{"Blade"},
{"Blistac"},
{"Bloodra"},
{"Bobcat"},
{"Boxburg"},
{"Boxville"},
{"Bravura"},
{"Broadway"},
{"Buccanee"},
{"Buffalo"},
{"Bullet"},
{"Burrito"},
{"Bus"},
{"Cabbie"},
{"Caddy"},
{"Cadrona"},
{"Camper"},
{"Cement"},
{"Cheetah"},
{"Clover"},
{"Club"},
{"Coach"},
{"Combine"},
{"Comet"},
{"CopCala"},
{"Police Ranger"},
{"Police Car (SF)"}, //CopCasf
{"CopCavg"},
{"Dft30"},
{"Dozer"},
{"Elegant"},
{"Elegy"},
{"Emperor"},
{"Enforcer"},
{"Esperant"},
{"Euros"},
{"FBI Rancher"},
{"FBI Truck"},
{"Feltzer"},
{"Firela"},
{"Firetruk"},
{"Flash"},
{"Flatbed"},
{"Forklift"},
{"Fortune"},
{"Glendale"},
{"Glenshit"},
{"Greenwoo"},
{"Hermes"},
{"Hotdog"},
{"Hotknife"},
{"Hotrina"},
{"Hotrinb"},
{"Hotring"},
{"Huntley"},
{"Hustler"},
{"Infernus"},
{"Intruder"},
{"Jester"},
{"Journey"},
{"Kart"},
{"Landstal"},
{"Linerun"},
{"Majestic"},
{"Manana"},
{"Merit"},
{"Mesa"},
{"Moonbeam"},
{"Mower"},
{"Mrwhoop"},
{"Mule"},
{"Nebula"},
{"Newsvan"},
{"Oceanic"},
{"Packer"},
{"Patriot"},
{"Peren"},
{"Petro"},
{"Phoenix"},
{"Picador"},
{"Pony"},
{"Premier"},
{"Previon"},
{"Primo"},
{"Pancher"},
{"Pcbandit"},
{"Rccam"},
{"Rctiger"},
{"Rdtrain"},
{"Regina"},
{"Remingtn"},
{"Rhino"},
{"Rnchlure"},
{"Romero"},
{"Rumpo"},
{"Sabre"},
{"Sadler"},
{"Sadlshit"},
{"Sandking"},
{"Savanna"},
{"Securica"},
{"Sentinel"},
{"Slamvan"},
{"Solair"},
{"Stafford"},
{"Stallion"},
{"Stratum"},
{"Stretch"},
{"Sultan"},
{"Sunrise"},
{"Supergt"},
{"Swatvan"},
{"Sweeper"},
{"Tahoma"},
{"Tampa"},
{"Taxi"},
{"Topfun"},
{"Tornado"},
{"Towtruck"},
{"Tractor"},
{"Trash"},
{"Tug"},
{"Turismo"},
{"Uranus"},
{"Utility"},
{"Vincent"},
{"Virgo"},
{"Voodoo"},
{"Walton"},
{"Washing"},
{"Willard"},
{"Windsor"},
{"Yankee"},
{"Yosemite"},
{"Zr3 50"}
};

new VehicleMonstermodel[MAX_MONSTER] =  {
406,
573,
444,
556,
557
};

new VehicleMonsternames[MAX_MONSTER][34] =  {
{"Dumper"},
{"Duneride"},
{"Monster"},
{"Monstera"},
{"Monsterb"}
};

new VehiclePlanesmodel[MAX_PLANES] =    {
592,
577,
511,
512,
593,
520,
553,
464,
476,
519,
460,
513,
539
};

new VehiclePlanesnames[MAX_PLANES][34] =    {
{"Andromda"},
{"At-400"},
{"Beagle"},
{"Cropdust"},
{"Dodo"},
{"Hydra"},
{"Nevada"},
{"Rcbaron"},
{"Rustler"},
{"Shamal"},
{"Skimmer"},
{"Stunt"},
{"Vortex"}
};

//----------------Fuctions------------------
//---------------Name-----------------------------------------------------------
stock GetVehicleName(vehicleid)
{
	new Vname[256];
	new model = GetVehicleModel(vehicleid);

	for(new i;i<MAX_BIKES;i++)
	{
	    if(model == VehicleBikesmodel[i])
	    Vname=VehicleBikesnames[i];
	}
	for(new i;i<MAX_BMX;i++)
	{
	    if(model == VehicleBmxmodel[i])
	    Vname=VehicleBmxnames[i];
	}
	for(new i;i<MAX_BOAT;i++)
	{
	    if(model == VehicleBoatmodel[i])
	    Vname=VehicleBoatnames[i];
	}
	for(new i;i<MAX_HELI;i++)
	{
	    if(model == VehicleHelimodel[i])
	    Vname=VehicleHelinames[i];
	}
	for(new i;i<MAX_CARS;i++)
	{
	    if(model == VehicleCarmodel[i])
	    Vname=VehicleCarnames[i];
	}
	for(new i;i<MAX_MONSTER;i++)
	{
	    if(model == VehicleMonstermodel[i])
	    Vname=VehicleMonsternames[i];
	}
	for(new i;i<MAX_PLANES;i++)
	{
	    if(model == VehiclePlanesmodel[i])
	    Vname=VehiclePlanesnames[i];
	}
	return Vname;
}
//---------------Name-----------------------------------------------------------
//---------------Type-----------------------------------------------------------
stock GetVehicleType(vehicleid)
{
	new Vtype[256];
	new model = GetVehicleModel(vehicleid);

	for(new i;i<MAX_BIKES;i++)
	{
	    if(model == VehicleBikesmodel[i])
	    Vtype="Motor Bike";
	}
	for(new i;i<MAX_BMX;i++)
	{
	    if(model == VehicleBmxmodel[i])
	    Vtype="Bike";
	}
	for(new i;i<MAX_BOAT;i++)
	{
	    if(model == VehicleBoatmodel[i])
	    Vtype="Boat";
	}
	for(new i;i<MAX_HELI;i++)
	{
	    if(model == VehicleHelimodel[i])
	    Vtype="Helicopter";
	}
	for(new i;i<MAX_CARS;i++)
	{
	    if(model == VehicleCarmodel[i])
	    Vtype="Car";
	}
	for(new i;i<MAX_MONSTER;i++)
	{
	    if(model == VehicleMonstermodel[i])
	    Vtype="Monster Truck";
	}
	for(new i;i<MAX_PLANES;i++)
	{
	    if(model == VehiclePlanesmodel[i])
	    Vtype="Plane";
	}
	return Vtype;
}
//---------------Type-----------------------------------------------------------
//---------------IsVehicleHasDriver---------------------------------------------
stock IsVehicleHasDriver(vehicleid)
{
	for(new i;i<MAX_PLAYERS;i++)
	{
	    if(IsPlayerInVehicle(i,vehicleid) && GetPlayerState(i) == PLAYER_STATE_DRIVER) return 1;
	}
	return 0;
}
//---------------IsVehicleHasDriver---------------------------------------------
//---------------GetVehicleDriverID---------------------------------------------
stock GetVehicleDriverID(vehicleid)
{
	for(new i;i<MAX_PLAYERS;i++)
	{
	    if(IsPlayerInVehicle(i,vehicleid) && GetPlayerState(i) == PLAYER_STATE_DRIVER) return i;
	}
	return INVALID_PLAYER_ID;
}
//---------------GetVehicleDriverID---------------------------------------------
//---------------Teleport Vehicle To Player-------------------------------------
stock TeleportVehicleToPlayer(vehicleid,playerid)
{
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	//--------------------------------------------
	new KickPlayer=GetVehicleDriverID(vehicleid);
	RemovePlayerFromVehicle(KickPlayer);
	PutPlayerInVehicle(playerid,vehicleid,0);
	SetVehiclePos(vehicleid,x,y,z+1);
	//--------------------------------------------
}
//---------------Teleport Vehicle To Player-------------------------------------
//---------------Teleport Player To Vehicle-------------------------------------
stock TeleportPlayerToVehicle(vehicleid,playerid)
{
	new Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	//--------------------------------------------
	SetPlayerPos(playerid,x+1,y+1,z+1);
	//--------------------------------------------
}
//---------------Teleport Player To Vehicle-------------------------------------
//--------------SendClientMessageToVehicle--------------------------------------
stock VehicleMessage(vehicleid,color,text[])
{
	for(new i;i<MAX_PLAYERS;i++)
	{
	    if(IsPlayerInVehicle(i,vehicleid))
	    {
	        SendClientMessage(i,color,text);
		}
	}
}
//--------------SendClientMessageToVehicle--------------------------------------
//----------------SetVehicleRandomColor-----------------------------------------
stock SetVehicleRandomColor(vehicleid)
{
	ChangeVehicleColor(vehicleid,random(9),random(9));
}
//----------------SetVehicleRandomColor-----------------------------------------
//-----------------ETC : IsKeyJustDown------------------------------------------
stock IsKeyJustDown(key, newkeys, oldkeys)
{
	if((newkeys & key) && !(oldkeys & key)) return 1;
	return 0;
}
//-----------------ETC : IsKeyJustDown------------------------------------------
