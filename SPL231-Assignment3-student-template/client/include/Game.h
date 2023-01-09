#pragma once

#include <string>
#include <map>
#include "Frame.h"
using std::string;
using std::map;

class Game
{
private:
    string title;
    map<string, string> general_stats;
    map<string, string> team_a_stats;
    map<string, string> team_b_stats;
    //Need to find a way to properly sort the reports by time of the event
    map<string, string> reports;

public:
    Game(string &game);
    ~Game();
    void addNewReport(Frame &frame);
};
//TODO - this will be an object that we create for each game that will hold all the reports from a game