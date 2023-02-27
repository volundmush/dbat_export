#pragma once

#include "sysdep.h"
#include "typestubs.h"

extern bool tech_handle_android_absorb(struct char_data *ch, struct char_data *vict);

extern bool tech_handle_zanzoken(struct char_data *ch, struct char_data *vict, const char* name);

extern void tech_handle_posmodifier(struct char_data *vict, int *pry, int *blk, int *dge, int *prob);

extern void tech_handle_fireshield(struct char_data *ch, struct char_data *vict, const char* part);

extern bool tech_handle_targeting(struct char_data *ch, char *arg, struct char_data **vict, struct obj_data **obj);

extern bool tech_handle_charge(struct char_data *ch, char *arg, double minimum, double *attperc);

extern bool tech_handle_crashdown(struct char_data *ch, struct char_data *vict);
