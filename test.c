#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define RESULT_FILENAME "/result.out"

int main(int argc, char **argv) {
    char localfilename[80];
    sprintf(localfilename, "%s%s", getenv("HOME"), CHILD_PID_FILENAME); 
    FILE *f = fopen(localfilename, "w");

    return 0;
}