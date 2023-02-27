//
// Created by volund on 10/11/22.
//
#pragma once

#include "sysdep.h"

/*
 * Intended use of this macro is to allow external packages to work with
 * a variety of CircleMUD versions without modifications.  For instance,
 * an IS_CORPSE() macro was introduced in pl13.  Any future code add-ons
 * could take into account the CircleMUD version and supply their own
 * definition for the macro if used on an older version of CircleMUD.
 * You are supposed to compare this with the macro CIRCLEMUD_VERSION()
 * in utils.h.  See there for usage.
 */
#define _CIRCLEMUD    0x030100 /* Major/Minor/Patchlevel - MMmmPP */

/*
 * If you want equipment to be automatically equipped to the same place
 * it was when players rented, set the define below to 1.  Please note
 * that this will require erasing or converting all of your rent files.
 * And of course, you have to recompile everything.  We need this feature
 * for CircleMUD to be complete but we refuse to break binary file
 * compatibility.
 */
#define USE_AUTOEQ    1    /* TRUE/FALSE aren't defined yet. */

/* CWG Version String */
#define CWG_VERSION "CWG Rasputin - 3.5.31"
#define DBAT_VERSION "DBAT - version 2.4"

/* preamble *************************************************************/

/*
 * As of bpl20, it should be safe to use unsigned data types for the
 * various virtual and real number data types.  There really isn't a
 * reason to use signed anymore so use the unsigned types and get
 * 65,535 objects instead of 32,768.
 *
 * NOTE: This will likely be unconditionally unsigned later.
 */





#define SG_MIN        2 /* Skill gain check must be less than this
			     number in order to be successful.
			     IE: 1% of a skill gain */

/* Ocarina Songs */
enum OcarinaSongs {
    SONG_SAFETY = 1,
    SONG_SHIELDING = 2,
    SONG_SHADOW_STITCH = 3,
    SONG_TELEPORT_EARTH = 4,
    SONG_TELEPORT_KONACK = 5,
    SONG_TELEPORT_ARLIA = 6,
    SONG_TELEPORT_NAMEK = 7,
    SONG_TELEPORT_VEGETA = 8,
    SONG_TELEPORT_FRIGID = 9,
    SONG_TELEPORT_AETHER = 10,
    SONG_TELEPORT_KANASSA = 11
};


/* Fighting Preferences */
enum FightPref {
    PREFERENCE_THROWING = 1,
    PREFERENCE_H2H = 2,
    PREFERENCE_KI = 3,
    PREFERENCE_WEAPON = 4
};

/* Ingredient vnums for recipes */
enum RecipeVnum {
    RCP_TOMATO = 17212,
    RCP_POTATO = 17213,
    RCP_ONION = 17215,
    RCP_CUCUMBER = 17217,
    RCP_CHILIPEPPER = 17219,
    RCP_FOUSTAFI = 17221,
    RCP_CARROT = 17223,
    RCP_GREENBEAN = 17225,
    RCP_NORMAL_MEAT = 1612,
    RCP_GOOD_MEAT = 6500,
    RCP_BLACKBASS = 1000,
    RCP_SILVERTROUT = 1001,
    RCP_STRIPEDBASS = 1002,
    RCP_BLUECATFISH = 1003,
    RCP_FLOUNDER = 1004,
    RCP_SILVEREEL = 1005,
    RCP_COBIA = 1006,
    RCP_TAMBOR = 1007,
    RCP_NARRI = 1008,
    RCP_VALBISH = 1009,
    RCP_GUSBLAT = 1010,
    RCP_REPEEIL = 1011,
    RCP_GRAVELREBOI = 1012,
    RCP_VOOSPIKE = 1013,
    RCP_SHADOWFISH = 1014,
    RCP_SHADEEEL = 1015,
    RCP_BROWNMUSH = 1608,
    RCP_GARLIC = 1131,
    RCP_RICE = 1590,
    RCP_FLOUR = 1591,
    RCP_LETTUCE = 17227,
    RCP_APPLEPLUM = 8001,
    RCP_FROZENBERRY = 4901,
    RCP_CARAMBOLA = 3416
};


/* Meal recipes */
enum MealRecipe {
    RECIPE_TOMATO_SOUP = 1,
    RECIPE_POTATO_SOUP = 2,
    RECIPE_VEGETABLE_SOUP = 3,
    RECIPE_MEAT_STEW = 4,
    RECIPE_STEAK = 5,
    RECIPE_ROAST = 6,
    RECIPE_CHILI_SOUP = 7,
    RECIPE_GRILLED_NORMFISH = 8,
    RECIPE_GRILLED_GOODFISH = 9,
    RECIPE_GRILLED_GREATFISH = 10,
    RECIPE_GRILLED_BESTFISH = 11,
    RECIPE_COOKED_RICE = 12,
    RECIPE_SUSHI = 13,
    RECIPE_BREAD = 14,
    RECIPE_SALAD = 15,
    RECIPE_APPLEPLUM = 16,
    RECIPE_FBERRY_MUFFIN = 17,
    RECIPE_CARAMBOLA_BREAD = 18
};


/* Completed Meal Object Vnums */
enum MealObject {
    MEAL_START = 1220,
    MEAL_TOMATO_SOUP = 1220,
    MEAL_STEAK = 1221,
    MEAL_POTATO_SOUP = 1222,
    MEAL_VEGETABLE_SOUP = 1223,
    MEAL_MEAT_STEW = 1224,
    MEAL_ROAST = 1225,
    MEAL_CHILI_SOUP = 1226,
    MEAL_NORM_FISH = 1227,
    MEAL_GOOD_FISH = 1228,
    MEAL_GREAT_FISH = 1229,
    MEAL_BEST_FISH = 1230,
    MEAL_COOKED_RICE = 1231,
    MEAL_SUSHI = 1232,
    MEAL_BREAD = 1233,
    MEAL_SALAD = 1234,
    MEAL_APPLEPLUM = 1235,
    MEAL_FBERRY_MUFFIN = 1236,
    MEAL_CARAMBOLA_BREAD = 1237
};

#define MEAL_LAST                1234

/* Fishing Defines */
enum FishStatus {
    FISH_NOFISH = 0,
    FISH_BITE = 1,
    FISH_HOOKED = 2,
    FISH_REELING = 3
};

/* Shadow Dragon Defines */
enum ShadowDragon {
    SHADOW_DRAGON1_VNUM = 81,
    SHADOW_DRAGON2_VNUM = 82,
    SHADOW_DRAGON3_VNUM = 83,
    SHADOW_DRAGON4_VNUM = 84,
    SHADOW_DRAGON5_VNUM = 85,
    SHADOW_DRAGON6_VNUM = 86,
    SHADOW_DRAGON7_VNUM = 87
};


/* room-related defines *************************************************/


/* The cardinal directions: used as index to room_data.dir_option[] */
enum Directions {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    UP = 4,
    DOWN = 5,
    NORTHWEST = 6,
    NORTHEAST = 7,
    SOUTHEAST = 8,
    SOUTHWEST = 9,
    INDIR = 10,
    OUTDIR = 11
};


/* Room flags: used in room_data.room_flags */
/* WARNING: In the world files, NEVER set the bits marked "R" ("Reserved") */
enum RoomFlags {
    ROOM_DARK = 0,   /* Dark			*/
    ROOM_DEATH = 1,   /* Death trap		*/
    ROOM_NOMOB = 2,   /* MOBs not allowed		*/
    ROOM_INDOORS = 3,   /* Indoors			*/
    ROOM_PEACEFUL = 4,   /* Violence not allowed	*/
    ROOM_SOUNDPROOF = 5,   /* Shouts, gossip blocked	*/
    ROOM_NOTRACK = 6,   /* Track won't go through	*/
    ROOM_NOINSTANT = 7,   /* IT not allowed		*/
    ROOM_TUNNEL = 8,   /* room for only 1 pers	*/
    ROOM_PRIVATE = 9,   /* Can't teleport in		*/
    ROOM_GODROOM = 10,  /* LVL_GOD+ only allowed	*/
    ROOM_HOUSE = 11,  /* (R) Room is a house	*/
    ROOM_HOUSE_CRASH = 12,  /* (R) House needs saving	*/
    ROOM_ATRIUM = 13,  /* (R) The door to a house	*/
    ROOM_OLC = 14,  /* (R) Modifyable/!compress	*/
    ROOM_BFS_MARK = 15,  /* (R) breath-first srch mrk	*/
    ROOM_VEHICLE = 16,  /* Requires a vehicle to pass       */
    ROOM_UNDERGROUND = 17,  /* Room is below ground      */
    ROOM_CURRENT = 18,  /* Room move with random currents	*/
    ROOM_TIMED_DT = 19,  /* Room has a timed death trap  	*/
    ROOM_EARTH = 20,  /* Room is on Earth */
    ROOM_VEGETA = 21,  /* Room is on Vegeta */
    ROOM_FRIGID = 22,  /* Room is on Frigid */
    ROOM_KONACK = 23,  /* Room is on Konack */
    ROOM_NAMEK = 24,  /* Room is on Namek */
    ROOM_NEO = 25,  /* Room is on Neo */
    ROOM_AL = 26,  /* Room is on AL */
    ROOM_SPACE = 27,  /* Room is on Space */
    ROOM_HELL = 28,  /* Room is Punishment Hell*/
    ROOM_REGEN = 29,  /* Better regen */
    ROOM_RHELL = 30,  /* Room is HELLLLLLL */
    ROOM_GRAVITYX10 = 31,  /* For rooms that have 10x grav */
    ROOM_AETHER = 32,  /* Room is on Aether */
    ROOM_HBTC = 33,  /* Room is extra special training area */
    ROOM_PAST = 34,  /* Inside the pendulum room */
    ROOM_CBANK = 35,  /* This room is a clan bank */
    ROOM_SHIP = 36,  /* This room is a private ship room */
    ROOM_YARDRAT = 37,  /* This room is on planet Yardrat   */
    ROOM_KANASSA = 38,  /* This room is on planet Kanassa   */
    ROOM_ARLIA = 39,  /* This room is on planet Arlia     */
    ROOM_AURA = 40,  /* This room has an aura around it  */
    ROOM_EORBIT = 41,  /* Earth Orbit                      */
    ROOM_FORBIT = 42,  /* Frigid Orbit                     */
    ROOM_KORBIT = 43,  /* Konack Orbit                     */
    ROOM_NORBIT = 44,  /* Namek  Orbit                     */
    ROOM_VORBIT = 45,  /* Vegeta Orbit                     */
    ROOM_AORBIT = 46,  /* Aether Orbit                     */
    ROOM_YORBIT = 47,  /* Yardrat Orbit                    */
    ROOM_KANORB = 48,  /* Kanassa Orbit                    */
    ROOM_ARLORB = 49,  /* Arlia Orbit                      */
    ROOM_NEBULA = 50,  /* Nebulae                          */
    ROOM_ASTERO = 51,  /* Asteroid                         */
    ROOM_WORMHO = 52,  /* Wormhole                         */
    ROOM_STATION = 53,  /* Space Station                    */
    ROOM_STAR = 54,  /* Is a star                        */
    ROOM_CERRIA = 55,  /* This room is on planet Cerria    */
    ROOM_CORBIT = 56,  /* This room is in Cerria's Orbit   */
    ROOM_BEDROOM = 57,  /* +25% regen                       */
    ROOM_WORKOUT = 58,  /* Workout Room                     */
    ROOM_GARDEN1 = 59,  /* 8 plant garden                   */
    ROOM_GARDEN2 = 60,  /* 20 plant garden                  */
    ROOM_FERTILE1 = 61,
    ROOM_FERTILE2 = 62,
    ROOM_FISHING = 63,
    ROOM_FISHFRESH = 64,
    ROOM_CANREMODEL = 65,
    NUM_ROOM_FLAGS = 66
};

/* Zone info: Used in zone_data.zone_flags */
enum ZoneFlags {
    ZONE_CLOSED = 0,
    ZONE_NOIMMORT = 1,
    ZONE_QUEST = 2,
    ZONE_DBALLS = 3,
    NUM_ZONE_FLAGS = 4
};


