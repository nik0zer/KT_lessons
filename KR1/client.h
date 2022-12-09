#ifndef CLIENT_H
#define CLIENT_H

int init_client();
int snd_msg(char* data, int rcv_client);
int rcv_msg(char* data);


#endif