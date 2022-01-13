#include <iostream>
#include<stdio.h>
#include <winsock2.h>
#include <string>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include<windows.h>
#include "ConnectionListener.h"
#include "CommandParser.h"
#include "ChatBotKernel.h"
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals;
using std::chrono::system_clock;
using namespace std;
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996) 


struct server_address {
    char address[14];
    string port;
};



string toupper(string s) {
    string temp = "";
    for (char x : s) temp += toupper(x);
    return temp;
}

void connect_to_server(SOCKET& socket , sockaddr_in &addr) {
    
    
    
    connect(socket, (struct sockaddr*)&addr, sizeof(addr));
    
}

void recv_from_server(SOCKET* socket) {
    char szBuffer[MAXBYTE] = { 0 };
    while (true){
    recv(*socket , szBuffer, MAXBYTE, NULL);
    cout << '\n';
    printf(szBuffer);
    cout << "\n >> ";
    }
}



int main()
 {
    /*
    

    char recv_address[14];
    string port;
    cout << "Enter IPaddress: ";
    cin >> recv_address;
    cout << '\n';
    cout << "Enter Port: ";
    cin >> port;
    cout << '\n';
    ConnectionListener Listener((char*)recv_address, stoi(port));
    thread list_thread(&ConnectionListener::Listen, Listener);

    server_address server_addr;
    cout << "Enter IPaddress: ";
    cin >> server_addr.address;
    cout << '\n';
    cout << "Enter Port: ";
    cin >> server_addr.port;
    cout << '\n';
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(server_addr.address);
    addr.sin_port = htons(stoi(server_addr.port));

    
    SOCKET ConnectionSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect_to_server(ConnectionSocket , addr);
    
   // thread t_recv(recv_from_server , &ConnectionSocket);
    
    char szBuffer[MAXBYTE] = { 0 };
   
    recv(ConnectionSocket, szBuffer, MAXBYTE, NULL);
    printf(szBuffer);
    Sleep(1000);
    
    while (true) {
        char buffer[1024] ;
        memset(buffer, 0, sizeof(buffer));
        cout << ">> ";
        cin.getline(buffer , sizeof(buffer));
        cout << buffer;
        cout << '\n';
        send(ConnectionSocket, buffer, sizeof(buffer), NULL);
        Sleep(5);
    }
    list_thread.join();

    */
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    char recv_address[14];
    string port;
    cout << "Enter IPaddress: ";
    cin >> recv_address;
    cout << '\n';
    cout << "Enter Port: ";
    cin >> port;
    cout << '\n';
    
    ChatBotKernel Kernel(recv_address , stoi(port));
    thread thread_Kernel(&ChatBotKernel::run , &Kernel);
    CommandParser parser;
    vector<lexeme> buf;
    int count = 0;
    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        cout << ">> ";
        if (count == 0) {
            cin.ignore();
            count++;
        }
        cin.getline(buffer, sizeof(buffer));
        if (buffer[0] == 0) continue;
        buf = parser.parse(string(buffer));
        Kernel.prompt_handler(buf);
        Sleep(5);
    }
}
