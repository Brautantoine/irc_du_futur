#include <iostream>
#include <winsock2.h> //FOR SOCKET
#include <windows.h> //FOR THREAD

#include <signal.h>

#include <vector>

#pragma comment(lib,"ws2_32.lib")

#define RECV_BUF_SIZE 512

struct client_thread {
    SOCKET m_socket;
    client_thread(SOCKET socket) : m_socket(socket) {}
};

std::vector<client_thread> clients;

void sendToAll(char *msg) {
    for (int i = 0 ; i < clients.size() ; i++) {
        send(clients[i].m_socket, msg, strlen(msg), 0);
    }
}

DWORD WINAPI thread_func(LPVOID lpParams) {
    client_thread *ct = (client_thread*) lpParams;

    char *szMessage = "Welcome to the server!\r\n";
	send(ct->m_socket, szMessage, strlen(szMessage),0);

    // Receive until the peer closes the connection
    int iResult = 0;
    char recvbuf[RECV_BUF_SIZE];
    do {
        memset(recvbuf, 0, sizeof(recvbuf));
        iResult = recv(ct->m_socket, recvbuf, RECV_BUF_SIZE, 0);
        if ( iResult > 0 ) {
            std::cout << "Bytes received: " << iResult << ": " << recvbuf << std::endl;
            sendToAll(recvbuf);
        }else if ( iResult == 0 ) {
            std::cout << "Connection closed" << std::endl;
        }else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
        }

    } while( iResult > 0 );

    // Shutdown our socket
	shutdown(ct->m_socket, SD_SEND);

	// Close our socket entirely
	closesocket(ct->m_socket);

    return 0;
}

int main()
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"WSA Initialization failed!\r\n";
		WSACleanup();
		return 0;
	}

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"Socket creation failed.\r\n";
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=INADDR_ANY;
	serverInf.sin_port=htons(8888);

	if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		std::cout<<"Unable to bind socket!\r\n";
		WSACleanup();
		return 0;
	}

	listen(Socket, 1);

    while (1) {
        SOCKET TempSock = SOCKET_ERROR;
        std::cout<<"Waiting for incoming connections...\r\n";
        TempSock=accept(Socket,NULL,NULL);

        if (TempSock != SOCKET_ERROR) {
            std::cout << "Client connected!\r\n\r\n";
            client_thread ct = client_thread(TempSock);
            clients.push_back(ct);
            CreateThread(NULL, 0, thread_func, &ct, 0, 0);
        }
    }

	return 0;
}
