/*
 *  ps8posix.c: A few POSIX functions that MSVC doesn't provide.
 *
 *  For specifications, see POSIX1.2008 standard, vol. 3, section 3.
 *  URL: http://pubs.opengroup.org/onlinepubs/9699919799/
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8posix
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <ctype.h>    /* for isalnum() */

#include "ps8posix.h"

int getopt(int argc, char* const argv[], const char *optstring)
{
    return 42; /* There is obviously some work to do here! */
}

/*
 *  Some notes on the specs for getopt():
 *
 *  - single-char options only
 *  - allowed chars are A-Z, a-z, 0-9 (can use isalnum() for this)
 *  - opt delimiter is a hyphen (-)
 *  - multiple opts may be grouped behind a single delimiter
 *  - an opt that takes an optarg terminates the group
 *  - an optional optarg is part of the same argument as the option
 *  - a mandatory optarg is the next argument
 *  - opts precede operands
 *  - the -- delimiter indicates no more opts
 *  - argc is the argument count as received by main
 *  - argv is the argument array as received by main
 *  - optstring is a string of recognized opt characters
 *  - a colon after a character indicates that it takes an option
 *  - optind is the index of the next element of argv to be processed
 *  - optind shall be initialized to 1 "by the system"
 *  - getopt shall update optind when done with each element of argv
 *  - not specified: what happens if app sets optind to 0 before calling getopt
 *  - not specified: when an element contains multiple opt chars, how does
 *                   getopt determine which options have already been processed
 *  - getopt shall return the next opt char (if found) that matches a char in
 *    optstring (if there is a match)
 *  - if opt that takes arg was last char in an element of argv, optarg shall
 *    contain the next element of argv, and optind += 2 (and if this exceeds
 *    argc, getopt shall return an error)
 *  - otherwise, optarg shall point to the string following the opt char in that
 *    element of argv, and optind += 1
 *  - if when getopt is called:
 *       argv[optind] != NULL
 *      *argv[optind] != '-'
 *       strncmp(argv[optind], "-", 1) == 0
 *    then getopt shall return -1 without incrementing optind
 *  - if strcmp(argv[optind], "--", getopt shall return -1 after incrementing
 *    optind
 *  - if an opt char that is not in optstring is found, return '?'
 *  - if (optarg is missing) {
 *      if optstring[0] was ':'
 *        return ':'
 *      else
 *        return '?'
 *      optopt = opt char for which optarg was missing
 *      if app did not set opterr to 0 && optstring[0] != ':'
 *        print a diagnostic message to stderr in the format specified for the getopts
 *          utility
 *  - getopt need not be thread safe
 */
