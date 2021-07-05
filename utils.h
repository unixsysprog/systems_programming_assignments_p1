/*
* 	utils.h
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*/


/*
* 	Arg struct to hold flag->value pairs. 
*	e.g., -f filename would be { "-f", "filename" }
*/
typedef struct {
	char *flag;
	char *value;
} Arg;

/*
*	parse_args takes an array of tokens and parses them into
*	flag/value pairs (Arg struct). Tokens not part of a flag/value
*	pair are just put into the tok_buf array.
*	
* 	@param av 		Input to main, e.g. list of arg tokens from stdin
*	@param ac 		Number of tokens in av
*	@param buf		Buffer to hold Arg structs
*	@param max_args	Max number of flag/value pairs to parse.
*	@param tok_buf	Buffer to hold non-flag/value args. Size should be ac.
*	@return 		Number of flag/value pairs parsed 
*/
int parse_args(char **av, int ac, Arg *buf, char **tok_buf, int max_args);

/*
* 	assert takes a boolean conditional and, if false/0, 
*	prints msg to stdout and exits with code (1)
*/
void assert(int condition, char *msg);

