#pragma once
#include <string>
#include "event.h"

using std::string;


// TODO: implement the STOMP protocol
class StompProtocol
{
private:
    ConnectionHandler &connectionHandler;
    static vector<string> split(const string& str, char delimiter);
    Frame toFrameSend(string &convert);
    Frame toFrameRecieve(string &convert);
    int receiptNum;

public:
    StompProtocol(ConnectionHandler &connectionHandler);
    bool should_terminate;
    void send(string &convert);
    void receive(string &convert);
    string toStringFile(Event &event);
};
