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

int max_client_num = 0;
int shmid;
int msgid[MAX_NUM_OF_CLIENT];
int* shm_ptr;

int init_server()
{
    umask(0);
    int key = ftok(path, MAX_NUM_OF_CLIENT + 1);
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    shm_ptr = (int*)shmat(shmid, NULL, 0);
    
}

int init_new_client()
{
    if(max_client_num >= MAX_NUM_OF_CLIENT)
    {
        *shm_ptr = -2;
        return -1;
    }
    int key = ftok(path, max_client_num);
    msgid[max_client_num] = msgget(key, IPC_CREAT | 0666);
    *shm_ptr = max_client_num;

    max_client_num++;
}

int send_msg_to_client(int num_of_client, char* msg)
{
    msg_struct m;
    m.type = 1;
    memcpy(m.data, msg, strlen(msg));
    msgsnd(msgid[num_of_client], &msg, sizeof(msg_struct) - sizeof(long), 0);
}

int read_msg_from_client(int msg_id)
{
    msg_struct m;
    if(msgrcv(msg_id, &m, sizeof(msg_struct) - sizeof(long), 0, 0) >= 0)
    {
        int rcv_client;
        
        char* msg;
        sscanf(m.data,"%d %ms", &rcv_client, &msg);
        if(rcv_client >= max_client_num)
        {
            return -1;
        }
        send_msg_to_client(rcv_client, msg);
        free(msg);
    }
}

int read_from_all_clients()
{
    for(int i = 0; i < max_client_num; i++)
    {
        read_msg_from_client(msgid[i]);
    }
}