#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

enum CONSTANTS
{
    MAX_NUM_OF_CLIENTS = 100,
    SIZE_OF_ORDER = 100,
};


int main(int argc)
{
    int socket_fd = socket(AF_IPX, SOCK_STREAM, 0);
    int num_curr_client_adrr = 0;
    struct sockaddr client_addr[MAX_NUM_OF_CLIENTS];

    bind(socket_fd, INADDR_ANY, sizeof(INADDR_ANY));

    listen(socket_fd, SIZE_OF_ORDER);

    while (1) {
        struct sockaddr curr_client_addr; 
        socklen_t len = 0;
        int client_socket = accept(socket_fd, &client_addr, &len);
        client_addr[num_curr_client_adrr] = curr_client_addr;

        char* message = (char*)calloc(sizeof(int) + sizeof(client_addr), 1);
        memcpy(message, &num_curr_client_adrr, sizeof(int));
        memcpy(message + sizeof(int), &client_addr, sizeof(client_addr));
        send(client_socket, message, sizeof(message), 0);
        num_curr_client_adrr++;
    }

    close(socket_fd);
}