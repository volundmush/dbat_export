/* ************************************************************************
* 	!PLEASE NOTE! With the introduction of CEDIT you should control   *
*	most of these entries from WITHIN THE GAME VIA CEDIT              *
* 	the values are load from the file lib/etc/config		  *
*	Please check there before making changes to the file.		  *
************************************************************************ */
/* ************************************************************************
*   File: config.c                                      Part of CircleMUD *
*  Usage: Configuration of various aspects of CircleMUD operation         *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

#include "config.h"
#include "interpreter.h"    /* alias_data definition for structs.h */

/*
 * Update:  The following constants and variables are now the default values
 * for backwards compatibility with the new cedit game configurator.  If you
 * would not like to use the cedit command, you can change the values in
 * this file instead.  - Mythran
 */
/*
 * Below are several constants which you can change to alter certain aspects
 * of the way CircleMUD acts.  Since this is a .c file, all you have to do
 * to change one of the constants (assuming you keep your object files around)
 * is change the constant in this file and type 'make'.  Make will recompile
 * this file and relink; you don't have to wait for the whole thing to
 * recompile as you do if you change a header file.
 *
 * I realize that it would be slightly more efficient to have lots of
 * #defines strewn about, so that, for example, the autowiz code isn't
 * compiled at all if you don't want to use autowiz.  However, the actual
 * code for the various options is quite small, as is the computational time
 * in checking the option you've selected at run-time, so I've decided the
 * convenience of having all your options in this one file outweighs the
 * efficency of doing it the other way.
 *
 */

/****************************************************************************/
/****************************************************************************/


/*
 * pk_allowed sets the tone of the entire game.  If pk_allowed is set to
 * NO, then players will not be allowed to kill, summon, charm, or sleep
 * other players, as well as a variety of other "asshole player" protections.
 * However, if you decide you want to have an all-out knock-down drag-out
 * PK Mud, just set pk_allowed to YES - and anything goes.
 */
int pk_allowed = false;

/* is playerthieving allowed? */
int pt_allowed = false;

/* minimum level a player must be to shout/holler/gossip/auction */
int level_can_shout = 1;

/* number of movement points it costs to holler */
int holler_move_cost = 20;

/* Pwipe Era */
int CURRENT_ERA = 8;

/* DBAT Specific variables */
int mob_specials_used = 0;
int number_of_assassins = 0;

char last_user_freed[MAX_INPUT_LENGTH];

/* Toplist Data */
int TOPLOADED = false;
char *topname[25];
int64_t toppoint[25] = {0};
/* End Top Data */

int ERAPLAYERS = 0;
int TOPCOUNTDOWN = 60;
int HEDITS = false;
int WISHTIME = 0;
int TOP_OF_NEWS = 0;
char *NEWS_TITLE;
time_t BOARDNEWMORT = 0;
time_t BOARDNEWIMM = 0;
time_t BOARDNEWCOD = 0;
time_t BOARDNEWDUO = 0;
time_t BOARDNEWBUI = 0;
time_t NEWSUPDATE = 0;
time_t INTERESTTIME = 0;
time_t LASTINTEREST = 0;
time_t LASTPAYOUT = 0;
int LASTNEWS = 0;
int LASTPAYTYPE = 0;
int SAIYAN_ALLOWED = false;
int MAJIN_ALLOWED = false;
int MOON_UP = false;
int DEATHPHASE = false;
int PCOUNT = 0;
int HIGHPCOUNT = 0;
time_t PCOUNTDATE = 0;
time_t PCOUNTDAY = 0;
/* This is for the dragon ball system */
int SELFISHMETER = 0;
int SHADOW_DRAGON1 = -1;
int SHADOW_DRAGON2 = -1;
int SHADOW_DRAGON3 = -1;
int SHADOW_DRAGON4 = -1;
int SHADOW_DRAGON5 = -1;
int SHADOW_DRAGON6 = -1;
int SHADOW_DRAGON7 = -1;

int DBALL_HUNTER1 = -1;
int DBALL_HUNTER2 = -1;
int DBALL_HUNTER3 = -1;
int DBALL_HUNTER4 = -1;

int DBALL_HUNTER1_VNUM = 88;
int DBALL_HUNTER2_VNUM = 89;
int DBALL_HUNTER3_VNUM = 0;
int DBALL_HUNTER4_VNUM = 0;
/* End dragon ball system stuff       */

/*  how many people can get into a tunnel?  The default is two, but there
 *  is also an alternate message in the case of one person being allowed.
 */
int tunnel_size = 2;

