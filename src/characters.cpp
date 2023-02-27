//
// Created by basti on 10/24/2021.
//
#include "characters.h"
#include "races.h"
#include "utils.h"
#include "spells.h"
#include "comm.h"
#include "class.h"
#include "fight.h"
#include "act.movement.h"
#include "weather.h"

static const char* robot = "Robotic-Humanoid";
static const char *robot_lower = "robotic-humanoid";


const char* ch_juggleRaceName(struct char_data *ch, bool capitalized) {
    int apparent = ch->race;

    switch (apparent) {
        case RACE_HOSHIJIN:
            if (ch->mimic) apparent = ch->mimic-1;
            break;
        case RACE_HALFBREED:
            switch (RACIAL_PREF(ch)) {
                case 1:
                    apparent = RACE_HUMAN;
                    break;
                case 2:
                    apparent = RACE_SAIYAN;
                    break;
            }
            break;
        case RACE_ANDROID:
            switch (RACIAL_PREF(ch)) {
                case 1:
                    apparent = RACE_ANDROID;
                    break;
                case 2:
                    apparent = RACE_HUMAN;
                    break;
                case 3:
                    if (capitalized) {
                        return robot;
                    } else {
                        return robot_lower;
                    }
            }
            break;
        case RACE_SAIYAN:
            if (PLR_FLAGGED(ch, PLR_TAILHIDE)) {
                apparent = RACE_HUMAN;
            }
            break;
    }

    return capitalized ? race_getName(apparent) : race_getNameLower(apparent);
}

void ch_restore_by(struct char_data *ch, struct char_data *by) {
    ch_restore(ch, false);

    act("You have been fully healed by $N!", false, ch, NULL, by, TO_CHAR | TO_SLEEP);
}

void ch_restore(struct char_data *ch, bool announce) {
    ch_restoreVitals(ch, announce);
    ch_restoreLimbs(ch, announce);
    ch_restoreStatus(ch, announce);
    ch_restoreLF(ch, announce);
}

void ch_resurrect(struct char_data *ch, enum ResurrectionMode mode) {
    // First, fully heal the character.
    ch_restore(ch, true);
    REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_ETHEREAL);
    REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_SPIRIT);
    REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_PDEATH);
    // Send them to their starting room and have them 'look'.
    char_from_room(ch);
    if (GET_DROOM(ch) != NOWHERE && GET_DROOM(ch) != 0 && GET_DROOM(ch) != 1) {
        char_to_room(ch, real_room(GET_DROOM(ch)));
    } else {
        char_to_room(ch, real_room(sen_startRoom(ch->chclass)));
    }
    look_at_room(IN_ROOM(ch), ch, 0);

    // If Costless, there's not going to be any penalties.
    int dur = 100;
    switch (mode) {
        case Costless:
            return;
        case Basic:
            if (ch->dcount >= 8 && ch->dcount < 10) {
                dur = 90;
            } else if (ch->dcount >= 5 && ch->dcount < 8) {
                dur = 75;
            } else if (ch->dcount >= 3 && ch->dcount < 5) {
                dur = 60;
            } else if (ch->dcount >= 1 && ch->dcount < 3) {
                dur = 40;
            }
            break;
        case RPP:
            dur = 100;
            break;
    }

    // Also no penalties if the character isn't at least level 10.
    if (GET_LEVEL(ch) > 9) {
        int losschance = axion_dice(0);
        send_to_char(ch,
                     "@RThe the strain of ch type of revival has caused you to be in a weakened state for 100 hours (Game time)! Strength, constitution, wisdom, intelligence, speed, and agility have been reduced by 8 points for the duration.@n\r\n");
        int str = -8, intel = -8, wis = -8, spd = -8, con = -8, agl = -8;
        if (ch->real_abils.intel <= 16) {
            intel = -4;
        }
        if (ch->real_abils.cha <= 16) {
            spd = -4;
        }
        if (ch->real_abils.dex <= 16) {
            agl = -4;
        }
        if (ch->real_abils.wis <= 16) {
            wis = -4;
        }
        if (ch->real_abils.con <= 16) {
            con = -4;
        }
        assign_affect(ch, AFF_WEAKENED_STATE, SKILL_WARP, dur, str, con, intel, agl, wis, spd);
        if (losschance >= 100) {
            int psloss = rand_number(100, 300);
            GET_PRACTICES(ch, GET_CLASS(ch)) -= psloss;
            send_to_char(ch, "@R...and a loss of @r%d@R PS!@n", psloss);
            if (GET_PRACTICES(ch, GET_CLASS(ch)) < 0) {
                GET_PRACTICES(ch, GET_CLASS(ch)) = 0;
            }
        }
    }
    GET_DTIME(ch) = 0;
    act("$n's body forms in a pool of @Bblue light@n.", true, ch, NULL, NULL, TO_ROOM);
}

void ch_ghostify(struct char_data *ch) {
    ch_restore(ch, true);
    SET_BIT_AR(AFF_FLAGS(ch), AFF_SPIRIT);
    SET_BIT_AR(AFF_FLAGS(ch), AFF_ETHEREAL);

    // upon death, ghost-bodies gain new natural limbs... unless they're a
    // cyborg and want to keep their implants.
    if (!PRF_FLAGGED(ch, PRF_LKEEP)) {
        if (PLR_FLAGGED(ch, PLR_CLLEG)) {
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_CLLEG);
        }
        if (PLR_FLAGGED(ch, PLR_CRLEG)) {
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_CRLEG);
        }
        if (PLR_FLAGGED(ch, PLR_CRARM)) {
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_CRARM);
        }
        if (PLR_FLAGGED(ch, PLR_CLARM)) {
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_CLARM);
        }
    }

    REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_KNOCKED);
    REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_SLEEP);
    REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_PARALYZE);
}

void ch_teleport_to(struct char_data *ch, IDXTYPE rnum) {
    char_from_room(ch);
    char_to_room(ch, real_room(rnum));
    look_at_room(IN_ROOM(ch), ch, 0);
    update_pos(ch);
}

bool ch_in_room_range(struct char_data *ch, IDXTYPE low_rnum, IDXTYPE high_rnum) {
    return GET_ROOM_VNUM(IN_ROOM(ch)) >= low_rnum && GET_ROOM_VNUM(IN_ROOM(ch)) <= high_rnum;
}

static uint16_t grav_threshold(int grav) {
    switch(grav) {
        case 10:
            return 5000;
        case 20:
            return 20000;
        case 30:
            return 50000;
        case 40:
            return 100000;
        case 50:
            return 200000;
        case 100:
            return 400000;
        case 200:
            return 1000000;
        case 300:
            return 5000000;
        case 400:
            return 8000000;
        case 500:
            return 15000000;
        case 1000:
            return 25000000;
        case 5000:
            return 100000000;
        case 10000:
            return 200000000;
        default:
            return 0;
    }
}

bool ch_can_tolerate_gravity(struct char_data *ch, int grav) {
    if (IS_NPC(ch)) return true;
    int tolerance = 0;
    tolerance = MAX(tolerance, sen_gravTolerance(ch->chclass));
    if (tolerance >= grav)
        return true;
    return (ch_getEffMaxPL(ch)) >= grav_threshold(grav);
}

int ch_calcTier(struct char_data *ch) {
    int tier = ch->level / 10;
    if ((ch->level % 10) == 0)
        tier--;
    tier = MAX(tier, 0);
    tier = MIN(tier, 9);
    return tier;
}

int64_t ch_calc_soft_cap(struct char_data *ch) {
    int tier = ch_calcTier(ch);
    int64_t *softmap = ch_getSoftMap(ch);
    return ch->level * softmap[tier];
}

bool ch_is_soft_cap(struct char_data *ch, int64_t type, long double mult) {
    if (IS_NPC(ch))
        return true;

    // Level 100 characters are never softcapped.
    if (ch->level >= 100) {
        return false;
    }
    int64_t cur_cap = ch_calc_soft_cap(ch) * mult;

    int64_t against = 0;

    switch (ch_getSoftType(ch)) {
        case 0:
            switch (type) {
                case 0: {
                    against = ch_getBasePL(ch);
                }
                    break;
                case 1: {
                    against = ch->baseki;
                }
                    break;
                case 2: {
                    against = ch_getBaseST(ch);
                }
                    break;
            }
            break;
        case 1: {
            against = ((ch_getBasePL(ch))) + ((ch->baseki)) + ((ch_getBaseST(ch)));
        }
            if (IS_ANDROID(ch) && type > 0) {
                cur_cap += type;
            }
            break;
    }
    return against >= cur_cap;
}



int ch_wearing_android_canister(struct char_data *ch) {
    if (!IS_ANDROID(ch))
        return 0;
    struct obj_data *obj = GET_EQ(ch, WEAR_BACKPACK);
    if (!obj)
        return 0;
    switch (GET_OBJ_VNUM(obj)) {
        case 1806:
            return 1;
        case 1807:
            return 2;
        default:
            return 0;
    }
}

int ch_calcGravCost(struct char_data *ch, int64_t num) {
    int cost = 0;
    if (!ch_can_tolerate_gravity(ch, ROOM_GRAVITY(IN_ROOM(ch))))
        cost = ROOM_GRAVITY(IN_ROOM(ch)) ^ 2;

    if (!num) {
        if (cost) {
            send_to_char(ch, "You sweat bullets straining against the current gravity.\r\n");
        }
        if (((ch_getCurST(ch))) > cost) {
            int64_t result;
            result = ch_decCurST(ch, cost, 0);
            return 1;
        } else {
            int64_t result;
            result = ch_decCurST(ch, cost, 0);
            return 0;
        }
    } else {
        return ((ch_getCurST(ch))) > (cost + num);
    }
}

int64_t ch_getCurHealth(struct char_data *ch) {
    return ch_getCurPL(ch);
}

