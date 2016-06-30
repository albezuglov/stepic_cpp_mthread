#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#define BUFFSIZE 1048576
#define OUT_FILE "/message.txt"



int main(int argc, char **argv) {
    shm_unlink("/test.shm");
    
    int shmid = shm_open ("/test.shm", O_CREAT|O_RDWR, 0666);
    if( shmid == -1 ) {
        perror( "shm_open" );
        return 1;
    }
    
    int res = ftruncate(shmid, BUFFSIZE);
    if( res == -1 ) {
        perror( "ftruncate" );
        return 1;
    }
    
    char *data = (char*)mmap(0, BUFFSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shmid, 0 );
    if( data == -1 ) {
        perror( "mmap" );
        return 1;
    }
    
    unsigned int i;
    char *s;
    s = data;
    for(i = 0; i < BUFFSIZE; i++) 
        *s++ = 13;
    
    s = data;  
    for(i = 0; i < 1024*1024; ++i)
        memset(s+i, 13, 1); //addr[i] = 42;
    return 0;
}