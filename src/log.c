
/*
 * log.c - logging routines 
 */

/*
 * $Id: log.c,v 1.3 2005/08/08 09:43:07 murrayma Exp $ 
 */

#include "copyright.h"
#include "config.h"

#include <sys/types.h>

#include "db.h"
#include "mudconf.h"
#include "externs.h"
#include "flags.h"
#include "powers.h"
#include "alloc.h"
#include "htab.h"
#include "ansi.h"

#if ARBITRARY_LOGFILES_MODE==2
extern void fileslave_dolog(dbref thing, const char *fname, const char *fdata);
#endif

#ifndef STANDALONE
/* *INDENT-OFF* */

NAMETAB logdata_nametab[] = {
    {(char *)"flags",		1,	0,	LOGOPT_FLAGS},
    {(char *)"location",		1,	0,	LOGOPT_LOC},
    {(char *)"owner",		1,	0,	LOGOPT_OWNER},
    {(char *)"timestamp",		1,	0,	LOGOPT_TIMESTAMP},
    { NULL,				0,	0,	0}};

NAMETAB logoptions_nametab[] = {
    {(char *)"accounting",		2,	0,	LOG_ACCOUNTING},
    {(char *)"all_commands",	2,	0,	LOG_ALLCOMMANDS},
    {(char *)"suspect_commands",	2,	0,	LOG_SUSPECTCMDS},
    {(char *)"bad_commands",	2,	0,	LOG_BADCOMMANDS},
    {(char *)"buffer_alloc",	3,	0,	LOG_ALLOCATE},
    {(char *)"bugs",		3,	0,	LOG_BUGS},
    {(char *)"checkpoints",		2,	0,	LOG_DBSAVES},
    {(char *)"config_changes",	2,	0,	LOG_CONFIGMODS},
    {(char *)"create",		2,	0,	LOG_PCREATES},
    {(char *)"killing",		1,	0,	LOG_KILLS},
    {(char *)"logins",		1,	0,	LOG_LOGIN},
    {(char *)"network",		1,	0,	LOG_NET},
    {(char *)"problems",		1,	0,	LOG_PROBLEMS},
    {(char *)"security",		2,	0,	LOG_SECURITY},
    {(char *)"shouts",		2,	0,	LOG_SHOUTS},
    {(char *)"startup",		2,	0,	LOG_STARTUP}, 
    {(char *)"wizard",		1,	0,	LOG_WIZARD},
    { NULL,				0,	0,	0}};

/* *INDENT-ON* */





#endif

char *strip_ansi_r(char *dest, char *raw, size_t n) {
    char *p = (char *) raw;
    char *q = dest;

    while (p && *p && ((q-dest) < n)) {
        if (*p == ESC_CHAR) {
            /*
             * Start of ANSI code. Skip to end. 
             */
            while (*p && !isalpha(*p))
                p++;
            if (*p)
                p++;
        } else
            *q++ = *p++;
    }
    *q = '\0';
    return dest;
}


char *strip_ansi(const char *raw) {
    static char buf[LBUF_SIZE];
    char *p = (char *) raw;
    char *q = buf;

    while (p && *p) {
        if (*p == ESC_CHAR) {
            /*
             * Start of ANSI code. Skip to end. 
             */
            while (*p && !isalpha(*p))
                p++;
            if (*p)
                p++;
        } else
            *q++ = *p++;
    }
    *q = '\0';
    return buf;
}

char *normal_to_white(raw)
    const char *raw;
{
    static char buf[LBUF_SIZE];
    char *p = (char *) raw;
    char *q = buf;


    while (p && *p) {
        if (*p == ESC_CHAR) {
            /*
             * Start of ANSI code. 
             */
            *q++ = *p++;	/*
            * ESC CHAR 
            */
            *q++ = *p++;	/*
            * [ character. 
            */
            if (*p == '0') {	/*
                                 * ANSI_NORMAL 
                                 */
                safe_str("0m", buf, &q);
                safe_chr(ESC_CHAR, buf, &q);
                safe_str("[37m", buf, &q);
                p += 2;
            }
        } else
            *q++ = *p++;
    }
    *q = '\0';
    return buf;
}

/*
 * ---------------------------------------------------------------------------
 * * start_log: see if it is OK to log something, and if so, start writing the
 * * log entry.
 */

int start_log(primary, secondary)
    const char *primary, *secondary;
{
    struct tm *tp;
    time_t now;

    mudstate.logging++;
    switch (mudstate.logging) {
        case 1:
        case 2:

            /*
             * Format the timestamp 
             */

            if ((mudconf.log_info & LOGOPT_TIMESTAMP) != 0) {
                time((time_t *) (&now));
                tp = localtime((time_t *) (&now));
                sprintf(mudstate.buffer, "%d%02d%02d.%02d%02d%02d ",
                        tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
                        tp->tm_hour, tp->tm_min, tp->tm_sec);
            } else {
                mudstate.buffer[0] = '\0';
            }
#ifndef STANDALONE
            /*
             * Write the header to the log 
             */

            if (secondary && *secondary)
                fprintf(stderr, "%s%s %3s/%-5s: ", mudstate.buffer,
                        mudconf.mud_name, primary, secondary);
            else
                fprintf(stderr, "%s%s %-9s: ", mudstate.buffer,
                        mudconf.mud_name, primary);
#endif
            /*
             * If a recursive call, log it and return indicating no log 
             */

            if (mudstate.logging == 1)
                return 1;
            fprintf(stderr, "Recursive logging request.\r\n");
        default:
            mudstate.logging--;
    }
    return 0;
}

/*
 * ---------------------------------------------------------------------------
 * * end_log: Finish up writing a log entry
 */

void end_log(void)
{
    fprintf(stderr, "\n");
    fflush(stderr);
    mudstate.logging--;
}

/*
 * ---------------------------------------------------------------------------
 * * log_perror: Write perror message to the log
 */

void log_perror(primary, secondary, extra, failing_object)
    const char *primary, *secondary, *extra, *failing_object;
{
    start_log(primary, secondary);
    if (extra && *extra) {
        log_text((char *) "(");
        log_text((char *) extra);
        log_text((char *) ") ");
    }
    perror((char *) failing_object);
    fflush(stderr);
    mudstate.logging--;
}

/*
 * ---------------------------------------------------------------------------
 * * log_text, log_number: Write text or number to the log file.
 */

void log_text(text)
    char *text;
{
    fprintf(stderr, "%s", strip_ansi(text));
}

void log_number(num)
    int num;
{
    fprintf(stderr, "%d", num);
}

/*
 * ---------------------------------------------------------------------------
 * * log_name: write the name, db number, and flags of an object to the log.
 * * If the object does not own itself, append the name, db number, and flags
 * * of the owner.
 */

void log_name(target)
    dbref target;
{
#ifndef STANDALONE
    char *tp;

    if ((mudconf.log_info & LOGOPT_FLAGS) != 0)
        tp = unparse_object((dbref) GOD, target, 0);
    else
        tp = unparse_object_numonly(target);
    fprintf(stderr, "%s", strip_ansi(tp));
    free_lbuf(tp);
    if (((mudconf.log_info & LOGOPT_OWNER) != 0) &&
            (target != Owner(target))) {
        if ((mudconf.log_info & LOGOPT_FLAGS) != 0)
            tp = unparse_object((dbref) GOD, Owner(target), 0);
        else
            tp = unparse_object_numonly(Owner(target));
        fprintf(stderr, "[%s]", strip_ansi(tp));
        free_lbuf(tp);
    }
#else
    fprintf(stderr, "%s(#%d)", Name(target), target);
#endif
    return;
}

/*
 * ---------------------------------------------------------------------------
 * * log_name_and_loc: Log both the name and location of an object
 */

void log_name_and_loc(player)
    dbref player;
{
    log_name(player);
    if ((mudconf.log_info & LOGOPT_LOC) && Has_location(player)) {
        log_text((char *) " in ");
        log_name(Location(player));
    }
    return;
}

char *OBJTYP(thing)
    dbref thing;
{
    if (!Good_obj(thing)) {
        return (char *) "??OUT-OF-RANGE??";
    }
    switch (Typeof(thing)) {
        case TYPE_PLAYER:
            return (char *) "PLAYER";
        case TYPE_THING:
            return (char *) "THING";
        case TYPE_ROOM:
            return (char *) "ROOM";
        case TYPE_EXIT:
            return (char *) "EXIT";
        case TYPE_GARBAGE:
            return (char *) "GARBAGE";
        default:
            return (char *) "??ILLEGAL??";
    }
}

void log_type_and_name(thing)
    dbref thing;
{
    char nbuf[16];

    log_text(OBJTYP(thing));
    sprintf(nbuf, " #%d(", thing);
    log_text(nbuf);
    if (Good_obj(thing))
        log_text(Name(thing));
    log_text((char *) ")");
    return;
}

void log_type_and_num(thing)
    dbref thing;
{
    char nbuf[16];

    log_text(OBJTYP(thing));
    sprintf(nbuf, " #%d", thing);
    log_text(nbuf);
    return;
}

#if ARBITRARY_LOGFILES_MODE>0
int log_to_file(thing, logfile, message)
    dbref thing;
    const char *logfile, *message;
{
    FILE *fp;
    char pathname[210];		/* Arbitrary limit in logfile length */

    if (!message || !*message)
        return 1;		/* Nothing to do */

    if (!logfile || !*logfile || strlen(logfile) > 200
            || strrchr(logfile, '/'))
        return 0;		/* invalid logfile name */

    sprintf(pathname, "logs/%s", logfile);
#if ARBITRARY_LOGFILES_MODE==2
    if (access(pathname, R_OK|W_OK) != 0)
        return 0;
    fileslave_dolog(thing, pathname, message);
    return 1;
#elif ARBITRARY_LOGFILES_MODE==1
    fp = fopen(pathname, "r+");
    if (!fp)
        return 0;		/* Logfile doesn't exist or not writable */

    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s\n", message);
    fclose(fp);
#endif
    return 1;
}

void do_log(player, cause, key, logfile, message)
    dbref player, cause;
    int key;
    char *logfile, *message;
{
    if (!message || !*message) {
        notify(player, "Nothing to log!");
        return;
    }

    if (!logfile || !*logfile || !log_to_file(player, logfile, message)) {
        notify(player, "Invalid logfile.");
        return;
    }
    notify(player, "Message logged.");
}
#endif
