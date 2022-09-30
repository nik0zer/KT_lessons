#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    umask(0);
    int num_of_proc = 0;
    scanf("%d", &num_of_proc);
    char path[] = "1";
    int key;
    int* cnt[3];
    for(int i = 0; i < 3; i++)
    {
        int key = ftok(path, i);
        int shmid = shmget(key, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
        if(shmid == -1)
        {
            shmid = shmget(key, sizeof(int), 0666);
            cnt[i] = (int*)shmat(shmid, NULL, 0);
        }
        else
        {
            cnt[i] = (int*)shmat(shmid, NULL, 0);
            *(cnt[i]) = 0;
        }
    }
    printf("num: %d\n", num_of_proc);
    if(num_of_proc == 0 || num_of_proc == 1)
    {
        (*(cnt[num_of_proc]))++;
        *(cnt[2]) = *(cnt[0]) + *(cnt[1]);
    }
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n", *(cnt[i]));
    }
}
