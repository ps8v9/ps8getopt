/*
 *  test.c: A main program to test ps8posix.c.
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8posix
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <assert.h>

#include "ps8posix.h"

int main(int argc, char *argv[])
{
    /* The following assert reflects getopt's unimplemented status. */
    assert(getopt(argc, argv, ":abc:d") == -1);
}