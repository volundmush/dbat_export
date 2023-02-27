#include "races.h"
#include "utils.h"
#include "interpreter.h"
#include "spells.h"
#include "comm.h"
#include "class.h"
#include "fight.h"
#include "weather.h"
#include "characters.h"

const char *race_abbrevs[NUM_RACES + 1] = {
        "Hum",
        "Sai",
        "Ice",
        "Kon",
        "Nam",
        "Mut",
        "Kan",
        "H-B",
        "Bio",
        "And",
        "Dem",
        "Maj",
        "Kai",
        "Tru",
        "Hos",
        "Ict",
        "Sab",
        "Ser",
        "Trl",
        "Dra",
        "Arl",
        "Mnd",
        "Mec",
        "Spi",
        "\n"
};

#define Y   true
#define N   false


const char *race_display[NUM_RACES] = {
        "@B1@W) @cHuman\r\n",
        "@B2@W) @cSaiyan\r\n",
        "@B3@W) @cIcer\r\n",
        "@B4@W) @cKonatsu\r\n",
        "@B5@W) @cNamekian\r\n",
        "@B6@W) @cMutant\r\n",
        "@B7@W) @cKanassan\r\n",
        "@B8@W) @cHalf Breed\r\n",
        "@B9@W) @cBio-Android\r\n",
        "@B10@W) @cAndroid\r\n",
        "@B11@W) @cDemon\r\n",
        "@B12@W) @cMajin\r\n",
        "@B13@W) @cKai\r\n",
        "@B14@W) @cTruffle\r\n",
        "@B15@W) @cHoshijin\r\n",
        "@B16@W) @YArlian\r\n",
        "@B17@W) @GAnimal\r\n",
        "@B18@W) @MSaiba\r\n",
        "@B19@W) @BSerpent\r\n",
        "@B20@W) @ROgre\r\n",
        "@B21@W) @CYardratian\r\n",
        "@B22@W) @GLizardfolk\r\n",
        "@B23@W) @GMechanical\r\n",
        "@B24@W) @MSpirit\r\n",
};

const char *d_race_types[NUM_RACES+1] = {
        "A Disguised Human",
        "A Disguised Saiyan",
        "A Disguised Icer",
        "A Disguised Konatsu",
        "A Disguised Namekian",
        "A Disguised Mutant",
        "A Disguised Kanassan",
        "A Disguised Halfbreed",
        "A Disguised Bioandroid",
        "A Disguised Android",
        "A Disguised Demon",
        "A Disguised Majin",
        "A Disguised Kai",
        "A Disguised Truffle",
        "A Disguised Hoshijin",
        "A Disguised Animal",
        "Saiba",
        "Serpent",
        "Ogre",
        "Yardratian",
        "A Disguised Arlian",
        "Dragon",
        "mechanical",
        "Spirit",
        "\n"
};

/* Taken from the SRD under OGL, see ../doc/srd.txt for information */
int racial_ability_mods[][6] = {
/*                      Str,Con,Int,Wis,Dex,Cha */
/* RACE_HUMAN       */ {0,  0,  0,  0,  0,  0},
/* RACE_SAIYAN      */
                       {0,  -2, 0,  0,  2,  0},
/* RACE_ICER        */
                       {-2, 2,  0,  0,  0,  0},
/* RACE_KONATSU     */
                       {0,  2,  0,  0,  0,  -2},
/* RACE_NAMEK       */
                       {0,  0,  0,  0,  0,  0},
/* RACE_MUTANT      */
                       {-2, 0,  0,  0,  2,  0},
/* RACE_KANASSAN    */
                       {0,  -2, 2,  0,  2,  2},
/* RACE_HALFBREED   */
                       {2,  0,  -2, 0,  0,  -2},
/* RACE_BIO         */
                       {0,  0,  0,  0,  0,  0},
/* RACE_ANDROID     */
                       {0,  0,  0,  0,  0,  0},
/* RACE_DEMON       */
                       {0,  0,  0,  0,  0,  0},
/* RACE_MAJIN       */
                       {0,  0,  0,  0,  0,  0},
/* RACE_KAI         */
                       {0,  0,  0,  0,  0,  0},
/* RACE_TRUFFLE     */
                       {14, 8,  -4, 0,  -2, -4},
/* RACE_HOSHIJIN      */
                       {-2, 0,  0,  0,  2,  -2},
/* RACE_ANIMAL      */
                       {0,  0,  0,  0,  0,  0},
/* RACE_ORC         */
                       {4,  0,  -2, -2, 0,  -2},
/* RACE_SNAKE       */
                       {0,  0,  0,  0,  0,  0},
/* RACE_TROLL       */
                       {12, 12, -4, -2, 4,  -4},
/* RACE_MINOTAUR    */
                       {8,  4,  -4, 0,  0,  -2},
/* RACE_KOBOLD      */
                       {-4, -2, 0,  0,  2,  0},
/* RACE_LIZARDFOLK  */
                       {0,  0,  0,  0,  0,  0},
/* RACE_WARHOST     */
                       {0,  0,  0,  0,  0,  0},
/* RACE_FAERIE      */
                       {0,  0,  0,  0,  0,  0},
                       {0,  0,  0,  0,  0}
};

