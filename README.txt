SA-MP Streamer Plugin v2.5
Copyright � Incognito 2010

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Preface
-------
This plugin streams objects, pickups, checkpoints, race checkpoints,
map icons, and 3D text labels at user-defined server ticks. Basic
area detection is also included. Because it is written entirely in
C++, much of the overhead from PAWN is avoided. This streamer, as a
result, is quite a bit faster than any other implementation currently
available in PAWN.

Information
-----------
The Windows version is streamer.dll (you will need the Microsoft .NET
Framework 3.5 SP1 or higher), and the Linux version is streamer.so.

Changelog
---------
v2.5:
- Added grid system for partitioning the game world into cells
- Added hash tables for numerous performance improvements
- Improved object streaming algorithm

v2.3.8
- Optimized a lot of streaming code
- Improved checkpoint handling
- Improved moving objects
- Resolved possible callback bugs
- Added Streamer_IsItemVisible, Streamer_DestroyAllVisibleItems,
  Streamer_CountVisibleItems, and Streamer_GetUpperBound

v2.3.7
- Fixed 3D text label crash
- Optimized more streaming code
- Resolved some checkpoint problems
- Added area detection natives and callbacks

v2.3.6
- Optimized some streaming code
- Fixed crash that may have occurred when destroying objects under
  OnDynamicObjectMoved
- Added plural tags to the data manipulation natives so that 3D text
  labels can be passed to them without a tag mismatch warning
- Added an extra ID to every item that can be set and retrieved with
  Streamer_SetIntData and Streamer_GetIntData
- Made any item that is altered with Streamer_SetFloatData or
  Streamer_SetIntData restream for every player automatically
- Added natives for each item to check if they're valid
- Consolidated all of the settings natives (with the exception of
  Streamer_TickRate) into Streamer_MaxItems and Streamer_VisibleItems

v2.3.5
- Added data manipulation natives: Streamer_GetFloatData,
  Streamer_GetIntData, Streamer_SetFloatData, and Streamer_SetIntData

v2.3.4:
- Fixed bug with OnPlayerPickUpDynamicPickup that resulted in it
  being called too many times when multiple scripts were loaded
- Fixed bug with checkpoints and race checkpoints that caused none to
  be streamed until the one that was visible was no longer in range
- Slightly improved native address finding and added an error message
  that prints in the server log when all natives cannot be found
- Consolidated all of the update natives into Streamer_Update
- Added Streamer_UpdateEx for loading items in a specified area

v2.3.3:
- Cleaned up and reorganized code
- Made the plugin automatically destroy all items created in a script
  when it is unloaded

v2.3.2:
- Added natives for toggling all dynamic checkpoints and race
  checkpoints
- Made a check to prevent too many objects, pickups, or 3D text
  labels from being created

v2.3.1:
- Fixed 3D text label attachment bug
- Fixed internal map icon ID assignment bug
- Rewrote PAWN invoke function

v2.3:
- Fixed PAWN invoke bug in Linux (thanks pod)

v2.2:
- Fixed item ID assignment bug
- Corrected another typo in the include file
- Improved moving objects slightly
- Made a few adjustments to the default streaming distances

v2.1:
- Made all streaming distances customizable via an extra optional
  parameter
- Removed global distance natives and slightly renamed a few other
  natives related to the settings to make them a bit less confusing
- Fixed a small issue with pickups that involved a typo in the
  include file
- Renamed the custom pickup callback to OnPlayerPickUpDynamicPickup
  (note the capitalization)

v2.0:
- Numerous bug fixes and optimizations
- Added support for pickups, checkpoints, race checkpoints,
  map icons, and 3D text labels
- Added optional parameters for specifying virtual worlds, interiors,
  and/or players
- Added more natives and callbacks for the new items
- Renamed and reorganized several natives

v1.1:
- Heavily modified dynamic moving objects so that they now are
  tracked in the plugin and synchronized with all players
- MoveDynamicObject now returns the time in milliseconds that it will
  take to reach the destination (just like the default native)
- Added CreatePlayerDynamicObject, CreateVWDynamicObject,
  DestroyAllDynamicObjects, CountDynamicObjects, and
  OnDynamicObjectMoved
- Optimized some streaming code and fixed a few bugs in the automatic
  setup system

