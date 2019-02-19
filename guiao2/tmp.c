#include "guiao2.h"
#include <stdio.h>

int main()
{
    int pid = fork();
    if (pid == 0) {
        printf("Sou o filho. O meu id = %d. Id do meu pai %d\n", getpid(), getppid());
        sleep(5);
        _exit(0);
    } else {
        printf("Sou o pai. O meu id é %d. Id do meu filho é %d\n", getpid(), pid);
    }
    int status;
    wait(&status);
    printf("status %d\n", status);
    return 0;
}
