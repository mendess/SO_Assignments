#include "guiao2.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid = fork();
    if (pid == 0) {
        //sleep(10);
        printf("Sou filho, o meu pid = %d\n", getpid());
        exit(-1);
    }
    int status;
    int pidF;
    //pidF = wait(&status);
    if (pid)
        sleep(40);
    printf("Pai: status = %d, pidF = %d\n", status, pidF);
    return 0;
}
