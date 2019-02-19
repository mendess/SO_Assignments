#include "e5_readln.c"
#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    if (argc < 2) {
        char c;
        int n;
        while ((n = readln(0, &c, 1)))
            write(1, &c, n);
    } else {
        int numLines = 10;
        int flag = 0;
        if (argv[1][0] == '-' && argv[1][1] != '\0') {
            numLines = atoi(argv[1] + 1);
            flag = 1;
        }

        int i = flag ? 2 : 1;
        if ((i == 1 && argc > 2) || (i == 2 && argc > 3)) {
            flag = 1;
        } else {
            flag = 0;
        }
        for (; i < argc; i++) {
            if (flag) {
                char c[strlen(argv[i]) + 10];
                sprintf(c, "==> %s <==\n", argv[i]);
                write(1, c, strlen(c));
            }
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1)
                continue;
            char buf[1024];
            int n;
            int lineCounter = 0;
            while (lineCounter < numLines
                && (n = readln(fd, buf, 1024))) {
                write(1, buf, n);
                lineCounter++;
            }
            write(1, "\n", 1);
        }
    }
}
