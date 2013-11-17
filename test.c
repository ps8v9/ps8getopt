/*
 *  test.c: A main program to test ps8getopt.c against the real getopt.
 *
 *  AUTHOR  : Matthew J. Fisher
 *  REPO    : https://github.com/ps8v9/ps8getopt
 *  LICENSE : This is free and unencumbered software released into the public
 *            domain. See the LICENSE file for further details.
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include <unistd.h> /* exists on POSIX systems and comes with MINGW */
extern char *optarg;
extern int opterr;
extern int optind;
extern int optopt;

#include "ps8getopt.h"
extern char *ps8_optarg;
extern int ps8_opterr;
extern int ps8_optind;
extern int ps8_optopt;

void info1(const char *optstring);
void info2(int argc, char* const argv[]);

bool test1();
bool test2(int argc, char* const argv[], const char *optstring);

int main()
{
    bool passed; /* Were all tests passed? */
    char *optstring = ":a-*$b:c";

    info1(optstring);
    passed = test1();

    /* Test with no command line options or operands. */
    int argc1 = 1;
    char *argv1[] = { "test" };
    info2(argc1, argv1);
    passed &= test2(argc1, argv1, optstring);

    /* Test with no command line options, and 1 operand. */
    int argc2 = 2;
    char *argv2[] = { "test", "abc"};
    info2(argc2, argv2);
    passed &= test2(argc2, argv2, optstring);

    /* Test with 1 command line option, and 1 operand. */
    int argc3 = 3;
    char *argv3[] = { "test", "-a", "bc"};
    info2(argc3, argv3);
    passed &= test2(argc3, argv3, optstring);

}

/* info1: Print the option chars from optstring that must be supported. */
void info1(const char *optstring)
{
    printf("optstring: %s\n", optstring);
    printf("supported chars in optstring: ");
    for (int i = 0; optstring[i] != '\0'; ++i)
       if (isalnum(optstring[i]) || optstring[i] == ':')
           putchar(optstring[i]);
    printf("\n\n");
}

/* info2: Echo the elements of the argv vector. */
void info2(int argc, char* const argv[])
{
    for (int i = 0; i < argc; ++ i)
        printf("argv[%d]: %s\n", i, argv[i]);
    putchar('\n');
}

/* test1: Was ps8_optind correctly initialized? */
bool test1()
{
    if(ps8_optind == optind)
        return true;

    fprintf(stderr, "Failed the initialization test:\n");
    fprintf(stderr, "  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    return false;
}

/* test2: Do results from ps8_getopt & getopt match with no opts? */
bool test2(int argc, char* const argv[], const char *optstring)
{
    int a = getopt(argc, argv, optstring);
    int b = ps8_getopt(argc, argv, optstring);

    if(ps8_optind == optind)
        return true;

    fprintf(stderr, "Failed the validation test:\n");
    fprintf(stderr, "  getopt returned: %d\n", a);
    fprintf(stderr, "  getopt returned: %d\n", b);
    return false;
}