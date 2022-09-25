#include "tg.h"

int init_fifo()
{
    mkfifo(path, 0777);
}

int read_str(int fd, int num_of_client)
{
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
    int num_of_read_client;
    char* read_str_upd;
    sscanf(read_str, "%d %ms" , &num_of_read_client, &read_str_upd);
    if(num_of_read_client != num_of_client)
    {
        printf("from client %d\n%s\n", num_of_read_client, read_str_upd);
    }
    else
    {
        write_str(fd, num_of_client, read_str_upd);
    }
    free(read_str);
}

int write_str(int fd, int num_of_client, char* str_to_write)
{
    char *str_upd = (char*)calloc(strlen(str_to_write) + 100, sizeof(char));
    sprintf(str_upd, "%d %s\0", num_of_client, str_to_write);
    write(fd, str_upd, strlen(str_upd) + 1);
}

