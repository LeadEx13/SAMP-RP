/*          This is dudb, dutils and dini merged to one .inc
 *                 for new usage of bank accounts
 *              created by Emilijo (Correlli) Lovric
 *
 *            Original dudb, dutils and dini were created
 *                       by Jan (DracoBlue.net)
 *
*/



#if defined _cutils_included
#endinput
#endif

#define _cutils_included
#pragma library cutils



#define MAX_STRING 255
#define dUser2(%1).( udb_User2(%1,
#define dUserINT2(%1).( udb_UserInt2(%1,
#define dUserSet2(%1).( udb_UserSet2(%1,
#define dUserSetINT2(%1).( udb_UserSetInt2(%1,
#define dUserSetFLOAT2(%1).( udb_UserSetFloat2(%1,
#define dUserFLOAT2(%1).( udb_UserFloat2(%1,



#if !defined floatstr
native Float:floatstr(const string[]);
#endif



new PRIVATE_Last_Money2[MAX_PLAYERS];



stock udb_hash2(buf[])
{
    new length = strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for(n = 0; n < length; n++)
    {
    s1 = (s1 + buf[n]) % 65521;
    s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}



stock udb_encode2(nickname[])
{
    new tmp[MAX_STRING];
    set(tmp, nickname);
    tmp=strreplace("_","_00",tmp);
    tmp=strreplace(";","_01",tmp);
    tmp=strreplace("!","_02",tmp);
    tmp=strreplace("/","_03",tmp);
    tmp=strreplace("\\","_04",tmp);
    tmp=strreplace("[","_05",tmp);
    tmp=strreplace("]","_06",tmp);
    tmp=strreplace("?","_07",tmp);
    tmp=strreplace(".","_08",tmp);
    tmp=strreplace("*","_09",tmp);
    tmp=strreplace("<","_10",tmp);
    tmp=strreplace(">","_11",tmp);
    tmp=strreplace("{","_12",tmp);
    tmp=strreplace("}","_13",tmp);
    tmp=strreplace(" ","_14",tmp);
    tmp=strreplace("\"","_15",tmp);
    tmp=strreplace(":","_16",tmp);
    tmp=strreplace("|","_17",tmp);
    tmp=strreplace("=","_18",tmp);
    return tmp;
}



stock udb_decode2(nickname[])
{
    new tmp[MAX_STRING];
    set(tmp, nickname);
    tmp=strreplace("_01",";",tmp);
    tmp=strreplace("_02","!",tmp);
    tmp=strreplace("_03","/",tmp);
    tmp=strreplace("_04","\\",tmp);
    tmp=strreplace("_05","[",tmp);
    tmp=strreplace("_06","]",tmp);
    tmp=strreplace("_07","?",tmp);
    tmp=strreplace("_08",".",tmp);
    tmp=strreplace("_09","*",tmp);
    tmp=strreplace("_10","<",tmp);
    tmp=strreplace("_11",">",tmp);
    tmp=strreplace("_12","{",tmp);
    tmp=strreplace("_13","}",tmp);
    tmp=strreplace("_14"," ",tmp);
    tmp=strreplace("_15","\"",tmp);
    tmp=strreplace("_16",":",tmp);
    tmp=strreplace("_17","|",tmp);
    tmp=strreplace("_18","=",tmp);
    tmp=strreplace("_00","_",tmp);
    return tmp;
}



stock udb_Exists2(nickname[])
{
    new tmp[MAX_STRING];
    format(tmp, sizeof(tmp), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return fexist(tmp);
}



stock udb_Remove2(nickname[])
{
    new tmp[MAX_STRING];
    format(tmp, sizeof(tmp), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_Remove2(tmp);
}



stock udb_UserSetInt2(nickname[], key[], value)
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_IntSet2(fname, key, value);
}



stock udb_UserSetFloat2(nickname[], key[], Float:value)
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_FloatSet2(fname, key, value);
}



stock udb_UserSet2(nickname[], key[], value[])
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_Set2(fname, key, value);
}



