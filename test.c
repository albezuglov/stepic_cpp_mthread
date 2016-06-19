#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define STATUSFILENAME "/pid"

int main(int argc, char **argv) {
    int pid = fork();
    if ( pid ) {
        char localfilename[80];
        sprintf(localfilename, "%s%s", getenv("HOME"), STATUSFILENAME); 
        FILE *f = fopen("pid", "w");
        fprintf (f, "%d", pid);
    }
    else {
        sigset_t mask;
        sigset_t orig_mask;
        
        sigemptyset (&mask);
        sigaddset (&mask, SIGTERM);
        sigaddset (&mask, SIGINT);
        
        if ( sigprocmask(SIG_BLOCK, &mask, &orig_mask)) {
            printf ("Not blocked :(\n");
        }
        else {
            printf ("Blocked!\n");
            sleep(100000);
        };
    }
    
    return 0;
}