/* exp change limits */
int max_exp_gain = 1000000;    /* max gainable per kill */
int max_exp_loss = 250000;    /* max losable per death */

/* number of tics (usually 75 seconds) before PC/NPC corpses decompose */
int max_npc_corpse_time = 5;
int max_pc_corpse_time = 10;

/* How many ticks before a player is sent to the void or idle-rented. */
int idle_void = 8;
int idle_rent_time = 48;

/* This level and up is immune to idling, LVL_IMPL+1 will disable it. */
int idle_max_level = ADMLVL_IMMORT;

/* should items in death traps automatically be junked? */
int dts_are_dumps = true;

/* What the new PULSE_VIOLENCE will be */

int pulse_violence = 5;

/* What will be the new PULSE_MOBILE */
int pulse_zone = 10;
int pulse_mobile = 10;
int pulse_autosave = 60;
int pulse_idlepwd = 15;
int pulse_sanity = 30;
int pulse_usage = 5;
int pulse_timesave = 30;
int pulse_current = 10;

/*
 * Whether you want items that immortals load to appear on the ground or not.
 * It is most likely best to set this to 'YES' so that something else doesn't
 * grab the item before the immortal does, but that also means people will be
 * able to carry around things like boards.  That's not necessarily a bad
 * thing, but this will be left at a default of 'NO' for historic reasons.
 */
int load_into_inventory = false;

/* "okay" etc. */
const char *OK = "Okay.\r\n";
const char *NOPERSON = "No-one by that name here.\r\n";
const char *NOEFFECT = "Nothing seems to happen.\r\n";

/*
 * You can define or not define TRACK_THOUGH_DOORS, depending on whether
 * or not you want track to find paths which lead through closed or
 * hidden doors. A setting of 'NO' means to not go through the doors
 * while 'YES' will pass through doors to find the target.
 */
int track_through_doors = true;

/*
 * This defines the cap for player character levels. It is impossible for
 * a player to level up to the cap; so if the cap is 101, the maximum
 * possible player level is 100.
 *
 * You should set this to whatever is appropriate for your doing your
 * highest level areas without much difficulty. No risk, no reward.
 */
int level_cap = 101;

/*
 * This enables object stacking - in the same manner as mob stacking, rather
 * that listing each identical object separately, a single listing with a
 * count of the number there are is given.  A value of 0 means standard
 * behaviour.
 */
int show_obj_stacking = true;

/*
 *  This enables mob stacking - that is, if a room contains more that
 *  one of the same mob, then they are listed on a single line, with a
 *  number indicating how many there are.  A value of 0 means standard
 *  behaviour.
 */
int show_mob_stacking = true;

/*
 *  This allows aggressive mobs to initiate a fight with other mobs. A
 *  value of 0 means standard behaviour.
 */
int mob_fighting = false;

/* IMC Option - is IMC turned on? */
int imc_is_enabled = false;
/****************************************************************************/
/****************************************************************************/

/* RENT/CRASHSAVE OPTIONS */

/*
 * Should the MUD allow you to 'rent' for free?  (i.e. if you just quit,
 * your objects are saved at no cost, as in Merc-type MUDs.)
 */
int free_rent = true;

/* maximum number of items players are allowed to rent */
int max_obj_save = 30;

/* receptionist's surcharge on top of item costs */
int min_rent_cost = 100;

/*
 * Should the game automatically save people?  (i.e., save player data
 * every 4 kills (on average), and Crash-save as defined below.  This
 * option has an added meaning past bpl13.  If auto_save is YES, then
 * the 'save' command will be disabled to prevent item duplication via
 * game crashes.
 */
int auto_save = true;

/*
 * if auto_save (above) is yes, how often (in minutes) should the MUD
 * Crash-save people's objects?   Also, this number indicates how often
 * the MUD will Crash-save players' houses.
 */
int autosave_time = 1;

/* Lifetime of crashfiles and forced-rent (idlesave) files in days */
int crash_file_timeout = 10;

/* Lifetime of normal rent files in days */
int rent_file_timeout = 30;

/* Do you want to automatically wipe players who've been gone too long? */
int auto_pwipe = true;

