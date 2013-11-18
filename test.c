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
bool test_initialization();
bool test_validation(int argc, char* const argv[], const char *optstring);
bool test_0_opts_0_operands(const char* optstring);
bool test_1_opt_0_operands(const char* optstring);
bool test_bad_opt_0_operands(const char* optstring);
bool test_0_opts_1_operand(const char* optstring);
bool test_1_opt_1_operand(const char* optstring);
bool test_bad_opt_1_operand(const char* optstring);
bool test_2_ungrouped_opts_1_operand(const char* optstring);
bool test_2_grouped_opts_1_operand(const char* optstring);
bool test_3_ungrouped_opts_1_operand(const char* optstring);
bool test_3_grouped_opts_1_operand(const char* optstring);
bool test_opt_w_inline_arg(const char* optstring);
bool test_opt_w_separate_arg(const char* optstring);

int main()
{
    int passed = 0; /* number of tests passed */
    int failed = 0; /* number of tests failed */
    int total  = 0;  /* total number of tests */

    char *optstring = ":a-*$bc1:2";
    show_supported_optstring(optstring);
    print_hr();

    if (test_initialization())
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_0_opts_0_operands(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_1_opt_0_operands(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_bad_opt_0_operands(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_0_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_1_opt_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_bad_opt_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_2_ungrouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_2_ungrouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_2_grouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_2_grouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_3_ungrouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_3_ungrouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_3_ungrouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_3_grouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_3_grouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();
    printf("Repeating test without resetting option indexes.\n");
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    if (test_3_grouped_opts_1_operand(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optstring = ":a:"; /* Note this change! */

    optind = 1; ps8_optind = 1; /* reset */
    if (test_opt_w_inline_arg(optstring))
        passed++;
    else
        failed++;
    print_hr();

    optind = 1; ps8_optind = 1; /* reset */
    if (test_opt_w_separate_arg(optstring))
        passed++;
    else
        failed++;
    print_hr();

    total = passed + failed;
    printf("Passed %d of %d tests.\n", passed, total);
    printf("Failed %d of %d tests.\n", failed, total);

    return failed;
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

/* Were extern variables correctly initialized? */
bool test_initialization()
{
    bool result;

    printf("Testing the initialization of extern variables.\n");

    result = (ps8_optarg == optarg);
    result &= (ps8_opterr == opterr);
    result &= (ps8_optind == optind);
    result &= (ps8_optopt = optopt);

    if (result)
        printf("Passed the test.\n");
    else
        printf("Failed the test:\n");

    printf("  optarg: %s; ps8_optarg: %s\n", optarg, ps8_optarg);
    printf("  opterr: %d; ps8_opterr: %d\n", opterr, ps8_opterr);
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    printf("  optopt: %d; ps8_optopt: %d\n", optopt, ps8_optopt);

    return result;
}

/* Does ps8_getopt return the same result as getopt? */
bool test_validation(int argc, char* const argv[], const char *optstring)
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
bool test_0_opts_0_operands(const char* optstring)
{
    int argc = 1;
    char *argv[] = { "test" };

    echo_argv(argc, argv);
    printf("Testing with 0 options and 0 operands.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 1 option and 0 operands. */
bool test_1_opt_0_operands(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "-a" };

    echo_argv(argc, argv);
    printf("Testing with 1 option and 0 operands.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 1 bad option and 0 operands. */
bool test_bad_opt_0_operands(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "-d" };

    echo_argv(argc, argv);
    printf("Testing with 1 bad option and 0 operands.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 0 options and 1 operand. */
bool test_0_opts_1_operand(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "abc"};

    echo_argv(argc, argv);
    printf("Testing with 0 options and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 1 option and 1 operand. */
bool test_1_opt_1_operand(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-a", "bc"};

    echo_argv(argc, argv);
    printf("Testing with 1 option and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 1 bad option and 1 operand. */
bool test_bad_opt_1_operand(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-d", "bc"};

    echo_argv(argc, argv);
    printf("Testing with 1 bad option and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 2 ungrouped options and 1 operand. */
bool test_2_ungrouped_opts_1_operand(const char* optstring)
{
    int argc = 4;
    char *argv[] = { "test", "-a", "-b", "c"};

    echo_argv(argc, argv);
    printf("Testing with 2 ungrouped options and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 2 grouped options and 1 operand. */
bool test_2_grouped_opts_1_operand(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-ab", "c"};

    echo_argv(argc, argv);
    printf("Testing with 2 grouped options and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 3 ungrouped options and 1 operand. */
bool test_3_ungrouped_opts_1_operand(const char* optstring)
{
    int argc = 5;
    char *argv[] = { "test", "-a", "-b", "-c", "d"};

    echo_argv(argc, argv);
    printf("Testing with 3 ungrouped options and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 3 grouped options and 1 operand. */
bool test_3_grouped_opts_1_operand(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-abc", "d"};

    echo_argv(argc, argv);
    printf("Testing with 3 grouped options and 1 operand.\n");

    return test_validation(argc, argv, optstring);
}

/* Test with 1 option that takes an inline optarg, and 0 operands. */
bool test_opt_w_inline_arg(const char* optstring)
{
    int argc = 2;
    char *argv[] = { "test", "-afoo" };
    bool result;

    echo_argv(argc, argv);
    printf("Testing with 1 opt that takes an inline arg, and 0 operands.\n");

    result = test_validation(argc, argv, optstring);
    result &= (ps8_optarg == optarg);
    result &= (ps8_opterr == opterr);
    result &= (ps8_optind == optind);
    result &= (ps8_optopt = optopt);

    printf("optarg: %s; ps8_optarg: %s\n", optarg, ps8_optarg);
    printf("opterr: %d; ps8_opterr: %d\n", opterr, ps8_opterr);
    printf("optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    printf("optopt: %d; ps8_optopt: %d\n", optopt, ps8_optopt);

    return result;
}

/* Test with 1 option that takes a separate optarg, and 0 operands. */
bool test_opt_w_separate_arg(const char* optstring)
{
    int argc = 3;
    char *argv[] = { "test", "-a", "foo" };
    bool result;

    echo_argv(argc, argv);
    printf("Testing with 1 opt that takes a separate arg, and 0 operands.\n");

    result = test_validation(argc, argv, optstring);
    result &= (ps8_optarg == optarg);
    result &= (ps8_opterr == opterr);
    result &= (ps8_optind == optind);
    result &= (ps8_optopt = optopt);

    if (result)
        printf("Passed the test.\n");
    else
        printf("Failed the test:\n");

    printf("  optarg: %s; ps8_optarg: %s\n", optarg, ps8_optarg);
    printf("  opterr: %d; ps8_opterr: %d\n", opterr, ps8_opterr);
    printf("  optind: %d; ps8_optind: %d\n", optind, ps8_optind);
    printf("  optopt: %d; ps8_optopt: %d\n", optopt, ps8_optopt);
    return result;
}

