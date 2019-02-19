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

typedef enum _parserStatus {
    PARSING,
    PIPE,
    BACKGROUND,
    EOC
} PARSER_STATUS;

/*
 * Acrescente ao interpretador de comandos proposto nos guiões anteriores
 * a possibilidade de encadear as entradas e saı́das de programas a executar
 * através de pipes anónimos (operador |)
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

int interpretExtras(char** argv, int from, int to)
{
    int offset = to;
    for (int i = to - 1; i >= from; --i) {
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

char** words(char* string)
{
    char* command = strdup(string);
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

int runCmd(char* cmd)
{
    // break the cmd stirng in an array of strings
    char** argv = words(cmd);
    if (changeDir(argv))
        return 0;
    int lastPipeIndex = 0;
    PARSER_STATUS status = PARSING;
    int prePipe = 0;
    int posPipe[2];
    int lastPid;
    for (int cursor = 0; argv[cursor] && (status == PARSING || status == PIPE); cursor++) {
        status = PARSING;
        if (argv[cursor][0] == '|')
            status = PIPE;
        else if (argv[cursor][0] == '&')
            status = BACKGROUND;
        else if (argv[cursor + 1] == NULL)
            status = EOC;

        if (status != PARSING) {
            if (status == PIPE)
                pipe(posPipe);
            if (!(lastPid = fork())) {
                argv[interpretExtras(argv, lastPipeIndex, cursor + 1)] = NULL;
                //pipes
                dup2(prePipe, 0);
                if (lastPipeIndex != 0)
                    close(prePipe);
                if (status == PIPE) {
                    dup2(posPipe[1], 1);
                    close(posPipe[1]);
                    close(posPipe[0]);
                }
                if (status != EOC)
                    argv[cursor] = NULL;

                execvp(argv[lastPipeIndex], argv + lastPipeIndex);
                perror("Failed to execute command");
                _exit(1);
            }
            if (status == PIPE)
                close(posPipe[1]);
            if (lastPipeIndex != 0)
                close(prePipe);
            prePipe = posPipe[0];
            lastPipeIndex = cursor + 1;
        }
    }
    free(argv);
    // Wait for process to finish if requested
    if (status != BACKGROUND) {
        int status;
        int pid;
        while ((pid = wait(&status)) > -1) {
            if (pid == lastPid) {
                if (WIFEXITED(status))
                    return WEXITSTATUS(status);
                return -1;
            }
        }
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
            buffer[n + offset - 1] = '\0';
            errorCd = runCmd(buffer);
            offset = 0;
        }
    }
    free(buffer);
    return 0;
}
