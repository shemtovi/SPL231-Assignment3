#pragma once
#include "ServerInputManager.h"
#include <string>

using std::string;

extern bool disconnect;

ServerInputManager::ServerInputManager(ConnectionHandler &connectionHandler): connectionHandler(connectionHandler){};

void ServerInputManager::run(){
    string serverInput = "";
    while(!disconnect){
        //Read from the socket and insert into serverInput
        connectionHandler.getLine(serverInput);
        //Send to protocol to manage the input
        connectionHandler.protocol.receive(serverInput);
    }
};