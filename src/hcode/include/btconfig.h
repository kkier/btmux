
/*
 * $Id: btconfig.h,v 1.9 2005/06/24 04:39:08 av1-op Exp $
 *
 * Author: Markus Stenberg <fingon@iki.fi>
 *
 *  Copyright (c) 1996 Markus Stenberg
 *  Copyright (c) 1999-2005 Kevin Stevens
 *       All rights reserved
 *
 * Created: Wed Oct  9 10:47:12 1996 fingon
 * Last modified: Tue Jun 23 06:56:18 1998 fingon
 *
 */

#include "config.h"

#ifndef BTCONFIG_H
#define BTCONFIG_H
/*
 * Define this if you want to use FASA-near-literal (gradiations on
 * engines are cut down to be more feasible) repair part spreads.
 */
/* No need to define here, its part of the configure system now
 * #define BT_COMPLEXREPAIRS
 */

/* Define this if you want to have "movement modes" on. This includes
 * sprinting, dodging, and evading. Dodging will only be enabled i
 * BT_EXTENDED_ADVANTAGES is defined since it can only be used by
 * the Dodge_Maneuver advantage therein.
 */
/* No need to define here, its part of the configure system now
 * #define BT_MOVEMENT_MODES
 */

/* Define this if you want to use some of Exile's extended skills
 * added. At this time it is just 'Research'. None of these skills
 * should involve anything but the extra skill entry and no hcode
 * behaviour added to them
 */
#define BT_EXILE_SKILLS

/* Define this if you want to use MW3-like character skills spreads.
 * This includes gunnery and piloting skills, but also computer
 * for shutdown rolls, and maybe more. Please note due to various
 * reasons these are called MW3-like and now MW-literal because
 * the literal MW3 spread gradiates all the skills too much and it
 * is not prefered for gameplay in this mode. It is a future possible
 * project to make this a #define with a # for parsing to switch out
 * MW3-literal skill spreads and fullfill thsi optionally.
 */
/* No need to define here, its part of the configure system now
 * #define BT_EXILE_MW3STATS
 */

/* Define this if you want to use extended advantages merged from the
 * Exile tree. This will make charstats in the DB not portable w/o
 * a +charclear to binaries running w/o this option.
 */
/* No need to define here, its part of the configure system now
 * #define BT_EXTENDED_ADVANTAGES
 */

/* Define this if you want Exile style targeting computers on. This is just
 * a XCode value called 'targcomp'. (0 None, 1 Short, 2, Long, 3 Multi, 4 AA)
 * An extrapolation of some maxtech tweaks.
 */
/* No need to define here, its part of the configure system now
 * #define BT_TARGCOMP_MODES
 */

/* Define this if you are wanting to have near instant techtime as a config
 * parameter name btech_freetechtime. Could be left at the base level but as
 * part of merge trying to keep defined segregation over new stuff
 */
/* No need to define here, its part of the configure system now
 * #define BT_FREETECHTIME
 */

/* Define if you want BV calculation functions. This include btgetbv()
 * and btgetbv_ref(), but will also perform damage per time based updates
 * on the mech live to support more balance XP ratio's.
 */
#define BT_CALCULATE_BV

/* Define if you want hcode to support an econ DB of sorts.
 * At this moment btsetpartcost(), btgetpartcost(), and btfasabasecost()
 * exist to interact with this. Maybe more later.
 */
/* No need to define here, its part of the configure system now
 * #define BT_ADVANCED_ECON
 */

/* Define if you want extra commands in debug objects for re-loading and
 * saving file at econ.db location, loading into econ memory default data, etc...
 * This is configured out since after initialization of the cost data there isn't
 * much use to have the commands around. Normal hcode save includes econ.db write.
 * Having the command to load default econ.db contents forever just wastes static
 * memory space and such. This default build has it one but I suggest turning it off
 * after either you have yer own acquired econ.db or create and save an initial one
 * after setting up.
 */
#define BT_ADVANCED_ECON_INIT

/* Define if you want Variable Recycle Times for weapons */
#define BT_USE_VRT

/* Define if you want part-specific weights for cargo */
#define BT_PART_WEIGHTS

/* Define if you want speed to be calculated on real weight, allowing
 * 'mechs to go faster than they were templated to 
 */
/* No need to define here, its part of the configure system now
 * #define WEIGHT_OVERSPEEDING 
 */

/* Define if you want 'mech frequencies to be copied to MechWarriors when
   they eject, autoeject or disembark */
/* No need to define here, its part of the configure system now
 * #define COPY_CHANS_ON_EJECT 
 */

