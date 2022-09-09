#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int uid = 0;
    int gid = 0;
    uid = getuid();
    gid = getgid();
    printf("userid = %d\ngroupid = %d", uid, gid);
}