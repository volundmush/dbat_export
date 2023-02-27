#pragma once

#include "structs.h"
#include "races.h"

// global variables

extern const char *config_sect[NUM_CONFIG_SECTIONS + 1];
extern const int class_hit_die_size[NUM_CLASSES];

// functions
extern void do_start(struct char_data *ch);

extern int invalid_class(struct char_data *ch, struct obj_data *obj);

extern int level_exp(struct char_data *ch, int level);

extern int load_levels();

extern void cedit_creation(struct char_data *ch);

extern void advance_level(struct char_data *ch, int whichclass);

extern int8_t ability_mod_value(int abil);

extern int8_t dex_mod_capped(const struct char_data *ch);

extern char *class_desc_str(struct char_data *ch, int howlong, int wantthe);

extern int total_skill_levels(struct char_data *ch, int skill);

extern int highest_skill_value(int level, int type);

extern int calc_penalty_exp(struct char_data *ch, int gain);

extern time_t birth_age(struct char_data *ch);

extern time_t max_age(struct char_data *ch);

extern const char* sen_getName(int sen_id);
extern const char* sen_getNameLower(int sen_id);
extern const char* sen_getAbbr(int sen_id);
extern int sen_findName(char *arg);
extern bool sen_isPC(int sen_id);
extern bool sen_raceOK(int sen_id, int race_id);
extern bool sen_rppCost(int sen_id, int race_id);
extern int sen_gravTolerance(int sen_id);
extern room_vnum sen_startRoom(int sen_id);
extern room_vnum sen_location(int sen_id);
extern const char* sen_style(int sen_id);