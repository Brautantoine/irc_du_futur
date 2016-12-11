#include "Server.h"
#include <iostream>
#include <csignal>

Server *server;

void quit() {
    std::cout << "shutdown\n";

    server->close();
    delete server;

    exit(1);
}

void signalHandler( int signum ) {

    std::cout << "Interrupt signal (" << signum << ") received.\n";
    quit();
}

int main() {
    signal(SIGINT, signalHandler);
    std::cout << "Server started\n";
    server = new Server();
	server->start();

	return 0;
}
