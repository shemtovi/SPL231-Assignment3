#pragma once
#include "ServerInputManager.h"
#include <string>

using std::string;

extern bool disconnect;

ServerInputManager::ServerInputManager(ConnectionHandler &connectionHandler): connectionHandler(connectionHandler){};

void ServerInputManager::run(){
    string serverInput = "";
    while(!connectionHandler.protocol.should_terminate){
        //Read from the socket and insert into serverInput
        connectionHandler.getLine(serverInput);
        //Send to protocol to manage the input
        T msg = connectionHandler.protocol.receive(serverInput);
        connectionHandler.sendLine(msg)
    }
};