stock udb_User2(nickname[], key[])
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    format(fname, sizeof(fname), dini_Get2(fname, key));
    return fname;
}



stock Float:udb_UserFloat2(nickname[], key[])
{
    new fname[MAX_STRING];
    format(fname,sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_Float2(fname, key);
}



stock udb_UserInt2(nickname[], key[])
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    return dini_Int2(fname, key);
}



stock udb_CheckLogin2(nickname[], pwd[])
{
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    if (udb_UserInt2(nickname, "password_hash") == udb_hash2(pwd)) return true;
    return false;
}



stock udb_Create2(nickname[], pwd[])
{
    if (udb_Exists2(nickname)) return false;
    new fname[MAX_STRING];
    format(fname, sizeof(fname), "scriptfiles2/%s.dudb.sav", udb_encode2(nickname));
    dini_Create2(fname);
    udb_UserSetInt2(nickname, "password_hash", udb_hash2(pwd));
    return true;
}



stock  dini_Exists2(filename[])
{
    if (fexist(filename)) return true;
    return false;
}



stock  dini_Remove2(filename[])
{
    if (!fexist(filename)) return false;
    fremove(filename);
    return true;
}



stock  dini_Create2(filename[])
{
    new File:fhnd;
    if (fexist(filename)) return false;
    fhnd = fopen(filename, io_write);
    fclose(fhnd);
    return true;
}



stock  dini_PRIVATE_ExtractKey2(line[])
{
    new tmp[MAX_STRING];
    tmp[0] = 0;
    if (strfind(line, "=", true) == -1) return tmp;
    set(tmp, strlower(ret_memcpy2(line, 0, strfind(line, "=", true))));
    return tmp;
}



stock  dini_PRIVATE_ExtractValue2(line[])
{
    new tmp[MAX_STRING];
    tmp[0] = 0;
    if (strfind(line, "=", true) == -1)
    {
    return tmp;
    }
    set(tmp, ret_memcpy2(line, strfind(line, "=", true)+1, strlen(line)));
    return tmp;
}



stock  dini_Set2(filename[], key[], value[])
{
    new File:fohnd, File:fwhnd;
    new bool:wasset = false;
    new tmpres[MAX_STRING];
    if(key[0] == 0) return false;
    format(tmpres,sizeof(tmpres),"%s.part", filename);
    fohnd = fopen(filename, io_read);
    if(!fohnd) return false;
    fremove(tmpres);
    fwhnd=fopen(tmpres, io_write);
    while (fread(fohnd, tmpres))
    {
    StripNewLine2(tmpres);
    if((!wasset)&&(equal(dini_PRIVATE_ExtractKey2(tmpres), key, true)))
    {
    format(tmpres,sizeof(tmpres),"%s=%s", key, value);
    wasset = true;
    }
    fwrite(fwhnd,tmpres);
    fwrite(fwhnd,"\r\n");
    }
    if(!wasset)
    {
    format(tmpres, sizeof(tmpres), "%s=%s", key, value);
    fwrite(fwhnd, tmpres);
    fwrite(fwhnd, "\r\n");
    }
    fclose(fohnd);
    fclose(fwhnd);
    format(tmpres, sizeof(tmpres), "%s.part", filename);
    if(fcopytextfile(tmpres, filename))
    {
    return fremove(tmpres);
    }
    return false;
}



stock  dini_IntSet2(filename[], key[], value)
{
    new valuestring[MAX_STRING];
    format(valuestring, sizeof(valuestring), "%d", value);
    return dini_Set2(filename, key, valuestring);
}



stock  dini_Int2(filename[], key[])
{
    return strval(dini_Get2(filename, key));
}



stock  dini_FloatSet2(filename[], key[], Float:value)
{
    new valuestring[MAX_STRING];
    format(valuestring, sizeof(valuestring), "%f", value);
    return dini_Set2(filename, key, valuestring);
}



stock  dini_Float2(filename[], key[])
{
    return floatstr(dini_Get(filename, key));
}



stock  dini_Bool2(filename[], key[])
{
    return strval(dini_Get2(filename, key));
}



