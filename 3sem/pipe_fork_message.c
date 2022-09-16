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
    fork_int = fork();
    if(fork_int)
    {
        for(int num_of_messages = 0; num_of_messages < 3;)
        {
            char* string_from_pipe = (char*)calloc(1024, sizeof(char));
            int read_bytes = read(pipefd[0], string_from_pipe, 1024);
            read_bytes > 0 ? num_of_messages++ : 0;
            printf("process №%d: ", (int)(string_from_pipe[0] - '0'));
            for(int i = 1; i < 1024; i++)
            {
                if(!isdigit(string_from_pipe[i]))
                {
                    printf("%c", string_from_pipe[i]);
                }
                else
                {
                    printf("\n");
                    printf("process №%d: ", (int)(string_from_pipe[i] - '0'));
                    num_of_messages++;
                }
                if(i == 1023)
                {
                    printf("\n");
                }
            }
        } 
        close(pipefd[0]);
        close(pipefd[1]);
    }
    else
    {
        int fork_int_0;
        for(int i = 0; i < 1000; i++)
        {

        }
        fork_int_0 = fork();
        if(fork_int_0)
        {
            char string_to_pipe[] = "1sjhhjkdgkkdfgjshfjdshfjf";
            write(pipefd[1], string_to_pipe, strlen(string_to_pipe));
            close(pipefd[0]);
            close(pipefd[1]);
            return 0;
        }
        else
        {
            int fork_int_1;
            fork_int_1 = fork();
            if(fork_int_1)
            {
                char string_to_pipe[] = "2skfdskfkkdsf";
                write(pipefd[1], string_to_pipe, strlen(string_to_pipe));
                close(pipefd[0]);
                close(pipefd[1]);
                return 0;
            }
            else
            {
                char string_to_pipe[] = "3dkfjksdfjasldklksad";
                write(pipefd[1], string_to_pipe, strlen(string_to_pipe));
                close(pipefd[0]);
                close(pipefd[1]);
                return 0;
            }
        }
    }
}