#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int pid = 0;
    int ppid = 0;
    int pidded = 0;
    pidded = getpid();
    if(fork() != -1)
    {
        pid = getpid();
        ppid = getppid();
        if(pidded == ppid)
            printf("Child:\nproc_id = %d\npar_proc_id = %d\n", pid, ppid);
        else
            printf("Parent:\nproc_id = %d\npar_proc_id = %d\n", pid, ppid);
    }
    else
        printf("FORK_ERROR");
    return 0;
}