/* Exit info: used in room_data.dir_option.exit_info */
#define EX_ISDOOR        (1 << 0)   /* Exit is a door		*/
#define EX_CLOSED        (1 << 1)   /* The door is closed	*/
#define EX_LOCKED        (1 << 2)   /* The door is locked	*/
#define EX_PICKPROOF     (1 << 3)   /* Lock can't be picked	*/
#define EX_SECRET        (1 << 4)   /* The door is hidden        */

#define NUM_EXIT_FLAGS 5

/* Sector types: used in room_data.sector_type */
enum SectorType {
    SECT_INSIDE = 0,           /* Indoors			*/
    SECT_CITY = 1,           /* In a city			*/
    SECT_FIELD = 2,           /* In a field		*/
    SECT_FOREST = 3,           /* In a forest		*/
    SECT_HILLS = 4,           /* In the hills		*/
    SECT_MOUNTAIN = 5,           /* On a mountain		*/
    SECT_WATER_SWIM = 6,           /* Swimmable water		*/
    SECT_WATER_NOSWIM = 7,           /* Water - need a boat	*/
    SECT_FLYING = 8,           /* Wheee!			*/
    SECT_UNDERWATER = 9,           /* Underwater		*/
    SECT_SHOP = 10,            /* Shop                      */
    SECT_IMPORTANT = 11,            /* Important Rooms           */
    SECT_DESERT = 12,            /* A desert                  */
    SECT_SPACE = 13,            /* This is a space room      */
    SECT_LAVA = 14,            /* This room always has lava */
    NUM_ROOM_SECTORS = 15
};


/* char and mob-related defines *****************************************/

/* PC classes */
/* Taken from the SRD under OGL, see ../doc/srd.txt for information */
enum Class {
    CLASS_UNDEFINED = -1,
    CLASS_ROSHI = 0,
    CLASS_PICCOLO = 1,
    CLASS_KRANE = 2,
    CLASS_NAIL = 3,
    CLASS_BARDOCK = 4,
    CLASS_GINYU = 5,
    CLASS_FRIEZA = 6,
    CLASS_TAPION = 7,
    CLASS_ANDSIX = 8,
    CLASS_DABURA = 9,
    CLASS_KABITO = 10,
    CLASS_JINTO = 11,
    CLASS_TSUNA = 12,
    CLASS_KURZAK = 13,
    CLASS_ASSASSIN = 14,
    CLASS_BLACKGUARD = 15,
    CLASS_DRAGON_DISCIPLE = 16,
    CLASS_DUELIST = 17,
    CLASS_DWARVEN_DEFENDER = 18,
    CLASS_ELDRITCH_KNIGHT = 19,
    CLASS_HIEROPHANT = 20,
    CLASS_HORIZON_WALKER = 21,
    CLASS_LOREMASTER = 22,
    CLASS_MYSTIC_THEURGE = 23,
    CLASS_SHADOWDANCER = 24,
    CLASS_THAUMATURGIST = 25,
    CLASS_NPC_EXPERT = 26,
    CLASS_NPC_ADEPT = 27,
    CLASS_NPC_COMMONER = 28,
    CLASS_NPC_ARISTOCRAT = 29,
    CLASS_NPC_WARRIOR = 30
};

#define MAX_SENSEI              15 /* Used by Sensei Style */

#define NUM_CLASSES             31
#define NUM_NPC_CLASSES    4
#define NUM_PRESTIGE_CLASSES    15
#define NUM_BASIC_CLASSES    (14)


/* Gauntlet crap */
#define GAUNTLET_ZONE  24    /* The gauntlet zone vnum */
#define GAUNTLET_START 2403  /* The waiting room at the start of the gauntlet */
#define GAUNTLET_END   2404  /* The treasure room at the end of the gauntlet  */

/* Death Types for producing corpses with depth */
enum DeathType {
    DTYPE_NORMAL = 0,    /* Default Death Type */
    DTYPE_HEAD = 1,    /* Lost their head    */
    DTYPE_HALF = 2,    /* Blown in half      */
    DTYPE_VAPOR = 3,    /* Vaporized by attack*/
    DTYPE_PULP = 4    /* Beat to a pulp     */
};


/* Character Creation Styles */
/* Let's define bonuses/negatives */
enum BonusTraits {
    BONUS_THRIFTY = 0,
    BONUS_PRODIGY = 1,
    BONUS_QUICK_STUDY = 2,
    BONUS_DIEHARD = 3,
    BONUS_BRAWLER = 4,
    BONUS_DESTROYER = 5,
    BONUS_HARDWORKER = 6,
    BONUS_HEALER = 7,
    BONUS_LOYAL = 8,
    BONUS_BRAWNY = 9,
    BONUS_SCHOLARLY = 10,
    BONUS_SAGE = 11,
    BONUS_AGILE = 12,
    BONUS_QUICK = 13,
    BONUS_STURDY = 14,
    BONUS_THICKSKIN = 15,
    BONUS_RECIPE = 16,
    BONUS_FIREPROOF = 17,
    BONUS_POWERHIT = 18,
    BONUS_HEALTHY = 19,
    BONUS_INSOMNIAC = 20,
    BONUS_EVASIVE = 21,
    BONUS_WALL = 22,
    BONUS_ACCURATE = 23,
    BONUS_LEECH = 24,
    BONUS_GMEMORY = 25,
    BONUS_SOFT = 26,
    BONUS_LATE = 27,
    BONUS_IMPULSE = 28,
    BONUS_SICKLY = 29,
    BONUS_PUNCHINGBAG = 30,
    BONUS_PUSHOVER = 31,
    BONUS_POORDEPTH = 32,
    BONUS_THINSKIN = 33,
    BONUS_FIREPRONE = 34,
    BONUS_INTOLERANT = 35,
    BONUS_COWARD = 36,
    BONUS_ARROGANT = 37,
    BONUS_UNFOCUSED = 38,
    BONUS_SLACKER = 39,
    BONUS_SLOW_LEARNER = 40,
    BONUS_MASOCHISTIC = 41,
    BONUS_MUTE = 42,
    BONUS_WIMP = 43,
    BONUS_DULL = 44,
    BONUS_FOOLISH = 45,
    BONUS_CLUMSY = 46,
    BONUS_SLOW = 47,
    BONUS_FRAIL = 48,
    BONUS_SADISTIC = 49,
    BONUS_LONER = 50,
    BONUS_BMEMORY = 51,
    MAX_BONUSES = 52,
};

/* Distinguishing Feature */
enum DistinguishingFeature {
    DISTFEA_EYE = 0,
    DISTFEA_HAIR = 1,
    DISTFEA_SKIN = 2,
    DISTFEA_HEIGHT = 3,
    DISTFEA_WEIGHT = 4
};


/* Custom Aura */
enum AuraColor {
    AURA_WHITE = 0,
    AURA_BLUE = 1,
    AURA_RED = 2,
    AURA_GREEN = 3,
    AURA_PINK = 4,
    AURA_PURPLE = 5,
    AURA_YELLOW = 6,
    AURA_BLACK = 7,
    AURA_ORANGE = 8
};


/* Eye Color */
enum EyeColor {
    EYE_UNDEFINED = -1,
    EYE_BLUE = 0,
    EYE_BLACK = 1,
    EYE_GREEN = 2,
    EYE_BROWN = 3,
    EYE_RED = 4,
    EYE_AQUA = 5,
    EYE_PINK = 6,
    EYE_PURPLE = 7,
    EYE_CRIMSON = 8,
    EYE_GOLD = 9,
    EYE_AMBER = 10,
    EYE_EMERALD = 11
};

/*Hair Length */
enum HairLength {
    HAIRL_UNDEFINED = -1,
    HAIRL_BALD = 0,
    HAIRL_SHORT = 1,
    HAIRL_MEDIUM = 2,
    HAIRL_LONG = 3,
    HAIRL_RLONG = 4
};



/*Hair Color */
enum HairColor {
    HAIRC_UNDEFINED = -1,
    HAIRC_NONE = 0,
    HAIRC_BLACK = 1,
    HAIRC_BROWN = 2,
    HAIRC_BLONDE = 3,
    HAIRC_GREY = 4,
    HAIRC_RED = 5,
    HAIRC_ORANGE = 6,
    HAIRC_GREEN = 7,
    HAIRC_BLUE = 8,
    HAIRC_PINK = 9,
    HAIRC_PURPLE = 10,
    HAIRC_SILVER = 11,
    HAIRC_CRIMSON = 12,
    HAIRC_WHITE = 13
};


/* Hair Style */
enum HairStyle {
    HAIRS_UNDEFINED = -1,
    HAIRS_NONE = 0,
    HAIRS_PLAIN = 1,
    HAIRS_MOHAWK = 2,
    HAIRS_SPIKY = 3,
    HAIRS_CURLY = 4,
    HAIRS_UNEVEN = 5,
    HAIRS_PONYTAIL = 6,
    HAIRS_AFRO = 7,
    HAIRS_FADE = 8,
    HAIRS_CREW = 9,
    HAIRS_FEATHERED = 10,
    HAIRS_DRED = 11
};

/* Skin Color */
enum SkinColor {
    SKIN_UNDEFINED = -1,
    SKIN_WHITE = 0,
    SKIN_BLACK = 1,
    SKIN_GREEN = 2,
    SKIN_ORANGE = 3,
    SKIN_YELLOW = 4,
    SKIN_RED = 5,
    SKIN_GREY = 6,
    SKIN_BLUE = 7,
    SKIN_AQUA = 8,
    SKIN_PINK = 9,
    SKIN_PURPLE = 10,
    SKIN_TAN = 11
};


/* Annual Sign Phase */
enum SignPhase {
    PHASE_PURITY = 0,
    PHASE_BRAVERY = 1,
    PHASE_HATRED = 2,
    PHASE_DOMINANCE = 3,
    PHASE_GUARDIAN = 4,
    PHASE_LOVE = 5,
    PHASE_STRENGTH = 6
};


/* Races */
enum Race {
    RACE_UNDEFINED = -1,
    RACE_HUMAN = 0,
    RACE_SAIYAN = 1,
    RACE_ICER = 2,
    RACE_KONATSU = 3,
    RACE_NAMEK = 4,
    RACE_MUTANT = 5,
    RACE_KANASSAN = 6,
    RACE_HALFBREED = 7,
    RACE_BIO = 8,
    RACE_ANDROID = 9,
    RACE_DEMON = 10,
    RACE_MAJIN = 11,
    RACE_KAI = 12,
    RACE_TRUFFLE = 13,
    RACE_HOSHIJIN = 14,
    RACE_ANIMAL = 15,
    RACE_SAIBA = 16,
    RACE_SERPENT = 17,
    RACE_OGRE = 18,
    RACE_YARDRATIAN = 19,
    RACE_ARLIAN = 20,
    RACE_DRAGON = 21,
    RACE_MECHANICAL = 22,
    RACE_SPIRIT = 23,

    NUM_RACES = 24,
};

enum AlignGoodEvil {
    ALIGN_SAINT = 0,
    ALIGN_VALIANT = 1,
    ALIGN_HERO = 2,
    ALIGN_DOGOOD = 3,
    ALIGN_NEUTRAL = 4,
    ALIGN_CROOK = 5,
    ALIGN_VILLAIN = 6,
    ALIGN_TERRIBLE = 7,
    ALIGN_HORRIBLE = 8,

    NUM_ALIGNS = 9
};


/* Taken from the SRD under OGL, see ../doc/srd.txt for information */
enum Sizes {
    SIZE_UNDEFINED = -1,
    SIZE_FINE = 0,
    SIZE_DIMINUTIVE = 1,
    SIZE_TINY = 2,
    SIZE_SMALL = 3,
    SIZE_MEDIUM = 4,
    SIZE_LARGE = 5,
    SIZE_HUGE = 6,
    SIZE_GARGANTUAN = 7,
    SIZE_COLOSSAL = 8,
    NUM_SIZES = 9,
};

enum WieldTypes {
    WIELD_NONE = 0,
    WIELD_LIGHT = 1,
    WIELD_ONEHAND = 2,
    WIELD_TWOHAND = 3
};


