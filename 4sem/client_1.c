#include "tg.h"
#include <sys/types.h>
#include <signal.h>

int main()
{
    umask(0);
    int num_of_client;
    scanf("%d", &num_of_client);
    init_fifo();
    int fifo_file = open(path, O_RDWR, 0777);
    int fork_int = fork();
    if(fork_int)
    {
        while(1)
        {
            char* str; 
            scanf("%ms", &str);
            if(strcmp(str, "q") == 0)
            {
                kill(fork_int, SIGINT);
                return 0;
                close(fifo_file);
            }
            write_str(fifo_file, num_of_client, str);
        }
    }
    else
    {
        while (1)
        {
            read_str(fifo_file, num_of_client);
        }
    }
}