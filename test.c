/*
 *  test.c: A main program to test ps8getopt.c.
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8getopt
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <assert.h>
#include <stdio.h>
#include <unistd.h> /* exists on POSIX systems and comes with MINGW */

#include "ps8getopt.h"

extern char *optarg;
extern int opterr;
extern int optind;
extern int optopt;

extern char *ps8_optarg;
extern int ps8_opterr;
extern int ps8_optind;
extern int ps8_optopt;

int main(int argc, char *argv[])
{
    printf("optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    assert(optind == ps8_optind);

    char *optstring = "abc";
    assert(getopt(argc, argv, optstring) == ps8_getopt(argc, argv, optstring));
}