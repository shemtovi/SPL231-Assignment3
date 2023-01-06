#pragma once
#include "Game.h"
#include <vector>
#include <unordered_map>
using std::string;

using std::vector;
using std::unordered_map;
class User
{
private:
    unordered_map<string, int> gamesToId;
    unordered_map<string, Game*> gamesStringToObject;
    int subsCounter;
public:
    User(/* args */);
    ~User();
    void addSubscription(string game);
    void removeSubscription(string game);
};
//TODO
