#include "tg.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int main()
{
    umask(0);
    int num_of_client;
    scanf("%d", &num_of_client);
    char path[] = "1";
    int key = ftok(path, 0);
    int shmid = shmget(key, 2 * sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    int* shm_ptr;
    if(shmid == -1)
    {
        shmid = shmget(key, 2 * sizeof(int), 0666);
        shm_ptr = (int*)shmat(shmid, NULL, 0);
    }
    else
    {
        shm_ptr = (int*)shmat(shmid, NULL, 0);
    }
    shm_ptr[0] = -1;
    shm_ptr[1] = 0;



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
            while(1)
            {
                if(shm_ptr[0] == -1)
                {
                    write_str(fifo_file, num_of_client, str, shm_ptr, shm_ptr + 1);
                    break;
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if(!(shm_ptr[0] == num_of_client || shm_ptr[0] == -1) && shm_ptr[1] == 1)
            {
                read_str(fifo_file, num_of_client, shm_ptr, shm_ptr + 1);
            }
        }
    }
}