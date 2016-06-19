#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PARENT_PID_FILENAME "/pid_parent"
#define CHILD_PID_FILENAME "/pid_child"

int main(int argc, char **argv) {
    int pid = fork();
    if ( pid ) {
        int state;
        wait (&state);
    }
    else {
        pid_t pid, ppid;
        pid = getpid();
        ppid = getppid();
        
        char localfilename[80];
        sprintf(localfilename, "%s%s", getenv("HOME"), CHILD_PID_FILENAME); 
        FILE *f = fopen(localfilename, "w");
        fprintf (f, "%d", pid);
        fclose(f);
        
        sprintf(localfilename, "%s%s", getenv("HOME"), PARENT_PID_FILENAME); 
        f = fopen(localfilename, "w");
        fprintf (f, "%d", ppid);
        fclose(f);

        sigset_t mask;
        int result;

        sigemptyset (&mask);
        sigaddset (&mask, SIGTERM);
        sigwait(&mask, &result);
        printf("Child exited\n");
    }
    
    return 0;
}