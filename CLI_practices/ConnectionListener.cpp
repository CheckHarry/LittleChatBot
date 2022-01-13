#include "ConnectionListener.h"
#include <iostream>
#include <sstream>
using namespace std;
#pragma warning(disable:28193) 




ConnectionListener::ConnectionListener(char* address_, int port_num_) {
	address = address_;
	port = port_num_;
	listening_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in listener_addr;
	memset(&listener_addr, 0, sizeof(listener_addr));
	listener_addr.sin_family = PF_INET;
	listener_addr.sin_addr.s_addr = inet_addr(address);
	listener_addr.sin_port = htons(port);  
	bind(listening_socket, (SOCKADDR*)&listener_addr, sizeof(SOCKADDR));
}


SOCKET ConnectionListener::ListenAndAccept() {
	listen(listening_socket, 20);
	SOCKADDR RequestAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET RequestSock = accept(listening_socket, (SOCKADDR*)&RequestAddr, &nSize);
	char* ip = inet_ntoa(((SOCKADDR_IN*)&RequestAddr)->sin_addr);
	//char* Port = inet_ntop(((SOCKADDR_IN*)&RequestAddr)->sin_port);
	cout << ip << endl;
	socket_pool.push_back(RequestSock);
	char* str = (char*)"Connection Success From Listener!";
	send(RequestSock, str, strlen(str) + sizeof(char), NULL);
	return RequestSock;
	/*
	while (true) {
		vector<char> buf(5000); // you are using C++ not C
		int bytes = recv(RequestSock, buf.data(), buf.size(), 0);
		std::cout << buf.data() << '\n';
	}
	*/
}

void ConnectionListener::Listening(SOCKET sock) {
	while (true) {
		vector<char> buf(5000); // you are using C++ not C
		int bytes = recv(sock, buf.data(), buf.size(), 0);
		std::cout << buf.data() << '\n';
	}
}