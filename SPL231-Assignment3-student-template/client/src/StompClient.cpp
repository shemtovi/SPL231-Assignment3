#include "../include/StompClient.h"
#include "../include/User.h"
#include "../include/ConnectionHandler.h"
#include "../include/ServerInputManager.h"
#include "../include/KeyboardInputManager.h"
#include "Frame.h"
#include <thread>

//Termination condition
bool disconnect = true;

int main (int argc, char *argv[]) {
	if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    User* user = new User();
    ConnectionHandler ch = new ConnectionHandler(host, port, *user);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    //Perform login
    while(disconnect){
        string input ="";
        getline(std::cin, input);
        int index = input.find(" ");
        if(input.substr(0,index).compare("login") == 0){
            connectionHandler.protocol.send(input);
            //if(connectionHandler.getLine() == CONNECTED)
                //disconnect = fasle
                
            //else
                //Tend to the ERROR
        }
        else{
            std::cout << "Please login before commiting any actions" << std::endl;
        }
    }

	//Initialize objects to later start as threads
	KeyboardInputManager readFromUser(connectionHandler);
	ServerInputManager readFromServer(connectionHandler);

    while(!connectionHandler.protocol.should_terminate){
        //This order of lines should make both threads operate concurrently while the main thread is waiting for them both to finish
        std::thread thread_readFromKeyboard(&KeyboardInputManager::run, &readFromUser);
		std::thread thread_readFromServer(&ServerInputManager::run, &readFromServer);
        thread_readFromKeyboard.join();
		thread_readFromServer.join();
    }
    connectionHandler.close();
    ch.~ConnectionHandler();
    std::cout << "Socket has been closed and the connection was terminated" << std::endl;

    return 0;
}