int64_t ch_getMaxHealth(struct char_data *ch) {
    return ch_getMaxPL(ch);
}

double ch_getCurHealthPercent(struct char_data *ch) {
    return ch_getCurPLPercent(ch);
}

int64_t ch_getPercentOfCurHealth(struct char_data *ch, double amt) {
    return ch_getPercentOfCurPL(ch, amt);
}

int64_t ch_getPercentOfMaxHealth(struct char_data *ch, double amt) {
    return ch_getPercentOfMaxPL(ch, amt);
}

bool ch_isFullHealth(struct char_data *ch) {
    return ch_isFullPL(ch);
}

int64_t ch_setCurHealth(struct char_data *ch, int64_t amt) {
    ch->hit = MAX(0L, abs_i64(amt));
    return ch->hit;
}

int64_t ch_setCurHealthPercent(struct char_data *ch, double amt) {
    ch->hit = MAX(0L, (int64_t) (ch_getMaxHealth(ch) * abs_double(amt)));
    return ch->hit;
};

int64_t ch_incCurHealth(struct char_data *ch, int64_t amt, bool limit_max) {
    if (limit_max) {
        ch->health = MIN(1.0, ch->health + abs_double(amt) / (double) ch_getEffMaxPL(ch));
    }
    else {
        ch->health += abs_double(amt) / (double) ch_getEffMaxPL(ch);
    }
    return ch_getCurHealth(ch);
};

int64_t ch_decCurHealth(struct char_data *ch, int64_t amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double) ch_getEffMaxPL(ch);
    }
    ch->health = MAX(fl, ch->health - abs_double(amt) / (double) ch_getEffMaxPL(ch));
    return ch_getCurHealth(ch);
}

int64_t ch_incCurHealthPercent(struct char_data *ch, double amt, bool limit_max) {
    if (limit_max)
        ch->health = MIN(1.0, ch->health + abs_double(amt));
    else
        ch->health += abs_double(amt);
    return ch_getCurHealth(ch);
}

int64_t ch_decCurHealthPercent(struct char_data *ch, double amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double) ch_getEffMaxPL(ch);
    }
    ch->health = MAX(fl, ch->health - abs_double(amt));
    return ch_getCurHealth(ch);
}

void ch_restoreHealth(struct char_data *ch, bool announce) {
    ch->health = 1;
}

int64_t ch_getMaxPLTrans(struct char_data *ch) {
    struct transform_bonus form = ch_getCurForm(ch);
    int64_t total = 0;
    if (form.flag) {
        total = (form.bonus + ch_getEffBasePL(ch)) * form.mult;
    } else {
        total = ch_getEffBasePL(ch) * form.mult;
    }
    return total;
}

int64_t ch_getMaxPL(struct char_data *ch) {
    int64_t total = ch_getMaxPLTrans(ch);
    if (GET_KAIOKEN(ch) > 0) {
        total += (total / 10) * GET_KAIOKEN(ch);
    }
    if (AFF_FLAGGED(ch, AFF_METAMORPH)) {
        total += (total * .6);
    }
    return total;
}

int64_t ch_getCurPL(struct char_data *ch) {
    if (ch->suppression > 0) {
        return ch_getEffMaxPL(ch) * min_double(ch->health, (double)(ch->suppression) / 100);
    } else {
        return ch_getEffMaxPL(ch) * ch->health;
    }
}

int64_t ch_getEffBasePL(struct char_data *ch) {
    if (ch->original) {
        return ch_getEffBasePL(ch->original);
    }
    if (ch->clones) {
        return ch_getBasePL(ch) / (ch->clones + 1);
    } else {
        return ch_getBasePL(ch);
    }
}

int64_t ch_getBasePL(struct char_data *ch) {
    return ch->basepl;
}

double ch_getCurPLPercent(struct char_data *ch) {
    return (double)((ch_getCurPL(ch))) / (double)((ch_getMaxPL(ch)));
}

int64_t ch_getPercentOfCurPL(struct char_data *ch, double amt) {
    return ch_getCurPL(ch) * abs_double(amt);
}

int64_t ch_getPercentOfMaxPL(struct char_data *ch, double amt) {
    return ch_getMaxPL(ch) * abs_double(amt);
}

bool ch_isFullPL(struct char_data *ch) {
    return ch->health >= 1.0;
}

int64_t ch_getCurKI(struct char_data *ch) {
    return ch_getMaxKI(ch) * ch->energy;
}

int64_t ch_getMaxKI(struct char_data *ch) {
    struct transform_bonus form = ch_getCurForm(ch);
    if (form.flag) {
        return (form.bonus + ch_getEffBaseKI(ch)) * form.mult;
    } else {
        return ch_getEffBaseKI(ch);
    }
}


int64_t ch_getEffBaseKI(struct char_data *ch) {
    if (ch->original) {
        return ch_getEffBaseKI(ch->original);
    }
    if (ch->clones) {
        return ch->baseki / (ch->clones + 1);
    } else {
        return ch->baseki;
    }
}

int64_t ch_getBaseKI(struct char_data *ch) {
    return ch->baseki;
}


int64_t ch_getPercentOfCurKI(struct char_data *ch, double amt) {
    return ch_getMaxKI(ch) * ch->energy * abs_double(amt);
}


int64_t ch_getPercentOfMaxKI(struct char_data *ch, double amt) {
    return ch_getMaxKI(ch) * abs_double(amt);
}

bool ch_isFullKI(struct char_data *ch) {
    return ch->energy >= 1.0;
}

int64_t ch_setCurKI(struct char_data *ch, int64_t amt) {
    ch->mana = MAX(0L, abs_i64(amt));
    return ch->mana;
}

int64_t ch_setCurKIPercent(struct char_data *ch, double amt) {
    ch->mana = MAX(0L, (int64_t) (ch_getMaxKI(ch) * abs_double(amt)));
    return ch->mana;
};

int64_t ch_incCurKI(struct char_data *ch, int64_t amt, bool limit_max) {
    if (limit_max) {
        ch->energy = MIN(1.0, ch->energy + abs_double(amt) / (double)((ch_getMaxKI(ch))));
    }
    else {
        ch->energy += abs_double(amt) / (double) ((ch_getMaxKI(ch)));
    }
    return ch_getMaxKI(ch) * ch->energy;
};

int64_t ch_decCurKI(struct char_data *ch, int64_t amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double)((ch_getMaxKI(ch)));
    }
    ch->energy = MAX(fl, ch->energy - abs_double(amt) / (double)((ch_getMaxKI(ch))));
    return ch_getMaxKI(ch) * ch->energy;
}

int64_t ch_incCurKIPercent(struct char_data *ch, double amt, bool limit_max) {
    if (limit_max)
        ch->energy = MIN(1.0, ch->energy + abs_double(amt));
    else
        ch->energy += abs_double(amt);
    return ch_getMaxKI(ch) * ch->energy;
}

int64_t ch_decCurKIPercent(struct char_data *ch, double amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double)((ch_getMaxKI(ch)));
    }
    ch->energy = MAX(fl,ch->energy - abs_double(amt));
    return ch_getMaxKI(ch) * ch->energy;
}


void ch_restoreKI(struct char_data *ch, bool announce) {
    ch->energy = 1;
}

int64_t ch_getCurST(struct char_data *ch) {
    return ch_getMaxST(ch) * ch->stamina;
}

int64_t ch_getMaxST(struct char_data *ch) {
    struct transform_bonus form = ch_getCurForm(ch);
    if (form.flag) {
        return (form.bonus + ch_getEffBaseST(ch)) * form.mult;
    } else {
        return ch_getEffBaseST(ch);
    }
}

int64_t ch_getEffBaseST(struct char_data *ch) {
    if (ch->original) {
        return ch_getEffBaseST(ch->original);
    }
    if (ch->clones) {
        return ch_getBaseST(ch) / (ch->clones + 1);
    } else {
        return ch_getBaseST(ch);
    }
}

int64_t ch_getBaseST(struct char_data *ch) {
    return ch->basest;
}

double ch_getCurSTPercent(struct char_data *ch) {
    return (double) ch_getCurST(ch) / (double) ch_getMaxST(ch);
}

int64_t ch_getPercentOfCurST(struct char_data *ch, double amt) {
    return ch_getCurST(ch) * abs_double(amt);
}


int64_t ch_getPercentOfMaxST(struct char_data *ch, double amt) {
    return ch_getMaxST(ch) * abs_double(amt);
}

bool ch_isFullST(struct char_data *ch) {
    return ch->stamina >= 1;
}

int64_t ch_setCurST(struct char_data *ch, int64_t amt) {
    ch->move = MAX(0L, abs_i64(amt));
    return ch->move;
}


int64_t ch_setCurSTPercent(struct char_data *ch, double amt) {
    ch->move = MAX(0L, (int64_t) (ch_getMaxST(ch) * abs_double(amt)));
    return ch->move;
};

int64_t ch_incCurST(struct char_data *ch, int64_t amt, bool limit_max) {
    if (limit_max) {
        ch->stamina = MIN(1.0, ch->stamina + abs_double(amt) / (double) ((ch_getMaxST(ch))));
    }
    else {
        ch->stamina += abs_double(amt) / (double) ((ch_getMaxST(ch)));
    }
    return ch_getCurST(ch);
};

int64_t ch_decCurST(struct char_data *ch, int64_t amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double) ch_getMaxST(ch);
    }
    ch->stamina = MAX(fl, ch->stamina - abs_double(amt) / (double) ((ch_getMaxST(ch))));
    return ch_getCurST(ch);
}

int64_t ch_incCurSTPercent(struct char_data *ch, double amt, bool limit_max) {
    if (limit_max)
        ch->stamina = MIN(1.0, ch->stamina + abs_double(amt));
    else
        ch->stamina += abs_double(amt);
    return ch_getMaxST(ch);
}

