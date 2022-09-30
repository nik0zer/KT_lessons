#ifndef TG_H
#define TG_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char path[] = "tg.fifo";

int init_fifo();

int read_str(int fd, int num_of_client, int* flag_of_client, int* status);

int write_str(int fd, int num_of_client, char* str_to_write, int* flag_of_client, int* status);

#endif