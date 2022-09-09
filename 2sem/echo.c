#include <stdio.h>

int main(int argc, char** argv)
{
    int i = 1;
    for(; i < argc - 1; i++)
    {
        printf("%s ", argv[i]);
    }
    if(i < argc)
    {
        printf("%s\n", argv[i]);
    }
    return 0;
}