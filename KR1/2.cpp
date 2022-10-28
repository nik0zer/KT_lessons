#include <unistd.h>
#include <limits.h> 
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return -1;
    }

    umask(0);

    char path_name[PATH_MAX] = {};
    char* path_name_ptr = NULL;

    path_name_ptr = getwd(path_name);
    if(path_name_ptr == NULL)
    {
        return -2;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);

    write(fd, path_name, strlen(path_name));
    
    close(fd);
}