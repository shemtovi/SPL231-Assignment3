#pragma once
#include "User.h"
using std::string;

//builder
User::User(): gamesToId(),gamesStringToObject(), subsCounter(0) {};

void  User::addSubscription(string game){
    subsCounter++;
    std::pair<string,int> new_sub (game,subsCounter);
    Game* new_game = new Game(game);
    std::pair<string, Game*> link_game (game, new_game);
    gamesToId.insert(new_sub);
};

void User::removeSubscription(string game){
    gamesToId.erase(game);
    //Maybe use the Game destructor to delete the game here
    gamesStringToObject.erase(game);
};
//TODO