#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>           /* For O_* constants */
#include <mqueue.h>

#define BUFFSIZE 1000
#define OUT_FILE "/message.txt"


int main(int argc, char **argv) {

    char msg[BUFFSIZE];
    memset ( msg, 0, BUFFSIZE );
    
    struct mq_attr mtr;
    mtr.mq_flags = O_RDWR;
    mtr.mq_maxmsg = 20;
    
    int queue = mq_open("/test.mq", O_CREAT, 0666, &mtr );

    // key_t key = ftok("/tmp/msg.temp", 1);
    // int msgid = msgget (key, IPC_CREAT | 0666);

    
    mq_receive(queue, msg, BUFFSIZE, 0 );
    {
        char out_filename[80];
        sprintf(out_filename, "%s%s", getenv("HOME"), OUT_FILE);
        FILE *out = fopen(out_filename, "w");
        fputs(msg, out );
        fclose(out);
    }

    return 0;
}