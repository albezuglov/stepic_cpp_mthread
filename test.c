#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define BUFFSIZE 1000
#define OUT_FILE "/message.txt"



int main(int argc, char **argv) {
    
    sem_unlink("/test.sem");
    sem_t *sem = sem_open("/test.sem", O_CREAT | O_RDWR, 0666, 66);
    // if( &sem == -1 ) {
    //     perror( "sem_open" );
    //     return 1;
    // }

    return 0;
}