v1.0:
- Initial release

Natives
-------
Settings:

native Streamer_TickRate(rate);
native Streamer_MaxItems(type, items);
native Streamer_VisibleItems(type, items);
native Streamer_CellDistance(Float:distance);
native Streamer_CellSize(Float:size);

Updates:

native Streamer_Update(playerid);
native Streamer_UpdateEx(playerid, Float:x, Float:y, Float:z);

Data Manipulation:

native Streamer_GetFloatData(type, {Text3D,_}:id, data, &Float:result);
native Streamer_GetIntData(type, {Text3D,_}:id, data);
native Streamer_SetFloatData(type, {Text3D,_}:id, data, Float:value);
native Streamer_SetIntData(type, {Text3D,_}:id, data, value);
native Streamer_GetUpperBound(type);

Miscellaneous:

native Streamer_IsItemVisible(playerid, type, {Text3D,_}:id);
native Streamer_DestroyAllVisibleItems(playerid, type);
native Streamer_CountVisibleItems(playerid, type);

Objects:

native CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamicObject(objectid);
native IsValidDynamicObject(objectid);
native SetDynamicObjectPos(objectid, Float:x, Float:y, Float:z);
native GetDynamicObjectPos(objectid, &Float:x, &Float:y, &Float:z);
native SetDynamicObjectRot(objectid, Float:rx, Float:ry, Float:rz);
native GetDynamicObjectRot(objectid, &Float:rx, &Float:ry, &Float:rz);
native MoveDynamicObject(objectid, Float:x, Float:y, Float:z, Float:speed);
native StopDynamicObject(objectid);
native DestroyAllDynamicObjects();
native CountDynamicObjects();

Pickups:

native CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamicPickup(pickupid);
native IsValidDynamicPickup(pickupid);
native DestroyAllDynamicPickups();
native CountDynamicPickups();

Checkpoints:

native CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamicCP(checkpointid);
native IsValidDynamicCP(checkpointid);
native TogglePlayerDynamicCP(playerid, checkpointid, toggle);
native TogglePlayerAllDynamicCPs(playerid, toggle);
native IsPlayerInDynamicCP(playerid, checkpointid);
native DestroyAllDynamicCPs();
native CountDynamicCPs();

Race Checkpoints:

native CreateDynamicRaceCP(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamicRaceCP(checkpointid);
native IsValidDynamicRaceCP(checkpointid);
native TogglePlayerDynamicRaceCP(playerid, checkpointid, toggle);
native TogglePlayerAllDynamicRaceCPs(playerid, toggle);
native IsPlayerInDynamicRaceCP(playerid, checkpointid);
native DestroyAllDynamicRaceCPs();
native CountDynamicRaceCPs();

Map Icons:

native CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamicMapIcon(iconid);
native IsValidDynamicMapIcon(iconid);
native DestroyAllDynamicMapIcons();
native CountDynamicMapIcons();

3D Text Labels:

native Text3D:CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:distance = 100.0);
native DestroyDynamic3DTextLabel(Text3D:id);
native IsValidDynamic3DTextLabel(Text3D:id);
native UpdateDynamic3DTextLabelText(Text3D:id, color, const text[]);
native DestroyAllDynamic3DTextLabels();
native CountDynamic3DTextLabels();

Areas:

native CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicRectangle(Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicSphere(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicCube(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1);
native DestroyDynamicArea(areaid);
native IsValidDynamicArea(areaid);
native TogglePlayerDynamicArea(playerid, areaid, toggle);
native TogglePlayerAllDynamicAreas(playerid, toggle);
native IsPlayerInDynamicArea(playerid, areaid);
native DestroyAllDynamicAreas();
native CountDynamicAreas();

Callbacks
---------
forward OnDynamicObjectMoved(objectid);
forward OnPlayerPickUpDynamicPickup(playerid, pickupid);
forward OnPlayerEnterDynamicCP(playerid, checkpointid);
forward OnPlayerLeaveDynamicCP(playerid, checkpointid);
forward OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
forward OnPlayerLeaveDynamicRaceCP(playerid, checkpointid);
forward OnPlayerEnterDynamicArea(playerid, areaid);
forward OnPlayerLeaveDynamicArea(playerid, areaid);

Definitions
-----------
#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

Enumerator
----------
enum
{
	E_STREAMER_ATTACHED_PLAYER,
	E_STREAMER_ATTACHED_VEHICLE,
	E_STREAMER_COLOR,
	E_STREAMER_DISTANCE,
	E_STREAMER_DRAW_DISTANCE,
	E_STREAMER_EXTRA_ID,
	E_STREAMER_INTERIOR_ID,
	E_STREAMER_MAX_X,
	E_STREAMER_MAX_Y,
	E_STREAMER_MAX_Z,
	E_STREAMER_MIN_X,
	E_STREAMER_MIN_Y,
	E_STREAMER_MIN_Z,
	E_STREAMER_MODEL_ID,
	E_STREAMER_MOVE_SPEED,
	E_STREAMER_MOVE_X,
	E_STREAMER_MOVE_Y,
	E_STREAMER_MOVE_Z,
	E_STREAMER_NEXT_X,
	E_STREAMER_NEXT_Y,
	E_STREAMER_NEXT_Z,
	E_STREAMER_PLAYER_ID,
	E_STREAMER_R_X,
	E_STREAMER_R_Y,
	E_STREAMER_R_Z,
	E_STREAMER_SIZE,
	E_STREAMER_TEST_LOS,
	E_STREAMER_TYPE,
	E_STREAMER_WORLD_ID,
	E_STREAMER_X,
	E_STREAMER_Y,
	E_STREAMER_Z
}

Instructions
------------
First, create a folder called plugins in your server directory if it
doesn't already exist. Place streamer.dll in it if you're using
Windows, or streamer.so if you're using Linux.

Add the following line to server.cfg so that the plugin will load the
next time the server starts: 

Windows:
plugins streamer

Linux:
plugins streamer.so

Next, put this in any filterscript or gamemode (it might be a good
idea to put it in your gamemode anyway since filterscripts can
sometimes conflict with one another):

#include <streamer>

That is it. Now simply add the plugin's natives and callbacks to your
script. Be very careful and look at the list above to ensure that you
are using them correctly�do not simply rename everything in your
script!

General Notes
-------------
- Default tickrate: 50
- Default maximum items: none (unlimited)
- Default visible items: 399 (objects); 2048 (pickups); 1024 (3D text
  labels)
- If -1 is specified for any of the optional parameters (worldid,
  interiorid, and playerid), the items will be streamed for all
  virtual worlds, interiors, and/or players.
- The tickrate does not represent any specific measurement of time
  and varies depending on the server's processing power. If items
  stream too slowly, lower the tickrate; if CPU usage gets too high,
  raise the tickrate.
- If some items are not appearing, there may be too many in one area.
  Limit the streaming distance by editing the last parameter on each
  native.
- Not all types of items have to be streamed. If the plugin is only
  used to stream objects, for example, then every other native can be
  safely ignored.
- Be careful when using streamed items with non-streamed items.
  Conflicts can sometimes arise.
- Ensure that all scripts are compiled with the latest include file.
  If the server outputs "Runtime error 19: 'File or function is not
  found'," then the gamemode is most likely compiled with an include
  file version that does not match the plugin version. 

Native Notes
------------
- Use Streamer_UpdateEx to preload items before setting a player's
  position or to stream items under OnPlayerRequestClass.
- Use the data manipulation natives like this (note the use of the
  defines and the enum above):

  Streamer_SetIntData(STREAMER_TYPE_OBJECT, gObject, E_STREAMER_MODEL_ID, 1225);

- To adjust an object's draw distance (added in SA-MP 0.3b), use
  Streamer_SetFloatData with E_STREAMER_DRAW_DISTANCE. The maximum
  draw distance is 300.0. Each object's default draw distance is 0.0.

Grid Notes
----------
- Use Streamer_CellDistance to adjust the area around which the
  plugin checks for nearby cells. Use Streamer_CellSize to adjust the
  size of each cell (this native rebuilds the grid, so use it only
  when necessary).
- It is recommended to make the cell distance a multiple of two in
  relation to the cell size. This prevents pop-in and ensures that
  all nearby cells are collected.
- The default cell distance is 400.0, and the default cell size is
  200.0. Unless there are any items with larger streaming distances
  than the default cell size, it is recommended to not increase these
  values for the best performance.
