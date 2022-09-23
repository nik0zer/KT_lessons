#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    umask(0);
    char path[] = "./l.fifo";
    mkfifo(path, 0777);
    int fork_int = fork();
    
    if(fork_int)
    {
        int fd = open(path, O_WRONLY);
        for(int i = 1; i < argc; i++)
        {
            write(fd, argv[i], strlen(argv[i]));
        }
        close(fd);
    }
    else
    {
        int fd = open(path, O_RDONLY);
        char* buf = (char*)calloc(100, sizeof(char));
        for(int i = 1; i == 1;)
        {
            i = read(fd, buf, 1);
            for(int j = 0; j < i; j++)
            {
                printf("%c", buf[j]);
            }
        }
        close(fd);
    }


}