#pragma once
#include "ServerInputManager.h"
#include "Frame.h"
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;
using std::pair;


extern bool connect;

ServerInputManager::ServerInputManager(ConnectionHandler &connectionHandler): connectionHandler(connectionHandler){};

void ServerInputManager::run(){
    string serverInput = "";
    while(!connectionHandler.protocol.should_terminate){
        //Read from the socket and insert into serverInput
        connectionHandler.getLine(serverInput);
        //Send to protocol to manage the input
        Frame frame = toFrameRecieve(serverInput);
        connectionHandler.protocol.receiveProcess(frame);
    }
};

Frame ServerInputManager::toFrameRecieve(string &convert){
    string commandLine ="";
    unordered_map<string, string> headers;
    string body = "";
    vector<string> lines = connectionHandler.split(convert, '\n');
    commandLine = lines[0];
    bool inHeaders = true;
    for(int i = 1; i<lines.size(); i++){
        string line = lines[i];
        if(inHeaders && line.size() == 0) inHeaders = false;
        else if(inHeaders){
            int dotIndex = line.find(':');
            string key = line.substr(0, dotIndex);
            string value = line.substr(dotIndex +1);
            pair<string, string> tempPair (key, value);
            headers.insert(tempPair);
        }
        else{
            body += line;
        }
    }
    return Frame(commandLine, headers, body);
};