/* Number of weapon types */
#define MAX_WEAPON_TYPES            26

/* Critical hit types */
enum CriticalTypes {
    CRIT_X2 = 0,
    CRIT_X3 = 1,
    CRIT_X4 = 2
};

#define MAX_CRIT_TYPE    CRIT_X4
#define NUM_CRIT_TYPES 3

/* Sex */
enum SexType {
    SEX_NEUTRAL = 0,
    SEX_MALE = 1,
    SEX_FEMALE = 2,

    NUM_SEX = 3,
};

/* Positions */
enum Positions {
    POS_DEAD = 0,    /* dead			*/
    POS_MORTALLYW = 1,    /* mortally wounded	*/
    POS_INCAP = 2,    /* incapacitated	*/
    POS_STUNNED = 3,    /* stunned		*/
    POS_SLEEPING = 4,    /* sleeping		*/
    POS_RESTING = 5,    /* resting		*/
    POS_SITTING = 6,    /* sitting		*/
    POS_FIGHTING = 7,    /* fighting		*/
    POS_STANDING = 8,    /* standing		*/
    NUM_POSITIONS = 9
};


/* AUCTIONING STATES */
enum AuctionState {
    AUC_NULL_STATE = 0,   /* not doing anything */
    AUC_OFFERING = 1,   /* object has been offfered */
    AUC_GOING_ONCE = 2,    /* object is going once! */
    AUC_GOING_TWICE = 3,    /* object is going twice! */
    AUC_LAST_CALL = 4,    /* last call for the object! */
    AUC_SOLD = 5,
/* AUCTION CANCEL STATES */
    AUC_NORMAL_CANCEL = 6,    /* normal cancellation of auction */
    AUC_QUIT_CANCEL = 7,    /* auction canclled because player quit */
    AUC_WIZ_CANCEL = 8,    /* auction cancelled by a god */
/* OTHER JUNK */
    AUC_STAT = 9,
    AUC_BID = 10
};

/* Player flags: used by char_data.act */
enum PlayerFlags {
    PLR_KILLER = 0,   /* Player is a player-killer        */
    PLR_THIEF = 1,   /* Player is a player-thief         */
    PLR_FROZEN = 2,   /* Player is frozen                 */
    PLR_DONTSET = 3,   /* Don't EVER set (ISNPC bit) 	*/
    PLR_WRITING = 4,   /* Player writing (board/mail/olc)  */
    PLR_MAILING = 5,   /* Player is writing mail           */
    PLR_CRASH = 6,   /* Player needs to be crash-saved   */
    PLR_SITEOK = 7,   /* Player has been site-cleared     */
    PLR_NOSHOUT = 8,   /* Player not allowed to shout/goss */
    PLR_NOTITLE = 9,   /* Player not allowed to set title  */
    PLR_DELETED = 10,  /* Player deleted - space reusable  */
    PLR_LOADROOM = 11,  /* Player uses nonstandard loadroom */
    PLR_NOWIZLIST = 12,  /* Player shouldn't be on wizlist  	*/
    PLR_NODELETE = 13,  /* Player shouldn't be deleted     	*/
    PLR_INVSTART = 14,  /* Player should enter game wizinvis*/
    PLR_CRYO = 15,  /* Player is cryo-saved (purge prog)*/
    PLR_NOTDEADYET = 16,  /* (R) Player being extracted.     	*/
    PLR_AGEMID_G = 17,  /* Player has had pos of middle age	*/
    PLR_AGEMID_B = 18,  /* Player has had neg of middle age	*/
    PLR_AGEOLD_G = 19,  /* Player has had pos of old age	*/
    PLR_AGEOLD_B = 20,  /* Player has had neg of old age	*/
    PLR_AGEVEN_G = 21,  /* Player has had pos of venerable age	*/
    PLR_AGEVEN_B = 22,  /* Player has had neg of venerable age	*/
    PLR_OLDAGE = 23,  /* Player is dead of old age	*/
    PLR_RARM = 24,  /* Player has a right arm           */
    PLR_LARM = 25,  /* Player has a left arm            */
    PLR_RLEG = 26,  /* Player has a right leg           */
    PLR_LLEG = 27,  /* Player has a left leg            */
    PLR_HEAD = 28,  /* Player has a head                */
    PLR_STAIL = 29,  /* Player has a saiyan tail         */
    PLR_TAIL = 30,  /* Player has a non-saiyan tail     */
    PLR_PILOTING = 31,  /* Player is sitting in the pilots chair */
    PLR_SKILLP = 32,  /* Player made a good choice in CC  */
    PLR_SPAR = 33,  /* Player is in a spar stance       */
    PLR_CHARGE = 34,  /* Player is charging               */
    PLR_TRANS1 = 35,  /* Transformation 1                 */
    PLR_TRANS2 = 36,  /* Transformation 2                 */
    PLR_TRANS3 = 37,  /* Transformation 3                 */
    PLR_TRANS4 = 38,  /* Transformation 4                 */
    PLR_TRANS5 = 39,  /* Transformation 5                 */
    PLR_TRANS6 = 40,  /* Transformation 6                 */
    PLR_ABSORB = 41,  /* Absorb model                     */
    PLR_REPAIR = 42,  /* Repair model                     */
    PLR_SENSEM = 43,  /* Sense-Powersense model           */
    PLR_POWERUP = 44,  /* Powering Up                      */
    PLR_KNOCKED = 45,  /* Knocked OUT                      */
    PLR_CRARM = 46,  /* Cybernetic Right Arm             */
    PLR_CLARM = 47,  /* Cybernetic Left Arm              */
    PLR_CRLEG = 48,  /* Cybernetic Right Leg             */
    PLR_CLLEG = 49,  /* Cybernetic Left Leg              */
    PLR_FPSSJ = 50,  /* Full Power Super Saiyan          */
    PLR_IMMORTAL = 51,  /* The player is immortal           */
    PLR_EYEC = 52,  /* The player has their eyes closed */
    PLR_DISGUISED = 53,  /* The player is disguised          */
    PLR_BANDAGED = 54,  /* THe player has been bandaged     */
    PLR_PR = 55,  /* Has had their potential released */
    PLR_HEALT = 56,  /* Is inside a healing tank         */
    PLR_FURY = 57,  /* Is in fury mode                  */
    PLR_POSE = 58,  /* Ginyu Pose Effect                */
    PLR_OOZARU = 59,
    PLR_ABSORBED = 60,
    PLR_MULTP = 61,
    PLR_PDEATH = 62,
    PLR_THANDW = 63,
    PLR_SELFD = 64,
    PLR_SELFD2 = 65,
    PLR_SPIRAL = 66,
    PLR_BIOGR = 67,
    PLR_LSSJ = 68,
    PLR_REPLEARN = 69,
    PLR_FORGET = 70,
    PLR_TRANSMISSION = 71,
    PLR_FISHING = 72,
    PLR_GOOP = 73,
    PLR_MULTIHIT = 74,
    PLR_AURALIGHT = 75,
    PLR_RDISPLAY = 76,
    PLR_STOLEN = 77,
    PLR_TAILHIDE = 78,  /* Hides tail for S & HB            */
    PLR_NOGROW = 79,  /* Halt Growth for S & HB           */

    NUM_PLR_FLAGS = 80,
};


/* Mob Personalty */
#define MAX_PERSONALITIES 5

/* Mobile flags: used by char_data.act */
enum MobFlags {
    MOB_SPEC = 0,  /* Mob has a callable spec-proc   	*/
    MOB_SENTINEL = 1,  /* Mob should not move            	*/
    MOB_NOSCAVENGER = 2,  /* Mob won't pick up items from rooms*/
    MOB_ISNPC = 3,  /* (R) Automatically set on all Mobs */
    MOB_AWARE = 4,  /* Mob can't be backstabbed          */
    MOB_AGGRESSIVE = 5,  /* Mob auto-attacks everybody nearby	*/
    MOB_STAY_ZONE = 6,  /* Mob shouldn't wander out of zone  */
    MOB_WIMPY = 7,  /* Mob flees if severely injured  	*/
    MOB_AGGR_EVIL = 8,  /* Auto-attack any evil PC's		*/
    MOB_AGGR_GOOD = 9,  /* Auto-attack any good PC's      	*/
    MOB_AGGR_NEUTRAL = 10, /* Auto-attack any neutral PC's   	*/
    MOB_MEMORY = 11, /* remember attackers if attacked    */
    MOB_HELPER = 12, /* attack PCs fighting other NPCs    */
    MOB_NOCHARM = 13, /* Mob can't be charmed         	*/
    MOB_NOSUMMON = 14, /* Mob can't be summoned             */
    MOB_NOSLEEP = 15, /* Mob can't be slept           	*/
    MOB_AUTOBALANCE = 16, /* Mob stats autobalance		*/
    MOB_NOBLIND = 17, /* Mob can't be blinded         	*/
    MOB_NOKILL = 18, /* Mob can't be killed               */
    MOB_NOTDEADYET = 19, /* (R) Mob being extracted.          */
    MOB_MOUNTABLE = 20, /* Mob is mountable.			*/
    MOB_RARM = 21, /* Player has a right arm            */
    MOB_LARM = 22, /* Player has a left arm             */
    MOB_RLEG = 23, /* Player has a right leg            */
    MOB_LLEG = 24, /* Player has a left leg             */
    MOB_HEAD = 25, /* Player has a head                 */
    MOB_JUSTDESC = 26, /* Mob doesn't use auto desc         */
    MOB_HUSK = 27, /* Is an extracted Husk              */
    MOB_SPAR = 28, /* This is mob sparring              */
    MOB_DUMMY = 29, /* This mob will not fight back      */
    MOB_ABSORB = 30, /* Absorb type android               */
    MOB_REPAIR = 31, /* Repair type android               */
    MOB_NOPOISON = 32, /* No poison                         */
    MOB_KNOWKAIO = 33, /* Knows kaioken                     */
    MOB_POWERUP = 34, /* Is powering up                    */
    NUM_MOB_FLAGS = 35
};


/*  flags: used by char_data.player_specials.pref */
enum PrefFlags {
    PRF_BRIEF = 0,  /* Room descs won't normally be shown	*/
    PRF_COMPACT = 1,  /* No extra CRLF pair before prompts		*/
    PRF_DEAF = 2,  /* Can't hear shouts              		*/
    PRF_NOTELL = 3,  /* Can't receive tells		    	*/
    PRF_DISPHP = 4,  /* Display hit points in prompt  		*/
    PRF_DISPMANA = 5,  /* Display mana points in prompt    		*/
    PRF_DISPMOVE = 6,  /* Display move points in prompt 		*/
    PRF_AUTOEXIT = 7,  /* Display exits in a room          		*/
    PRF_NOHASSLE = 8,  /* Aggr mobs won't attack           		*/
    PRF_QUEST = 9,  /* On quest					*/
    PRF_SUMMONABLE = 10, /* Can be summoned				*/
    PRF_NOREPEAT = 11, /* No repetition of comm commands		*/
    PRF_HOLYLIGHT = 12, /* Can see in dark				*/
    PRF_COLOR = 13, /* Color					*/
    PRF_SPARE = 14, /* Used to be second color bit		*/
    PRF_NOWIZ = 15, /* Can't hear wizline			*/
    PRF_LOG1 = 16, /* On-line System Log (low bit)		*/
    PRF_LOG2 = 17, /* On-line System Log (high bit)		*/
    PRF_NOAUCT = 18, /* Can't hear auction channel		*/
    PRF_NOGOSS = 19, /* Can't hear gossip channel			*/
    PRF_NOGRATZ = 20, /* Can't hear grats channel			*/
    PRF_ROOMFLAGS = 21, /* Can see room flags (ROOM_x)		*/
    PRF_DISPAUTO = 22, /* Show prompt HP, MP, MV when < 30%.	*/
    PRF_CLS = 23, /* Clear screen in OasisOLC 			*/
    PRF_BUILDWALK = 24, /* Build new rooms when walking		*/
    PRF_AFK = 25, /* Player is AFK				*/
    PRF_AUTOLOOT = 26, /* Loot everything from a corpse		*/
    PRF_AUTOGOLD = 27, /* Loot gold from a corpse			*/
    PRF_AUTOSPLIT = 28, /* Split gold with group			*/
    PRF_FULL_EXIT = 29, /* Shows full autoexit details		*/
    PRF_AUTOSAC = 30, /* Sacrifice a corpse 			*/
    PRF_AUTOMEM = 31, /* Memorize spells				*/
    PRF_VIEWORDER = 32, /* if you want to see the newest first 	*/
    PRF_NOCOMPRESS = 33, /* If you want to force MCCP2 off          	*/
    PRF_AUTOASSIST = 34, /* Auto-assist toggle                      	*/
    PRF_DISPKI = 35, /* Display ki points in prompt 		*/
    PRF_DISPEXP = 36, /* Display exp points in prompt 		*/
    PRF_DISPTNL = 37, /* Display TNL exp points in prompt 		*/
    PRF_TEST = 38, /* Sets triggers safety off for imms         */
    PRF_HIDE = 39, /* Hide on who from other mortals            */
    PRF_NMWARN = 40, /* No mail warning                           */
    PRF_HINTS = 41, /* Receives hints                            */
    PRF_FURY = 42, /* Sees fury meter                           */
    PRF_NODEC = 43,
    PRF_NOEQSEE = 44,
    PRF_NOMUSIC = 45,
    PRF_LKEEP = 46,
    PRF_DISTIME = 47, /* Part of Prompt Options */
    PRF_DISGOLD = 48, /* Part of Prompt Options */
    PRF_DISPRAC = 49, /* Part of Prompt Options */
    PRF_NOPARRY = 50,
    PRF_DISHUTH = 51, /* Part of Prompt Options */
    PRF_DISPERC = 52, /* Part of Prompt Options */
    PRF_CARVE = 53,
    PRF_ARENAWATCH = 54,
    PRF_NOGIVE = 55,
    PRF_INSTRUCT = 56,
    PRF_GHEALTH = 57,
    PRF_IHEALTH = 58,
    PRF_ENERGIZE = 59,

