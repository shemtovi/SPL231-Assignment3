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
    unordered_map<string, int> gamesToSubId;
    unordered_map<string, Game*> gamesStringToObject;
    string userName;
    int subsId;
public:
    User(/* args */);
    ~User();
    void addSubscription(string game);
    void removeSubscription(string game);
    int getSubId(string &game);
    void setUserName(string &name);
    string getUserName();
};
