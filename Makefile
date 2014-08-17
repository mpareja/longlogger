all: longlogger

install: longlogger
	cp longlogger /usr/bin/longlogger

longlogger: longlogger.c
	gcc -Wall -Werror longlogger.c -o longlogger
