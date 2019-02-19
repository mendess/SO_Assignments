# Includes

`#include <unistd.h>`

`#include <fcntl.h>`


# API

chamadas ao sistema: defs e decls essenciais 
`O_RDONLY`, `O_WRONLY`, `O_CREAT`, `O_*`

```C
int open(const char *path, int oflag [, mode]);`
ssize_t read(int fildes, void *buf, size_t nbyte);`
ssize_t write(int fildes, const void *buf, size_t nbyte);`
int close(int fildes);
```