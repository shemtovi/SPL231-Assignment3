#pragma once
#include "ConnectionHandler.h"
class KeyboardInputManager
{
private:
    ConnectionHandler &connectionHandler;
public:
    KeyboardInputManager(ConnectionHandler &connectionHandler);
    void run();
    ~KeyboardInputManager();
};