    NUM_PRF_FLAGS = 60,
};


/* Player autoexit levels: used as an index to exitlevels           */
enum AutoExitLevel {
    EXIT_OFF = 0,       /* Autoexit off                     */
    EXIT_NORMAL = 1,       /* Brief display (stock behaviour)  */
    EXIT_NA = 2,       /* Not implemented - do not use     */
    EXIT_COMPLETE = 3,       /* Full display                     */
};

#define exitlevel(ch) (!IS_NPC(ch) ? (PRF_FLAGGED((ch),PRF_AUTOEXIT) ? 1 : 0 ) + (PRF_FLAGGED((ch),PRF_FULL_EXIT) ? 2 : 0 ) : 0 )
#define EXIT_LEV(ch) (exitlevel(ch))


/* Affect bits: used in char_data.affected_by */
/* WARNING: In the world files, NEVER set the bits marked "R" ("Reserved") */
enum AffBits {
    AFF_DONTUSE = 0,    /* DON'T USE! 		*/
    AFF_BLIND = 1,    /* (R) Char is blind         */
    AFF_INVISIBLE = 2,    /* Char is invisible         */
    AFF_DETECT_ALIGN = 3,    /* Char is sensitive to align*/
    AFF_DETECT_INVIS = 4,    /* Char can see invis chars  */
    AFF_DETECT_MAGIC = 5,    /* Char is sensitive to magic*/
    AFF_SENSE_LIFE = 6,    /* Char can sense hidden life*/
    AFF_WATERWALK = 7,    /* Char can walk on water    */
    AFF_SANCTUARY = 8,    /* Char protected by sanct.  */
    AFF_GROUP = 9,    /* (R) Char is grouped       */
    AFF_CURSE = 10,   /* Char is cursed            */
    AFF_INFRAVISION = 11,   /* Char can see in dark      */
    AFF_POISON = 12,   /* (R) Char is poisoned      */
    AFF_WEAKENED_STATE = 13,   /* Char protected from evil  */
    AFF_PROTECT_GOOD = 14,   /* Char protected from good  */
    AFF_SLEEP = 15,   /* (R) Char magically asleep */
    AFF_NOTRACK = 16,   /* Char can't be tracked     */
    AFF_UNDEAD = 17,   /* Char is undead 		*/
    AFF_PARALYZE = 18,   /* Char is paralized		*/
    AFF_SNEAK = 19,   /* Char can move quietly     */
    AFF_HIDE = 20,   /* Char is hidden            */
    AFF_UNUSED20 = 21,   /* Room for future expansion */
    AFF_CHARM = 22,   /* Char is charmed         	*/
    AFF_FLYING = 23,   /* Char is flying         	*/
    AFF_WATERBREATH = 24,   /* Char can breath non O2    */
    AFF_ANGELIC = 25,   /* Char is an angelic being  */
    AFF_ETHEREAL = 26,   /* Char is ethereal          */
    AFF_MAGICONLY = 27,   /* Char only hurt by magic   */
    AFF_NEXTPARTIAL = 28,   /* Next action cannot be full*/
    AFF_NEXTNOACTION = 29,   /* Next action cannot attack (took full action between rounds) */
    AFF_STUNNED = 30,   /* Char is stunned		*/
    AFF_TAMED = 31,   /* Char has been tamed	*/
    AFF_CDEATH = 32,   /* Char is undergoing creeping death */
    AFF_SPIRIT = 33,   /* Char has no body          */
    AFF_STONESKIN = 34,   /* Char has temporary DR     */
    AFF_SUMMONED = 35,   /* Char is summoned (i.e. transient */
    AFF_CELESTIAL = 36,   /* Char is celestial         */
    AFF_FIENDISH = 37,   /* Char is fiendish          */
    AFF_FIRE_SHIELD = 38,   /* Char has fire shield      */
    AFF_LOW_LIGHT = 39,   /* Char has low light eyes   */
    AFF_ZANZOKEN = 40,   /* Char is ready to zanzoken */
    AFF_KNOCKED = 41,   /* Char is knocked OUT!      */
    AFF_MIGHT = 42,   /* Strength +3               */
    AFF_FLEX = 43,   /* Agility +3                */
    AFF_GENIUS = 44,   /* Intelligence +3           */
    AFF_BLESS = 45,   /* Bless for better regen    */
    AFF_BURNT = 46,   /* Disintergrated corpse     */
    AFF_BURNED = 47,   /* Burned by honoo or similar skill */
    AFF_MBREAK = 48,   /* Can't charge while flagged */
    AFF_HASS = 49,   /* Does double punch damage  */
    AFF_FUTURE = 50,   /* Future Sight */
    AFF_PARA = 51,   /* Real Paralyze */
    AFF_INFUSE = 52,   /* Ki infused attacks */
    AFF_ENLIGHTEN = 53,   /* Enlighten */
    AFF_FROZEN = 54,   /* They got frozededed */
    AFF_FIRESHIELD = 55,   /* They have a blazing personality */
    AFF_ENSNARED = 56,   /* They have silk ensnaring their arms! */
    AFF_HAYASA = 57,   /* They are speedy!                */
    AFF_PURSUIT = 58,   /* Being followed */
    AFF_WITHER = 59,   /* Their body is withered */
    AFF_HYDROZAP = 60,   /* Custom Skill Kanso Suru */
    AFF_POSITION = 61,   /* Better combat position */
    AFF_SHOCKED = 62,   /* Psychic Shock          */
    AFF_METAMORPH = 63,   /* Metamorphisis, Demon's Ripoff Custom Skill */
    AFF_HEALGLOW = 64,   /* Healing Glow */
    AFF_EARMOR = 65,   /* Ethereal Armor */
    AFF_ECHAINS = 66,   /* Ethereal Chains */
    AFF_WUNJO = 67,   /* Wunjo rune */
    AFF_POTENT = 68,   /* Purisaz rune */
    AFF_ASHED = 69,   /* Leaves ash */
    AFF_PUKED = 70,
    AFF_LIQUEFIED = 71,
    AFF_SHELL = 72,
    AFF_IMMUNITY = 73,
    AFF_SPIRITCONTROL = 74,
    NUM_AFF_FLAGS = 75,
};


/* Modes of connectedness: used by descriptor_data.state */
enum ConnectionState {
    CON_PLAYING = 0,    /* Playing - Nominal state		*/
    CON_CLOSE = 1,    /* User disconnect, remove character.	*/
    CON_GET_NAME = 2,    /* By what name ..?			*/
    CON_NAME_CNFRM = 3,    /* Did I get that right, x?		*/
    CON_PASSWORD = 4,    /* Password:				*/
    CON_NEWPASSWD = 5,    /* Give me a password for x		*/
    CON_CNFPASSWD = 6,    /* Please retype password:		*/
    CON_QSEX = 7,    /* Sex?					*/
    CON_QCLASS = 8,    /* Class?				*/
    CON_RMOTD = 9,    /* PRESS RETURN after MOTD		*/
    CON_MENU = 10,    /* Your choice: (main menu)		*/
    CON_EXDESC = 11,    /* Enter a new description:		*/
    CON_CHPWD_GETOLD = 12,    /* Changing passwd: get old		*/
    CON_CHPWD_GETNEW = 13,    /* Changing passwd: get new		*/
    CON_CHPWD_VRFY = 14,    /* Verify new password			*/
    CON_DELCNF1 = 15,    /* Delete confirmation 1		*/
    CON_DELCNF2 = 16,    /* Delete confirmation 2		*/
    CON_DISCONNECT = 17,    /* In-game link loss (leave character)	*/
    CON_OEDIT = 18,    /* OLC mode - object editor		*/
    CON_REDIT = 19,    /* OLC mode - room editor		*/
    CON_ZEDIT = 20,    /* OLC mode - zone info editor		*/
    CON_MEDIT = 21,    /* OLC mode - mobile editor		*/
    CON_SEDIT = 22,    /* OLC mode - shop editor		*/
    CON_TEDIT = 23,    /* OLC mode - text editor		*/
    CON_CEDIT = 24,    /* OLC mode - config editor		*/
    CON_QRACE = 25,     /* Race? 				*/
    CON_ASSEDIT = 26,     /* OLC mode - Assemblies                */
    CON_AEDIT = 27,    /* OLC mode - social (action) edit      */
    CON_TRIGEDIT = 28,    /* OLC mode - trigger edit              */
    CON_RACE_HELP = 29,    /* Race Help 				*/
    CON_CLASS_HELP = 30,    /* Class Help 				*/
    CON_QANSI = 31,    /* Ask for ANSI support     */
    CON_GEDIT = 32,    /* OLC mode - guild editor 		*/
    CON_QROLLSTATS = 33,    /* Reroll stats 			*/
    CON_IEDIT = 34,    /* OLC mode - individual edit		*/
    CON_LEVELUP = 35,    /* Level up menu			*/
    CON_QSTATS = 36,    /* Assign starting stats        	*/
    CON_HAIRL = 37,     /* Choose your hair length        */
    CON_HAIRS = 38,     /* Choose your hair style         */
    CON_HAIRC = 39,     /* Choose your hair color         */
    CON_SKIN = 40,     /* Choose your skin color         */
    CON_EYE = 41,     /* Choose your eye color          */
    CON_Q1 = 42,     /* Make a life choice!            */
    CON_Q2 = 43,     /* Make a second life choice!     */
    CON_Q3 = 44,     /* Make a third life choice!      */
    CON_Q4 = 45,     /* Make a fourth life choice!     */
    CON_Q5 = 46,     /* Make a fifth life choice!      */
    CON_Q6 = 47,     /* Make a sixth life choice!      */
    CON_Q7 = 48,     /* Make a seventh life choice!    */
    CON_Q8 = 49,     /* Make an eighth life choice!    */
    CON_Q9 = 50,     /* Make a ninth life choice!      */
    CON_QX = 51,     /* Make a tenth life choice!      */
    CON_HSEDIT = 52,     /* House Olc                      */
    CON_ALPHA = 53,     /* Alpha Password                 */
    CON_ALPHA2 = 54,     /* Alpha Password For Newb        */
    CON_ANDROID = 55,
    CON_HEDIT = 56,     /* OLC mode - help edit           */
    CON_GET_USER = 57,
    CON_GET_EMAIL = 58,
    CON_UMENU = 59,
    CON_USER_CONF = 60,
    CON_DISTFEA = 61,
    CON_HW = 62,
    CON_AURA = 63,
    CON_BONUS = 64,
    CON_NEGATIVE = 65,
    CON_NEWSEDIT = 66,
    CON_RACIAL = 67,
    CON_POBJ = 68,
    CON_ALIGN = 69,
    CON_SKILLS = 70,
    CON_USER_TITLE = 71,
    CON_GENOME = 72,

