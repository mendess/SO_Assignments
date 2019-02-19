#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * Modifique o programa anterior de modo a que, depois de realizar os redireccionamentos, seja criado um
 * novo processo que realize operações de leitura e escrita. Observe o conteúdo dos ficheiros. Repare que o
 * processo filho “nasce” com as mesmas associações de descritores de ficheiros do processo pai
 */
int main(int argc, const char** argv)
{
    int fd0, fd1, fd2;
    fd0 = open("/etc/passwd", O_RDONLY);
    dup2(fd0, 0);
    fd1 = open("stdout.txt", O_CREAT | O_WRONLY | O_TRUNC);
    dup2(fd1, 1);
    fd2 = open("stderr.txt", O_CREAT | O_WRONLY | O_TRUNC);
    dup2(fd2, 2);
    if (fd0 == -1 || fd1 == -1 || fd2 == -2)
        return -1;
    char buffer[1024];
    int n;
    if (!fork()) {
        while ((n = read(0, buffer, 1024)) > 0) {
            write(1, buffer, 1024);
            write(2, buffer, 1024);
        }
    }
    return 0;
}
