#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv, char** envp)
{
    if(argc < 2)
    {
        printf("ERROR_NO_ARGV");
        return 0;
    }
    int fid = fork();
    if(fid == 0)
    {
        execvp(argv[1], argv + 1);
    }
    else
    {
        for(int i = 0; i < 100; i++)
        {
            printf("%d\n", i);
        }
    }
}