    NUM_CON_TYPES = 73,
};


/* Colors that the player can define */
enum ColorDef {
    COLOR_NORMAL = 0,
    COLOR_ROOMNAME = 1,
    COLOR_ROOMOBJS = 2,
    COLOR_ROOMPEOPLE = 3,
    COLOR_HITYOU = 4,
    COLOR_YOUHIT = 5,
    COLOR_OTHERHIT = 6,
    COLOR_CRITICAL = 7,
    COLOR_HOLLER = 8,
    COLOR_SHOUT = 9,
    COLOR_GOSSIP = 10,
    COLOR_AUCTION = 11,
    COLOR_CONGRAT = 12,
    COLOR_TELL = 13,
    COLOR_YOUSAY = 14,
    COLOR_ROOMSAY = 15,
    NUM_COLOR = 16,
};


/* Character equipment positions: used as index for char_data.equipment[] */
/* NOTE: Don't confuse these constants with the ITEM_ bitvectors
   which control the valid places you can wear a piece of equipment */
enum WearPosition {
    WEAR_UNUSED0 = 0,
    WEAR_FINGER_R = 1,
    WEAR_FINGER_L = 2,
    WEAR_NECK_1 = 3,
    WEAR_NECK_2 = 4,
    WEAR_BODY = 5,
    WEAR_HEAD = 6,
    WEAR_LEGS = 7,
    WEAR_FEET = 8,
    WEAR_HANDS = 9,
    WEAR_ARMS = 10,
    WEAR_UNUSED1 = 11,
    WEAR_ABOUT = 12,
    WEAR_WAIST = 13,
    WEAR_WRIST_R = 14,
    WEAR_WRIST_L = 15,
    WEAR_WIELD1 = 16,
    WEAR_WIELD2 = 17,
    WEAR_BACKPACK = 18,
    WEAR_EAR_R = 19,
    WEAR_EAR_L = 20,
    WEAR_SH = 21,
    WEAR_EYE = 22,
    NUM_WEARS = 23,    /* This must be the # of eq positions!! */
};

enum SpellLevel {
    SPELL_LEVEL_0 = 0,
    SPELL_LEVEL_1 = 1,
    SPELL_LEVEL_2 = 2,
    SPELL_LEVEL_3 = 3,
    SPELL_LEVEL_4 = 4,
    SPELL_LEVEL_5 = 5,
    SPELL_LEVEL_6 = 6,
    SPELL_LEVEL_7 = 7,
    SPELL_LEVEL_8 = 8,
    SPELL_LEVEL_9 = 9,

    MAX_SPELL_LEVEL = 10,                    /* how many spell levels */
};

#define MAX_MEM          (MAX_SPELL_LEVEL * 10) /* how many total spells */

enum MagicDomain {
    DOMAIN_UNDEFINED = -1,
    DOMAIN_AIR = 0,
    DOMAIN_ANIMAL = 1,
    DOMAIN_CHAOS = 2,
    DOMAIN_DEATH = 3,
    DOMAIN_DESTRUCTION = 4,
    DOMAIN_EARTH = 5,
    DOMAIN_EVIL = 6,
    DOMAIN_FIRE = 7,
    DOMAIN_GOOD = 8,
    DOMAIN_HEALING = 9,
    DOMAIN_KNOWLEDGE = 10,
    DOMAIN_LAW = 11,
    DOMAIN_LUCK = 12,
    DOMAIN_MAGIC = 13,
    DOMAIN_PLANT = 14,
    DOMAIN_PROTECTION = 15,
    DOMAIN_STRENGTH = 16,
    DOMAIN_SUN = 17,
    DOMAIN_TRAVEL = 18,
    DOMAIN_TRICKERY = 19,
    DOMAIN_UNIVERSAL = 20,
    DOMAIN_WAR = 22,
    DOMAIN_WATER = 23,
    DOMAIN_ARTIFACE = 24,
    DOMAIN_CHARM = 25,
    DOMAIN_COMMUNITY = 26,
    DOMAIN_CREATION = 27,
    DOMAIN_DARKNESS = 28,
    DOMAIN_GLORY = 29,
    DOMAIN_LIBERATION = 30,
    DOMAIN_MADNESS = 31,
    DOMAIN_NOBILITY = 32,
    DOMAIN_REPOSE = 33,
    DOMAIN_RUNE = 34,
    DOMAIN_SCALYKIND = 35,
    DOMAIN_WEATHER = 36,

    NUM_DOMAINS = 37,
};

enum MagicSchool {
    SCHOOL_UNDEFINED = -1,
    SCHOOL_ABJURATION = 0,
    SCHOOL_CONJURATION = 1,
    SCHOOL_DIVINATION = 2,
    SCHOOL_ENCHANTMENT = 3,
    SCHOOL_EVOCATION = 4,
    SCHOOL_ILLUSION = 5,
    SCHOOL_NECROMANCY = 6,
    SCHOOL_TRANSMUTATION = 7,
    SCHOOL_UNIVERSAL = 8,
    NUM_SCHOOLS = 10
};

#define DEITY_UNDEFINED            (-1)

#define NUM_DEITIES            0

/* Combat feats that apply to a specific weapon type */
enum CombatFeats {
    CFEAT_IMPROVED_CRITICAL = 0,
    CFEAT_WEAPON_FINESSE = 1,
    CFEAT_WEAPON_FOCUS = 2,
    CFEAT_WEAPON_SPECIALIZATION = 3,
    CFEAT_GREATER_WEAPON_FOCUS = 4,
    CFEAT_GREATER_WEAPON_SPECIALIZATION = 5,

    CFEAT_MAX = 5
};


/* Spell feats that apply to a specific school of spells */
enum SpellCombatFeats {
    CFEAT_SPELL_FOCUS = 0,
    CFEAT_GREATER_SPELL_FOCUS = 1
};

#define SFEAT_MAX                1

/* object-related defines ********************************************/


/* Item types: used by obj_data.type_flag */
enum ItemTypes {
    ITEM_LIGHT = 1,        /* Item is a light source	*/
    ITEM_SCROLL = 2,        /* Item is a scroll		*/
    ITEM_WAND = 3,        /* Item is a wand		*/
    ITEM_STAFF = 4,        /* Item is a staff		*/
    ITEM_WEAPON = 5,        /* Item is a weapon		*/
    ITEM_FIREWEAPON = 6,        /* Unimplemented		*/
    ITEM_CAMPFIRE = 7,        /* Burn things for fun!		*/
    ITEM_TREASURE = 8,        /* Item is a treasure, not gold	*/
    ITEM_ARMOR = 9,        /* Item is armor		*/
    ITEM_POTION = 10,        /* Item is a potion		*/
    ITEM_WORN = 11,        /* Unimplemented		*/
    ITEM_OTHER = 12,        /* Misc object			*/
    ITEM_TRASH = 13,        /* Trash - shopkeeps won't buy	*/
    ITEM_TRAP = 14,        /* Unimplemented		*/
    ITEM_CONTAINER = 15,        /* Item is a container		*/
    ITEM_NOTE = 16,        /* Item is note 		*/
    ITEM_DRINKCON = 17,        /* Item is a drink container	*/
    ITEM_KEY = 18,        /* Item is a key		*/
    ITEM_FOOD = 19,        /* Item is food			*/
    ITEM_MONEY = 20,        /* Item is money (gold)		*/
    ITEM_PEN = 21,        /* Item is a pen		*/
    ITEM_BOAT = 22,        /* Item is a boat		*/
    ITEM_FOUNTAIN = 23,        /* Item is a fountain		*/
    ITEM_VEHICLE = 24,               /* Item is a vehicle            */
    ITEM_HATCH = 25,               /* Item is a vehicle hatch      */
    ITEM_WINDOW = 26,               /* Item is a vehicle window     */
    ITEM_CONTROL = 27,               /* Item is a vehicle control    */
    ITEM_PORTAL = 28,               /* Item is a portal	        */
    ITEM_SPELLBOOK = 29,               /* Item is a spellbook	        */
    ITEM_BOARD = 30,               /* Item is a message board 	*/
    ITEM_CHAIR = 31,               /* Is a chair                   */
    ITEM_BED = 32,               /* Is a bed                     */
    ITEM_YUM = 33,               /* This was good food           */
    ITEM_PLANT = 34,               /* This will grow!              */
    ITEM_FISHPOLE = 35,               /* FOR FISHING                  */
    ITEM_FISHBAIT = 36,               /* DITTO                        */

    NUM_ITEM_TYPES = 37,
};


/* Take/Wear flags: used by obj_data.wear_flags */
enum WearFlags {
    ITEM_WEAR_TAKE = 0,  /* Item can be taken         */
    ITEM_WEAR_FINGER = 1,  /* Can be worn on finger     */
    ITEM_WEAR_NECK = 2,  /* Can be worn around neck   */
    ITEM_WEAR_BODY = 3,  /* Can be worn on body       */
    ITEM_WEAR_HEAD = 4,  /* Can be worn on head       */
    ITEM_WEAR_LEGS = 5,  /* Can be worn on legs       */
    ITEM_WEAR_FEET = 6,  /* Can be worn on feet       */
    ITEM_WEAR_HANDS = 7,  /* Can be worn on hands      */
    ITEM_WEAR_ARMS = 8,  /* Can be worn on arms       */
    ITEM_WEAR_SHIELD = 9,  /* Can be used as a shield   */
    ITEM_WEAR_ABOUT = 10, /* Can be worn about body    */
    ITEM_WEAR_WAIST = 11, /* Can be worn around waist  */
    ITEM_WEAR_WRIST = 12, /* Can be worn on wrist      */
    ITEM_WEAR_WIELD = 13, /* Can be wielded            */
    ITEM_WEAR_HOLD = 14, /* Can be held               */
    ITEM_WEAR_PACK = 15, /* Can be worn as a backpack */
    ITEM_WEAR_EAR = 16, /* Can be worn as an earring */
    ITEM_WEAR_SH = 17, /* Can be worn as wings      */
    ITEM_WEAR_EYE = 18, /* Can be worn as a mask     */

    NUM_ITEM_WEARS = 19
};


