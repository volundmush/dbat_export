#pragma once

#include "structs.h"

// global variables
extern const struct guild_info_type guild_info[6];
extern const char *d_race_types[NUM_RACES+1];

// functions
extern void racial_body_parts(struct char_data *ch);

extern void set_height_and_weight_by_race(struct char_data *ch);

extern int invalid_race(struct char_data *ch, struct obj_data *obj);

extern bool race_isPC(int race_id);
extern int race_getSize(int race_id);
extern const char* race_getAbbr(int race_id);
extern const char* race_getAbbrLower(int race_id);
extern const char* race_getName(int race_id);
extern const char* race_getNameLower(int race_id);
extern bool race_NoisyTransforms(int race_id);
extern bool race_HasTail(int race_id);
extern bool race_canTransform(int race_id);
extern bool race_canRevert(int race_id);
extern bool race_isPeople(int race_id);
extern bool race_isValidSex(int race_id, int sex_id);
extern int race_getRPPCost(int race_id);
extern int race_getRPPRefund(int race_id);
extern bool race_CanBeMimiced(int race_id);
extern int race_findName(char *arg);
extern bool race_valid(int race_id);