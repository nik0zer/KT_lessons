#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int num_of_files = 0;
int num_of_files_hard_links = 0;

enum ERRORS
{
    NOT_ENOUGH_ARGC = 1,
    WRONG_DIR = 2
};

int recursive_file_decent(char* path)
{
    DIR* dir = opendir(path);
    if(dir == NULL)
    {
        return WRONG_DIR;
    }

    struct dirent* file = readdir(dir);
    while(file != NULL)
    {
        struct stat stat_buf;
        char dir_smb[] = "/\0";
        char* path1 = (char*)calloc(strlen(path) + 256, sizeof(char));
        strcpy(path1, path);
        strcat(path1, dir_smb);
        strcat(path1, file->d_name);
        stat(path1, &stat_buf);
        
        if(file->d_type != 4)
        {
            num_of_files++;
            printf("%s\n", path1);
            if(stat_buf.st_nlink >= 2)
            {
                num_of_files_hard_links++;
            }
        }
        else
        {
            if(strcmp(file->d_name, ".\0") != 0 && strcmp(file->d_name, "..\0") != 0)
            {
                recursive_file_decent(path1);
            }
        }

        free(path1);

        file = readdir(dir);
    }


    closedir(dir);
}

int print_dir_names(char* path)
{
    DIR* dir = opendir(path);
    if(dir == NULL)
    {
        return WRONG_DIR;
    }

    struct dirent* file = readdir(dir);
    while(file != NULL)
    {
        if(file->d_type == 4)
        {
            printf("%s\n", file->d_name);
        }
        file = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        return NOT_ENOUGH_ARGC;
    }

    recursive_file_decent(argv[1]);
    printf("%d\n%d\n", num_of_files, num_of_files_hard_links);
    print_dir_names(argv[1]);


    
}