stock  dini_BoolSet2(filename[], key[], value)
{
    new valuestring[MAX_STRING];
    format(valuestring, sizeof(valuestring), "%d", value);
    return dini_Set2(filename, key, valuestring);
}



stock  dini_Unset2(filename[], key[])
{
    new File:fohnd, File:fwhnd;
    new tmpres[MAX_STRING];
    format(tmpres, sizeof(tmpres), "%s.part", filename);
    fohnd = fopen(filename, io_read);
    if (!fohnd) return false;
    fremove(tmpres);
    fwhnd = fopen(tmpres, io_write);
    while (fread(fohnd, tmpres))
    {
    StripNewLine2(tmpres);
    if (equal(dini_PRIVATE_ExtractKey2(tmpres), key, true))
    {
    }
    else
    {
    format(tmpres, sizeof(tmpres), "%s", tmpres);
    fwrite(fwhnd, tmpres);
    fwrite(fwhnd, "\r\n");
    }
    }
    fclose(fohnd);
    fclose(fwhnd);
    format(tmpres, sizeof(tmpres), "%s.part", filename);
    if (fcopytextfile(tmpres, filename))
    {
    return fremove(tmpres);
    }
    return false;
}



stock  dini_Get2(filename[], key[])
{
    new File:fohnd;
    new tmpres[MAX_STRING];
    new tmpres2[MAX_STRING];
    tmpres[0] = 0;
    fohnd = fopen(filename, io_read);
    if (!fohnd) return tmpres;
    while(fread(fohnd, tmpres))
    {
    StripNewLine2(tmpres);
    if (equal(dini_PRIVATE_ExtractKey2(tmpres), key, true))
    {
    tmpres2[0] = 0;
    strcat(tmpres2, dini_PRIVATE_ExtractValue2(tmpres));
    fclose(fohnd);
    return tmpres2;
    }
    }
    fclose(fohnd);
    return tmpres;
}



stock  dini_Isset2(filename[], key[])
{
    new File:fohnd;
    new tmpres[MAX_STRING];
    fohnd = fopen(filename, io_read);
    if (!fohnd) return false;
    while (fread(fohnd, tmpres))
    {
    StripNewLine2(tmpres);
    if (equal(dini_PRIVATE_ExtractKey2(tmpres), key, true))
    {
    fclose(fohnd);
    return true;
    }
    }
    fclose(fohnd);
    return false;
}



stock IsNumeric2(const string[])
{
    new length = strlen(string);
    if (length == 0) return false;
    for (new i = 0; i < length; i++)
    {
    if((string[i] > '9' || string[i] < '0' && string[i] != '-'
    && string[i] != '+')
    || (string[i] == '-' && i != 0)
    || (string[i] == '+' && i != 0)
    ) return false;
    }
    if (length == 1 && (string[0] == '-' || string[0] == '+')) return false;
    return true;
}

#pragma unused IsNumeric2



stock mktime2(hour, minute, second, day, month, year)
{
    new timestamp2;
    timestamp2 = second + (minute * 60) + (hour * 3600);
    new days_of_month[12];
    if(((year % 4 == 0) && (year % 100 != 0))
    || (year % 400 == 0))
    {
    days_of_month = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    }
    else
    {
    days_of_month = {31,28,31,30,31,30,31,31,30,31,30,31};
    }
    new days_this_year = 0;
    days_this_year = day;
    if(month > 1)
    {
    for(new i = 0; i < month-1; i++)
    {
    days_this_year += days_of_month[i];
    }
    }
    timestamp2 += days_this_year * 86400;
    for(new j = 1970; j < year; j++)
    {
    timestamp2 += 31536000;
    if (((year % 4 == 0) && (year % 100 != 0))
    || (year % 400 == 0))  timestamp2 += 86400;
    }
    return timestamp2;
}

#pragma unused mktime2