/* Autowipe deletion criteria
   This struct holds information used to determine which players to wipe
   then the mud boots.  The levels must be in ascending order, with a
   descending level marking the end of the array.  A level -1 entry in the
   beginning is the case for players with the PLR_DELETED flag.  The
   values below match the stock purgeplay.c criteria.

   Detailed explanation by array element:
   * Element 0, level -1, days 0: Players with PLR_DELETED flag are always
	wiped.
   * Element 1, level 0, days 0: Players at level 0 have created a
	character, but have never actually entered the game, so always
	wipe them.
   * Element 2, level 1, days 30: Players at level 1 are wiped if they
	haven't logged on in the past 30 days.
   * Element 3, level 4, days 90: Players level 2 through 4 are wiped if
	they haven't logged on in the past 90 days.
   * Element 4, level 10, days 180: Players level 5-10 get 180 days.
   * Element 5, level 20, days 360: Players level 11-20 get 360 days.
   * Element 6, level 30, days 360: Players level 21-30 get 360 days.
   * Element 7: Because -1 is less than 30, this is assumed to
	be the end of the criteria.  The days entry is not used in this
	case.
*/
const struct pclean_criteria_data pclean_criteria[7] = {
/*	LEVEL		DAYS	*/
        {0,   0}, /* level 0 */
        {1,   30},
        {4,   90},
        {10,  180},
        {50,  360}, /* highest mortal */
        {100, 360}, /* all immortals */
        {-1,  0}  /* no more level checks */
};

/* Do you want players who self-delete to be wiped immediately with no
   backup?
*/
int selfdelete_fastwipe = true;

/****************************************************************************/
/****************************************************************************/


/* ROOM NUMBERS */
room_vnum death_start_room = 6000;

/* virtual number of room that mortals should enter at */
room_vnum mortal_start_room = 2;

/* virtual number of room that immorts should enter at by default */
room_vnum immort_start_room = 2;

/* virtual number of room that frozen players should enter at */
room_vnum frozen_start_room = 2;

/*
 * virtual numbers of donation rooms.  note: you must change code in
 * do_drop of act.item.c if you change the number of non-NOWHERE
 * donation rooms.
 */
room_vnum donation_room_1 = 3063;
room_vnum donation_room_2 = NOWHERE;    /* unused - room for expansion */
room_vnum donation_room_3 = NOWHERE;    /* unused - room for expansion */


/****************************************************************************/
/****************************************************************************/


/* GAME OPERATION OPTIONS */

/*
 * Please read 128bit.readme before setting this to true. Set this
 * flag if you want the conversion to take place.
 */
int bitwarning = false;

/*
 * If you want to look at normal worldfiles but DO NOT want to save
 * to 128bit format, turn this to false. However, do not save through
 * olc, or your worldfiles will be 128bit anyway.
 */
int bitsavetodisk = true;

/*
 * This is the default port on which the game should run if no port is
 * given on the command-line.  NOTE WELL: If you're using the
 * 'autorun' script, the port number there will override this setting.
 * Change the PORT= line in autorun instead of (or in addition to)
 * changing this.
 */
uint16_t DFLT_PORT = 5001;

/*
 * IP address to which the MUD should bind.  This is only useful if
 * you're running Circle on a host that host more than one IP interface,
 * and you only want to bind to *one* of them instead of all of them.
 * Setting this to NULL (the default) causes Circle to bind to all
 * interfaces on the host.  Otherwise, specify a numeric IP address in
 * dotted quad format, and Circle will only bind to that IP address.  (Of
 * course, that IP address must be one of your host's interfaces, or it
 * won't work.)
 */
const char *DFLT_IP = NULL; /* bind to all interfaces */
/* const char *DFLT_IP = "192.168.1.1";  -- bind only to one interface */

/* default directory to use as data directory */
const char *DFLT_DIR = "data";

/*
 * What file to log messages to (ex: "log/syslog").  Setting this to NULL
 * means you want to log to stderr, which was the default in earlier
 * versions of Circle.  If you specify a file, you don't get messages to
 * the screen. (Hint: Try 'tail -f' if you have a UNIX machine.)
 */
const char *LOGNAME = NULL;
/* const char *LOGNAME = "log/syslog";  -- useful for Windows users */

/* maximum number of players allowed before game starts to turn people away */
int max_playing = 300;

/* maximum size of bug, typo and idea files in bytes (to prevent bombing) */
int max_filesize = 50000;

/* maximum number of password attempts before disconnection */
int max_bad_pws = 3;

/*
 * Rationale for enabling this, as explained by naved@bird.taponline.com.
 *
 * Usually, when you select ban a site, it is because one or two people are
 * causing troubles while there are still many people from that site who you
 * want to still log on.  Right now if I want to add a new select ban, I need
 * to first add the ban, then SITEOK all the players from that site except for
 * the one or two who I don't want logging on.  Wouldn't it be more convenient
 * to just have to remove the SITEOK flags from those people I want to ban
 * rather than what is currently done?
 */
int siteok_everyone = true;

