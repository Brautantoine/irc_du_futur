#include "Globals.h"
#include <iostream>
#include <csignal>

using namespace Globals;

void quit() {
    std::cout << "shutdown\n";

    delete server;
    exit(1);
}

void signalHandler(int signum) {
    std::cout << "Interrupt signal:" << signum << std::endl;
    quit();
}

int main() {
    signal(SIGINT, signalHandler);

    std::cout << "Server started\n";


    server = new Server();
    server->loop();

	return 0;
}
