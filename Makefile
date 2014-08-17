all: longlogger

longlogger: longlogger.c
	gcc -Wall -Werror longlogger.c -o longlogger