/* Extra object flags: used by obj_data.extra_flags */
enum ItemFlags {
    ITEM_GLOW = 0,  /* Item is glowing              */
    ITEM_HUM = 1,  /* Item is humming              */
    ITEM_NORENT = 2,  /* Item cannot be rented        */
    ITEM_NODONATE = 3,  /* Item cannot be donated       */
    ITEM_NOINVIS = 4,  /* Item cannot be made invis    */
    ITEM_INVISIBLE = 5,  /* Item is invisible            */
    ITEM_MAGIC = 6,  /* Item is magical              */
    ITEM_NODROP = 7,  /* Item is cursed: can't drop   */
    ITEM_BLESS = 8,  /* Item is blessed              */
    ITEM_ANTI_GOOD = 9,  /* Not usable by good people    */
    ITEM_ANTI_EVIL = 10, /* Not usable by evil people    */
    ITEM_ANTI_NEUTRAL = 11, /* Not usable by neutral people */
    ITEM_ANTI_WIZARD = 12, /* Not usable by mages          */
    ITEM_ANTI_CLERIC = 13, /* Not usable by clerics        */
    ITEM_ANTI_ROGUE = 14, /* Not usable by thieves        */
    ITEM_ANTI_FIGHTER = 15, /* Not usable by warriors       */
    ITEM_NOSELL = 16, /* Shopkeepers won't touch it   */
    ITEM_ANTI_DRUID = 17, /* Not usable by druids         */
    ITEM_2H = 18, /* Requires two free hands      */
    ITEM_ANTI_BARD = 19, /* Not usable by bards          */
    ITEM_ANTI_RANGER = 20, /* Not usable by rangers        */
    ITEM_ANTI_PALADIN = 21, /* Not usable by paladins       */
    ITEM_ANTI_HUMAN = 22, /* Not usable by humans         */
    ITEM_ANTI_ICER = 23, /* Not usable by dwarves        */
    ITEM_ANTI_SAIYAN = 24, /* Not usable by elves          */
    ITEM_ANTI_KONATSU = 25, /* Not usable by gnomes         */
    ITEM_UNIQUE_SAVE = 26,    /* unique object save           */
    ITEM_BROKEN = 27, /* Item is broken hands         */
    ITEM_UNBREAKABLE = 28, /* Item is unbreakable          */
    ITEM_ANTI_MONK = 29, /* Not usable by monks          */
    ITEM_ANTI_BARBARIAN = 30, /* Not usable by barbarians     */
    ITEM_ANTI_SORCERER = 31, /* Not usable by sorcerers      */
    ITEM_DOUBLE = 32, /* Double weapon                */
    ITEM_ONLY_WIZARD = 33, /* Only usable by mages         */
    ITEM_ONLY_CLERIC = 34, /* Only usable by clerics       */
    ITEM_ONLY_ROGUE = 35, /* Only usable by thieves       */
    ITEM_ONLY_FIGHTER = 36, /* Only usable by warriors      */
    ITEM_ONLY_DRUID = 37, /* Only usable by druids        */
    ITEM_ONLY_BARD = 38, /* Only usable by bards         */
    ITEM_ONLY_RANGER = 39, /* Only usable by rangers       */
    ITEM_ONLY_PALADIN = 40, /* Only usable by paladins      */
    ITEM_ONLY_HUMAN = 41, /* Only usable by humans        */
    ITEM_ONLY_ICER = 42, /* Only usable by dwarves       */
    ITEM_ONLY_SAIYAN = 43, /* Only usable by elves         */
    ITEM_ONLY_KONATSU = 44, /* Only usable by gnomes        */
    ITEM_ONLY_MONK = 45, /* Only usable by monks         */
    ITEM_ONLY_BARBARIAN = 46, /* Only usable by barbarians    */
    ITEM_ONLY_SORCERER = 47, /* Only usable by sorcerers     */
    ITEM_ANTI_ARCANE_ARCHER = 48, /* Not usable by Aracane Archers          */
    ITEM_ANTI_ARCANE_TRICKSTER = 49, /* Not usable by Aracane tricksters       */
    ITEM_ANTI_ARCHMAGE = 50, /* Not usable by Archmages                */
    ITEM_ANTI_ASSASSIN = 51, /* Not usable by Assassins                */
    ITEM_ANTI_BLACKGUARD = 52, /* Not usable by Blackguards              */
    ITEM_ANTI_DRAGON_DISCIPLE = 53, /* Not usable by Dragon disciples         */
    ITEM_ANTI_DUELIST = 54, /* Not usable by Duelists                 */
    ITEM_ANTI_DWARVEN_DEFENDER = 55, /* Not usable by Dwarven defenders        */
    ITEM_ANTI_ELDRITCH_KNIGHT = 56, /* Not usable by Eldritch knights         */
    ITEM_ANTI_HIEROPHANT = 57, /* Not usable by Hierophants              */
    ITEM_ANTI_HORIZON_WALKER = 58, /* Not usable by Horizon walkers          */
    ITEM_ANTI_LOREMASTER = 59, /* Not usable by Loremasters              */
    ITEM_ANTI_MYSTIC_THEURGE = 60, /* Not usable by Mystic theurges          */
    ITEM_ANTI_SHADOWDANCER = 61, /* Not useable by shadowdancers           */
    ITEM_ANTI_THAUMATURGIST = 62, /* Not useable by thaumaturgists          */
    ITEM_BSCOUTER = 63,
    ITEM_MSCOUTER = 64,
    ITEM_ASCOUTER = 65,
    ITEM_USCOUTER = 66,
    ITEM_WEAPLVL1 = 67,
    ITEM_WEAPLVL2 = 68,
    ITEM_WEAPLVL3 = 69,
    ITEM_WEAPLVL4 = 70,
    ITEM_WEAPLVL5 = 71,
    ITEM_CBOARD = 72,
    ITEM_FORGED = 73,
    ITEM_SHEATH = 74,
    ITEM_ONLY_JINTO = 75,
    ITEM_BURIED = 76,
    ITEM_SLOT1 = 77,
    ITEM_SLOT2 = 78,
    ITEM_TOKEN = 79,
    ITEM_SLOT_ONE = 80,
    ITEM_SLOTS_FILLED = 81,
    ITEM_RESTRING = 82,
    ITEM_CUSTOM = 83,
    ITEM_PROTECTED = 84,
    ITEM_NORANDOM = 85,
    ITEM_THROW = 86,
    ITEM_HOT = 87,
    ITEM_PURGE = 88,
    ITEM_ICE = 89,
    ITEM_DUPLICATE = 90,
    ITEM_MATURE = 91,
    ITEM_CARDCASE = 92,
    ITEM_NOPICKUP = 93,
    ITEM_NOSTEAL = 94,

    NUM_ITEM_FLAGS = 96
};


/* Modifier constants used with obj affects ('A' fields) */
enum ApplyFlags {
    APPLY_NONE = 0,    /* No effect			*/
    APPLY_STR = 1,    /* Apply to strength		*/
    APPLY_DEX = 2,    /* Apply to dexterity		*/
    APPLY_INT = 3,    /* Apply to intelligence	*/
    APPLY_WIS = 4,    /* Apply to wisdom		*/
    APPLY_CON = 5,    /* Apply to constitution	*/
    APPLY_CHA = 6,    /* Apply to charisma		*/
    APPLY_CLASS = 7,    /* Reserved			*/
    APPLY_LEVEL = 8,    /* Reserved			*/
    APPLY_AGE = 9,    /* Apply to age			*/
    APPLY_CHAR_WEIGHT = 10,    /* Apply to weight		*/
    APPLY_CHAR_HEIGHT = 11,    /* Apply to height		*/
    APPLY_MANA = 12,    /* Apply to max mana		*/
    APPLY_HIT = 13,    /* Apply to max hit points	*/
    APPLY_MOVE = 14,    /* Apply to max move points	*/
    APPLY_GOLD = 15,    /* Reserved			*/
    APPLY_EXP = 16,    /* Reserved			*/
    APPLY_AC = 17,    /* Apply to Armor Class		*/
    APPLY_ACCURACY = 18,    /* Apply to accuracy		*/
    APPLY_DAMAGE = 19,    /* Apply to damage 		*/
    APPLY_REGEN = 20,    /* Regen Rate Buffed            */
    APPLY_TRAIN = 21,    /* Skill training rate buffed   */
    APPLY_LIFEMAX = 22,    /* Life Force max buffed        */
    APPLY_UNUSED3 = 23,    /* Unused			*/
    APPLY_UNUSED4 = 24,    /* Unused			*/
    APPLY_RACE = 25,       /* Apply to race                */
    APPLY_TURN_LEVEL = 26,       /* Apply to turn undead         */
    APPLY_SPELL_LVL_0 = 27,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_1 = 28,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_2 = 29,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_3 = 30,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_4 = 31,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_5 = 32,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_6 = 33,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_7 = 34,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_8 = 35,       /* Apply to spell cast per day  */
    APPLY_SPELL_LVL_9 = 36,       /* Apply to spell cast per day  */
    APPLY_KI = 37,    /* Apply to max ki		*/
    APPLY_FORTITUDE = 38,    /* Apply to fortitue save	*/
    APPLY_REFLEX = 39,    /* Apply to reflex save		*/
    APPLY_WILL = 40,    /* Apply to will save		*/
    APPLY_SKILL = 41,       /* Apply to a specific skill    */
    APPLY_FEAT = 42,       /* Apply to a specific feat     */
    APPLY_ALLSAVES = 43,       /* Apply to all 3 save types 	*/
    APPLY_RESISTANCE = 44,       /* Apply to resistance	 	*/
    APPLY_ALL_STATS = 45,       /* Apply to all attributes	*/
    NUM_APPLIES = 46
};


/* Container flags - value[1] */
#define CONT_CLOSEABLE      (1 << 0)    /* Container can be closed	*/
#define CONT_PICKPROOF      (1 << 1)    /* Container is pickproof	*/
#define CONT_CLOSED         (1 << 2)    /* Container is closed		*/
#define CONT_LOCKED         (1 << 3)    /* Container is locked		*/

#define NUM_CONT_FLAGS 4

/* Some different kind of liquids for use in values of drink containers */
enum Liquids {
    LIQ_WATER = 0,
    LIQ_BEER = 1,
    LIQ_WINE = 2,
    LIQ_ALE = 3,
    LIQ_DARKALE = 4,
    LIQ_WHISKY = 5,
    LIQ_LEMONADE = 6,
    LIQ_FIREBRT = 7,
    LIQ_LOCALSPC = 8,
    LIQ_SLIME = 9,
    LIQ_MILK = 10,
    LIQ_TEA = 11,
    LIQ_COFFE = 12,
    LIQ_BLOOD = 13,
    LIQ_SALTWATER = 14,
    LIQ_CLEARWATER = 15,

    NUM_LIQ_TYPES = 16,
};

enum Materials {
    MATERIAL_BONE = 0,
    MATERIAL_CERAMIC = 1,
    MATERIAL_COPPER = 2,
    MATERIAL_DIAMOND = 3,
    MATERIAL_GOLD = 4,
    MATERIAL_IRON = 5,
    MATERIAL_LEATHER = 6,
    MATERIAL_MITHRIL = 7,
    MATERIAL_OBSIDIAN = 8,
    MATERIAL_STEEL = 9,
    MATERIAL_STONE = 10,
    MATERIAL_SILVER = 11,
    MATERIAL_WOOD = 12,
    MATERIAL_GLASS = 13,
    MATERIAL_ORGANIC = 14,
    MATERIAL_CURRENCY = 15,
    MATERIAL_PAPER = 16,
    MATERIAL_COTTON = 17,
    MATERIAL_SATIN = 18,
    MATERIAL_SILK = 19,
    MATERIAL_BURLAP = 20,
    MATERIAL_VELVET = 21,
    MATERIAL_PLATINUM = 22,
    MATERIAL_ADAMANTINE = 23,
    MATERIAL_WOOL = 24,
    MATERIAL_ONYX = 25,
    MATERIAL_IVORY = 26,
    MATERIAL_BRASS = 27,
    MATERIAL_MARBLE = 28,
    MATERIAL_BRONZE = 29,
    MATERIAL_KACHIN = 30,
    MATERIAL_RUBY = 31,
    MATERIAL_SAPPHIRE = 32,
    MATERIAL_EMERALD = 33,
    MATERIAL_GEMSTONE = 34,
    MATERIAL_GRANITE = 35,
    MATERIAL_ENERGY = 36,
    MATERIAL_HEMP = 37,
    MATERIAL_CRYSTAL = 38,
    MATERIAL_EARTH = 39,
    MATERIAL_LIQUID = 40,
    MATERIAL_CLOTH = 41,
    MATERIAL_METAL = 42,
    MATERIAL_WAX = 43,
    MATERIAL_OTHER = 44,
    MATERIAL_FOOD = 45,
    MATERIAL_OIL = 46,

    NUM_MATERIALS = 47,
};


/* other miscellaneous defines *******************************************/


/* Player conditions */
enum PlayerConditions {
    DRUNK = 0,
    HUNGER = 1,
    THIRST = 2
};


/* Sun state for weather_data */
enum SunState {
    SUN_DARK = 0,
    SUN_RISE = 1,
    SUN_LIGHT = 2,
    SUN_SET = 3,
};



/* Sky conditions for weather_data */
enum SkyState {
    SKY_CLOUDLESS = 0,
    SKY_CLOUDY = 1,
    SKY_RAINING = 2,
    SKY_LIGHTNING = 3
};


