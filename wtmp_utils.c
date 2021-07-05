/*
* 	wtmp_utils.c
*	Christopher Fuentes
*	cfuentes@g.harvard.edu
*	HUID 60857326
*
* 	wtmp_utils.c Is modified from utmplib.c from lecture 2,
*	Credit for functions:
		int wtmp_close()
		int wtmp_reload()
		wtmp *wtmp_next()
		int wtmp_open( char *filename )
	goes to Bruce Molay & csci e-28
*/

#define _XOPEN_SOURCE

#include  	<stdio.h>
#include    <stdlib.h>
#include   	<fcntl.h>
#include   	<sys/types.h>
#include    <unistd.h>
#include    <time.h>
#include    <string.h>
#include    "wtmp_utils.h"
#include    "utils.h"

#define WTSIZE      (sizeof(wtmp))
#define MAXDATELEN  100

static  char    *wtmpbuf;     
static  int     num_recs;                             
static  int     cur_rec;                              
static  int     fd_wtmp = -1; 
static  int     NRECS;  

void convert_time(time_t timestamp, char *time_buf);

/*
*   Loops through every record, returning the last
*   matching occurence of username.
*/

wtmp *last_user_record(char *username) {
    wtmp    *cur, 
            *last = NULL;
    while ( (cur = wtmp_next()) != NULLWT ) {
        if (strcmp(cur->ut_name, username) == 0) {
            last = cur;
        }
    }
    return last;   
}

/*
*   Given a time input string of the form
*   SHORT_DATE_FMT, matches the next
*   wtmp record with a date that matches
*   timeval when converted to SHORT_DATE_FMT
*/

wtmp *next_rec_on_date(char *timeval) {
    wtmp    *cur;
    while ( (cur = wtmp_next()) != NULLWT ) {
        time_t timestamp = cur->ut_time;
        char    timestring[MAXDATELEN];
        convert_time(timestamp, timestring);
        if (strcmp(timeval, timestring) == 0) {
            return cur;
        }
    }
    return NULLWT;
}

/*
*   converts a time_t timstamp to a string
*   in SHORT_DATE_FMT format. 
*/
void convert_time(time_t timestamp, char *time_buf) {
    struct tm *tp = localtime(&timestamp);       
    strftime(time_buf, MAXDATELEN, SHORT_DATE_FMT, tp);
}
                      
int wtmp_open( char *filename ) {
    fd_wtmp = open( filename, O_RDONLY );       
    cur_rec = num_recs = 0;   
    if (fd_wtmp != -1) {
        //Attempt to malloc a buffer equal to the filesize
        int file_bytes  = lseek(fd_wtmp, 0, SEEK_END);
        assert(file_bytes != -1, "Unable to determine filesize");
        NRECS           = file_bytes / WTSIZE;
        size_t size     = sizeof(char) * NRECS * WTSIZE;
        wtmpbuf         = malloc(size);
        assert(wtmpbuf != NULL, "Unable to allocate memory for file");
        assert(0==lseek(fd_wtmp, 0, SEEK_SET), "Unable to reset seek point");
    }                  
    return fd_wtmp;                             
}

wtmp *wtmp_next() {
    wtmp    *recp;

    if ( fd_wtmp == -1 )                     
        return NULLWT;
    if ( cur_rec==num_recs && wtmp_load() <= 0 ) 
        return NULLWT;
                                   
    recp = (wtmp *) &wtmpbuf[cur_rec * WTSIZE];
    cur_rec++;
    return recp;
}

int wtmp_load() {
    int     amt_read, 
            bufsize = NRECS*WTSIZE;         
    amt_read = read(fd_wtmp, wtmpbuf, bufsize);  
    if ( amt_read < 0 )			
        amt_read = -1;
                                                
    num_recs = amt_read/WTSIZE;		 
    cur_rec  = 0;				
    return num_recs;				
}

int wtmp_close() {
    int rv = 0;
    if ( fd_wtmp != -1 )           
        rv = close( fd_wtmp );  
        free(wtmpbuf);
    return rv;
}

void show_info( wtmp *wtbufp ) {
    if ( wtbufp->ut_type != USER_PROCESS )
        return;

    printf("%-8s", wtbufp->ut_name);        /* the logname  */
    printf(" ");                            /* a space  */
    printf("%-12.12s", wtbufp->ut_line);    /* the tty  */
    printf(" ");                            /* a space  */
    showtime( wtbufp->ut_time, DATE_FMT );  /* display time */
    if ( wtbufp->ut_host[0] != '\0' )
        printf(" (%s)", wtbufp->ut_host);   /* the host */
    printf("\n");                           /* newline  */
}

void showtime( time_t timeval , char *fmt ) {
    char    result[MAXDATELEN];

    struct tm *tp = localtime(&timeval);        
    strftime(result, MAXDATELEN, fmt, tp);     
    fputs(result, stdout);
}