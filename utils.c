/*
* 	utils.c
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*
* 	utils contains common utility functions for
*	parsing flagged arguments from an array of 
*	tokens as well as a simple assert() implementation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define FLAG_LEN 2

int parse_args(char **av, int ac, Arg *buf, char **tok_buf, int max_args) {
	int i 			= 0, 
		current_arg = 0,
		current_tok = 0;

	while (i < ac){
		char *tok = av[i];
		if (strlen(tok) >= FLAG_LEN && tok[0] == '-' && (ac - i) > 1) {
			if (current_arg < max_args) {
				Arg arg 			= { tok, av[++i] };
				buf[current_arg++] 	= arg;
			}
		} else {
			tok_buf[current_tok++] 	= tok;
		}
		i++; 
	}
	return current_arg;
}

void assert(int condition, char *message) {
	if (condition == 0) {
		printf("%s\n", message);
		exit(1);
	}
}