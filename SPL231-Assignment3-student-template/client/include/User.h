#pragma once
#include "Game.h"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;
class User
{
private:
    unordered_map<Game, int> gamesToGames_id;
public:
    User(/* args */);
    ~User();
};
//TODO
