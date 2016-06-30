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

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0)


int main(int argc, char **argv) {

    char msg[BUFFSIZE+1];
    memset ( msg, 0, BUFFSIZE+1 );
    
    struct mq_attr mtr;
    mtr.mq_flags = 0;
    mtr.mq_maxmsg = 20;
    mtr.mq_msgsize = BUFFSIZE;
    mtr.mq_curmsgs = 0;
    
    mq_unlink("/test.mq");
    mqd_t queue = mq_open("/test.mq", O_CREAT | O_RDWR, 0666, &mtr );
    printf ("Result queue = --%d--\n", queue);
    // key_t key = ftok("/tmp/msg.temp", 1);
    // int msgid = msgget (key, IPC_CREAT | 0666);

    
    int res = mq_receive(queue, msg, BUFFSIZE, 0 );
    printf ("Result receive = --%d--\n", res);
    {
        char out_filename[80];
        sprintf(out_filename, "%s%s", getenv("HOME"), OUT_FILE);
        FILE *out = fopen(out_filename, "w");
        fputs(msg, out );
        fclose(out);
    }

    return 0;
}