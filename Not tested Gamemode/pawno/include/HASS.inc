#include <a_samp>
/*================================
Hovi's Stramer System
By Hovi(hovihovi/vuch_hovi)
================================*/
/*
native HCrateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance);
native HMapIcon(Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist);
*/
stock HCrateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance) return CallRemoteFunction("HCrateObject", "dfffffff",modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance);
stock HMapIcon(Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist) return CallRemoteFunction("HMapIcon", "fffddf",Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist);