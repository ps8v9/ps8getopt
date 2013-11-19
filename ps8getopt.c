/*
 *  ps8getopt.c: An implementation of the getopt() function.
 *
 *  For specifications, see POSIX1.2008 standard, vol. 3, section 3.
 *  URL: http://pubs.opengroup.org/onlinepubs/9699919799/
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8getopt
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps8getopt.h"

char *ps8_optarg;
int ps8_opterr = 1;
int ps8_optind = 1;
int ps8_optopt = 63;

static int optchar_offset = 1;

int ps8_getopt(int argc, char* const argv[], const char *optstring)
{
    /* Sanity checks. */

    if (argc <= ps8_optind)
        return -1;

    char *optgroup = argv[ps8_optind];

    if (optgroup == NULL || optgroup[0] != '-' || (strcmp(optgroup, "-") == 0))
        return -1;
    if (strcmp(optgroup, "--") == 0) {
        ps8_optind++;
        return -1;
    }

    /* Try to match next option char from argv to a char in optstring. */

    char optchar = optgroup[optchar_offset];
    bool matched = false;
    int optstr_len = strlen(optstring);
    int i;

    for (i = 0; i < optstr_len; ++i) {
        if (optstring[i] == optchar) {
            matched = true;
            break;
        }
    }

    if (! matched)
        return '?';

    /* Found a valid opt char. What do we know about it? */

    bool takes_arg = (optstring[i + 1] == ':');
    bool terminates_optgroup = (optgroup[optchar_offset + 1] == '\0');

    /* Do the specified things! */

    if (!takes_arg) {
        if (terminates_optgroup) {
            ps8_optind++;
            optchar_offset = 1;
        } else {
            optchar_offset++;
        }
        return optchar;
    }

    if (terminates_optgroup) {
        ps8_optarg = argv[ps8_optind + 1];
        ps8_optind += 2;
        if (ps8_optind > argc) {
            /* Option argument is missing. */
            /* What does the real getopt do here? */
            return '?';
        }
    } else {
        ps8_optarg = optgroup + optchar_offset + 1;
        ps8_optind++;
        optchar_offset = 1;
    }

    return optchar;

}
