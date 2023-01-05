#include "../include/StompClient.h"
#include "../include/User.h"
#include "../include/ConnectionHandler.h"
#include "../include/SocketInputManager.h"
#include "../include/KeyboardInputManager.h"
#include <thread>

bool logout = false;
std::string last_input="";

int main (int argc, char *argv[]) {
	if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

	//Initialize objects to later start as threads
	KeyboardInputManager readFromUser(connectionHandler);
	SocketInputManager readFromSocket(connectionHandler);
	
	
	//Here we need to deal with a login command

    while(!logout){
        std::thread readFromKeyboard_thread(&KeyboardInputManager::run, &readFromUser);
		std::thread readFromSocket_thread(&SocketInputManager::run, &readFromSocket);

		readFromKeyboard_thread.join();
		readFromSocket_thread.join();
    }

    delete user;
    return 0;
}