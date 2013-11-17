/*
 *  ps8getopt.h: An implementation of the getopt() function.
 *
 *  For specifications, see POSIX1.2008 standard, vol. 3, section 3.
 *  URL: http://pubs.opengroup.org/onlinepubs/9699919799/
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8getopt
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#ifndef PS8_GETOPT_H
#define PS8_GETOPT_H

int ps8_getopt(int argc, char* const argv[], const char *optstring);

#endif /* PS8_GETOPT_H */
