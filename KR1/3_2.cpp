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


    while(*shm_flag != -1)
    {
    if(*shm_flag == 1)
    {
        char* argv[MAX_ARGS + 1];
        for(int i  = 1; i < MAX_ARGS + 1; i++)
        {
            if(shm_argv[i - 1][0] != '\0')
            {
                argv[i] = (char*)calloc(PATH_MAX, sizeof(char));
                strcpy(argv[i], shm_argv[i - 1]);
            }
            else
            {
                argv[i] = NULL;
            }
        }
        argv[0] = (char*)calloc(PATH_MAX, sizeof(char));
        strcpy(argv[0], shm_str);
        
        int pid = fork();
        if(pid == 0)
        {
            execvp(shm_str, argv);
        }
        *shm_flag = 0;
        for(int i  = 0; i < MAX_ARGS + 1; i++)
        {
            free(argv[i]);
        }
    }
    }
    for(int i = 0; i < MAX_ARGS; i++)
    {
        shmctl(shmid[i], IPC_RMID, NULL);
    }
    shmctl(shmid_1, IPC_RMID, NULL);
    shmctl(shmid_2, IPC_RMID, NULL);
}