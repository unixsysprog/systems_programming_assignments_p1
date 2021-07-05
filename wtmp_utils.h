/*
* 	wtmp_utils.h
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*/
#include    <utmp.h>

typedef struct utmp wtmp;

#define NULLWT      ((wtmp *)NULL)

//Default date fmt of who
#define DATE_FMT    		"%Y-%m-%d %H:%M" 
//Format used to truncate to days
#define SHORT_DATE_FMT 		"%Y-%m-%d" 

/*
*  	Returns last record of username login, or NULL
*	if not found. 
*/
wtmp *last_user_record(char *username);

/*
*	Returns the next record found with matching timeval,
*	truncated to day. 
*/
wtmp *next_rec_on_date(char *timeval);

/*
* 	The following four functions taken and modified from 
*	utmplib.c by Bruce Molay & csci e-28
*/

int wtmp_close();
int wtmp_load();
wtmp *wtmp_next();
int wtmp_open( char *filename );

/*
* 	The following two functions taken from 
*	who3.c by Bruce Molay & csci e-28;
*/
void showtime( time_t timeval , char *fmt );
void show_info( wtmp *wtbufp );
