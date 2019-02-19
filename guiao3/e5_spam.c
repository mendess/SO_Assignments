#include "guiao3.h"
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        if (!fork())
            execlp(argv[i], argv[i], NULL);
    }
    while (wait(NULL) != -1)
        ;
}
