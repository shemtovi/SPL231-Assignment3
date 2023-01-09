#pragma once
#include "Game.h"

Game::Game(string &game):title(game), general_stats(),team_a_stats(), team_b_stats(), reports(){};


void Game::addNewReport(Frame &frame){
    
};
//TODO - this will be an object that we create for each game that will hold all the report from a game