/* Define if you want 'mech frequencies *not* to be copied to MechWarriors
   but would rather see a random frequency. */
/* \todo If COPY_CHANS_ON_EJECT isn't defined, assume RANDOM_CHAN_ON_EJECT.
 * this makes a little more sense and is less configuration 
 */
/*
 * #define RANDOM_CHAN_ON_EJECT 
 */

/* Define for heatsink on/off msgs when using heatcutoff */
/* #define HEATCUTOFF_DEBUG */

/* Define if you want weight-class based 'status' pictures */
#define WEIGHTVARIABLE_STATUS

/* Define if you want the radio OBSERVATORIC units to be more
   Observation-lounge like: hears everything, and reports more. */
#define OBSERVATORIC_OL_RADIO

#define RS_MECH_IDLE  86400
#define SIM_MECH_IDLE 3600

/* Where the dogfighting becomes 'fun' */
#define ATMO_Z    100

/* Orbit elevation */
#define ORBIT_Z   300

/* At max 5x */
#define ACCEL_MOD 5

/* How many secs it takes to apply one maxthrust
   (mod'ed by location _and_ type of craft) */
#define AERO_SECS_THRUST  30

#define PIL_XP_EVERY_N_STEPS 10

/* Where dead pilots go */
#define AFTERLIFE_DBREF mudconf.afterlife_dbref
#define AFTERSCEN_DBREF mudconf.afterscen_dbref

/* Where used MW templates go to wait for reincarnation (<g>) */
#define USED_MW_STORE   mudconf.btech_usedmechstore

#define MINE_NEXT_MODIFIER 2/3
#define MINE_MIN           5
#define MINE_TABLE         2	/* 0 = General, 2 = KICK */

/* Have weird jump code? (undef = basic MUSE one) */
#define ODDJUMP

/* Whether we want 'BT' partial or not */
#define BT_PARTIAL

/* unload / load, addstuff / removestuff multiple kinds of items at
   once */
#define ECON_ALLOW_MULTIPLE_LOAD_UNLOAD

/* Whether we acknowledge Munchkins exist or not */
#define CLAN_SUPPORT

/* Whether we support C3 or not */
#define C3_SUPPORT

/* Whether we want it enabled or not */
#define MENU_CHARGEN

/* Whether we want customization code or not */
#define MENU_CUSTOMIZE

/* Show BTHs on Debug */
#define BTH_DEBUG

/* Show some XP calculation messages on Debug */
#define XP_DEBUG

/* Shows ton of unneccessary debug messages */
#undef  TEMPLATE_DEBUG

/* Show jump coords on Debug */
#undef JUMPDEBUG

/* Show sensor BTHs on Debug */
#undef SENSOR_BTH_DEBUG

/* Don't see see/dontsee msgs */
#undef SENSOR_DEBUG

/* Shows errors whenever need be */
#define TEMPLATE_VERBOSE_ERRORS

/* Show loading / saving of map stuff specifically */
#undef VERBOSE_MAP_STUFF

/* Define if buildings should regenerate CF */
#define BUILDINGS_REPAIR_THEMSELVES
#define BUILDINGS_REBUILD_FROM_DESTRUCTION

#define BUILDING_REPAIR_AMOUNT     1
#define BUILDING_REPAIR_DELAY    120	/* 1 pt / 1 min */

/* Howlong to wait before rebuilding cf0'd buildings. */
#define BUILDING_DREBUILD_DELAY 7200	/* 2 hours */

/* Define if ECM status (ECM active, ECCM active, ECM-disturbed and
 * ECM-protected) should show on contacts (as 'E', 'P', 'e' and 'p') */
#define ECM_ON_CONTACTS

#define LATERAL_TICK  6
#define HEAT_TICK     2
#define JUMP_TICK     1
#define MOVE_TICK     1		/* How oft da mecha move ;-) */
#define MOVE_MOD      MOVE_TICK / 2
#define WEAPON_TICK   2

#define ARTY_SPEED    5		/* Artillery round flies 5 hexes / second */
#define ARTILLERY_MAPSHEET_SIZE 20	/* Size of single arty mapsheet */
#define ARTILLERY_MINIMUM_FLIGHT 10	/* How long's the minimum flight time */

#define DROP_TO_STAND_RECYCLE (MOVE_TICK * 12)
#define JUMP_TO_HIT_RECYCLE   (JUMP_TICK * 12 / (MechType(mech) == CLASS_BSUIT ? 4 : 1))

