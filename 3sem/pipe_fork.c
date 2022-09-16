#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int pipefd[2];
    pipe(pipefd);
    int fork_int;
    char* string_to_pipe;
    scanf("%ms", &string_to_pipe);
    fork_int = fork();
    if(fork_int)
    {
        write(pipefd[1], string_to_pipe, strlen(string_to_pipe));
        close(pipefd[0]);
        close(pipefd[1]);
        return 0;
    }
    else
    {
        char* string_from_pipe = (char*)calloc(1024, sizeof(char));
        read(pipefd[0], string_from_pipe, 1024);
        printf("child: %s", string_from_pipe);
        close(pipefd[0]);
        close(pipefd[1]);
        return 0;
    }
}