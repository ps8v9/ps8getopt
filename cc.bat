@echo off

set PROG=test
if exist %PROG%.exe del %PROG%.exe

gcc -o %PROG% --std=c99 -Wall %DEBUG% %PROG%.c ps8getopt.c

if exist %PROG%.o   del %PROG%.o
if exist %PROG%.obj del %PROG%.obj
