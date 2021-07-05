/*
* 	lastlogin.c
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*
* 	lastlogin takes a username and optional
*	filename as input and prints the last
*	login record for that user to stdout. 
*/

#include 	<stdio.h>
#include 	"utils.h"
#include 	"wtmp_utils.h"
#include	<stdlib.h>

#define MAX_ARGS 		1 /* -f filename 	*/
#define MAX_TOKENS 		1 /* 	username 	*/
#define USAGE_STRING 	"Usage: lastlogin [-f filename] username"


char *validate_input(int num_flags, int ac, char **av, Arg *args);

int main(int ac, char **av) {
	Arg 	args[MAX_ARGS];

	char 	*tok_buf[MAX_TOKENS];
	char 	*filename, 
			*username;

	int 	num_flags 		= parse_args(av, ac, args, tok_buf, MAX_ARGS);

	wtmp	*last_login;
 
	filename 	= validate_input(num_flags, ac, av, args);
	username 	= tok_buf[1];

	assert(wtmp_open(filename) != -1, "Error opening wtmp file");
	assert((last_login = last_user_record(username)) != NULL, "No records of username");
	show_info(last_login);

	return 0;
}

/*
	Accepts args to main, broken into flag/value pairs
	and other tokens, verifies that user entered 
	either just a username or username and -f filename,
	and returns either the filename or the sys WTMP_FILE
*/
char *validate_input(int num_flags, int ac, char **av, Arg *args) {
	if (num_flags == 1) { //If a file is specified, there should be 4 tokens.
		assert(ac == 4, USAGE_STRING);
		return args[0].value;
	} else {  			//There should be 2 (the program name and username)
		assert(ac == 2, USAGE_STRING);
		return WTMP_FILE;
	}
}

