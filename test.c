#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFSIZE 1000
#define IN_SOCKET "/in.fifo"
#define OUT_SOCKET "/out.fifo"


int main(int argc, char **argv) {
    char in_sock_name[80], out_sock_name[80];
    sprintf(in_sock_name, "%s%s", getenv("HOME"), IN_SOCKET);
    sprintf(out_sock_name, "%s%s", getenv("HOME"), OUT_SOCKET);
    char buff[BUFFSIZE];
    int res_in, res_out;

    if ( (res_in=mkfifo(in_sock_name, 0444)) || (res_out=mkfifo(in_sock_name, 0666))) {
        printf("%u  %u", res_in, res_out);
//        return -1;
    }

        
    FILE *in_sock = fopen(in_sock_name, "r");
    FILE *out_sock = fopen(out_sock_name, "w");
    
    while ( fgets(buff, BUFFSIZE, in_sock) != NULL)
        fputs(buff, out_sock );
    
    fclose(in_sock);
    fclose(out_sock);
    return 0;
}