/* Rent codes */
enum RentCode {
    RENT_UNDEF = 0,
    RENT_CRASH = 1,
    RENT_RENTED = 2,
    RENT_CRYO = 3,
    RENT_FORCED = 4,
    RENT_TIMEDOUT = 5,
};


/* for the 128bits */
#define RF_ARRAY_MAX    4
#define PM_ARRAY_MAX    4
#define PR_ARRAY_MAX    4
#define AF_ARRAY_MAX    4
#define TW_ARRAY_MAX    4
#define EF_ARRAY_MAX    4
#define AD_ARRAY_MAX    4
#define FT_ARRAY_MAX    4
#define ZF_ARRAY_MAX    4


/* History */
enum HistoryType {
    HIST_ALL = 0,
    HIST_SAY = 1,
    HIST_GOSSIP = 2,
    HIST_WIZNET = 3,
    HIST_TELL = 4,
    HIST_SHOUT = 5,
    HIST_GRATS = 6,
    HIST_HOLLER = 7,
    HIST_AUCTION = 8,
    HIST_SNET = 9,

    NUM_HIST = 10
};


/* other #defined constants **********************************************/

/*
 * ADMLVL_IMPL should always be the HIGHEST possible admin level, and
 * ADMLVL_IMMORT should always be the LOWEST immortal level.
 */
enum AdminLevel {
    ADMLVL_NONE = 0,
    ADMLVL_IMMORT = 1,
    ADMLVL_BUILDER = 2,
    ADMLVL_GOD = 3,
    ADMLVL_VICE = 4,
    ADMLVL_GRGOD = 5,
    ADMLVL_IMPL = 6
};

/* First character level that forces epic levels */
#define LVL_EPICSTART        101

/*
 * ADM flags - define admin privs for chars
 */
enum AdminFlags {
    ADM_TELLALL = 0,    /* Can use 'tell all' to broadcast GOD */
    ADM_SEEINV = 1,    /* Sees other chars inventory IMM */
    ADM_SEESECRET = 2,    /* Sees secret doors IMM */
    ADM_KNOWWEATHER = 3,    /* Knows details of weather GOD */
    ADM_FULLWHERE = 4,    /* Full output of 'where' command IMM */
    ADM_MONEY = 5,    /* Char has a bottomless wallet GOD */
    ADM_EATANYTHING = 6,    /* Char can eat anything GOD */
    ADM_NOPOISON = 7,    /* Char can't be poisoned IMM */
    ADM_WALKANYWHERE = 8,    /* Char has unrestricted walking IMM */
    ADM_NOKEYS = 9,    /* Char needs no keys for locks GOD */
    ADM_INSTANTKILL = 10,    /* "kill" command is instant IMPL */
    ADM_NOSTEAL = 11,    /* Char cannot be stolen from IMM */
    ADM_TRANSALL = 12,    /* Can use 'trans all' GRGOD */
    ADM_SWITCHMORTAL = 13,    /* Can 'switch' to a mortal PC body IMPL */
    ADM_FORCEMASS = 14,    /* Can force rooms or all GRGOD */
    ADM_ALLHOUSES = 15,    /* Can enter any house GRGOD */
    ADM_NODAMAGE = 16,    /* Cannot be damaged IMM */
    ADM_ALLSHOPS = 17,    /* Can use all shops GOD */
    ADM_CEDIT = 18,    /* Can use cedit IMPL */

    NUM_ADMFLAGS = 19
};


/* Level of the 'freeze' command */
#define ADMLVL_FREEZE    ADMLVL_GRGOD

#define NUM_OF_DIRS    12    /* number of directions in a room (nsewud) */

/*
 * OPT_USEC determines how many commands will be processed by the MUD per
 * second and how frequently it does socket I/O.  A low setting will cause
 * actions to be executed more frequently but will increase overhead due to
 * more cycling to check.  A high setting (e.g. 1 Hz) may upset your players
 * as actions (such as large speedwalking chains) take longer to be executed.
 * You shouldn't need to adjust this.
 */
#define OPT_USEC    100000        /* 10 passes per second */
#define PASSES_PER_SEC    (1000000 / OPT_USEC)
#define RL_SEC        * PASSES_PER_SEC
#define CD_TICK         * PASSES_PER_SEC

#define PULSE_ZONE    (CONFIG_PULSE_ZONE RL_SEC)
#define PULSE_MOBILE    (CONFIG_PULSE_MOBILE RL_SEC)
#define PULSE_VIOLENCE  (CONFIG_PULSE_VIOLENCE RL_SEC)
#define PULSE_AUCTION    (15 RL_SEC)
#define PULSE_AUTOSAVE    (CONFIG_PULSE_AUTOSAVE RL_SEC)
#define PULSE_IDLEPWD    (CONFIG_PULSE_IDLEPWD RL_SEC)
#define PULSE_SANITY    (CONFIG_PULSE_SANITY RL_SEC)
#define PULSE_USAGE    (CONFIG_PULSE_SANITY * 60 RL_SEC)   /* 5 mins */
#define PULSE_TIMESAVE    (CONFIG_PULSE_TIMESAVE * 300 RL_SEC) /* should be >= SECS_PER_MUD_HOUR */
#define PULSE_CURRENT    (CONFIG_PULSE_CURRENT RL_SEC)
#define PULSE_1SEC      (1 RL_SEC)
#define PULSE_2SEC      (2 RL_SEC)
#define PULSE_3SEC      (3 RL_SEC)
#define PULSE_4SEC      (4 RL_SEC)
#define PULSE_5SEC      (5 RL_SEC)
#define PULSE_6SEC      (6 RL_SEC)
#define PULSE_7SEC      (7 RL_SEC)

/* Cool Down Ticks */
#define PULSE_CD1       (1 CD_TICK)
#define PULSE_CD2       (2 CD_TICK)
#define PULSE_CD3       (3 CD_TICK)
#define PULSE_CD4       (4 CD_TICK) /* This and the 3 above are for safety */
#define PULSE_CD5       (5 CD_TICK) /* Punch */
#define PULSE_CD6       (6 CD_TICK)
#define PULSE_CD7       (7 CD_TICK)
#define PULSE_CD8       (8 CD_TICK)
#define PULSE_CD9       (9 CD_TICK)
#define PULSE_CD10      (10 CD_TICK)
#define PULSE_CD11      (11 CD_TICK)
#define PULSE_CD12      (12 CD_TICK)
/* End CD Ticks    */


/* Variables for the output buffering system */
#define MAX_SOCK_BUF            (96 * 1024) /* Size of kernel's sock buf   */
#define MAX_PROMPT_LENGTH       1024          /* Max length of prompt        */
#define GARBAGE_SPACE        512          /* Space for **OVERFLOW** etc  */
#define SMALL_BUFSIZE        6020        /* Static output buffer size   */
/* Max amount of output that can be buffered */
#define LARGE_BUFSIZE       (MAX_SOCK_BUF - GARBAGE_SPACE - MAX_PROMPT_LENGTH)

#define HISTORY_SIZE        5    /* Keep last 5 commands. */
#define MAX_STRING_LENGTH    64936
#define MAX_INPUT_LENGTH    2048    /* Max length per *line* of
input */
#define MAX_RAW_INPUT_LENGTH    4096    /* Max size of *raw* input */
#define MAX_MESSAGES        100
#define MAX_NAME_LENGTH        20
#define MAX_PWD_LENGTH        30
#define MAX_TITLE_LENGTH    120
#define HOST_LENGTH        40
#define EXDSCR_LENGTH        16384
#define MAX_TONGUE        3
#define MAX_SKILLS        200
#define MAX_AFFECT        32
#define MAX_OBJ_AFFECT        6
#define MAX_NOTE_LENGTH        6000    /* arbitrary */
#define SKILL_TABLE_SIZE    1000
#define SPELLBOOK_SIZE        50
#define MAX_FEATS            750
#define MAX_HELP_KEYWORDS       256
#define MAX_HELP_ENTRY          MAX_STRING_LENGTH
#define NUM_FEATS_DEFINED       252
#define MAX_ARMOR_TYPES         5
#define NUM_CONFIG_SECTIONS     7
#define NUM_CREATION_METHODS    5
#define NUM_ATTACK_TYPES        15
#define NUM_MTRIG_TYPES         20
#define NUM_OTRIG_TYPES         20
#define NUM_WTRIG_TYPES         20
#define NUM_ZONE_FLAGS          36
#define NUM_TRADERS             78
#define NUM_SHOP_FLAGS          3
#define NUM_DOOR_CMD            5
#define MAX_ASSM                11
#define NUM_FULLNESS        5
#define NUM_WEEK_DAYS        7
#define NUM_MONTHS        12
#define NUM_CONDITIONS        3
#define NUM_WIELD_NAMES        4

/* define the largest set of commands for a trigger */
#define MAX_CMD_LENGTH          16384 /* 16k should be plenty and then some */


/*
 * A MAX_PWD_LENGTH of 10 will cause BSD-derived systems with MD5 passwords
 * and GNU libc 2 passwords to be truncated.  On BSD this will enable anyone
 * with a name longer than 5 character to log in with any password.  If you
 * have such a system, it is suggested you change the limit to 20.
 *
 * Please note that this will erase your player files.  If you are not
 * prepared to do so, simply erase these lines but heed the above warning.
 */

/* object-related structures ******************************************/
#define NUM_OBJ_VAL_POSITIONS 16

enum ItemValAll {
    VAL_ALL_HEALTH = 4,
    VAL_ALL_MAXHEALTH = 5,
    VAL_ALL_MATERIAL = 7
};

/*
 * Uses for generic object values on specific object types
 * Please use these instead of numbers to prevent overlaps.
 */
enum ItemValLight {
    VAL_LIGHT_TIME = 0,
    VAL_LIGHT_UNUSED2 = 1,
    VAL_LIGHT_HOURS = 2,
    VAL_LIGHT_UNUSED4 = 3,
    VAL_LIGHT_HEALTH = 4,
    VAL_LIGHT_MAXHEALTH = 5,
    VAL_LIGHT_UNUSED7 = 6,
    VAL_LIGHT_MATERIAL = 7
};

enum ItemValScroll {
    VAL_SCROLL_LEVEL = 0,
    VAL_SCROLL_SPELL1 = 1,
    VAL_SCROLL_SPELL2 = 2,
    VAL_SCROLL_SPELL3 = 3,
    VAL_SCROLL_HEALTH = 4,
    VAL_SCROLL_MAXHEALTH = 5,
    VAL_SCROLL_UNUSED7 = 6,
    VAL_SCROLL_MATERIAL = 7,
};

enum ItemValWand {
    VAL_WAND_LEVEL = 0,
    VAL_WAND_MAXCHARGES = 1,
    VAL_WAND_CHARGES = 2,
    VAL_WAND_SPELL = 3,
    VAL_WAND_HEALTH = 4,
    VAL_WAND_MAXHEALTH = 5,
    VAL_WAND_UNUSED7 = 6,
    VAL_WAND_MATERIAL = 7,
};

enum ItemValStaff {
    VAL_STAFF_LEVEL = 0,
    VAL_STAFF_MAXCHARGES = 1,
    VAL_STAFF_CHARGES = 2,
    VAL_STAFF_SPELL = 3,
    VAL_STAFF_HEALTH = 4,
    VAL_STAFF_MAXHEALTH = 5,
    VAL_STAFF_UNUSED7 = 6,
    VAL_STAFF_MATERIAL = 7
};

enum ItemValWeapon {
    VAL_WEAPON_SKILL = 0,
    VAL_WEAPON_DAMDICE = 1,
    VAL_WEAPON_DAMSIZE = 2,
    VAL_WEAPON_DAMTYPE = 3,
    VAL_WEAPON_HEALTH = 4,
    VAL_WEAPON_MAXHEALTH = 5,
    VAL_WEAPON_CRITTYPE = 6,
    VAL_WEAPON_MATERIAL = 7,
    VAL_WEAPON_CRITRANGE = 8
};

