#pragma once
#include <ws2tcpip.h>
#include <vector>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996) 




class ConnectionListener
{	
private:
	char* address;
	int port;
	SOCKET listening_socket;
	std::vector<SOCKET> socket_pool;
public:
	ConnectionListener(char* address_, int port_num_);
	SOCKET ListenAndAccept();
	void Listening(SOCKET sock);

	
};

