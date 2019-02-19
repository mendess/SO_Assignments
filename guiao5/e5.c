#include <stdio.h>
#include <unistd.h>

/*
 * Escreva um programa que emule o funcionamento do interpretador de comandos
 * na execução encadeada de grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l
 */
int main()
{
    char** commands[4];
    char* grep[] = { "grep", "-v", "^#", "/etc/passwd", NULL };
    char* cut[] = { "cut", "-f7", "-d:", NULL };
    char* uniq[] = { "uniq", NULL };
    char* wc[] = { "wc", "-l", NULL };
    commands[0] = grep;
    commands[1] = cut;
    commands[2] = uniq;
    commands[3] = wc;
    int beforePipe = 0;
    int afterPipe[2];
    int n = 4;
    for (int i = 0; i < n; i++) {
        if (i < n - 1)
            pipe(afterPipe);
        if (!fork()) {
            if (i > 0) {
                dup2(beforePipe, 0);
                close(beforePipe);
            }
            if (i < n - 1) {
                dup2(afterPipe[1], 1);
                close(afterPipe[0]);
                close(afterPipe[1]);
            }
            execvp(commands[i][0], commands[i]);
            _exit(1);
        }
        if (i < n - 1)
            close(afterPipe[1]);
        if (i > 0)
            close(beforePipe);
        beforePipe = afterPipe[0];
    }
    return 0;
}
