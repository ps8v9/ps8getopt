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

void show_supported_optstring(const char *optstring);
void echo_argv(int argc, char* const argv[]);
void print_hr();
bool initialization_test();
bool validation_test(int argc, char* const argv[], const char *optstring);
bool no_options_no_operands_test(const char* optstring);
bool no_options_one_operand_test(const char* optstring);
bool one_option_one_operand_test(const char* optstring);
bool two_ungrouped_options_one_operand_test(const char* optstring);
bool two_grouped_options_one_operand_test(const char* optstring);

int main()
{
    bool passed; /* Were all tests passed? */
    char *optstring = ":a-*$b:c";

    show_supported_optstring(optstring);                         print_hr();
    passed = initialization_test();                              print_hr();

    passed &= no_options_no_operands_test(optstring);                           print_hr();

    passed &= no_options_one_operand_test(optstring);                       print_hr();
    optind = 1; ps8_optind = 1; /* reset */

    passed &= one_option_one_operand_test(optstring);            print_hr();
    optind = 1; ps8_optind = 1; /* reset */

    passed &= two_ungrouped_options_one_operand_test(optstring); print_hr();
    optind = 1; ps8_optind = 1; /* reset */

    passed &= two_grouped_options_one_operand_test(optstring);   print_hr();
    optind = 1; ps8_optind = 1; /* reset */

    return (passed) ? 0 : 1;
}

/* Show supported chars from optstring. */
void show_supported_optstring(const char *optstring)
{
    printf("optstring: %s\n", optstring);
    printf("Supported chars in optstring: ");
    for (int i = 0; optstring[i] != '\0'; ++i)
       if (isalnum(optstring[i]) || optstring[i] == ':')
           putchar(optstring[i]);
    putchar('\n');
}

/* Echo the elements of the argv vector. */
void echo_argv(int argc, char* const argv[])
{
    printf("Command line:\n");
    for (int i = 0; i < argc; ++ i)
        printf("  argv[%d]: %s\n", i, argv[i]);
}

/* Print a short line of dashes. */
void print_hr()
{
    for (int i = 0; i < 5; ++i)
        putchar('-');
    putchar('\n');
}

/* Was ps8_optind correctly initialized? */
bool initialization_test()
{
    printf("Testing the initialization of ps8_optind.\n");
    if(ps8_optind == optind) {
        printf("Passed the test.\n");
        printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
        return true;
    } else {
        printf("Failed the test:\n");
        printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
        return false;
    }
}

/* Does ps8_getopt return the same result as getopt? */
bool validation_test(int argc, char* const argv[], const char *optstring)
{
    int a = getopt(argc, argv, optstring);
    int b = ps8_getopt(argc, argv, optstring);
    bool passed = (a == b);

    if (passed)
        printf("Passed");
     else
        printf("Failed");
    printf(" the test.\n");
    printf("  getopt returned: %d\n", a);
    printf("  ps8_getopt returned: %d\n", b);

    return passed;
}

/* Test with 0 options and 0 operands. */
bool no_options_no_operands_test(const char* optstring)
{
    int argc = 1;
    char *argv[] = { "test" };

    echo_argv(argc, argv);
    printf("Testing with 0 options and 0 operands.\n");

    return validation_test(argc, argv, optstring);
}

/* Test with 0 options and 1 operand. */
bool no_options_one_operand_test(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "abc"};

    echo_argv(argc, argv);
    printf("Testing with 0 options and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}

/* Test with 1 option and 1 operand. */
bool one_option_one_operand_test(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-a", "bc"};

    echo_argv(argc, argv);
    printf("Testing with 1 option and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}

/* Test with 2 ungrouped options and 1 operand. */
bool two_ungrouped_options_one_operand_test(const char* optstring)
{
    int argc = 4;
    char *argv[] = { "test", "-a", "-b", "c"};

    echo_argv(argc, argv);
    printf("Testing with 2 ungrouped options and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}

/* Test with 2 grouped options and 1 operand. */
bool two_grouped_options_one_operand_test(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-ab", "c"};

    echo_argv(argc, argv);
    printf("Testing with 2 grouped options and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}
