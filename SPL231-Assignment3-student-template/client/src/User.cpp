#pragma once
#include "User.h"
using std::string;

//builder
User::User(): gamesToSubId(),gamesStringToObject(), userName(""), subsId(0){};

void  User::addSubscription(string game){
    std::pair<string,int> new_sub (game,subsId);
    Game* new_game = new Game(game);
    std::pair<string, Game*> link_game (game, new_game);
    gamesToSubId.insert(new_sub);
    subsId++;
};

void User::removeSubscription(string game){
    gamesToSubId.erase(game);
    //Maybe use the Game destructor to delete the game here
    
    gamesStringToObject.erase(game);

};

int User::getSubId(string &game){
    int subscriptionId = gamesToSubId.at(game);
    return subscriptionId;
};

void User::setUserName(string &name){
    userName = name;
};

string User::getUserName(){
    return userName;
};