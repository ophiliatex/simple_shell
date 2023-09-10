This project is aimed at developing a simple version of the UNIX commandline interface.
The betty style of coding is used throughout the development phase.
The program is expected to have the exact same output as sh (/bin/sh)
as well as the exact same error output.
The only difference is when it print an error,
the name of the program is equivalent to argv[0] of this program.
There is a limited list of allowed functions and system calls
hence some goto ones were not used as one would expect
The shell is compiled this way: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

