#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv)
{
    umask(0);
    if(argc < 2)
    {
        return -1;
    }
    int fd = open(argv[1] , O_WRONLY | O_CREAT, 0777);
    
    char* str;
    scanf("%ms", &str);
    printf("%d", strlen(str));
    write(fd, str, strlen(str));

    close(fd);
    return 0;
}