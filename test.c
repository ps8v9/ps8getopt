/*
 *  test.c: A main program to test ps8getopt.c.
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8getopt
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <assert.h>

#include "ps8getopt.h"

int main(int argc, char *argv[])
{
    /* The following assert will reveal getopt's unimplemented status. */
    assert(getopt(argc, argv, ":abc:d") == -1);
}