#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

int printf_stat(struct stat file_stat)
{
    printf("[%d %d %d %d %d %d %d %d]\n", file_stat.st_dev, file_stat.st_ino, file_stat.st_mode, file_stat.st_nlink, 
    file_stat.st_uid, file_stat.st_gid, file_stat.st_rdev, file_stat.st_size);
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return -1;
    }

    DIR* dir = opendir(argv[1]);

    int err = 0;

    while(err == 0)
    {
        struct stat file_stat;
        struct dirent* file_info;
        
        file_info = readdir(dir);
        if(file_info == NULL)
        err = -1;
        else
        {
        printf("%s ", file_info->d_name);
        stat(file_info->d_name, &file_stat);


        printf_stat(file_stat);
        }
    }

    closedir(dir);
    
}