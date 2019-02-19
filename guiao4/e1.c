#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
/*
 * Escreva um programa que redireccione o descritor associado ao seu standard input para o ficheiro
 * /etc/passwd, e o standard output e error respectivamente para saida.txt e erros.txt. Tenha em conta
 * que estes ficheiros deverão ser abertos – e eventualmente criados – com modos de acessos compatı́veis
 * com o redireccionamento pretendido. Por exemplo, o ficheiro saida.txt terá que ser aberto para escrita,
 * criando-o se necessário, truncado e com permissões apropriadas. Experimente ler uma linha a partir do
 * seu standard input e repeti-la nos descritores de output e error usando directamente read() e write().
 * Experimente ainda realizar as mesmas operações através de funções da biblioteca de C – p. ex., fgets(),
 * printf() ou fprintf(). Em todas as situações, repare no conteúdo dos ficheiros criados. Note que depois
 * de cada redireccionamento, os descritores dos ficheiros abertos deixam de ser necessários, e como tal é
 * boa prática fechá-los de imediato.
*/

int main(){
    int fd0,fd1,fd2;
    fd0 = open("/etc/passwd", O_RDONLY);
    dup2(fd0,0);
    fd1 = open("stdout.txt", O_CREAT|O_WRONLY|O_TRUNC);
    dup2(fd1,1);
    fd2 = open("stderr.txt", O_CREAT|O_WRONLY|O_TRUNC);
    dup2(fd2,2);
    if(fd0 == -1 || fd1 == -1 || fd2 == -2) return -1;
    char buffer[1024];
    int n;
    while((n=read(0,buffer,1024)) > 0){
        write(1,buffer,1024);
        write(2,buffer,1024);
    }
    return 0;
}
