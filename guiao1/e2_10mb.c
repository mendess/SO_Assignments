#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define DEZMEGA 1024 * 1024

int main(int argc, char const* argv[])
{
    if (argc < 1) {
        printf("Provide the file name\n");
        return 1;
    }
    char c[11] = "aaaaaaaaaa";
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
    for (int i = 0; i < DEZMEGA; ++i) {
        write(fd, &c, 1);
    }
    close(fd);
    return 0;
}
