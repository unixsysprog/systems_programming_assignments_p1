# This is a makefile.  A makefile contains rules that tell
# how to build a program, often from separate source files
#
# This sample makefile shows how to build dumputmp from
# the two source files dumputmp.c and utmplib.c
#
# You must modify this file so it contains rules to make
# your solution to the project
# (note: the indented lines MUST start with a single tab
#

dumputmp: dumputmp.o utmplib.o
	cc dumputmp.o utmplib.o -o dumputmp

see: dumputmp sample.wtmp
	./dumputmp sample.wtmp | more

dumputmp.o: dumputmp.c
	$(CC) -c dumputmp.c

utmplib.o: utmplib.c
	$(CC) -c utmplib.c

who2: who2.c
	$(CC) who2.c -o who2

who3: who3.c utmplib.o
	$(CC)  who3.c utmplib.o -o who3

utils.o: utils.c
	$(CC) -c -Wall utils.c

wtmp_utils.o: wtmp_utils.c
	$(CC) -c -Wall wtmp_utils.c

lastlogin: lastlogin.c utils.o wtmp_utils.o
	$(CC) -Wall lastlogin.c utils.o wtmp_utils.o -o lastlogin

whodate: whodate.c utils.o wtmp_utils.o
	$(CC) -Wall whodate.c  utils.o  wtmp_utils.o -o whodate

clean:
	rm -f *.o core dumputmp whodate lastlogin who2 who3

