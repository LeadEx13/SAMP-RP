#include <a_samp>
/*================================
By Freddy)
================================*/
/*
native FreddyCrateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance);
native FreddyMapIcon(Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist);
*/
stock FreddyCrateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance) return CallRemoteFunction("FreddyCrateObject", "dfffffff",modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,Float:distance);
stock FreddyMapIcon(Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist) return CallRemoteFunction("HMapIcon", "fffddf",Float:X, Float:Y, Float:Z, Markertype, Color, Float:dist);