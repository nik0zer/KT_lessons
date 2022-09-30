#include "tg.h"

int init_fifo()
{
    mkfifo(path, 0777);
}

int read_str(int fd, int num_of_client, int* flag_of_client, int* status)
{
    while (*status != 1)
    {
    }
    
    char* read_str = (char*)calloc(10000, sizeof(char));
    for(int i = 0; i < 10000; i++)
    {  
        int k = read(fd, read_str + i, 1);
        if(k == 0 || read_str[i] == '\n')
        {
            read_str[i] = '\0';
            break;
        }
        if(read_str[i] == '\0')
            break;
    }
    read_str[10000 - 1] == '\0';
    printf("from client %d\n%s\n", *flag_of_client, read_str);
    free(read_str);
    *flag_of_client = -1;
}

int write_str(int fd, int num_of_client, char* str_to_write, int* flag_of_client, int* status)
{
    *status = 0;
    *flag_of_client = num_of_client;
    char *str_upd = (char*)calloc(strlen(str_to_write) + 100, sizeof(char));
    sprintf(str_upd, "%s\0", str_to_write);
    write(fd, str_upd, strlen(str_upd) + 1);
    free(str_upd);
    *status = 1;
}