int64_t ch_decCurSTPercent(struct char_data *ch, double amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double)((ch_getMaxST(ch)));
    }
    ch->stamina = MAX(fl, ch->stamina - abs_double(amt));
    return ch_getCurST(ch);
}


void ch_restoreST(struct char_data *ch, bool announce) {
    ch->stamina = 1;
}

int64_t ch_getCurLF(struct char_data *ch) {
    return ch_getMaxLF(ch) * ch->life;
}

int64_t ch_getMaxLF(struct char_data *ch) {
    return (IS_DEMON(ch) ? (((GET_MAX_MANA(ch) * 0.5) + (GET_MAX_MOVE(ch) * 0.5)) * 0.75) + GET_LIFEBONUSES(ch)
                           : (IS_KONATSU(ch) ? (((GET_MAX_MANA(ch) * 0.5) + (GET_MAX_MOVE(ch) * 0.5)) * 0.85) +
                                                 GET_LIFEBONUSES(ch) : (GET_MAX_MANA(ch) * 0.5) +
                                                                         (GET_MAX_MOVE(ch) * 0.5) +
                                                                         GET_LIFEBONUSES(ch)));
}

double ch_getCurLFPercent(struct char_data *ch) {
    return ch->life;
}

int64_t ch_getPercentOfCurLF(struct char_data *ch, double amt) {
    return ch_getCurLF(ch) * abs_double(amt);
}

int64_t ch_getPercentOfMaxLF(struct char_data *ch, double amt) {
    return ch_getMaxLF(ch) * abs_double(amt);
}

bool ch_isFullLF(struct char_data *ch) {
    return ch->life >= 1.0;
}

int64_t ch_setCurLF(struct char_data *ch, int64_t amt) {
    ch->life = MAX(0L, abs_i64(amt));
    return ch_getCurLF(ch);
}

int64_t ch_setCurLFPercent(struct char_data *ch, double amt) {
    ch->life = MAX(0L, (int64_t) (ch_getMaxLF(ch) * abs_double(amt)));
    return ch_getCurLF(ch);
};

int64_t ch_incCurLF(struct char_data *ch, int64_t amt, bool limit_max) {
    if (limit_max) {
        ch->life = MIN(1.0, ch->stamina + abs_double(amt) / (double) ((ch_getMaxLF(ch))));
    }
    else {
        ch->life += abs_double(amt) / (double)((ch_getMaxLF(ch)));
    }
    return ch_getCurLF(ch);
};

int64_t ch_decCurLF(struct char_data *ch, int64_t amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double)((ch_getMaxLF(ch)));
    }
    ch->life = MAX(fl, ch->life - abs_double(amt) / (double)((ch_getMaxLF(ch))));
    return ch_getCurLF(ch);
}

int64_t ch_incCurLFPercent(struct char_data *ch, double amt, bool limit_max) {
    if (limit_max)
        ch->life = MIN(1.0, ch->life + abs_double(amt));
    else
        ch->life += abs_double(amt);
    return ch_getCurLF(ch);
}

int64_t ch_decCurLFPercent(struct char_data *ch, double amt, int64_t floor) {
    double fl = 0.0;
    if (floor > 0) {
        fl = (double) floor / (double) ch_getMaxLF(ch);
    }
    ch->life = MAX(fl, ch->life - abs_double(amt));
    return ch_getCurLF(ch);
}


void ch_restoreLF(struct char_data *ch, bool announce) {
    ch->life = 1;
}


bool ch_isFullVitals(struct char_data *ch) {
    return ch_isFullHealth(ch) && ch_isFullKI(ch) && ch_isFullST(ch);
}

void ch_restoreVitals(struct char_data *ch, bool announce) {
    ch_restoreHealth(ch, announce);
    ch_restoreKI(ch, announce);
    ch_restoreST(ch, announce);
}

void ch_restoreStatus(struct char_data *ch, bool announce) {
    ch_cureStatusKnockedOut(ch, announce);
    ch_cureStatusBurn(ch, announce);
    ch_cureStatusPoison(ch, announce);
}

void ch_setStatusKnockedOut(struct char_data *ch) {
    SET_BIT_AR(AFF_FLAGS(ch), AFF_KNOCKED);
    if (AFF_FLAGGED(ch, AFF_FLYING)) {
        REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_FLYING);
        GET_ALT(ch) = 0;
    }
    GET_POS(ch) = POS_SLEEPING;
}

void ch_cureStatusKnockedOut(struct char_data *ch, bool announce) {
    if (AFF_FLAGGED(ch, AFF_KNOCKED)) {
        if (announce) {
            act("@W$n@W is no longer senseless, and wakes up.@n", false, ch, NULL, NULL, TO_ROOM);
            send_to_char(ch, "You are no longer knocked out, and wake up!@n\r\n");
        }

        if (CARRIED_BY(ch)) {
            if (GET_ALIGNMENT(CARRIED_BY(ch)) > 50) {
                carry_drop(CARRIED_BY(ch), 0);
            } else {
                carry_drop(CARRIED_BY(ch), 1);
            }
        }

        REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_KNOCKED);
        GET_POS(ch) = POS_SITTING;
    }
}

void ch_cureStatusBurn(struct char_data *ch, bool announce) {
    if (AFF_FLAGGED(ch, AFF_BURNED)) {
        if (announce) {
            send_to_char(ch, "Your burns are healed now.\r\n");
            act("$n@w's burns are now healed.@n", true, ch, NULL, NULL, TO_ROOM);
        }
        REMOVE_BIT_AR(AFF_FLAGS(ch), AFF_BURNED);
    }
}

void ch_cureStatusPoison(struct char_data *ch, bool announce) {
    act("@C$n@W suddenly looks a lot better!@b", false, ch, NULL, NULL, TO_NOTVICT);
    affect_from_char(ch, SPELL_POISON);
}

static const char* limb_names[] = {
        "right arm",
        "left arm",
        "right leg",
        "left leg"
};

void ch_restoreLimbs(struct char_data *ch, bool announce) {
    // restore head...
    GET_LIMBCOND(ch, 0) = 100;

    // limbs...
    for (int l = 0; l < 4; l++) {
        if (announce) {
            if (GET_LIMBCOND(ch, l) <= 0)
                send_to_char(ch, "Your %s grows back!\r\n", limb_names[l]);
            else if (GET_LIMBCOND(ch, l) < 50)
                send_to_char(ch, "Your %s is no longer broken!\r\n", limb_names[l]);
        }
        GET_LIMBCOND(ch, l) = 100;
    }

    // and lastly, tail.
    ch_gainTail(ch);
}

int64_t ch_gainBasePL(struct char_data *ch, int64_t amt, bool trans_mult) {
    ch->basepl += amt;
    return ch->basepl;
}

int64_t ch_gainBaseST(struct char_data *ch, int64_t amt, bool trans_mult) {
    ch->basest += amt;
    return ch->basest;
}

int64_t ch_gainBaseKI(struct char_data *ch, int64_t amt, bool trans_mult) {
    ch->baseki += amt;
    return ch->baseki;
}

int64_t ch_loseBasePL(struct char_data *ch, int64_t amt, bool trans_mult) {
    ch->basepl = MAX(1L, ch->basepl - amt);
    return ch->basepl;
}

int64_t ch_gainBasePLPercent(struct char_data *ch, double amt, bool trans_mult) {
    return ch_gainBasePL(ch, ch->basepl * amt, trans_mult);
}

int64_t ch_gainBaseKIPercent(struct char_data *ch, double amt, bool trans_mult) {
    return ch_gainBaseKI(ch, ch->baseki * amt, trans_mult);
}

int64_t ch_gainBaseSTPercent(struct char_data *ch, double amt, bool trans_mult) {
    return ch_gainBaseST(ch, ch->basest * amt, trans_mult);
}

int64_t ch_loseBasePLPercent(struct char_data *ch, double amt, bool trans_mult) {
    return ch_loseBasePL(ch, ch->basepl * amt, trans_mult);
}

void ch_gainBaseAllPercent(struct char_data *ch, double amt, bool trans_mult) {
    int64_t result2;
    result2 = ch_gainBasePLPercent(ch, amt, trans_mult);
    int64_t result1;
    result1 = ch_gainBaseKIPercent(ch, amt, trans_mult);
    int64_t result;
    result = ch_gainBaseSTPercent(ch, amt, trans_mult);
}


int64_t ch_getMaxCarryWeight(struct char_data *ch) {
    return MAX(1, (ch_getMaxPL(ch) / 200) + (GET_STR(ch) * 50));
}

int64_t ch_getCurGearWeight(struct char_data *ch) {
    int64_t total_weight = 0;

    for (int i = 0; i < NUM_WEARS; i++) {
        if (GET_EQ(ch, i)) {
            total_weight += GET_OBJ_WEIGHT(GET_EQ(ch, i));
        }
    }
    return total_weight;
}

int64_t ch_getCurCarriedWeight(struct char_data *ch) {
    return ch_getCurGearWeight(ch) + ch->carry_weight;
}

int64_t ch_getAvailableCarryWeight(struct char_data *ch) {
    return ch_getMaxCarryWeight(ch) - ch_getCurCarriedWeight(ch);
}

double ch_speednar(struct char_data *ch) {
    double ratio = (double) ((ch_getCurCarriedWeight(ch))) / (double)((ch_getMaxCarryWeight(ch)));
    if (ratio >= .05)
        return max_double(0.01, min_double(1.0, 1.0 - ratio));
    return 1.0;
}

int64_t ch_getEffMaxPL(struct char_data *ch) {
    return IS_NPC(ch) ? ch_getMaxPL(ch) : ch_getMaxPL(ch) * ch_speednar(ch);
}

bool ch_isWeightedPL(struct char_data *ch) {
    return ch_getMaxPL(ch) > ch_getEffMaxPL(ch);
}

