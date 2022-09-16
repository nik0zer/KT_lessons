#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    umask(0);
    if(argc < 2)
    {
        return -1;
    }
    int fd = open(argv[1] ,O_RDONLY);
    int eoff = 10;
    char* byte = (char*)malloc(10);
    while(eoff == 10)
    {
        eoff = read(fd, byte, 10);
        for(int i = 0; i < eoff; i++)
        {
            printf("%c", *(byte + i));
        }
    }
    close(fd);
    return 0;
}