stock ValidEmail2(email[])
{
    new len = strlen(email);
    new cstate = 0;
    new i;
    for(i = 0; i < len; i++)
    {
    if((cstate == 0 || cstate == 1)
    && (email[i] >= 'A' && email[i] <= 'Z')
    || (email[i] >= 'a' && email[i] <= 'z')
    || (email[i] == '.')  || (email[i] == '-')
    || (email[i] == '_'))
    {
    }
    else
    {
    if ((cstate == 0) && (email[i] == '@'))
    {
    cstate = 1;
    }
    else
    {
    return false;
    }
    }
    }
    if (cstate < 1) return false;
    if (len < 6) return false;
    if ((email[len-3] == '.') || (email[len-4] == '.')
    || (email[len-5] == '.')) return true;
    return false;
}

#pragma unused ValidEmail2



stock Time2()
{
    new hour, minute, second;
    new year, month, day;
    gettime(hour, minute, second);
    getdate(year, month, day);
    return mktime2(hour, minute, second, day, month, year);
}

#pragma unused Time2



Now2()
{
    new hour, minute, second;
    new year, month, day;
    gettime(hour, minute, second);
    getdate(year, month, day);
    return mktime2(hour, minute, second, day, month, year);
}

#pragma unused Now2



HexToInt2(string[])
{
    if (string[0] == 0) return 0;
    new i;
    new cur = 1;
    new res = 0;
    for (i = strlen(string); i > 0; i--)
    {
    if(string[i-1]<58) res = res+cur*(string[i-1]-48);
    else res = res+cur*(string[i-1]-65+10);
    cur = cur*16;
    }
    return res;
}

#pragma unused HexToInt2



StrToInt2(string[])
{
    return strval(string);
}

#pragma unused StrToInt2



IntToStr2(value)
{
    new tmp[MAX_STRING];
    valstr(tmp, num);
    return tmp;
}

#pragma unused IntToStr2



trunc2(Float:value)
{
    return floatround(value,floatround_floor);
}

#pragma unused trunc2



SetPlayerMoney2(playerid, howmuch)
{
    PRIVATE_Last_Money2[playerid] = howmuch;
    GivePlayerMoney(playerid, howmuch-GetPlayerMoney(playerid));
}

#pragma unused SetPlayerMoney2



fcopy2(oldname[], newname[])
{
    new File:ohnd, File:nhnd;
    if(!fexist(oldname)) return false;
    ohnd = fopen(oldname, io_read);
    nhnd = fopen(newname, io_write);
    new buf2[1];
    new i;
    for(i = flength(ohnd); i > 0; i--)
    {
    fputchar(nhnd, fgetchar(ohnd, buf2[0], false), false);
    }
    fclose(ohnd);
    fclose(nhnd);
    return true;
}

#pragma unused fcopy2



fcopytextfile2(oldname[], newname[])
{
    new File:ohnd,File:nhnd;
    if(!fexist(oldname)) return false;
    ohnd = fopen(oldname, io_read);
    nhnd = fopen(newname, io_write);
    new tmpres[MAX_STRING];
    while(fread(ohnd, tmpres))
    {
    StripNewLine2(tmpres);
    format(tmpres, sizeof(tmpres), "%s\r\n", tmpres);
    fwrite(nhnd, tmpres);
    }
    fclose(ohnd);
    fclose(nhnd);
    return true;
}

#pragma unused fcopytextfile2



frename2(oldname[], newname[]) {
    if (!fexist(oldname)) return false;
    fremove(newname);
    if (!fcopy(oldname, newname)) return false;
    fremove(oldname);
    return true;
}

#pragma unused frename2



stock StripNewLine2(string[])
{
    new len = strlen(string);
    if (string[0] == 0) return ;
    if ((string[len - 1] == '\n') || (string[len - 1] == '\r'))
    {
    string[len - 1] = 0;
    if (string[0]==0) return ;
    if ((string[len - 2] == '\n') || (string[len - 2] == '\r')) string[len - 2] = 0;
    }
}

#pragma unused StripNewLine2



