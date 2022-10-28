#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

struct msg_struct {
    long type;
    char data[100];
};

const char* PATH = "a.out";

int main(int argc, char** argv)
{
    umask(0);
    if(argc < 2)
    {
        return -1;
    }
    int n = 0;
    if(sscanf(argv[1], "%d", &n) !=  1 || n <= 1)
    {
        return -2;
    }

    int key = ftok(PATH, 0);

    if(key < 0)
    {
        return -3;
    }

    int msg_id = msgget(key, 0666 | IPC_CREAT);

    if(msg_id < 0)
    {
        return -4;
    }

    struct msg_struct m1 = {1, "1"};

    int pid = 0;

    for(int i = 1; i < n; i++)
    {
        if(pid == 0)
        {
            pid = fork();
            if(pid != 0)
            {
                pid = i;
                break;
            }
        }
    }
    if(pid != 1)
    {
        if (msgsnd(msg_id, &m1, sizeof(struct msg_struct) - sizeof(long), 0) < 0)
        {
            return -5;
        }
    }
    else
    {
        int k = 0;
        while (1)
        {
            if(msgrcv(msg_id, &m1, sizeof(struct msg_struct) - sizeof(long), 0, 0) >= 0)
            {
                k++;
                printf("message_number:%d\n", k);
                if(k == n - 1)
                    break;
            }
        }
        if (msgctl(msg_id, IPC_RMID, NULL) == 0)
        {
            return 0;
        }
        return -6;
    }
        
}