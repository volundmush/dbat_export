//
// Created by volund on 10/20/21.
//
#pragma once

#include "structs.h"

// functions
extern void timed_dt(struct char_data *ch);

extern void run_autowiz();

extern void reboot_wizlists();

extern void mutant_limb_regen(struct char_data *ch);

extern void set_title(struct char_data *ch, char *title);

extern void gain_level(struct char_data *ch, int whichclass);

extern void gain_exp(struct char_data *ch, int64_t gain);

extern void gain_exp_regardless(struct char_data *ch, int gain);

extern void gain_condition(struct char_data *ch, int condition, int value);

extern void point_update();