ret_memcpy2(source[], index=0, numbytes)
{
    new tmp[MAX_STRING];
    new i = 0;
    tmp[0] = 0;
    if(index >= strlen(source)) return tmp;
    if(numbytes+index >= strlen(source)) numbytes = strlen(source)-index;
    if(numbytes <= 0) return tmp;
    for(i = index; i < numbytes+index; i++)
    {
    tmp[i-index] = source[i];
    if(source[i] == 0) return tmp;
    }
    tmp[numbytes] = 0;
    return tmp;
}

#pragma unused ret_memcpy2



stock copy2(dest[], source[], count)
{
    dest[0] = 0;
    if (count < 0) return false;
    if (count > strlen(source)) count = strlen(source);
    new i = 0;
    for (i = 0; i < count; i++)
    {
    dest[i] = source[i];
    if (source[i] == 0) return true;
    }
    dest[count]=0;
    return true;
}

#pragma unused copy2



stock delete2(string[], count)
{
    new tmp[MAX_STRING];
    tmp[0] = 0;
    if (count <= 0)
    {
    format(tmp, sizeof(tmp), "%s", string);
    return tmp;
    }
    tmp = ret_memcpy2(string, count, strlen(string));
    return tmp;
}

#pragma unused delete2



stock set2(dest[], source[])
{
    new count = strlen(source);
    new i = 0;
    for (i = 0; i < count; i++)
    {
    dest[i] = source[i];
    }
    dest[count] = 0;
}

#pragma unused set2



stock equal2(str1[], str2[], bool:ignorecase)
{
    if (strlen(str1) != strlen(str2)) return false;
    if (strcmp(str1, str2, ignorecase) == 0) return true;
    return false;
}

#pragma unused equal2



strtok2(const string[], &index, seperator=' ')
{
    new length = strlen(string);
    new offset = index;
    new result[MAX_STRING];
    while ((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1)))
    {
    result[index - offset] = string[index];
    index++;
    }
    result[index - offset] = EOS;
    if ((index < length) && (string[index] == seperator))
    {
    index++;
    }
    return result;
}

#pragma unused strtok2



stock mod2(up, down)
{
    return up-(floatround((up/down), floatround_floor))*down;
}

#pragma unused mod2



stock div2(up, down)
{
    return (floatround((up/down), floatround_floor));
}

#pragma unused div2



stock num_hash2(buf[])
{
    new length=strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for(n = 0; n < length; n++)
    {
    s1 = (s1 + buf[n]) % 65521;
    s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

#pragma unused num_hash2



stock hash2(str2[])
{
    new tmpdasdsa[MAX_STRING];
    tmpdasdsa[0] = 0;
    valstr(tmpdasdsa, num_hash(str2));
    return tmpdasdsa;
}

#pragma unused hash2



strreplace2(trg[], newstr[], src[])
{
    new f = 0;
    new s1[MAX_STRING];
    new tmp[MAX_STRING];
    format(s1, sizeof(s1), "%s", src);
    f = strfind(s1, trg);
    tmp[0] = 0;
    while(f >= 0)
    {
    strcat(tmp, ret_memcpy2(s1, 0, f));
    strcat(tmp, newstr);
    format(s1, sizeof(s1), "%s", ret_memcpy2(s1, f+strlen(trg), strlen(s1)-f));
    f = strfind(s1, trg);
    }
    strcat(tmp,s1);
    return tmp;
}

#pragma unused strreplace2



strlower2(txt[])
{
    new tmp[MAX_STRING];
    tmp[0] = 0;
    if(txt[0] == 0) return tmp;
    new i = 0;
    for(i = 0; i < strlen(txt); i++)
    {
    tmp[i] = tolower(txt[i]);
    }
    tmp[strlen(txt)] = 0;
    return tmp;
}

#pragma unused strlower2



strupper2(txt[])
{
    new tmp[MAX_STRING];
    tmp[0] = 0;
    if (txt[0] == 0) return tmp;
    new i = 0;
    for (i = 0; i <strlen(txt); i++)
    {
    tmp[i] = toupper(txt[i]);
    }
    tmp[strlen(txt)] = 0;
    return tmp;
}

#pragma unused strupper2