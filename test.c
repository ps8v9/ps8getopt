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
bool no_more_args_test(const char* optstring);
bool validation_test(int argc, char* const argv[], const char *optstring);
bool no_args_test(const char* optstring);
bool one_operand_test(const char* optstring);
bool one_option_one_operand_test(const char* optstring);

int main()
{
    bool passed; /* Were all tests passed? */
    char *optstring = ":a-*$b:c";

    show_supported_optstring(optstring);              print_hr();
    passed = initialization_test();                   print_hr();
    passed &= no_more_args_test(optstring);           print_hr();
    passed &= no_args_test(optstring);                print_hr();
    passed &= one_operand_test(optstring);            print_hr();
    passed &= one_option_one_operand_test(optstring); print_hr();

    return (passed) ? 0 : 1;
}

/* show_supported_optstring: Show supported chars from optstring. */
void show_supported_optstring(const char *optstring)
{
    printf("optstring: %s\n", optstring);
    printf("supported chars in optstring: ");
    for (int i = 0; optstring[i] != '\0'; ++i)
       if (isalnum(optstring[i]) || optstring[i] == ':')
           putchar(optstring[i]);
    putchar('\n');
}

/* info2: Echo the elements of the argv vector. */
void echo_argv(int argc, char* const argv[])
{
    printf("Input:\n");
    for (int i = 0; i < argc; ++ i)
        printf("  argv[%d]: %s\n", i, argv[i]);
}

/* print_hr: Print a line of dashes. */
void print_hr()
{
    for (int i = 0; i < 72; ++i)
        putchar('-');
    putchar('\n');
}

/* initialization_test: Was ps8_optind correctly initialized? */
bool initialization_test()
{
    if(ps8_optind == optind) {
        printf("Passed the initialization test:\n");
        printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
        return true;
    } else {
        printf("Failed the initialization test:\n");
        printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
        return false;
    }
}

/* no_more_args_test: Does ps8_getopt return -1 when there are no more elements in argv? */
bool no_more_args_test(const char* optstring)
{
    int argc = 1;
    char *argv[] = { "test" };
    bool passed = (ps8_getopt(argc, argv, optstring) == -1);

    echo_argv(argc, argv);
    if (passed)
        printf("Passed");
     else
        printf("Failed");
    printf(" the no more args test.\n");

    return passed;
}

/* Test whether ps8_getopt returns the same result as getopt. */
bool validation_test(int argc, char* const argv[], const char *optstring)
{
    int a = getopt(argc, argv, optstring);
    int b = ps8_getopt(argc, argv, optstring);
    bool passed = (a == b);

    if (passed)
        printf("Passed");
     else
        printf("Failed");
    printf(" the validation test.\n");
    printf("  getopt returned: %d\n", a);
    printf("  ps8_getopt returned: %d\n", b);

    return passed;
}

/* no_args_test: Test with 0 command line options or operands. */
bool no_args_test(const char* optstring)
{
    int argc = 1;
    char *argv[] = { "test" };

    echo_argv(argc, argv);
    printf("Testing with no command line options or operands.\n");

    return validation_test(argc, argv, optstring);
}

/* one_operand_test: Test with 0 command line options and 1 operand. */
bool one_operand_test(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "abc"};

    echo_argv(argc, argv);
    printf("Testing with 0 command line options and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}

/* one_option_one_operand_test: Test with 1 option and 1 operand. */
bool one_option_one_operand_test(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-a", "bc"};

    echo_argv(argc, argv);
    printf("Testing with 1 command line option and 1 operand.\n");

    return validation_test(argc, argv, optstring);
}