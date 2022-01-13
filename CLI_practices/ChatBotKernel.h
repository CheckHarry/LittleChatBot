#pragma once
#include "CommandParser.h"
#include "ConnectionListener.h"
#include <vector>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <mutex>
#include <thread>
using namespace std;

class ChatBotKernel
{
private:
	enum class State {chatting , idle};
	State state = State::idle;
	SOCKET ConnectionSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	ConnectionListener Listener;
	mutex socket_pool_mutex;
	vector<SOCKET> socket_pool;
	SOCKET current_socket;
public:
	ChatBotKernel(char ip[14], int port);
	void prompt_handler(vector<lexeme>& prompt);
	void command_handler(vector<lexeme>& command);
	//void message_handler(vector<lexeme>& message);

	void run();
	void ListenerRunning();
	
};

