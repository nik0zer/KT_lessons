#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include "config.h"

int shmid;
int msgid;
int* shm_ptr;

int init_client()
{
    umask(0);
    int key = ftok(path, MAX_NUM_OF_CLIENT + 1);
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    shm_ptr = (int*)shmat(shmid, NULL, 0);

    while(*shm_ptr == -1)
    {

    }

    *shm_ptr = -1;
    while(*shm_ptr == -1)
    {

    }
    if(*shm_ptr == -2)
    {
        return -1;
    }
    int key = ftok(path, *shm_ptr);
    msgid = msgget(key, IPC_CREAT | 0666);
}

int snd_msg(char* data, int rcv_client)
{
    msg_struct m;
    m.type = 1;
    memcpy(m.data, data, sizeof(data));
    if(msgsnd(msgid, &m, sizeof(msg_struct) - sizeof(long), 0) < 0)
    return -1;
}

int rcv_msg(char* data)
{
    msg_struct m;
    m.type = 1;
    if(msgrcv(msgid, &m, sizeof(msg_struct) - sizeof(long), 0, 0) >= 0)
    data = (char*)realloc(data, sizeof(char) * strlen(m.data));
}
