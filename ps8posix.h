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
#ifndef PS8POSIX_H
#define PS8POSIX_H

int getopt(int argc, char* const argv[], const char *optstring);

char *optarg;
int opterr;
int optind;
int optopt;

#endif /* PS8POSIX_H */