#define INITIAL_PLOS_TICK 1	/* How many secs after startup */
#define LOS_TICK          2	/* Update LOS tables */
#define HIDE_TICK        10
#define PLOS_TICK         3	/* How many seconds interval between checks */
#define SCHANGE_TICK     10	/* Sensor change */
#define SPOT_TICK        10	/* How oft is the range for spotting checked? */

#define PHYSICAL_RECYCLE_TIME 30
#define STARTUP_TIME 30
#define UNCONSCIOUS_TIME 30	/* ORIGINAL authors thought it was UNCONCIOUS */
#define WEAPON_RECYCLE_TIME 30	/* weapon_tick's */
#define FALL_TICK     3		/* How oft do we call fall event? */
#define FALL_ACCEL    1		/* How much do we accelerate each event? */
#define OOD_SPEED     2		/* 2 Z / tic ; 150 sec for landing */
#define OOD_TICK      1
#define DUMP_TICK     30	/* How long does it take to eject 1 ton of ammo? */
#define DUMP_GRAD_TICK 1	/* This oft we _maybe_ dump stuff */
#define DUMP_SPEED   (DUMP_TICK/DUMP_GRAD_TICK)
#define MASC_TICK      60	/* Time for each MASC regen / fail */
#define SCHARGE_TICK   60	/* Time for each Supercharger regen / fail */
#define RANDOM_TICK     6	/* How many seconds do we want to use same rnd# for
				   BTHs etc */
#define DS_SPAM_TIME   10	/* At max, 1 mapemit every 10 secs concerning a
				   single DS */

#define MAX_BOOM_TIME  30	/* Max time between first and last CT int hit for
				   fusion explosion */
#define BOOM_BTH        9	/* Roll below this or 'boom' */
#define MAX_C3_SLAVES   3

/* Skills used if pilot's not valid and no default mech skills */
#define DEFAULT_GUNNERY   6
#define DEFAULT_PILOTING  6
#define DEFAULT_SPOTTING  8
#define DEFAULT_ARTILLERY 8
#define DEFAULT_COMM      6

/* Default ranges and stuff */
#define DEFAULT_TACRANGE    20
#define DEFAULT_LRSRANGE    40
#define DEFAULT_RADIORANGE  80
#define DEFAULT_SCANRANGE   20
#define DEFAULT_HEATSINKS   10

/* IS guys suck */
#define DEFAULT_COMPUTER     2
#define DEFAULT_RADIO	     3
#define DEFAULT_PART_LEVEL   3

/* Clans get better stuff */
#define DEFAULT_CLCOMPUTER   5
#define DEFAULT_CLRADIO	     5
#define DEFAULT_CLPART_LEVEL 5

/* Display Types */
#define LRS_DISPLAY_WIDTH 70
#define LRS_DISPLAY_WIDTH2 35
#define LRS_DISPLAY_HEIGHT 11
#define LRS_DISPLAY_HEIGHT2 5

/* Census config: */

#undef HAVE_LOC_IN_CENSUS

#define NAMELEN 20
#define RANKLEN 20
#define JOBLEN  30
#ifdef HAVE_LOC_IN_CENSUS
#define LOCLEN  20
#endif


/*3030 / MUSE mode */

/*ADVANCED_LOS: If we want the non-100 percent LOS or not */

/*def for 3030, undef for MUSE */

/*SIMPLE_SENSORS: Just basic vislight sensors without option of changing them*/

/*undef for 3030, def for MUSE */

/*LOCK_TICK: 8 for 3030, 0 for MUSE */

#if 1

/* 3030 set */

#define ADVANCED_LOS
#undef  SIMPLE_SENSORS
#define LOCK_TICK     8
#else

/* MUSE set */

#undef ADVANCED_LOS
#define SIMPLE_SENSORS
#define LOCK_TICK     0

#endif

#define INITIAL_RANK 3		/* When starting chargen */
#define FINAL_RANK   2		/* When finished with chargen */

#define ECM_RANGE    6

/* From 160 sec to 3840 sec */

/* #define FIRE_DURATION  ((Number(40,Number(60,960))) * 4) */
#define FIRE_DURATION ((Number(60,180)))

/* From 90 sec to 1200 sec */

/* #define SMOKE_DURATION ((Number(30,Number(60,400))) * 4) */
#define SMOKE_DURATION ((Number(90,150)))

/* What kind of evil magic DFM's affect */
#undef DFM_AFFECT_BTH

#define LITE_RANGE 30

typedef unsigned char byte;

#endif				/* BTCONFIG_H */
