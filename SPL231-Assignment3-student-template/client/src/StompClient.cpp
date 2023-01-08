#include "../include/StompClient.h"
#include "../include/User.h"
#include "../include/ConnectionHandler.h"
#include "../include/ServerInputManager.h"
#include "../include/KeyboardInputManager.h"
#include <thread>

//Termination condition
bool disconnect = false;

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
	ServerInputManager readFromServer(connectionHandler);

    //Create a current user for the client
    User* user = new User();

	//

    while(!disconnect){
        //This order of lines should make both threads operate concurrently while the main thread is waiting for them both to finish
        std::thread thread_readFromKeyboard(&KeyboardInputManager::run, &readFromUser);
        thread_readFromKeyboard.join();
		std::thread thread_readFromSocket(&ServerInputManager::run, &readFromServer);
		thread_readFromSocket.join();
    }

    return 0;
}