#include <unistd.h>
#include <fcntl.h>

/* chamadas ao sistema: defs e decls essenciais */
/* O_RDONLY, O_WRONLY, O_CREAT, O_* */
/*
int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int close(int fildes);
*/

int main(int argc, char const *argv[]){
    int n;
    char c;
    while(read(0,&c,1))
        write(1,&c,1);
    return 0;
}
