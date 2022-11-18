#ifndef CONFIG_H
#define CONFIG_H

enum CONSTANTS
{
    SIZE_OF_MESSAGE = 100,
    MAX_NUM_OF_CLIENT = 100
};

char path[] = "server.c";

struct  {
    long type;
    char data[SIZE_OF_MESSAGE];
} typedef msg_struct;



 




#endif