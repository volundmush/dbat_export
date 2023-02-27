#pragma once
#include "sysdep.h"
#include "typestubs.h"
#include "structs.h"

extern struct room_data* rm_findVnum(room_vnum vnum);
extern room_vnum rm_getVnum(struct room_data *room);
extern struct zone_data* rm_getZone(struct room_data *room);
extern int rm_getSector(struct room_data *room);
