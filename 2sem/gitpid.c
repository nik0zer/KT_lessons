#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int pid = 0;
    int ppid = 0;
    int pidded = 0;
    pidded = getpid();
    fork();
    pid = getpid();
    ppid = getppid();
    if(pidded == ppid)
        printf("Child:\nprocrid = %d\nparprocpid = %d\n", pid, ppid);
    else
        printf("Parent:\nprocrid = %d\nparprocpid = %d\n", pid, ppid);
    return 0;
}