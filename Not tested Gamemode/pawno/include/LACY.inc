//LACY SYSTEM
forward LACY_GiveMoney(playerid, amount);
forward LACY_MoneyCheat_Allow(playerid, amount1);

public LACY_GiveMoney(playerid, amount)
{
	if(amount > 0)
		LACY_MoneyCheat_Allow(playerid, amount);
	GivePlayerMoney(playerid, amount);
}

public LACY_MoneyCheat_Allow(playerid, amount1)
{
	new tmpname[256];
	new amount[256];

	format(tmpname, 256, "LACY_MoneyCheat_Allow_%d", playerid);
	if(existproperty(13, "", adler32hash(tmpname)))
	{
	    new tmp;
	    new value[255];
		getproperty(13, "", adler32hash(tmpname), value);
		strunpack(value,value);
	    tmp = strval(value);
	    amount1 = amount1+tmp;
	    format(amount, 256, "%d", amount1);
	    deleteproperty(13, "", adler32hash(tmpname));
	    setproperty(13, "", adler32hash(tmpname), amount);
	}
	else
	{
	    format(amount, 256, "%d", amount1);
	    setproperty(13, "", adler32hash(tmpname), amount);
	}
}

adler32hash(buf[]) {
 new length=strlen(buf);
 new s1 = 1;
 new s2 = 0;
 new n;
 for (n=0; n<length; n++) {
  s1 = (s1 + buf[n]) % 65521;
  s2 = (s2 + s1)     % 65521;
 }
 return (s2 << 16) + s1;
}

forward LACY_WeaponCheat_Allow(playerid, weapid, amount1);
public LACY_WeaponCheat_Allow(playerid, weapid, amount1)
{
	new tmpname[256];
	new amount[256];

	format(tmpname, 256, "LACY_MoneyCheat_Allow_%d_%d",  weapid, playerid);
	if(existproperty(13, "", adler32hash(tmpname)))
	{
	    new tmp;
	    new value[255];
		getproperty(13, "", adler32hash(tmpname), value);
		strunpack(value,value);
	    tmp = strval(value);
	    amount1 = amount1+tmp;
	    format(amount, 256, "%d", amount1);
	    deleteproperty(13, "", adler32hash(tmpname));
	    setproperty(13, "", adler32hash(tmpname), amount);
	}
	else
	{
	    format(amount, 256, "%d", amount1);
	    setproperty(13, "", adler32hash(tmpname), amount);
	}

}

forward LACY_GiveWeapon(playerid, weapid, amount);
public LACY_GiveWeapon(playerid, weapid, amount)
{
	if(amount > 0 && IsValidWeapon(weapid))
	{
		LACY_WeaponCheat_Allow(playerid, weapid, amount);
		GivePlayerWeapon(playerid, weapid, amount);	
	}
	return 1;
}
forward LACY_ResetWeapons(playerid);
public LACY_ResetWeapons(playerid)
{
	
	for(new i; i<46; i++)
	{
	    LACY_WeaponCheat_Delete(playerid,i);
	}
    ResetPlayerWeapons(playerid);
    return 1;
}
stock IsValidWeapon(weaponid)
{
        if (weaponid > 0) return 1;
        return 0;
}

LACY_WeaponCheat_Delete(playerid,weapid)
{
	new tmpname[256];

	format(tmpname, 256, "LACY_MoneyCheat_Allow_%d_%d", weapid, playerid);
	if(existproperty(13, "", adler32hash(tmpname)))
	{
	    deleteproperty(13, "", adler32hash(tmpname));
	}

}