#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int pid = 0;
    int ppid = 0;
    pid = getpid();
    ppid = getppid();
    printf("procrid = %d\nparprocpid = %d", pid, ppid);
}