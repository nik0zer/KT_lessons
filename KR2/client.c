#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

enum CONSTANTS
{
    MAX_NUM_OF_CLIENTS = 100,
};

enum ERRORS
{
    NOT_ENOUGH_ARGC = 1,
    WRONG_DIR = 2
};

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        return NOT_ENOUGH_ARGC;
    }

    int socket_fd = socket(AF_IPX, SOCK_STREAM, 0);

    struct in_addr server_addr;
    struct in_addr client_addr[MAX_NUM_OF_CLIENTS];
    int curr_client_adr = 0;

    int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    


}