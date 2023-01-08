#pragma once

#include <string>
#include <unordered_map>
using std::string;

class Game
{
private:
    string title;
    


public:
    Game(string game);
    ~Game();
};
//TODO - this will be an object that we create for each game that will hold all the report from a game