void ch_apply_kaioken(struct char_data *ch, int times, bool announce) {
    GET_KAIOKEN(ch) = times;
    REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_POWERUP);

    if (announce) {
        send_to_char(ch, "@rA dark red aura bursts up around your body as you achieve Kaioken x %d!@n\r\n", times);
        act("@rA dark red aura bursts up around @R$n@r as they achieve a level of Kaioken!@n", true, ch, NULL,
              NULL, TO_ROOM);
    }

}

void ch_remove_kaioken(struct char_data *ch, int8_t announce) {
    int kaio = GET_KAIOKEN(ch);
    if (!kaio) {
        return;
    }
    GET_KAIOKEN(ch) = 0;

    switch (announce) {
        case 1:
            send_to_char(ch, "You drop out of kaioken.\r\n");
            act("$n@w drops out of kaioken.@n", true, ch, NULL, NULL, TO_ROOM);
            break;
        case 2:
            send_to_char(ch, "You lose focus and your kaioken disappears.\r\n");
            act("$n loses focus and $s kaioken aura disappears.", true, ch, NULL, NULL, TO_ROOM);
    }
}

bool ch_hasTail(struct char_data *ch) {
    if (!race_HasTail(ch->race))
        return false;
    switch (ch->race) {
        case RACE_ICER:
        case RACE_BIO:
            return PLR_FLAGGED(ch, PLR_TAIL);
        case RACE_SAIYAN:
        case RACE_HALFBREED:
            return PLR_FLAGGED(ch, PLR_STAIL);
        default:
            return false;
    }
}

void ch_loseTail(struct char_data *ch) {
    if (!ch_hasTail(ch)) return;
    switch (ch->race) {
        case RACE_ICER:
        case RACE_BIO:
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_TAIL);
            remove_limb(ch, 6);
            GET_TGROWTH(ch) = 0;
            break;
        case RACE_SAIYAN:
        case RACE_HALFBREED:
            REMOVE_BIT_AR(PLR_FLAGS(ch), PLR_STAIL);
            remove_limb(ch, 5);
            if (PLR_FLAGGED(ch, PLR_OOZARU)) {
                oozaru_revert(ch);
            }
            GET_TGROWTH(ch) = 0;
            break;
    }
}

void ch_gainTail(struct char_data *ch) {
    if (ch_hasTail(ch)) return;
    switch (ch->race) {
        case RACE_ICER:
        case RACE_BIO:
            SET_BIT_AR(PLR_FLAGS(ch), PLR_TAIL);
            break;
        case RACE_SAIYAN:
        case RACE_HALFBREED:
            SET_BIT_AR(PLR_FLAGS(ch), PLR_STAIL);
            if (MOON_OK(ch)) {
                oozaru_transform(ch);
            }
            break;
    }
}

static const struct {int flag; int tier;} trans_map[] = {
        {PLR_TRANS1, 1},
        {PLR_TRANS2, 2},
        {PLR_TRANS3, 3},
        {PLR_TRANS4, 4},
        {PLR_TRANS5, 5},
        {PLR_TRANS6, 6}
};

int ch_transFlagToTier(int flag) {
    switch (flag) {
        case PLR_TRANS1:
            return 1;
        case PLR_TRANS2:
            return 2;
        case PLR_TRANS3:
            return 3;
        case PLR_TRANS4:
            return 4;
        case PLR_TRANS5:
            return 5;
        case PLR_TRANS6:
            return 6;
        default:
            return 0;
    }
}

int ch_getCurrentTransTier(struct char_data *ch) {
    int trans_tier = 0;
    for(int i = 0; i < 6; i++) {
        if(PLR_FLAGGED(ch, trans_map[i].flag)) trans_tier = MAX(trans_tier, trans_map[i].tier);
    }
    return trans_tier;
}

int ch_getMaxTransformTier(struct char_data *ch) {
    switch (ch->race) {
        case RACE_SAIYAN:
            if (PLR_FLAGGED(ch, PLR_LSSJ)) {
                return 2;
            } else {
                return 4;
            }
        case RACE_HUMAN:
        case RACE_ICER:
        case RACE_NAMEK:
        case RACE_BIO:
            return 4;
        case RACE_TRUFFLE:
        case RACE_MUTANT:
        case RACE_HALFBREED:
        case RACE_MAJIN:
        case RACE_KAI:
        case RACE_KONATSU:
            return 3;
        case RACE_ANDROID:
            return 6;
        default:
            return 0;
    }
}

bool ch_checkCanTransform(struct char_data *ch) {
    // No point checking for Saiyan/Halfbreed because it's just as expensive to check for
    // the Oozaru flag.
    if (PLR_FLAGGED(ch, PLR_OOZARU)) {
        send_to_char(ch, "You are the great Oozaru right now and can't transform!\r\n");
        return false;
    }

    if (GET_KAIOKEN(ch) > 0) {
        send_to_char(ch, "You are in kaioken right now and can't transform!\r\n");
        return false;
    }

    return true;
}

bool ch_getSoftType(struct char_data *ch) {
    switch (ch->race) {
        case RACE_BIO:
        case RACE_MAJIN:
            return 1;
        case RACE_ANDROID:
            if (PLR_FLAGGED(ch, PLR_ABSORB)) {
                return 0;
            } else {
                return 1;
            }
        default:
            return 0;
    }
}

