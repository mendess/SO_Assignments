#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char** argv)
{
    if (argc != 3)
        printf("Use: <file1> <file2>\n");
    char c1, c2;
    int n1, n2, byteN = 0, lineC = 1;
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);
    while ((n1 = read(fd1, &c1, 1)) > 0
        && (n2 = read(fd2, &c2, 1)) > 0) {
        if (c1 != c2)
            break;
        if (c1 == '\n') {
            lineC++;
            byteN = 0;
        }
        byteN++;
    }
    if (c1 == c2)
        printf("Files are the same\n");
    else if (n1 < 1)
        printf("EOF on %s\n", argv[1]);
    else if (n2 < 1)
        printf("EOF on %s\n", argv[2]);
    else
        printf("%s %s differ: char %d, line %d\n",
            argv[1],
            argv[2],
            byteN,
            lineC);
    return 0;
}
