#include "ChatBotKernel.h"
#include "CommandParser.h"
#include <winsock2.h>
#include <iostream>
#pragma warning(disable:4996) 



ChatBotKernel::ChatBotKernel(char ip[14] , int port) : Listener(ip, port){
	
}



void ChatBotKernel::prompt_handler(vector<lexeme>& prompt) {
	if (prompt.empty()) return;
	if (prompt[0].lexeme_type == lexeme::message) {
		if (state == State::chatting) send(current_socket, prompt[0].value.c_str(), 1024, NULL);
		else { cout << "You are not chatting. \n"; }
	}
	else if (prompt[0].lexeme_type == lexeme::command) {
		command_handler(prompt);
	}


}

void ChatBotKernel::command_handler(vector<lexeme>& command) {
	if (command.empty()) return;
	if (command[0].value == "connect") {
		if (state == State::chatting) printf("You are curretly chatting , please exit current chat for connect to other one. \n");
		if (command.size() < 3) printf("Incorrect number of connect arguments.\n");
		else if (state == State::idle) {
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr(command[1].value.c_str());
			addr.sin_port = htons(stoi(command[2].value.c_str()));
			SOCKET target_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			int result = connect(target_socket, (struct sockaddr*)&addr, sizeof(addr));
			if (result == 0) {
				cout << "Connect Success ! \n";
				socket_pool_mutex.lock();
				current_socket = target_socket;
				socket_pool.push_back(target_socket);
				socket_pool_mutex.unlock();
				state = State::chatting;
				current_socket = target_socket;
			}
			else {
				cout << "Connection fail ! \n";
			}
		}
	}
	else if(command[0].value == "exit") {
		if (state == State::chatting) {
			cout << "Exit from chatting. \n";
			state = State::idle;
		}
		else {
			cout << "You are not chatting! \n";
		}
	}
	else if (command[0].value == "ls") {
		// TODO
	}
	else if (command[0].value == "chat") {
		// TODO
	}
}

void ChatBotKernel::run() {
	ListenerRunning();
}

void ChatBotKernel::ListenerRunning() {
	
	vector<thread*> ListeningPool;
	while(true){
	SOCKET s = Listener.ListenAndAccept();
	thread* t = new thread(&ConnectionListener::Listening , Listener , s);
	ListeningPool.push_back(t);
	socket_pool_mutex.lock();
	cout << "receive Connection ! \n";
	socket_pool.push_back(s);
	socket_pool_mutex.unlock();
	}

	for (thread* t : ListeningPool) {
		(*t).join();
	}
	
}