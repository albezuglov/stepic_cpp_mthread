#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFSIZE 80
#define OUT_FILE "/message.txt"

struct message {
    long type;
    char value[BUFFSIZE];
};

int main(int argc, char **argv) {

    struct message msg;
    memset ( msg.value, 0, BUFFSIZE );

    key_t key = ftok("/tmp/msg.temp", 1);
    int msgid = msgget (key, IPC_CREAT | 0666);
    
    msgrcv(msgid, &msg, BUFFSIZE, 0, 0 );
    {
        char out_filename[80];
        sprintf(out_filename, "%s%s", getenv("HOME"), OUT_FILE);
        FILE *out = fopen(out_filename, "w");
        fputs(msg.value, out );
        fclose(out);
    }

    return 0;
}