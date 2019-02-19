#include "guiao3.h"
#include <stdio.h>
#include <string.h>

int runProgram(const char* program)
{
    int noError = 0;
    int counter = 0;
    while (!noError) {
        if (!fork()) {
            sleep(1);
            execl(program, program, NULL);
        }
        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            noError = 1;

        counter++;
    }
    return counter;
}

int find(int needle, int* haystack, ssize_t size)
{
    for (int i = 0; i < size; i++)
        if (haystack[i] == needle)
            return i;
    return -1;
}

int spam(int argc, const char** argv)
{
    int counters[argc];
    int pids[argc];
    memset(counters, 0, argc);
    memset(pids, 0, argc);
    for (int i = 1; i < argc; i++)
        if (!(pids[i] = fork()))
            _exit(runProgram(argv[i]));

    int status;
    int pid;
    while ((pid = wait(&status)) != -1)
        if (WIFEXITED(status))
            counters[find(pid, pids + 1, argc - 1) + 1] = WEXITSTATUS(status);

    for (int i = 1; i < argc; i++)
        printf("%s %d\n", argv[i], counters[i]);

    return 0;
}

int main(int argc, const char** argv)
{
    if (argc < 2) {
        printf("Use: ./ea1_controler [program,...]\n");
        return 1;
    }
    spam(argc, argv);
    return 0;
}
