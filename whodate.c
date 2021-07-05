/*
* 	whodate.c
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*
* 	whodate takes a date and optional filename
*	and prints all login records for that date. 
*/

#define _XOPEN_SOURCE

#include <stdio.h>
#include "utils.h"
#include <time.h>
#include "wtmp_utils.h"

#define MAX_ARGS 		1 /* -f filename   		*/
#define MAX_TOKENS 		3 /* year month date 	*/
#define MAX_DATE_LEN 	100
#define USAGE_STRING 	"Usage: whodate [-f filename] yyyy mm dd"

char *validate_input(int num_flags, int ac, char **av, Arg *args);

int main(int ac, char **av) {
	Arg 	args[MAX_ARGS];
	char 	*tok_buf[MAX_TOKENS];
	char 	*filename,
			*year, 
			*month,
			*day;
	char 	date_string[MAX_DATE_LEN];
	struct 	tm tm;
	wtmp 	*rec;
	int 	num_flags 		= parse_args(av, ac, args, tok_buf, MAX_ARGS);

	filename 	= validate_input(num_flags, ac, av, args);
	
	year 	= tok_buf[1];
	month 	= tok_buf[2];
	day 	= tok_buf[3];

	assert(wtmp_open(filename) != -1, "Error opening wtmp file");
	assert(sprintf(date_string, "%s-%s-%s", year, month, day) > -1, "Sprintf failed.");
	
    strptime(date_string, SHORT_DATE_FMT, &tm);
 
    while ( (rec = next_rec_on_date(date_string)) != NULLWT )
		show_info(rec);

	return 0;
}

char *validate_input(int num_flags, int ac, char **av, Arg *args) {
	if (num_flags == 1) { //If a file is specified, there should be 6 tokens.
		assert(ac == 6, USAGE_STRING);
		return args[0].value;
	} else {  		//There should be 4 (the program name and date strings)
		assert(ac == 4, USAGE_STRING);
		return WTMP_FILE;
	}
}