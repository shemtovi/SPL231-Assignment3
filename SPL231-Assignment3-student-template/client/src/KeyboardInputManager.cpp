#pragma once
#include "KeyboardInputManager.h"
#include <string>

using std::string;


extern bool disconnect;

KeyboardInputManager::KeyboardInputManager(ConnectionHandler &connectionHandler): connectionHandler(connectionHandler){};

void KeyboardInputManager::run(){
    string keyboardInput = "";
    while(!connectionHandler.protocol.should_terminate){
        //Read from keyboard and insert to keyboardInput
        getline(std::cin, keyboardInput);
        //send to protocol to handle the input
        
        connectionHandler.protocol.send(keyboardInput);
    }


}