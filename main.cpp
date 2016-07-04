#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>

#define OUT_FILE "/main.pid"

void * thread_func(void *arg) {
    int i;
    int loc_id = * (int *) arg;
    for (i = 0; i < 4; i++) {
        printf("Thread %i is running\n", loc_id);
        sleep(1);
    }
    sleep(100);
}


int main(int argc, char **argv) {
    char localfilename[80];
    sprintf(localfilename, "%s%s", getenv("HOME"), OUT_FILE);
    FILE *outfile = fopen(localfilename, "w+");
    
    pid_t pid = getpid();
    fprintf(outfile, "%d", pid);
    fclose(outfile);
    
    int id1, result;
    pthread_t thread1;
    
    id1 = 1;
    result = pthread_create(&thread1, NULL, thread_func, &id1);
    if ( result != 0 ) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    result = pthread_join(thread1, NULL);
    if (result != 0) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    
    
    return 0;
}