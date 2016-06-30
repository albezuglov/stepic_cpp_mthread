#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h> 

#define BUFFSIZE 1048576
#define OUT_FILE "/message.txt"



int main(int argc, char **argv) {
    
    key_t key = ftok("/tmp/mem.temp", 1);
    if( key == -1 ) {
        perror( "ftok" );
        return 1;
    }
    
    int shmid = shmget (key, BUFFSIZE, IPC_CREAT|0666);
    if( shmid == -1 ) {
        perror( "shmget" );
        return 1;
    }

    char *data = shmat(shmid, 0, 0);
    if( data == -1 ) {
        perror( "shmat" );
        return 1;
    }    
    
    unsigned int i;
    char *s;
    s = data;
    for(i = 0; i < BUFFSIZE; i++) 
        *s++ = 42;
    
    s = data;  
    for(i = 0; i < 1024*1024; ++i)
        memset(s+i, 42, 1); //addr[i] = 42;
    return 0;
}