void racial_ability_modifiers(struct char_data *ch) {
    int chrace = 0;
    if (GET_RACE(ch) >= NUM_RACES || GET_RACE(ch) < 0) {
        log("SYSERR: Unknown race %d in racial_ability_modifiers", GET_RACE(ch));
    } else {
        chrace = GET_RACE(ch);
    }

    /*ch->real_abils.str += racial_ability_mods[chrace][0];
    ch->real_abils.con += racial_ability_mods[chrace][1];
    ch->real_abils.intel += racial_ability_mods[chrace][2];
    ch->real_abils.wis += racial_ability_mods[chrace][3];
    ch->real_abils.dex += racial_ability_mods[chrace][4];*/
}


/* Converted into metric units: cm and kg; SRD has english units. */
struct {
    int height[NUM_SEX];    /* cm */
    int heightdie;    /* 2d(heightdie) added to height */
    int weight[NUM_SEX];    /* kg */
    int weightfac;    /* added height * weightfac/100 added to weight */
} hw_info[NUM_RACES] = {
/* RACE_HUMAN      */ {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_SAIYAN     */
                      {{140, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_ICER       */
                      {{100, 111, 95},  10, {17, 18, 16}, 18},
/* RACE_KONATSU    */
                      {{121, 124, 109}, 20, {52, 59, 45}, 125},
/* RACE_NAMEK      */
                      {{137, 140, 135}, 20, {40, 45, 36}, 89},
/* RACE_MUTANT     */
                      {{141, 150, 140}, 10, {46, 54, 39}, 89},
/* RACE_KANASSAN   */
                      {{135, 135, 135}, 15, {37, 39, 36}, 63},
/* RACE_HALFBREED  */
                      {{141, 147, 135}, 30, {59, 68, 50}, 125},
/* RACE_BIO        */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_ANDROID    */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_DEMON      */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_MAJIN      */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_KAI        */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_TRUFFLE    */
                      {{40,  50,  45},  16, {16, 24, 9},  8},
/* RACE_HOSHIJIN     */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_ANIMAL     */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_ORC        */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_SNAKE      */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_TROLL      */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_MINOTAUR   */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_KOBOLD     */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_LIZARDFOLK */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_WARHOST    */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89},
/* RACE_FAERIE     */
                      {{141, 147, 135}, 26, {46, 54, 39}, 89}
};


void set_height_and_weight_by_race(struct char_data *ch) {
    int race, sex, mod;

    if (!IS_NPC(ch)) {
        return;
    }

    race = GET_RACE(ch);
    sex = GET_SEX(ch);
    if (sex < SEX_NEUTRAL || sex >= NUM_SEX) {
        log("Invalid gender in set_height_and_weight_by_race: %d", sex);
        sex = SEX_NEUTRAL;
    }
    if (race <= RACE_UNDEFINED || race >= NUM_RACES) {
        log("Invalid gender in set_height_and_weight_by_race: %d", GET_SEX(ch));
        race = RACE_UNDEFINED + 1; /* first defined race */
    }

    mod = dice(2, hw_info[race].heightdie);
    GET_HEIGHT(ch) = hw_info[race].height[sex] + mod;
    mod *= hw_info[race].weightfac;
    mod /= 100;
    GET_WEIGHT(ch) = hw_info[race].weight[sex] + mod;
}


int invalid_race(struct char_data *ch, struct obj_data *obj) {
    if (GET_ADMLEVEL(ch) >= ADMLVL_IMMORT)
        return false;

    if (OBJ_FLAGGED(obj, ITEM_ANTI_HUMAN) && IS_HUMAN(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ANTI_SAIYAN) && IS_SAIYAN(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ANTI_ICER) && IS_ICER(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ANTI_KONATSU) && IS_KONATSU(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ONLY_HUMAN) && !IS_HUMAN(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ONLY_ICER) && !IS_ICER(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ONLY_SAIYAN) && !IS_SAIYAN(ch))
        return true;

    if (OBJ_FLAGGED(obj, ITEM_ONLY_KONATSU) && !IS_KONATSU(ch))
        return true;

    return false;
}


int get_size(struct char_data *ch) {
    if (ch->size == SIZE_UNDEFINED) {
        ch->size = race_getSize(ch->race);
    }
    return ch->size;
}


const int size_bonus_table[NUM_SIZES] = {
/* XTINY */    8,
/* TINY */    4,
/* XSMALL */    2,
/* SMALL */    1,
/* MEDIUM */    0,
/* LARGE */    -1,
/* HUGE */    -2,
/* GIGANTIC */    -4,
/* COLOSSAL */    -8
};


int get_size_bonus(int sz) {
    if (sz < 0 || sz >= NUM_SIZES)
        sz = SIZE_MEDIUM;
    return size_bonus_table[sz];
}


int wield_type(int chsize, const struct obj_data *weap) {
    if (GET_OBJ_TYPE(weap) != ITEM_WEAPON) {
        return OBJ_FLAGGED(weap, ITEM_2H) ? WIELD_TWOHAND : WIELD_ONEHAND;
    } else if (chsize > GET_OBJ_SIZE(weap)) {
        return WIELD_LIGHT;
    } else if (chsize == GET_OBJ_SIZE(weap)) {
        return WIELD_ONEHAND;
    } else if (chsize == GET_OBJ_SIZE(weap) - 1) {
        return WIELD_TWOHAND;
    } else if (chsize < GET_OBJ_SIZE(weap) - 1) {
        return WIELD_NONE; /* It's just too big for you! */
    } else {
        log("unknown size vector in wield_type: chsize=%d, weapsize=%d", chsize, GET_OBJ_SIZE(weap));
        return WIELD_NONE;
    }
}

int race_bodyparts[NUM_RACES][NUM_WEARS] = {
        /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22 */
        /* U, F, F, N, N, B, H, L, F, H, A, U, A, W, W, W, W, W, B, E, E, W, M */
/* RACE_HUMAN       */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_SAIYAN      */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_ICER        */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_KONATSU     */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_NAMEK       */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_MUTANT      */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_KANASSAN    */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_HALFBREED   */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_BIO         */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_ANDROID     */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_DEMON       */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_MAJIN       */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_KAI         */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_TRUFFLE     */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_HOSHIJIN    */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_ANIMAL      */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_ORC         */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_SNAKE       */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_TROLL       */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_MINOTAUR    */
                       {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_ARLIAN      */
                       {0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_LIZARDFOLK  */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
/* RACE_WARHOST     */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/* RACE_FAERIE      */
                       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void racial_body_parts(struct char_data *ch) {
    int i;

    for (i = 1; i < NUM_WEARS; i++) {
        if (race_bodyparts[GET_RACE(ch)][i]) {
            SET_BIT_AR(BODY_PARTS(ch), i);
        } else {
            if (BODY_FLAGGED(ch, i))
                REMOVE_BIT_AR(BODY_PARTS(ch), i);
        }
    }
}


bool race_isPC(int race_id) {
    switch(race_id) {
        case RACE_ANIMAL:
        case RACE_SERPENT:
        case RACE_OGRE:
        case RACE_YARDRATIAN:
        case RACE_DRAGON:
        case RACE_MECHANICAL:
        case RACE_SPIRIT:
            return false;
        default:
            return true;
    }
}

int race_getSize(int race_id) {
    switch(race_id) {
        case RACE_TRUFFLE:
            return SIZE_SMALL;
        case RACE_ANIMAL:
            return SIZE_FINE;
        case RACE_OGRE:
            return SIZE_LARGE;
        case RACE_SPIRIT:
            return SIZE_TINY;
        default:
            return SIZE_MEDIUM;
    }
}

const char* race_getAbbr(int race_id) {
    switch(race_id) {
        case RACE_HUMAN:
            return "Hum";
        case RACE_SAIYAN:
            return "Sai";
        case RACE_ICER:
            return "Ice";
        case RACE_KONATSU:
            return "Kon";
        case RACE_NAMEK:
            return "Nam";
        case RACE_MUTANT:
            return "Mut";
        case RACE_KANASSAN:
            return "Kan";
        case RACE_HALFBREED:
            return "H-B";
        case RACE_BIO:
            return "Bio";
        case RACE_ANDROID:
            return "And";
        case RACE_DEMON:
            return "Dem";
        case RACE_MAJIN:
            return "Maj";
        case RACE_KAI:
            return "Kai";
        case RACE_TRUFFLE:
            return "Tru";
        case RACE_HOSHIJIN:
            return "Hos";
        case RACE_ANIMAL:
            return "Ani";
        case RACE_SAIBA:
            return "Sab";
        case RACE_SERPENT:
            return "Ser";
        case RACE_OGRE:
            return "Ogr";
        case RACE_YARDRATIAN:
            return "Yar";
        case RACE_ARLIAN:
            return "Arl";
        case RACE_DRAGON:
            return "Drg";
        case RACE_MECHANICAL:
            return "Mec";
        case RACE_SPIRIT:
            return "Spi";
        default:
            return "Unk";
    }
}

const char* race_getAbbrLower(int race_id) {
    static char abbr[30];
    strcpy(abbr, race_getAbbr(race_id));
    str_lower(abbr);
    return abbr;
}

const char* race_getName(int race_id) {
    switch(race_id) {
        case RACE_HUMAN:
            return "Human";
        case RACE_SAIYAN:
            return "Saiyan";
        case RACE_ICER:
            return "Icer";
        case RACE_KONATSU:
            return "Konatsu";
        case RACE_NAMEK:
            return "Namekian";
        case RACE_MUTANT:
            return "Mutant";
        case RACE_KANASSAN:
            return "Kanassan";
        case RACE_HALFBREED:
            return "Halfbreed";
        case RACE_BIO:
            return "BioAndroid";
        case RACE_ANDROID:
            return "Android";
        case RACE_DEMON:
            return "Demon";
        case RACE_MAJIN:
            return "Majin";
        case RACE_KAI:
            return "Kai";
        case RACE_TRUFFLE:
            return "Truffle";
        case RACE_HOSHIJIN:
            return "Hoshijin";
        case RACE_ANIMAL:
            return "Animal";
        case RACE_SAIBA:
            return "Saiba";
        case RACE_SERPENT:
            return "Serpent";
        case RACE_OGRE:
            return "Ogre";
        case RACE_YARDRATIAN:
            return "Yardratian";
        case RACE_ARLIAN:
            return "Arlian";
        case RACE_DRAGON:
            return "Dragon";
        case RACE_MECHANICAL:
            return "Mechanical";
        case RACE_SPIRIT:
            return "Spirit";
        default:
            return "Unknown";
    }
}

const char* race_getNameLower(int race_id) {
    static char name[30];
    strcpy(name, race_getName(race_id));
    str_lower(name);
    return name;
}

bool race_NoisyTransforms(int race_id) {
    switch(race_id) {
        case RACE_ANDROID:
            return false;
        default:
            return true;
    }
}

bool race_HasTail(int race_id) {
    switch(race_id) {
        case RACE_ICER:
        case RACE_BIO:
        case RACE_SAIYAN:
        case RACE_HALFBREED:
            return true;
        default:
            return false;
    }
}

bool race_canTransform(int race_id) {
    switch (race_id) {
        case RACE_HUMAN:
        case RACE_KAI:
        case RACE_TRUFFLE:
        case RACE_KONATSU:
        case RACE_MUTANT:
        case RACE_ICER:
        case RACE_HALFBREED:
        case RACE_NAMEK:
        case RACE_SAIYAN:
        case RACE_BIO:
        case RACE_MAJIN:
        case RACE_ANDROID:
            return true;
        default:
            return false;

    }
}

bool race_canRevert(int race_id) {
    if (!race_canTransform(race_id)) {
        return false;
    }
    switch (race_id) {
        case RACE_MAJIN:
        case RACE_ANDROID:
        case RACE_BIO:
        case RACE_TRUFFLE:
            return false;
        default:
            return true;
    }
}

bool race_isPeople(int race_id) {
    switch (race_id) {
        case RACE_ANIMAL:
        case RACE_SAIBA:
        case RACE_MECHANICAL:
        case RACE_SPIRIT:
            return false;
        default:
            return true;
    }
}

bool race_isValidSex(int race_id, int sex_id) {
    switch (race_id) {
        case RACE_NAMEK:
            return sex_id == SEX_NEUTRAL;
        default:
            return true;
    }
}

int race_getRPPCost(int race_id) {
    switch (race_id) {
        case RACE_SAIYAN:
            return 60;
        case RACE_BIO:
            return 35;
        case RACE_MAJIN:
            return 55;
        case RACE_HOSHIJIN:
            return 14;
        default:
            return 0;
    }
}

int race_getRPPRefund(int race_id) {
    switch (race_id) {
        case RACE_SAIYAN:
            return 40;
        case RACE_BIO:
            return 20;
        case RACE_MAJIN:
            return 35;
        case RACE_HOSHIJIN:
            return 15;
        default:
            return 0;
    }
}

bool race_CanBeMimiced(int race_id) {
    switch (race_id) {
        case RACE_ICER:
        case RACE_NAMEK:
        case RACE_BIO:
        case RACE_DEMON:
        case RACE_MAJIN:
        case RACE_HOSHIJIN:
        case RACE_ARLIAN:
            return false;
        default:
            return race_isPC(race_id);
    }
}

int race_findName(char *arg) {
    for(int i = 0; i < NUM_RACES; i++) {
        if(!strcasecmp(race_getName(i), arg)) return i;
    }
    return RACE_UNDEFINED;
}

bool race_valid(int race_id) {
    return (race_id >= 0 && race_id <= 23);
}