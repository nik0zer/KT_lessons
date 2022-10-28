#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> 
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "3.h"

int main()
{
    umask(0);
    int key_1 = ftok(PATH, 0);
    int key_2 = ftok(PATH, 1);
    int shmid_1 = shmget(key_1, sizeof(int), IPC_CREAT | 0666);
    int shmid_2 = shmget(key_2, sizeof(char) * PATH_MAX, IPC_CREAT | 0666);


    char* shm_argv[MAX_ARGS];
    int shmid[MAX_ARGS];
    for(int i = 0; i < MAX_ARGS; i++)
    {
        int key = ftok(PATH, i + 2);
        shmid[i] = shmget(key, sizeof(char) * PATH_MAX, IPC_CREAT | 0666);
        shm_argv[i] = (char*)shmat(shmid[i], NULL, 0);
    }

    int* shm_flag = (int*)shmat(shmid_1, NULL, 0);
    *shm_flag = 0;
    char* shm_str = (char*)shmat(shmid_2, NULL, 0);

    strcpy(shm_str, "dkfj\0");

    char str[PATH_MAX] = {};
    int num_of_args = 0;
    scanf("%d %s", &num_of_args ,str);
    while(strcmp(str, "q") != 0)
    {
        if(*shm_flag != 1)
        {
            if(MAX_ARGS < num_of_args)
            {
                return -1;
            }
            for(int i = 0; i < num_of_args; i++)
            {
                scanf("%s", shm_argv[i]);
            }
            for(int i = num_of_args; i < MAX_ARGS; i++)
            {
                memset(shm_argv[i], '\0', PATH_MAX);
            }
            strcpy(shm_str, str);

            *shm_flag = 1;
            scanf("%d %s", &num_of_args ,str);
        }
    }
    *shm_flag = -1;
}