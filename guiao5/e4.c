#include <unistd.h>

/*
 * Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
 * de ls /etc | wc -l
 */
int main()
{
    int pfd[2];
    char buf[10];
    pipe(pfd);
    if (!fork()) {
        dup2(pfd[1], 1);
        close(pfd[0]);
        execlp("ls", "ls", "/etc", NULL);
    }
    if (!fork()) {
        dup2(pfd[0], 0);
        close(pfd[1]);
        execlp("wc", "wc", "-l", NULL);
    }
    close(pfd[0]);
    close(pfd[1]);

    return 0;
}
