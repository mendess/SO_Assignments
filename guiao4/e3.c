#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * Modifique novamente o programa inicial de modo a que seja executado o comando wc, sem argumentos,
 * depois do redireccionamento dos descritores de entrada e saı́da. Note que, mais uma vez, as associações
 * – e redireccionamentos – de descritores de ficheiros são preservados pela primitiva exec()
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
    if (!fork()) {
        execlp("wc", "wc", NULL);
    }
}
