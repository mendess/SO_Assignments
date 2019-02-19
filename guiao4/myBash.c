#include "../guiao1/e5_readln.c"
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define PICKCOLOUR(var) (var == 0 ? GREEN : RED)
/*
 * Acrescente ao interpretador de comandos proposto no guião anterior a possibilidade
 * de redireccionar as entradas, saı́das e erros dos comandos por ele executados.
 * Considere os operadores de redireccionamento <, >, >>, 2> e 2>>
 */

void redirect(char* file, int to, int append)
{
    int fd;
    switch (to) {
    case 0:
        fd = open(file, O_RDONLY);
        break;
    case 1:
    case 2:
        if (append)
            fd = open(file, O_CREAT | O_WRONLY | O_APPEND);
        else
            fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);
        break;
    }
    dup2(fd, to);
    close(fd);
}

int interpretExtras(int argc, char** argv)
{
    int offset = argc;
    for (int i = argc - 1; i > -1; --i) {
        switch (argv[i][0]) {
        case '<':
            redirect(argv[i + 1], 0, 0);
            offset = i;
            break;
        case '>':
            switch (argv[i][1]) {
            case '\0':
                redirect(argv[i + 1], 1, 0);
                offset = i;
                break;
            case '>':
                redirect(argv[i + 1], 1, 1);
                offset = i;
                break;
            }
            break;
        case '2':
            switch (argv[i][1]) {
            case '>':
                redirect(argv[i + 1], 2, argv[i][2] == '>');
                offset = i;
                break;
            }
            break;
        }
    }
    return offset;
}

char** words(char* string, size_t size, int* numWords)
{
    char* command = strndup(string, size);
    command[size - 1] = '\0';
    int argc = 5;
    char** argv = malloc(argc * sizeof(char*));
    int i = 0;
    char* token = strtok(command, " ");
    do {
        if (!(i < argc))
            argv = realloc(argv, (argc *= 2) * sizeof(char*));

        argv[i++] = token;

        token = strtok(NULL, " ");
    } while (token);
    argv[i] = NULL;
    *numWords = i;
    return argv;
}

int changeDir(char** argv)
{
    if (strcmp(argv[0], "cd"))
        return 0;
    if (!argv[1]) {
        chdir(getenv("HOME"));
        return 1;
    }
    chdir(argv[1]);
    return 1;
}

int runCmd(char* cmd, size_t size)
{
    // break the cmd stirng in an array of strings
    int i;
    char** argv = words(cmd, size, &i);
    if (changeDir(argv))
        return 1;
    // Check for to see if I should wait for the process to finish
    int background = argv[i - 1][0] == '&' && argv[i - 1][1] == '\0';
    if (background)
        argv[i - 1] = NULL;
    // Execute the command
    if (!fork()) {
        argv[interpretExtras(i, argv)] = NULL;
        execvp(argv[0], argv);
    }
    free(argv);
    // Wait for process to finish if requested
    if (!background) {
        int status;
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        return -1;
    }
    return 0;
}

int main()
{
    int bufferSize = 4096;
    char cwd[4096];
    char* buffer = malloc(bufferSize);
    int offset = 0;
    char* bashPrefix = "¬";
    int errorCd = 0;
    while (1) {
        if (!offset) {
            printf(BLUE "%s" BOLD "%s%s" RESET " ",
                getcwd(cwd, 4096),
                PICKCOLOUR(errorCd), bashPrefix);
            fflush(stdout);
        }
        int n = readln(0, buffer + offset, bufferSize - offset);

        if (n < 1 || !strncmp(buffer, "exit\n", n))
            break;

        if (buffer[n - 1] != '\n') {
            offset += bufferSize;
            buffer = realloc(buffer, bufferSize *= 2);
        } else {
            errorCd = runCmd(buffer, n + offset);
            offset = 0;
        }
    }
    free(buffer);
    return 0;
}