void ch_echoTransform(struct char_data *ch, int tier) {
    switch (ch->race) {
        case RACE_HUMAN:
            switch (tier) {
                case 1:
                    act("@WYou spread your feet out and crouch slightly as a bright white aura bursts around your body. Torrents of white and blue energy burn upwards around your body while your muscles grow and become more defined at the same time. In a sudden rush of power you achieve @CSuper @cHuman @GFirst@W sending surrounding debris high into the sky!",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W crouches slightly while spreading $s feet as a bright white aura bursts up around $s body. Torrents of white and blue energy burn upwards around $s body while $s muscles grow and become more defined at the same time. In a sudden rush of power debris is sent flying high into the air with $m achieving @CSuper @cHuman @GFirst@W!",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WSuddenly a bright white aura bursts into existance around your body, you feel the intensity of your hidden potential boil until it can't be contained any longer! Waves of ki shoot out from your aura streaking outwards in many directions. A roar that shakes everything in the surrounding area sounds right as your energy reaches its potential and you achieve @CSuper @cHuman @GSecond@W!",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W is suddenly covered with a bright white aura as $e grits $s teeth, apparently struggling with the power boiling to the surface! Waves of ki shoot out from $s aura, streaking in several directions as a mighty roar shakes everything in the surrounding area. As $s aura calms $e smiles, having achieved @CSuper @cHuman @GSecond@W!",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WYou clench both of your fists as the bright white aura around your body is absorbed back into your flesh. As it is absorbed, your muscles triple in size and electricity crackles across your flesh. You grin as you feel the power of @CSuper @cHuman @GThird@W!",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W clenches both of $s fists as the bright white aura around $s body is absorbed back into $s flesh. As it is absorbed, $s muscles triple in size and bright electricity crackles across $s flesh. $e smiles as $e achieves the power of @CSuper @cHuman @GThird@W!",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WYou grit your teeth and clench your fists as a sudden surge of power begins to tear through your body! Your muscles lose volume and gain mass, condensing into sleek hyper efficiency as a spectacular shimmering white aura flows over you, flashes of multicolored light flaring up in rising stars around your new form, a corona of glory! You feel your ultimate potential realized as you ascend to @CSuper @cHuman @GFourth@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W grits $s teeth and clenches $s fists as a sudden surge of power begins to tear through $s body! $n@W's muscles lose volume and gain mass, condensing into sleek hyper efficiency as a spectacular shimmering white aura flows over $m, flashes of multicolored light flare up in rising stars around $s new form, a corona of glory! $n@W smiles as his ultimate potential is realized as $e ascends to @CSuper @cHuman @GFourth@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                default:
                    return;
            }
        case RACE_ICER:
            switch (tier) {
                case 1:
                    act("@WYou yell with pain as your body begins to grow and power surges within! Your legs expand outward to triple their previous length. Soon after your arms, chest, and head follow. Your horns grow longer and curve upwards while lastly your tail expands. You are left confidently standing, having completed your @GFirst @cTransformation@W.@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W yells with pain as $s body begins to grow and power surges outward! $s legs expand outward to triple their previous length. Soon after $s arms, chest, and head follow. $s horns grow longer and curve upwards while lastly $s tail expands. $e is left confidently standing, having completed $s @GFirst @cTransformation@W.@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WSpikes grow out from your elbows as your power begins to climb to new heights. The muscles along your forearms grow to double their former size as the spikes growing from your elbows flatten and sharpen into blades. You have achieved your @GSecond @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WSpikes grow out from @C$n@W's elbows as $s power begins to climb to new heights. The muscles along $s forearms grow to double their former size as the spikes growing from $s elbows flatten and sharpen into blades. $e has achieved your @GSecond @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WA blinding light surrounds your body while your rising power begins to rip up the ground beneath you! Your skin and torso shell begin to crack as your new body struggles to free its self. Huge chunks of debris lift free of the ground as your power begins to rise to unbelievable heights. Suddenly your old skin and torso shell burst off from your body, leaving a sleek form glowing where they had been. Everything comes crashing down as your power evens out, leaving you with your @GThird @cTransformation @Wcompleted!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA blinding light surrounds @C$n@W's body while $s rising power begins to rip up the ground beneath $m! $s skin and torso shell begin to crack as $s new body struggles to free its self. Huge chunks of debris lift free of the ground as $s power begins to rise to unbelievable heights. Suddenly $s old skin and torso shell burst off from $s body, leaving a sleek form glowing where they had been. Everything comes crashing down as @C$n@W's power evens out, leaving $m with $s @GThird @cTransformation @Wcompleted!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WA feeling of complete power courses through your viens as your body begins to change radically! You triple in height while a hard shell forms over your entire torso. Hard bones grow out from your head forming four ridges that jut outward. A hard covering grows up over your mouth and nose completing the transformation! A dark crimson aura flames around your body as you realize your @GFourth @cTransformation@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W's body begins to change radically! $e triples in height while a hard shell forms over $s entire torso. Hard bones grow out from $s head forming four ridges that jut outward. A hard covering grows up over $s mouth and nose completing the transformation! A dark crimson aura flames around @C$n@W's body as $e realizes $s @GFourth @cTransformation@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_KONATSU:
            switch (tier) {
                case 1:
                    act("@WA dark shadowy aura with flecks of white energy begins to burn around your body! Strength and agility can be felt rising up within as your form becomes blurred and ethereal looking. You smile as you realize your @GFirst @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA dark shadowy aura with flecks of white energy begins to burn around @C$n@W's body! $s form becomes blurred and ethereal-looking as $s muscles become strong and lithe. $e smiles as $e achieves $s @GFirst @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WThe shadowy aura surrounding your body burns larger than ever as dark bolts of purple electricity crackles across your skin. Your eyes begin to glow white as shockwaves of power explode outward! All the shadows in the immediate area are absorbed into your aura in an instant as you achieve your @GSecond @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WThe shadowy aura surrounding @C$n@W's body burns larger than ever as dark bolts of purple electricity crackles across $s skin. $s eyes begin to glow white as shockwaves of power explode outward! All the shadows in the immediate area are absorbed into $s aura in an instant as $e achieves $s @GSecond @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WThe shadowy aura around you explodes outward as your power begins to rise!  You're overcome with a sudden realization, that the shadows are an extension of yourself, that light isn't needed for your shadows to bloom.  With this newfound wisdom comes ability and power!  The color in your aura drains as the shadows slide inward and cling to your body like a second, solid black skin!  Shockwaves roll off of you in quick succession, pelting the surrounding area harshly!  Accompanying the waves, a pool of darkness blossoms underneath you, slowly spreading the shadows to the whole area, projecting onto any surface nearby!  Purple and black electricity crackle in your solid white aura, and you grin as you realize your @GThird @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WThe shadowy aura around $n explodes outward as $s power begins to rise!  Realization dawns on $s face, followed shortly by confidence! The color in $s aura drains as the shadows slide inward to cling to $s body like a second, solid black skin! Shockwaves roll off of $n in quick succession, pelting the surrounding area harshly!  Accompanying the waves, a pool of darkness blossoms underneath them, slowly spreading the shadows to the whole area, projecting onto any surface nearby! Purple and black electricity crackle in $s solid white aura, and he grins as $e realizes $s @GThird @DShadow @BForm@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_NAMEK:
            switch (tier) {
                case 1:
                    act("@WYou crouch down and clench your fists as your muscles begin to bulge! Sweat pours down your body as the ground beneath your feet cracks and warps under the pressure of your rising ki! With a sudden burst that sends debris flying you realize a new plateau in your power, having achieved @CSuper @gNamek @GFirst@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wcrouches down and clenches $s fists as $s muscles begin to bulge! Sweat pours down $s body as the ground beneath $s feet cracks and warps under the pressure of  $s rising ki! With a sudden burst that sends debris flying $e seems to realize a new plateau in $s power, having achieved @CSuper @gNamek @GFirst@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WYou gasp in shock as a power within your body that you had not been aware of begins to surge to the surface! Your muscles grow larger as energy crackles between your antennae intensely! A shockwave of energy explodes outward as you achieve a new plateau in power, @CSuper @gNamek @GSecond@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wgasps in shock as a power within $s body begins to surge out! $s muscles grow larger as energy crackles between $s antennae intensely! A shockwave of energy explodes outward as $e achieves a new plateau in power, @CSuper @gNamek @GSecond@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WA fierce clear aura bursts up around your body as you struggle to control a growing power within! Energy leaks off of your aura at an astounding rate filling the air around you with small orbs of ki. As your power begins to level off the ambient ki hovering around you is absorbed inward in a sudden shock that leaves your skin glowing! You have achieved a rare power, @CSuper @gNamek @GThird@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA fierce clear aura bursts up around @C$n@W's body as $e struggles to control $s own power! Energy leaks off of $s aura at an astounding rate filling the air around $m with small orbs of ki. As $s power begins to level off the ambient ki hovering around $m is absorbed inward in a sudden shock that leaves $s skin glowing! $e has achieved a rare power, @CSuper @gNamek @GThird@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WAn inner calm fills your mind as your power surges higher than ever before. Complete clarity puts everything once questioned into perspective. While this inner calm is filling your mind, an outer storm of energy erupts around your body! The storm of energy boils and crackles while growing larger. You have achieved @CSuper @gNamek @GFourth@W, a mystery of the ages.@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W smiles calmly as a look of complete understand fills $s eyes. While $e remains perfectly calm and detached a massivly powerful storm of energy erupts from his body. This storm of energy shimmers with the colors of the rainbow and boils and crackles with awesome power! $s smile disappears as he realizes a mysterious power of the ages, @CSuper @gNamek @GFourth@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_MUTANT:
            switch (tier) {
                case 1:
                    act("@WYour flesh grows tougher as power surges up from within. Your fingernails grow longer, sharper, and more claw-like. Lastly your muscles double in size as you achieve your @GFirst @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W flesh grows tougher as power surges up around $m. $s fingernails grow longer, sharper, and more claw-like. Lastly $s muscles double in size as $e achieves $s @GFirst @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WSpikes grow out from your elbows as your power begins to climb to new heights. The muscles along your forearms grow to double their former size as the spikes growing from your elbows flatten and sharpen into blades. You have achieved your @GSecond @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WSpikes grow out from @C$n@W's elbows as $s power begins to climb to new heights. The muscles along $s forearms grow to double their former size as the spikes growing from $s elbows flatten and sharpen into blades. $e has achieved your @GSecond @mMutation@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WA dark cyan aura bursts up around your body as the ground begins to crack beneath you! You scream out in pain as your power begins to explode! Two large spikes grow out from your shoulder blades as you reach your @GThird @mMutation!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA dark cyan aura bursts up around @C$n@W's body as the ground begins to crack beneath $m and $e screams out in pain as $s power begins to explode! Two large spikes grow out from $s shoulder blades as $e reaches $s @GThird @mMutation!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_HALFBREED:
        case RACE_SAIYAN:
            switch (tier) {
                case 1:
                    act("@WSomething inside your mind snaps as your rage spills over! Lightning begins to strike the ground all around you as you feel torrents of power rushing through every fiber of your being. Your hair suddenly turns golden as your eyes change to the color of emeralds. In a final rush of power a golden aura rushes up around your body! You have become a @CSuper @YSaiyan@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W screams in rage as lightning begins to crash all around! $s hair turns golden and $s eyes change to an emerald color as a bright golden aura bursts up around $s body! As $s energy stabilizes $e wears a fierce look upon $s face, having transformed into a @CSuper @YSaiyan@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    if (PLR_FLAGGED(ch, PLR_LSSJ)) {
                        act("@WYou roar and then stand at your full height. You flex every muscle in your body as you feel your strength grow! Your eyes begin to glow @wwhite@W with energy, your hair turns @Ygold@W, and at the same time a @wbright @Yg@yo@Yl@yd@Ye@yn@W aura flashes up around your body! You release your @YL@ye@Dg@We@wn@Yd@ya@Dr@Yy@W power upon the universe!@n",
                            true, ch, NULL, NULL, TO_CHAR);
                        act("@C$n @Wroars and then stands at $s full height. Then $s muscles start to buldge and grow as $e flexes them! Suddenly $s eyes begin to glow @wwhite@W with energy, $s hair turns @Ygold@W, and at the same time a @wbright @Yg@yo@Yl@yd@Ye@yn@W aura flashes up around $s body! @C$n@W releases $s @YL@ye@Dg@We@wn@Yd@ya@Dr@Yy@W power upon the universe!@n",
                            true, ch, NULL, NULL, TO_ROOM);
                        return;
                    } else {
                        act("@WBlinding rage burns through your mind as a sudden eruption of energy surges forth! A golden aura bursts up around your body, glowing as bright as the sun. Rushing winds rocket out from your body in every direction as bolts of electricity begin to crackle in your aura. As your aura dims you are left standing confidently, having achieved @CSuper @YSaiyan @GSecond@W!@n",
                            true, ch, NULL, NULL, TO_CHAR);
                        act("@C$n@W stands up straight with $s head back as $e releases an ear piercing scream! A blindingly bright golden aura bursts up around $s body, glowing as bright as the sun. As rushing winds begin to rocket out from $m in every direction, bolts of electricity flash and crackle in $s aura. As $s aura begins to dim $e is left standing confidently, having achieved @CSuper @YSaiyan @GSecond@W!@n",
                            true, ch, NULL, NULL, TO_ROOM);
                    }
                    return;
                case 3:
                    act("@WElectricity begins to crackle around your body as your aura grows explosively! You yell as your powerlevel begins to skyrocket while your hair grows to multiple times the length it was previously. Your muscles become incredibly dense instead of growing in size, preserving your speed. Finally your irises appear just as your transformation becomes complete, having achieved @CSuper @YSaiyan @GThird@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WElectricity begins to crackle around @C$n@W, as $s aura grows explosively! $e yells as the energy around $m skyrockets and $s hair grows to multiple times its previous length. $e smiles as $s irises appear and $s muscles tighten up. $s transformation complete, $e now stands confidently, having achieved @CSuper @YSaiyan @GThird@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WHaving absorbed enough blutz waves, your body begins to transform! Red fur grows over certain parts of your skin as your hair grows longer and unkempt. A red outline forms around your eyes while the irises of those very same eyes change to an amber color. Energy crackles about your body violently as you achieve the peak of saiyan perfection, @CSuper @YSaiyan @GFourth@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WHaving absorbed enough blutz waves, @C$n@W's body begins to transform! Red fur grows over certain parts of $s skin as $s hair grows longer and unkempt. A red outline forms around $s eyes while the irises of those very same eyes change to an amber color. Energy crackles about $s body violently as $e achieves the peak of saiyan perfection, @CSuper @YSaiyan @GFourth@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_BIO:
            switch (tier) {
                case 1:
                    act("@gYou bend over as @rpain@g wracks your body! Your limbs begin to grow out, becoming more defined and muscular. As your limbs finish growing outward you feel a painful sensation coming from your back as a long tail with a spike grows out of your back! As the pain subsides you stand up straight and a current of power shatters part of the ground beneath you. You have @rmatured@g beyond your @Gl@ga@Dr@gv@Ga@ge stage!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@W$n @gbends over as a @rpainful@g look covers $s face! $s limbs begin to grow out, becoming more defined and muscular. As $s limbs finish growing outward $e screams as a long tail with a spike grows rips out of $s back! As $e calms $e stands up straight and a current of power shatters part of the ground beneath $m. $e has @rmatured@g beyond $s @Gl@ga@Dr@gv@Ga@ge stage!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WYour exoskeleton begins to glow spectacularly while the shape of your body begins to change. Your tail shrinks slightly. Your hands, feet, and facial features become more refined. While your body colors change slightly. The crests on your head change, standing up straighter on either side of your head as well. As you finish transforming a wave of power floods your being. You have achieved your @gSemi@D-@GPerfect @BForm@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W's exoskeleton begins to glow spectacularly while the shape of $s body begins to change. $s tail shrinks slightly. $s hands, feet, and facial features become more refined. While $s body colors change slightly. The crests on $s head change, standing up straighter on either side of $s head as well. As $e finishes transforming a wave of power rushes out from $m. $e has achieved $s @gSemi@D-@GPerfect @BForm@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WYour whole body is engulfed in blinding light as your exoskeleton begins to change shape! Your hands, feet, and facial features become more refined and humanoid. While your colors change, becoming more subdued and neutral. A bright golden aura bursts up around your body as you achieve your @GPerfect @BForm@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W whole body is engulfed in blinding light as $s exoskeleton begins to change shape! $s hands, feet, and facial features become more refined and humanoid. While $s colors change, becoming more subdued and neutral. A bright golden aura bursts up around $s body as $e achieves $s @GPerfect @BForm@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WA rush of power explodes from your perfect body, crushing nearby debris and sending dust billowing in all directions. Electricity crackles throughout your aura intensely while your muscles grow slightly larger but incredibly dense. You smile as you realize that you have taken your perfect form beyond imagination. You are now @CSuper @GPerfect@W!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA rush of power explodes from @C$n@W's perfect body, crushing nearby debris and sending dust billowing in all directions. Electricity crackles throughout $s aura intensely while $s muscles grow slightly larger but incredibly dense. $e smiles as $e has taken $s perfect form beyond imagination. $e is now @CSuper @GPerfect@W!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_ANDROID:
            switch (tier) {
                case 1:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 5:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 6:
                    act("@WYou stop for a moment as the nano-machines within your body reprogram and restructure you. You are now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n @Wstops for a moment as the nano-machines within $s body reprogram and restructure $m. $e is now more powerful and efficient!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_MAJIN:
            switch (tier) {
                case 1:
                    act("@WA dark pink aura bursts up around your body as images of good and evil fill your mind! You feel the power within your body growing intensely, reflecting your personal alignment as your body changes!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WA dark pink aura bursts up around @C$n@W's body as images of good and evil fill $s mind! $e feels the power within $s body growing intensely, reflecting $s personal alignment as $s body changes!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WAn intense pink aura surrounds your body as it begins to change, taking on the characteristics of those you have ingested! Explosions of pink energy burst into existence all around you as your power soars to sights unseen!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WAn intense pink aura surrounds @C$n@W's body as it begins to change, taking on the characteristics of those $e has ingested! Explosions of pink energy burst into existence all around $m as $s power soars to sights unseen!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WRipples of intense pink energy rush upwards around your body as it begins to morph into its truest form! The ground beneath your feet forms into a crater from the very pressure of your rising ki! Earthquakes shudder throughout the area as your finish morphing!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@WRipples of intense pink energy rush upwards around @C$n@W's body as it begins to morph into its truest form! The ground beneath $s feet forms into a crater from the very pressure of $s rising ki! Earthquakes shudder throughout the area as $e finishes morphing!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_KAI:
            switch (tier) {
                case 1:
                    act("@WThoughts begin to flow through your mind of events throughout your life. The progression leads up to more recent events and finally to this very moment. All of it's significance overwhelms you momentarily and your motivation and drive increase. As your attention is drawn back to your surroundings, you feel as though your thinking, senses, and reflexes have sharpened dramatically.  At the core of your being, a greater depth of power can be felt.@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@W$n@W's face tenses, it becoming clear momentarily that they are deep in thought. After a brief lapse in focus, their attention seems to return to their surroundings. Though it's not apparent why they were so distracted, something definitely seems different about $m.@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WYou feel a sudden rush of emotion, escalating almost to a loss of control as your thoughts race. Your heart begins to beat fast as memories mix with the raw emotion. A faint blue glow begins to surround you. As your emotions level off, you feel a deeper understanding of the universe as you know it. You visibly calm back down to an almost steely eyed resolve as you assess your surroundings. The blue aura wicks around you for a few moments and then dissipates. Thought it's full impact is not yet clear to you, you are left feeling as though both your power and inner strength have turned into nearly bottomless wells.@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@W$n@W's appears to be hit by some sudden pangs of agony, their face contorted in pain.  After a moment a faint blue aura appears around them, glowing brighter as time passes. You can feel something in the pit of your stomach, letting you know that something very significant is changing around you. Before long $n@W's aura fades, leaving a very determined looking person in your presence.@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WYour minds' eye becomes overwhelmed by secrets unimaginable. The threads of the very universe become visible in your heightened state of awareness. Reaching out, a single thread vibrates, producing a @Rred @Wcolor -- yours. Your fingertips brush against it and your senses become clouded by a vast expanse of white color and noise. As your vision and hearing return, you understand the threads tying every living being together. Your awareness has expanded beyond comprehension!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W's eyes grow wide, mouth agape. $s body begins to shiver uncontrollably! $s arms reaches out cautiously before falling back down to $s side. $s face relaxes visibly, features returning to a normal state. $s irises remain larger than before, a slight smile softening $s gaze.@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_TRUFFLE:
            switch (tier) {
                case 1:
                    act("@WYour mind accelerates working through the mysteries of the universe while at the same time your body begins to change! Innate nano-technology within your body begins to activate, forming flexible metal plating across parts of your skin!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@W begins to write complicated calculations in the air as though $e were possessed while at the same time $s body begins to change! Innate nano-technology within $s body begins to activate, forming flexible metal plating across parts of $s skin!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@WComplete understanding of every physical thing floods your mind as the nano-technology within you continues to change your body! Your eyes change; becoming glassy, hard, and glowing. Your muscles merge with a nano-fiber strengthening them at the molecular level! Finally your very bones become plated in nano-metals that have yet to be invented naturally!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n@.s nano-technology continues to change $s body! $s eyes change; becoming glassy, hard, and glowing. $s muscles merge with a nano-fiber strengthening them at the molecular level! Finally $s very bones become plated in nano-metals that have yet to be invented naturally!@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@WYou have reached the final stage of enlightenment and the nano-technology thriving inside you begin to initiate the changes! Your neural pathways become refined, your reflexes honed, your auditory and ocular senses sharpening far beyond normal levels! Your gravitational awareness improves, increasing sensitivity and accuracy in your equilibrum!@n",
                        true, ch, NULL, NULL, TO_CHAR);
                    act("@C$n begins to mumble quietly, slowly at first and gradually picking up speed. A glint is seen from $s eyes and $s arms reach outwards briefly as $e appears to catch his balance. $s arms drop back to $s sides as balance is regained, a vicious smile on $s face.@n",
                        true, ch, NULL, NULL, TO_ROOM);
                    return;

            }
    }
    send_to_char(ch,
                 "You strain and scream and... hold on, you don't have a transformation. How did this happen? Go tell an admin!\r\n");
}

void ch_echoRevert(struct char_data *ch, int tier) {
    switch (ch->race) {
        case RACE_HUMAN:
            switch (tier) {
                case 1:
                    act("@wYou revert from @CSuper @cHuman @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cHuman @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CSuper @cHuman @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cHuman @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@wYou revert from @CSuper @cHuman @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cHuman @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 4:
                    act("@wYou revert from @CSuper @cHuman @GFourth@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cHuman @GFourth@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
            break;
        case RACE_SAIYAN:
        case RACE_HALFBREED:
            switch (tier) {
                case 4:
                    act("@wYou revert from @CSuper @cSaiyan @GFourth@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cSaiyan @GFourth@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@wYou revert from @CSuper @cSaiyan @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cSaiyan @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    if (PLR_FLAGGED(ch, PLR_LSSJ)) {
                        act("@wYou revert from your @YLegendary @CSuper Saiyan@w form.@n", true, ch, NULL,
                            NULL, TO_CHAR);
                        act("@w$n@w reverts from $s @YLegendary @CSuper Saiyan@w form@w.@n", true, ch, NULL,
                            NULL,
                            TO_ROOM);
                    } else {
                        act("@wYou revert from @CSuper @cSaiyan @GSecond@w.@n", true, ch, NULL, NULL,
                            TO_CHAR);
                        act("@w$n@w reverts from @CSuper @cSaiyan @GSecond@w.@n", true, ch, NULL, NULL,
                            TO_ROOM);
                    }
                    return;
                case 1:
                    act("@wYou revert from @CSuper @cSaiyan @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cSaiyan @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_ICER:
            switch (tier) {
                case 4:
                    act("@wYou revert from @CTransform @GFourth@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CTransform @GFourth@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@wYou revert from @CTransform @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CTransform @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CTransform @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CTransform @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 1:
                    act("@wYou revert from @CTransform @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CTransform @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_KONATSU:
            switch (tier) {
                case 3:
                    act("@wYou revert from @CShadow @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CShadow @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CShadow @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CShadow @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 1:
                    act("@wYou revert from @CShadow @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CShadow @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_NAMEK:
            switch (tier) {
                case 4:
                    act("@wYou revert from @CSuper @cNamek @GFourth@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cNamek @GFourth@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 3:
                    act("@wYou revert from @CSuper @cNamek @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cNamek @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CSuper @cNamek @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cNamek @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 1:
                    act("@wYou revert from @CSuper @cNamek @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CSuper @cNamek @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
            break;
        case RACE_MUTANT:
            switch (tier) {
                case 3:
                    act("@wYou revert from @CMutate @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMutate @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CMutate @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMutate @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 1:
                    act("@wYou revert from @CMutate @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMutate @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
        case RACE_KAI:
            switch (tier) {
                case 3:
                    act("@wYou revert from @CMystic @GThird@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMystic @GThird@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 2:
                    act("@wYou revert from @CMystic @GSecond@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMystic @GSecond@w.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
                case 1:
                    act("@wYou revert from @CMystic @GFirst@w.@n", true, ch, NULL, NULL, TO_CHAR);
                    act("@w$n@w reverts from @CMystic @GFirst.@n", true, ch, NULL, NULL, TO_ROOM);
                    return;
            }
    }
}

void ch_displayTransReq(struct char_data *ch) {
    switch (GET_TRANSCLASS(ch)) {
        case 1:
            send_to_char(ch, "\r\n@RYou have @rterrible@R transformation BPL Requirements.@n\r\n");
            break;
        case 2:
            send_to_char(ch, "\r\n@CYou have @caverage@C transformation BPL Requirements.@n\r\n");
            break;
        case 3:
            send_to_char(ch, "\r\n@GYou have @gGREAT@G transformation BPL Requirements.@n\r\n");
            break;
    }
}

bool ch_checkTransUnlock(struct char_data *ch, int tier) {
    // First, check for special requirements which are not 'paid'.
    switch (ch->race) {
        case RACE_BIO:
            if (tier > 3 - GET_ABSORBS(ch)) {
                send_to_char(ch, "You need to absorb something to transform!\r\n");
                return false;
            }
            break;
        case RACE_MAJIN:
            switch (tier) {
                case 2:
                    if (GET_ABSORBS(ch) > 0) {
                        send_to_char(ch, "You need to ingest someone before you can use that form.\r\n");
                        return false;
                    }
                    if (GET_LEVEL(ch) < 50) {
                        send_to_char(ch, "You must be at least level 50 to reach that form.\r\n");
                        return false;
                    }
            }
            break;
    }
    int rpp_cost = 0;

    // Second, check for RPP requirements.
    switch (ch->race) {
        case RACE_ANDROID:
            switch (tier) {
                case 1:
                    break; // free for androids. They pay PS instead.
                case 6:
                    rpp_cost = 5;
                    break;
                default:
                    rpp_cost = 1;
                    break;
            }
            break;
        case RACE_MAJIN:
            switch (tier) {
                case 1:
                    rpp_cost = 1;
                    break;
                case 2:
                case 3:
                    rpp_cost = 2;
                    break;
            }
            break;

        default:
            if (ch_getMaxTransformTier(ch) == tier) {
                rpp_cost = 2;
            } else {
                rpp_cost = 1;
            }
    }

    if (rpp_cost) {
        if (GET_TRANSCOST(ch, tier) == false) {
            if (GET_RP(ch) < rpp_cost) {
                send_to_char(ch, "You need %i RPP in order to unlock this transformation.\r\n", rpp_cost);
                return false;
            } else {
                GET_RP(ch) -= rpp_cost;
                GET_TRANSCOST(ch, tier) = true;
                send_to_char(ch, "You pay %i RPP to permanently unlock this transformation!\r\n", rpp_cost);
            }
        }
    }

    // Android upgrades cost PS instead of RPP. But this system has now been standardized so anything can.
    int ps_cost = 0;
    switch (ch->race) {
        case RACE_ANDROID:
            switch (tier) {
                case 1:
                    ps_cost = 50;
                    break;
            }
    }

    if (ps_cost) {
        if (GET_TRANSCOST(ch, tier) == false) {
            if (GET_PRACTICES(ch, GET_CLASS(ch)) < 50) {
                send_to_char(ch,
                             "You need %i practice points in order to obtain a transformation for the first time.\r\n",
                             ps_cost);
                return false;
            } else {
                GET_PRACTICES(ch, GET_CLASS(ch)) -= 50;
                GET_TRANSCOST(ch, tier) = true;
                send_to_char(ch, "You pay %i PS to permanently unlock this transformation!\r\n", ps_cost);
            }
        }
    }

    // if we got down this far, we have unlocked the transformation!
    return true;
}

void ch_displayForms(struct char_data *ch) {
    switch (ch->race) {
        case RACE_HUMAN:
            send_to_char(ch, "              @YSuper @CHuman@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YSuper @CHuman @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CHuman @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CHuman @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CHuman @WFourth @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_SAIYAN:
            if (PLR_FLAGGED(ch, PLR_LSSJ)) {
                send_to_char(ch, "                @YSuper @CSaiyan@n\r\n");
                send_to_char(ch, "@b-------------------------------------------------@n\r\n");
                send_to_char(ch, "@YSuper @CSaiyan @WFirst   @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                               : "??????????");
                send_to_char(ch, "@YLegendary @CSuper Saiyan @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                               : "??????????");
                send_to_char(ch, "@b-------------------------------------------------@n\r\n");
            } else {
                send_to_char(ch, "              @YSuper @CSaiyan@n\r\n");
                send_to_char(ch, "@b------------------------------------------------@n\r\n");
                send_to_char(ch, "@YSuper @CSaiyan @WFirst  @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                               : "??????????");
                send_to_char(ch, "@YSuper @CSaiyan @WSecond @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                               : "??????????");
                send_to_char(ch, "@YSuper @CSaiyan @WThird  @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                               : "??????????");
                send_to_char(ch, "@YSuper @CSaiyan @WFourth @R-@G %s BPL Req\r\n",
                             ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                               : "??????????");
                send_to_char(ch, "@b------------------------------------------------@n\r\n");
            }
            break;
        case RACE_ICER:
            send_to_char(ch, "              @YTransform@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YTransform @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YTransform @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YTransform @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@YTransform @WFourth @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_KONATSU:
            send_to_char(ch, "              @YShadow@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YShadow @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YShadow @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YShadow @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_NAMEK:
            send_to_char(ch, "              @YSuper @CNamek@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YSuper @CNamek @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CNamek @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CNamek @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CNamek @WFourth @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_MUTANT:
            send_to_char(ch, "              @YMutate@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YMutate @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YMutate @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YMutate @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_HALFBREED:
            send_to_char(ch, "              @YSuper @CSaiyan@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YSuper @CSaiyan @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CSaiyan @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper @CSaiyan @WThird  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_BIO:
            send_to_char(ch, "              @YPerfection@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YMature        @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YSemi-Perfect  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YPerfect       @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@YSuper Perfect @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_ANDROID:
            send_to_char(ch, "              @YUpgrade@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@Y1.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@Y2.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@Y3.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@Y4.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 4) * 0.75) ? add_commas(trans_req(ch, 4))
                                                                           : "??????????");
            send_to_char(ch, "@Y5.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 5) * 0.75) ? add_commas(trans_req(ch, 5))
                                                                           : "??????????");
            send_to_char(ch, "@Y6.0 @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 6) * 0.75) ? add_commas(trans_req(ch, 6))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_MAJIN:
            send_to_char(ch, "              @YMorph@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YMorph @WAffinity @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YMorph @WSuper    @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YMorph @WTrue     @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_KAI:
            send_to_char(ch, "              @YMystic@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YMystic @WFirst     @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YMystic @WSecond    @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YMystic @WThird     @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        case RACE_TRUFFLE:
            send_to_char(ch, "              @YAscend@n\r\n");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            send_to_char(ch, "@YAscend @WFirst  @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 1) * 0.75) ? add_commas(trans_req(ch, 1))
                                                                           : "??????????");
            send_to_char(ch, "@YAscend @WSecond @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 2) * 0.75) ? add_commas(trans_req(ch, 2))
                                                                           : "??????????");
            send_to_char(ch, "@YAscend @WThird @R-@G %s BPL Req\r\n",
                         ((ch_getBasePL(ch))) >= (trans_req(ch, 3) * 0.75) ? add_commas(trans_req(ch, 3))
                                                                           : "??????????");
            send_to_char(ch, "@b------------------------------------------------@n\r\n");
            break;
        default:
            send_to_char(ch, "You do not have a transformation.\r\n");
            break;
    }
}

static const struct transform_bonus base_form = {.bonus=0, .mult=1, .drain=0, .flag=0};
static const struct transform_bonus oozaru = {.bonus = 10000, .mult=2, .drain=0, .flag=PLR_OOZARU};

static const struct transform_bonus human_trans_bonus[] = {
        {.bonus=1000000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=12000000, .mult=3, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=50000000, .mult=4, .drain=.2, .flag=PLR_TRANS3},
        {.bonus=270000000, .mult=4.5, .drain=.2, .flag=PLR_TRANS4},
};

static const struct transform_bonus saiyan_trans_bonus[] = {
        {.bonus=800000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=20000000, .mult=3, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=80000000, .mult=4, .drain=.2, .flag=PLR_TRANS3},
        {.bonus=182000000, .mult=5.5, .drain=.2, .flag=PLR_TRANS4},
};

static const struct transform_bonus namekian_trans_bonus[] = {
        {.bonus=200000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=4000000, .mult=3, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=65000000, .mult=4, .drain=.2, .flag=PLR_TRANS3},
        {.bonus=230000000, .mult=4.5, .drain=.2, .flag=PLR_TRANS4},
};

static const struct transform_bonus konatsu_trans_bonus[] = {
        {.bonus=1000000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=56000000, .mult=4, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=290000000, .mult=5, .drain=.2, .flag=PLR_TRANS3}
};

static const struct transform_bonus icer_trans_bonus[] = {
        {.bonus=400000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=7000000, .mult=3, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=45000000, .mult=4, .drain=.2, .flag=PLR_TRANS3},
        {.bonus=200000000, .mult=5, .drain=.2, .flag=PLR_TRANS4},
};


static const struct transform_bonus saiyan_trans_bonus_legendary[] = {
        {.bonus=800000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=185000000, .mult=6, .drain=.2, .flag=PLR_TRANS2},
};

static const struct transform_bonus truffle_trans_bonus[] = {
        {.bonus=1300000, .mult=3, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=80000000, .mult=4, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=300000000, .mult=5, .drain=.2, .flag=PLR_TRANS3}
};

static const struct transform_bonus kai_trans_bonus[] = {
        {.bonus=1100000, .mult=3, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=115000000, .mult=4, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=270000000, .mult=5, .drain=.2, .flag=PLR_TRANS3}
};

static const struct transform_bonus halfbreed_trans_bonus[] = {
        {.bonus=900000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=16500000, .mult=4, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=240000000, .mult=5, .drain=.2, .flag=PLR_TRANS3}
};

static const struct transform_bonus mutant_trans_bonus[] = {
        {.bonus=100000, .mult=2, .drain=.1, .flag=PLR_TRANS1},
        {.bonus=8500000, .mult=3, .drain=.2, .flag=PLR_TRANS2},
        {.bonus=80000000, .mult=4, .drain=.2, .flag=PLR_TRANS3}
};

static const struct transform_bonus majin_trans_bonus[] = {
        {.bonus=1250000, .mult=2, .drain=0, .flag=PLR_TRANS1},
        {.bonus=15000000, .mult=3, .drain=0, .flag=PLR_TRANS2},
        {.bonus=340000000, .mult=4.5, .drain=0, .flag=PLR_TRANS3}
};

static const struct transform_bonus bio_trans_bonus[] = {
        {.bonus=1000000, .mult=2, .drain=0, .flag=PLR_TRANS1},
        {.bonus=8000000, .mult=3, .drain=0, .flag=PLR_TRANS2},
        {.bonus=70000000, .mult=3.5, .drain=0, .flag=PLR_TRANS3},
        {.bonus=400000000, .mult=4, .drain=0, .flag=PLR_TRANS4},
};

static const struct transform_bonus android_trans_bonus_sense[] = {
        {.bonus=12500000, .mult=1, .drain=0, .flag=PLR_TRANS1},
        {.bonus=50000000, .mult=1, .drain=0, .flag=PLR_TRANS2},
        {.bonus=312000000, .mult=1, .drain=0, .flag=PLR_TRANS3},
        {.bonus=2500000000, .mult=1, .drain=0, .flag=PLR_TRANS4},
        {.bonus=5000000000, .mult=1, .drain=0, .flag=PLR_TRANS5},
        {.bonus=10000000000, .mult=1, .drain=0, .flag=PLR_TRANS6},
};

static const struct transform_bonus android_trans_bonus[] = {
        {.bonus=5000000, .mult=1, .drain=0, .flag=PLR_TRANS1},
        {.bonus=20000000, .mult=1, .drain=0, .flag=PLR_TRANS2},
        {.bonus=125000000, .mult=1, .drain=0, .flag=PLR_TRANS3},
        {.bonus=1000000000, .mult=1, .drain=0, .flag=PLR_TRANS4},
        {.bonus=2500000000, .mult=1, .drain=0, .flag=PLR_TRANS5},
        {.bonus=5000000000, .mult=1, .drain=0, .flag=PLR_TRANS6},
};

static const struct transform_bonus hoshi_birth = {
        .bonus=0, .mult=2, .drain=0, .flag=PLR_TRANS1
};
static const struct transform_bonus hoshi_life = {
        .bonus=0, .mult=3, .drain=0, .flag=PLR_TRANS2
};

const struct transform_bonus* ch_getTransMap(struct char_data *ch) {
    switch (ch->race) {
        case RACE_ANDROID:
            if (PLR_FLAGGED(ch, PLR_SENSEM)) {
                return android_trans_bonus_sense;
            } else {
                return android_trans_bonus;
            }
        case RACE_SAIYAN:
            if (PLR_FLAGGED(ch, PLR_LSSJ)) {
                return saiyan_trans_bonus_legendary;
            } else {
                return saiyan_trans_bonus;
            }
        case RACE_HUMAN:
            return human_trans_bonus;
        case RACE_NAMEK:
            return namekian_trans_bonus;
        case RACE_ICER:
            return icer_trans_bonus;
        case RACE_KONATSU:
            return konatsu_trans_bonus;
        case RACE_MUTANT:
            return mutant_trans_bonus;
        case RACE_HALFBREED:
            return halfbreed_trans_bonus;
        case RACE_BIO:
            return bio_trans_bonus;
        case RACE_MAJIN:
            return majin_trans_bonus;
        case RACE_KAI:
            return kai_trans_bonus;
        case RACE_TRUFFLE:
            return truffle_trans_bonus;
        default:
            return NULL;
    }
}

static int64_t soft_cap_variable[] = {
        1500,
        4500,
        15000,
        45000,
        60000,
        240000,
        600000,
        750000,
        2400000,
        4500000
};

static int64_t soft_cap_fixed[] = {
        500,
        1500,
        5000,
        15000,
        20000,
        80000,
        200000,
        250000,
        800000,
        1500000
};

static int64_t soft_cap_demon[] = {
        500,
        1500,
        5000,
        25000,
        40000,
        100000,
        250000,
        300000,
        1000000,
        2000000
};

int64_t* ch_getSoftMap(struct char_data *ch) {
    switch (ch->race) {
        case RACE_DEMON:
        case RACE_KANASSAN:
            return soft_cap_demon;
        case RACE_ANDROID:
            if (PLR_FLAGGED(ch, PLR_ABSORB)) {
                return soft_cap_fixed;
            } else {
                return soft_cap_variable;
            }
        case RACE_BIO:
        case RACE_MAJIN:
            return soft_cap_variable;
        default:
            return soft_cap_fixed;
    }
}

struct transform_bonus ch_getCurForm(struct char_data *ch) {
    if (PLR_FLAGGED(ch, PLR_OOZARU)) return oozaru;
    if (IS_HOSHIJIN(ch)) {
        struct transform_bonus hoshi_form;
        double bon_mult = 0;
        switch (GET_PHASE(ch)) {
            case 0: // death phase
                return base_form;
            case 1: // birth phase
                hoshi_form = hoshi_birth;
                bon_mult = 4;
                break;
            case 2: // life phase
                hoshi_form = hoshi_life;
                bon_mult = 8;
                break;
            default:
                return base_form;
        }
        if (ETHER_STREAM(ch))
            bon_mult += .5;
        hoshi_form.bonus = (ch_getBasePL(ch) * .1) * bon_mult;
        return hoshi_form;
    }

    int tier = ch_getCurrentTransTier(ch);
    if (!tier) return base_form;
    const struct transform_bonus *t_map = ch_getTransMap(ch);
    if (!t_map) return base_form;
    return t_map[tier-1];
}

struct trans_map {
    char *name;
    int tier;
};

static const struct trans_map two_form_map[] = {{"first",  1},
                                                {"second", 2}};
static const struct trans_map three_form_map[] = {{"first",  1},
                                                  {"second", 2},
                                                  {"third",  3}};
static const struct trans_map four_form_map[] = {{"first",  1},
                                                 {"second", 2},
                                                 {"third",  3},
                                                 {"fourth", 4}};
static const struct trans_map bio_form_map[] = {{"mature",        1},
                                                {"semi-perfect",  2},
                                                {"perfect",       3},
                                                {"super-perfect", 4}};
static const struct trans_map android_form_map[] = {{"1.0", 1},
                                                    {"2.0", 2},
                                                    {"3.0", 3},
                                                    {"4.0", 4},
                                                    {"5.0", 5},
                                                    {"6.0", 6}};
static const struct trans_map majin_form_map[] = {{"affinity", 1},
                                                  {"super",    2},
                                                  {"true",     3}};

static struct transform_bonus no_form;

static const struct trans_map* ch_getTierMap(struct char_data *ch) {
    switch (ch->race) {
        case RACE_ANDROID:
            return android_form_map;
        case RACE_BIO:
            return bio_form_map;
        case RACE_MAJIN:
            return majin_form_map;
        default:
            switch (ch_getMaxTransformTier(ch)) {
                case 2:
                    return two_form_map;
                case 3:
                    return three_form_map;
                case 4:
                    return four_form_map;
                default:
                    // This shouldn't actually be possible, but this is better than throwing an exception.
                    return NULL;
            }
    }
}

struct transform_bonus ch_findForm(struct char_data *ch, char *arg) {
    int tiers = ch_getMaxTransformTier(ch);
    if(!tiers) return no_form;
    const struct trans_map* t_map = ch_getTierMap(ch);
    const struct transform_bonus* trans_bonuses = ch_getTransMap(ch);
    for (int i = 0; i < tiers; i++) {
        if (!strcasecmp(t_map[i].name, arg)) {
            return trans_bonuses[i];
        }
    }
    return no_form;
}