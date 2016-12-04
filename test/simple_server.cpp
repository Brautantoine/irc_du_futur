#include <iostream>
#include <thread> //use C++11
#include <vector>
#include <algorithm> //for std::remove

#include <csignal> //for signalHandler (catch CTRL-C, exit, ...)
#include <winsock2.h>

#define RECV_BUF_SIZE 512

std::vector<SOCKET> clients;

void signalHandler( int signum ) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    exit(signum);
}

void sendToAll(const char *msg) {
    for (int i = 0 ; i < clients.size() ; i++) {
        send(clients[i], msg, strlen(msg), 0);
    }
}

void sendToAllExcept(SOCKET except_client, char *msg) {
    for (int i = 0 ; i < clients.size() ; i++) {
        if (clients[i] != except_client) {
            std::cout << "Sending to " << clients[i] << ": " << msg << std::endl;
            send(clients[i], msg, strlen(msg), 0);
        }
    }
}

void new_connection(SOCKET socket) {
    clients.push_back(socket);

    char *szMessage = "\x1b[93;41mWelcome \x1b[7mto the server!\r\n";
	send(socket, szMessage, strlen(szMessage), 0);

    // Receive until the peer closes the connection
    int iResult = 0;
    char recvbuf[RECV_BUF_SIZE];
    do {
        memset(recvbuf, 0, sizeof(recvbuf));
        iResult = recv(socket, recvbuf, RECV_BUF_SIZE, 0);
        if (iResult > 0) {
            std::cout << "Bytes received: " << iResult << ": " << recvbuf << " from: "<< socket << std::endl;

            sendToAll(recvbuf);
        } else if (iResult == 0) {
            std::cout << "Connection closed" << std::endl;
        } else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
        }

    } while( iResult > 0 );

    clients.erase(std::remove(clients.begin(), clients.end(), socket), clients.end());

    // Shutdown our socket
	shutdown(socket, SD_SEND);

	// Close our socket entirely
	closesocket(socket);

}

int main()
{
    signal(SIGINT, signalHandler);

	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2), &WsaDat)!=0)
	{
		std::cout << "WSA Initialization failed!\r\n";
		WSACleanup();
		return 0;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		std::cout<<"Socket creation failed.\r\n";
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(8888);

	if(bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		std::cout << "Unable to bind socket!\r\n";
		WSACleanup();
		return 0;
	}

	listen(Socket, 1);

    while (1) {
        SOCKET TempSock = SOCKET_ERROR;

        std::cout << "Waiting for incoming connections...\r\n";
        TempSock = accept(Socket, NULL, NULL);

        if (TempSock != SOCKET_ERROR) {
            std::cout << "Client connected!\r\n\r\n";

            std::thread t(new_connection, TempSock);
            t.detach();
        }
    }

	return 0;
}