/*
 * Some nameservers are very slow and cause the game to lag terribly every 
 * time someone logs in.  The lag is caused by the gethostbyaddr() function
 * which is responsible for resolving numeric IP addresses to alphabetic names.
 * Sometimes, nameservers can be so slow that the incredible lag caused by
 * gethostbyaddr() isn't worth the luxury of having names instead of numbers
 * for players' sitenames.
 *
 * If your nameserver is fast, set the variable below to NO.  If your
 * nameserver is slow, of it you would simply prefer to have numbers
 * instead of names for some other reason, set the variable to YES.
 *
 * You can experiment with the setting of nameserver_is_slow on-line using
 * the SLOWNS command from within the MUD.
 */

int nameserver_is_slow = false;

const char *ANSIQUESTION = "Do you support the ANSI color standard (Yn)? ";

/*
 * Will changes save automaticaly in OLC ?
 */
int auto_save_olc = 1;

/*
 * if you wish to enable Aedit, set this to 1 
 * This will make the mud look for a file called socials.new,
 * which is in a different format than the stock socials file.
 */
int use_new_socials = 1;

const char *MENU =
        "\r\n"
        "@GWelcome to @YCircleMUD!@n\r\n"
        "@B0@W) @CExit from @YCircleMUD.@n\r\n"
        "@B1@W) @CEnter the game.@n\r\n"
        "@B2@W) @CEnter description.@n\r\n"
        "@B3@W) @CGame Info (Please Read)@n\r\n"
        "@B4@W) @CChange password.@n\r\n"
        "@B5@W) @CDelete this character.@n\r\n"
        "\r\n"
        "   @WMake your choice: @n";


const char *WELC_MESSG =
        "\r\n"
        "Welcome to the land of CircleMUD!  May your visit here be... Interesting."
        "\r\n\r\n";

const char *START_MESSG =
        "Welcome.  This is your new CircleMUD character!  You can now earn gold,\r\n"
        "gain experience, find weapons and equipment, and much more -- while\r\n"
        "meeting people from around the world!\r\n";

/****************************************************************************/
/****************************************************************************/


/* AUTOWIZ OPTIONS */

/*
 * Should the game automatically create a new wizlist/immlist every time
 * someone immorts, or is promoted to a higher (or lower) god level?
 * NOTE: this only works under UNIX systems.
 */
int use_autowiz = true;

/* If yes, what is the lowest level which should be on the wizlist?  (All
   immort levels below the level you specify will go on the immlist instead.) */
int min_wizlist_lev = ADMLVL_GOD;

/* Portal Object */

/*
 * This should be the VNUM of an object you wish to use as a template
 * for portal spells when cast. If this object is not in your obj files
 * you will get a core dump when casting.
 */

obj_vnum portal_object = 2;

/* Initial points pool size for points pool based character creation. */
int initial_points = 20;

/*
 * Do you want EXITS and AUTOEXIT to automatically display closed doors?
 * Set to NO to mimic historic behaviour - a player has to explicitly
 * look in a certain direction to see a door there.
 */
int disp_closed_doors = true;

/*
 * Do you want players to be able to reroll their status at creation?
 * Set to NO to mimic historic behaviour - a player gets the stats rolled
 * and cannot see the values at creation time.
 */
int reroll_status = false;

/*
 * Advancement options
 * allow_multiclass: Controls whether you can advance multiple classes
 * allow_prestige: Controls whether you can advance prestige classes
 * auto_level: Controls whether you will automatically go up a level when
 *   you have enough experience. I recommend that you leave auto_level 
 *   YES if allow_multiclass is NO and vice versa. auto-leveling will 
 *   only level your primary class!
 */

int allow_multiclass = false;
int allow_prestige = false;
int auto_level = true;

/*
 * Do you want to enable MCCP2 stream compression? It is safe to enable
 * this option even on systems without zlib, but compression will not
 * happen without zlib.
 *
 * Enabling compression will save a great deal of bandwidth for data
 * being transmitted to users with MCCP2-compliant MUD clients.
 */
int enable_compression = true;

/*
 * Do you want to enable different spoken languages? Set to YES and
 * you will have different races speaking in different languages.
 */
int enable_languages = true;

/*
 * Do you want to treat all objects as unique? Set to YES and
 * every object created in the game will be flagged as UNIQUE. This
 * will help prevent object duping.
 */
int all_items_unique = true;

/*
 * Multiplier that is applied to gaining experience.
 */
float exp_multiplier = 1.0;

/*
 * You can now choose the method of new character creation. We have
 * 5 methods currently, but it can be expanded to use any other method
 * you create.
 */
int method = 0;