enum ItemValFireWeapon {
    VAL_FIREWEAPON_UNUSED1 = 0,
    VAL_FIREWEAPON_UNUSED2 = 1,
    VAL_FIREWEAPON_UNUSED3 = 2,
    VAL_FIREWEAPON_UNUSED4 = 3,
    VAL_FIREWEAPON_HEALTH = 4,
    VAL_FIREWEAPON_MAXHEALTH = 5,
    VAL_FIREWEAPON_UNUSED7 = 6,
    VAL_FIREWEAPON_MATERIAL = 7
};

enum ItemValMissile {
    VAL_MISSILE_UNUSED1 = 0,
    VAL_MISSILE_UNUSED2 = 1,
    VAL_MISSILE_UNUSED3 = 2,
    VAL_MISSILE_UNUSED4 = 3,
    VAL_MISSILE_HEALTH = 4,
    VAL_MISSILE_MAXHEALTH = 5,
    VAL_MISSILE_UNUSED7 = 6,
    VAL_MISSILE_MATERIAL = 7,
};

enum ItemValTreasure {
    VAL_TREASURE_UNUSED1 = 0,
    VAL_TREASURE_UNUSED2 = 1,
    VAL_TREASURE_UNUSED3 = 2,
    VAL_TREASURE_UNUSED4 = 3,
    VAL_TREASURE_HEALTH = 4,
    VAL_TREASURE_MAXHEALTH = 5,
    VAL_TREASURE_UNUSED7 = 6,
    VAL_TREASURE_MATERIAL = 7,
};

enum ItemValArmor {
    VAL_ARMOR_APPLYAC = 0,
    VAL_ARMOR_SKILL = 1,
    VAL_ARMOR_MAXDEXMOD = 2,
    VAL_ARMOR_CHECK = 3,
    VAL_ARMOR_HEALTH = 4,
    VAL_ARMOR_MAXHEALTH = 5,
    VAL_ARMOR_SPELLFAIL = 6,
    VAL_ARMOR_MATERIAL = 7,
};

enum ItemValPotion {
    VAL_POTION_LEVEL = 0,
    VAL_POTION_SPELL1 = 1,
    VAL_POTION_SPELL2 = 2,
    VAL_POTION_SPELL3 = 3,
    VAL_POTION_HEALTH = 4,
    VAL_POTION_MAXHEALTH = 5,
    VAL_POTION_UNUSED7 = 6,
    VAL_POTION_MATERIAL = 7,
};

enum ItemValWorn {
    VAL_WORN_UNUSED1 = 0,
    VAL_WORN_UNUSED2 = 1,
    VAL_WORN_UNUSED3 = 2,
    VAL_WORN_UNUSED4 = 3,
    VAL_WORN_HEALTH = 4,
    VAL_WORN_MAXHEALTH = 5,
    VAL_WORN_UNUSED7 = 6,
    VAL_WORN_MATERIAL = 7,
};

enum ItemValOther {
    VAL_OTHER_UNUSED1 = 0,
    VAL_OTHER_UNUSED2 = 1,
    VAL_OTHER_UNUSED3 = 2,
    VAL_OTHER_UNUSED4 = 3,
    VAL_OTHER_HEALTH = 4,
    VAL_OTHER_MAXHEALTH = 5,
    VAL_OTHER_UNUSED7 = 6,
    VAL_OTHER_MATERIAL = 7
};

enum ItemValTrash {
    VAL_TRASH_UNUSED1 = 0,
    VAL_TRASH_UNUSED2 = 1,
    VAL_TRASH_UNUSED3 = 2,
    VAL_TRASH_UNUSED4 = 3,
    VAL_TRASH_HEALTH = 4,
    VAL_TRASH_MAXHEALTH = 5,
    VAL_TRASH_UNUSED7 = 6,
    VAL_TRASH_MATERIAL = 7
};

enum ItemValTrap {
    VAL_TRAP_SPELL = 0,
    VAL_TRAP_HITPOINTS = 1,
    VAL_TRAP_UNUSED3 = 2,
    VAL_TRAP_UNUSED4 = 3,
    VAL_TRAP_HEALTH = 4,
    VAL_TRAP_MAXHEALTH = 5,
    VAL_TRAP_UNUSED7 = 6,
    VAL_TRAP_MATERIAL = 7
};

enum ItemValContainer {
    VAL_CONTAINER_CAPACITY = 0,
    VAL_CONTAINER_FLAGS = 1,
    VAL_CONTAINER_KEY = 2,
    VAL_CONTAINER_CORPSE = 3,
    VAL_CONTAINER_HEALTH = 4,
    VAL_CONTAINER_MAXHEALTH = 5,
    VAL_CONTAINER_UNUSED7 = 6,
    VAL_CONTAINER_MATERIAL = 7,
    VAL_CONTAINER_OWNER = 8
};

enum ItemValNote {
    VAL_NOTE_LANGUAGE = 0,
    VAL_NOTE_UNUSED2 = 1,
    VAL_NOTE_UNUSED3 = 2,
    VAL_NOTE_UNUSED4 = 3,
    VAL_NOTE_HEALTH = 4,
    VAL_NOTE_MAXHEALTH = 5,
    VAL_NOTE_UNUSED7 = 6,
    VAL_NOTE_MATERIAL = 7
};

enum ItemValDrink {
    VAL_DRINKCON_CAPACITY = 0,
    VAL_DRINKCON_HOWFULL = 1,
    VAL_DRINKCON_LIQUID = 2,
    VAL_DRINKCON_POISON = 3,
    VAL_DRINKCON_HEALTH = 4,
    VAL_DRINKCON_MAXHEALTH = 5,
    VAL_DRINKCON_UNUSED7 = 6,
    VAL_DRINKCON_MATERIAL = 7
};

enum ItemValKey {
    VAL_KEY_UNUSED1 = 0,
    VAL_KEY_UNUSED2 = 1,
    VAL_KEY_KEYCODE = 2,
    VAL_KEY_UNUSED4 = 3,
    VAL_KEY_HEALTH = 4,
    VAL_KEY_MAXHEALTH = 5,
    VAL_KEY_UNUSED7 = 6,
    VAL_KEY_MATERIAL = 7
};

enum ItemValFood {
    VAL_FOOD_FOODVAL = 0,
    VAL_FOOD_UNUSED2 = 1,
    VAL_FOOD_UNUSED3 = 2,
    VAL_FOOD_POISON = 3,
    VAL_FOOD_HEALTH = 4,
    VAL_FOOD_MAXHEALTH = 5,
    VAL_FOOD_UNUSED7 = 6,
    VAL_FOOD_MATERIAL = 7,
};

enum ItemValMoney {
    VAL_MONEY_SIZE = 0,
    VAL_MONEY_UNUSED2 = 1,
    VAL_MONEY_UNUSED3 = 2,
    VAL_MONEY_UNUSED4 = 3,
    VAL_MONEY_HEALTH = 4,
    VAL_MONEY_MAXHEALTH = 5,
    VAL_MONEY_UNUSED7 = 6,
    VAL_MONEY_MATERIAL = 7
};

enum ItemValPen {
    VAL_PEN_UNUSED1 = 0,
    VAL_PEN_UNUSED2 = 1,
    VAL_PEN_UNUSED3 = 2,
    VAL_PEN_UNUSED4 = 3,
    VAL_PEN_HEALTH = 4,
    VAL_PEN_MAXHEALTH = 5,
    VAL_PEN_UNUSED7 = 6,
    VAL_PEN_MATERIAL = 7,
};

enum ItemValBoat {
    VAL_BOAT_UNUSED1 = 0,
    VAL_BOAT_UNUSED2 = 1,
    VAL_BOAT_UNUSED3 = 2,
    VAL_BOAT_UNUSED4 = 3,
    VAL_BOAT_HEALTH = 4,
    VAL_BOAT_MAXHEALTH = 5,
    VAL_BOAT_UNUSED7 = 6,
    VAL_BOAT_MATERIAL = 7,
};

enum ItemValFountain {
    VAL_FOUNTAIN_CAPACITY = 0,
    VAL_FOUNTAIN_HOWFULL = 1,
    VAL_FOUNTAIN_LIQUID = 2,
    VAL_FOUNTAIN_POISON = 3,
    VAL_FOUNTAIN_HEALTH = 4,
    VAL_FOUNTAIN_MAXHEALTH = 5,
    VAL_FOUNTAIN_UNUSED7 = 6,
    VAL_FOUNTAIN_MATERIAL = 7,
};

enum ItemValVehicle {
    VAL_VEHICLE_ROOM = 0,
    VAL_VEHICLE_UNUSED2 = 1,
    VAL_VEHICLE_UNUSED3 = 2,
    VAL_VEHICLE_APPEAR = 3,
    VAL_VEHICLE_HEALTH = 4,
    VAL_VEHICLE_MAXHEALTH = 5,
    VAL_VEHICLE_UNUSED7 = 6,
    VAL_VEHICLE_MATERIAL = 7
};

enum ItemValHatch {
    VAL_HATCH_DEST = 0,
    VAL_HATCH_FLAGS = 1,
    VAL_HATCH_DCSKILL = 2,
    VAL_HATCH_DCMOVE = 3,
    VAL_HATCH_HEALTH = 4,
    VAL_HATCH_MAXHEALTH = 5,
    VAL_HATCH_UNUSED7 = 6,
    VAL_HATCH_MATERIAL = 7,
    VAL_HATCH_DCLOCK = 8,
    VAL_HATCH_DCHIDE = 9
};

enum ItemValWindow {
    VAL_WINDOW_UNUSED1 = 0,
    VAL_WINDOW_UNUSED2 = 1,
    VAL_WINDOW_UNUSED3 = 2,
    VAL_WINDOW_UNUSED4 = 3,
    VAL_WINDOW_HEALTH = 4,
    VAL_WINDOW_MAXHEALTH = 5,
    VAL_WINDOW_UNUSED7 = 6,
    VAL_WINDOW_MATERIAL = 7
};

enum ItemValControl {
    VAL_CONTROL_UNUSED1 = 0,
    VAL_CONTROL_UNUSED2 = 1,
    VAL_CONTROL_UNUSED3 = 2,
    VAL_CONTROL_UNUSED4 = 3,
    VAL_CONTROL_HEALTH = 4,
    VAL_CONTROL_MAXHEALTH = 5,
    VAL_CONTROL_UNUSED7 = 6,
    VAL_CONTROL_MATERIAL = 7,
};

enum ItemValPortal {
    VAL_PORTAL_DEST = 0,
    VAL_PORTAL_DCSKILL = 1,
    VAL_PORTAL_DCMOVE = 2,
    VAL_PORTAL_APPEAR = 3,
    VAL_PORTAL_HEALTH = 4,
    VAL_PORTAL_MAXHEALTH = 5,
    VAL_PORTAL_UNUSED7 = 6,
    VAL_PORTAL_MATERIAL = 7,
    VAL_PORTAL_DCLOCK = 8,
    VAL_PORTAL_DCHIDE = 9,
};

enum ItemValBoard {
    VAL_BOARD_READ = 0,
    VAL_BOARD_WRITE = 1,
    VAL_BOARD_ERASE = 2,
    VAL_BOARD_UNUSED4 = 3,
    VAL_BOARD_HEALTH = 4,
    VAL_BOARD_MAXHEALTH = 5,
    VAL_BOARD_UNUSED7 = 6,
    VAL_BOARD_MATERIAL = 7,
    VAL_DOOR_DCLOCK = 8,
    VAL_DOOR_DCHIDE = 9
};

enum ItemValCorpse {
    VAL_CORPSE_HEAD = 8,
    VAL_CORPSE_RARM = 9,
    VAL_CORPSE_LARM = 10,
    VAL_CORPSE_RLEG = 11,
    VAL_CORPSE_LLEG = 12,
};

enum ItemValPlant {
    VAL_GROWTH = 0,
    VAL_MATGOAL = 1,
    VAL_MATURITY = 2,
    VAL_MAXMATURE = 3,
    VAL_WATERLEVEL = 6,
    VAL_SOILQ = 8
};

#define LEVELTYPE_CLASS    1
#define LEVELTYPE_RACE    2