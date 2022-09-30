#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv)
{
    umask(0);
    char path[] = "1";
    int key = ftok(path, 0);
    int shmid = shmget(key, sizeof(argv[1]), 0666);
    char* ptr = (char*)shmat(shmid, NULL, 0);
    printf(ptr);
    shmctl(shmid, IPC_RMID, NULL);
}

