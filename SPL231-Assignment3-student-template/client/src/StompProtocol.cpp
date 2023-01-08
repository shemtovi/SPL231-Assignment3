#pragma once
#include "StompProtocol.h"
#include "ConnectionHandler.h"
#include "StompClient.h"
#include "User.h"
#include "Frame.h"
#include "event.h"
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::pair;
using std::map;

bool should_terminate=false;
StompProtocol::StompProtocol(ConnectionHandler &connectionHandler): connectionHandler(connectionHandler), receiptNum(0){};
void StompProtocol::send(string &convert){
    Frame frame = toFrameSend(convert);
    string stringFrame = frame.toString() + '\0';
    connectionHandler.sendLine(stringFrame);
};

//TODO
void StompProtocol::receive(string &convert){
    Frame frame = toFrameRecieve(convert);
    //process
    

};

Frame StompProtocol::toFrameSend(string &convert){
    receiptNum++;
    string commandLine = "";
    unordered_map<string, string> headers;
    string body = "";
    vector<string> lines = split(convert, ' ');
    string type = lines[0];
    //frames to send
    //login - CONNECT
    if(type.compare("login") == 0){
        commandLine = "CONNECT";
        //Decide what to do with illegal input - temporary solution:
        if(lines.size() != 4){
            pair<string, string> header ("error","");
            headers.insert(header);
        }
        else{
            connectionHandler.user->setUserName(lines[2]);
            pair<string, string> version ("accept-version", "1.2");
            pair<string, string> host ("host", "stomp.cs.bgu.ac.il");
            pair<string, string> login ("login", lines[2]);
            pair<string, string> passcode ("passcode", lines[3]);
            headers.insert(version);
            headers.insert(host);
            headers.insert(login);
            headers.insert(passcode);
        }
    }
    //logout - DISCONNECT
    if(type.compare("logout") == 0){
        commandLine = "DISCONNECT";
        if(lines.size() != 1){
            pair<string, string> header ("error","");
            headers.insert(header);
        }
        else{
            string receipt_num = std::to_string(receiptNum);
            pair<string, string> header ("receipt",  receipt_num);
            headers.insert(header);
        }
    }
    //join - SUBSCRIBE
    if(type.compare("join") == 0){
        commandLine = "SUBSCRIBE";
        if(lines.size() != 2){
            pair<string, string> header ("error","");
            headers.insert(header);
        }
        else{
            pair<string, string> destination ("destination", "/" + lines[1]);
            connectionHandler.user->addSubscription(lines[1]);
            int subID = connectionHandler.user->getSubId(lines[1]);
            string sub_id = std::to_string(subID);
            pair<string, string> id ("id", sub_id);
            string receipt_num = std::to_string(receiptNum);
            pair<string, string> receipt ("receipt",  receipt_num);
            headers.insert(destination);
            headers.insert(id);
            headers.insert(receipt);
        }

    }
    //exit - UNSUBSCRIBE
    if(type.compare("exit") == 0){
        commandLine = "UNSUBSCRIBE";
        if(lines.size() != 2){
            pair<string, string> header ("error","");
            headers.insert(header);
        }
        else{
            int subID = connectionHandler.user->getSubId(lines[1]);
            connectionHandler.user->removeSubscription(lines[1]);
            string sub_id = std::to_string(subID);
            pair<string, string> id ("id", sub_id);
            string receipt_num = std::to_string(receiptNum);
            pair<string, string> receipt ("receipt",  receipt_num);
            headers.insert(receipt);
        }
        
    }
    //report - SEND
    if(type.compare("report") == 0){
        commandLine = "SEND";
        if(lines.size() != 2){
            pair<string, string> header ("error","");
            headers.insert(header);
        }
        else{
            names_and_events toReport = parseEventsFile(lines[1]);
            string game = "/" + toReport.team_a_name + "_" + toReport.team_b_name;
            pair<string, string> gameName ("destination", game);
            headers.insert(gameName);
            body = body + "user: " + connectionHandler.user->getUserName() + "\n";
            Event event = toReport.events.back();
            body = body + toStringFile(event); 
        }
    }

    return Frame(commandLine, headers, body);
};

Frame StompProtocol::toFrameRecieve(string &convert){
    string commandLine ="";
    unordered_map<string, string> headers;
    string body = "";
    vector<string> lines = split(convert, '\n');
    commandLine = lines[0];
    bool inHeaders = true;
    for(int i = 1; i<lines.size(); i++){
        string line = lines[i];
        if(inHeaders && line.size() == 0) inHeaders = false;
        else if(inHeaders){
            int dotIndex = line.find(':');
            string key = line.substr(0, dotIndex);
            string value = line.substr(dotIndex +1);
            pair<string, string> tempPair (key, value);
            headers.insert(tempPair);
        }
        else{
            body += line;
        }
    }
    return Frame(commandLine, headers, body);
}

string StompProtocol::toStringFile(Event &event){
    std::stringstream body;
    string general_game_updates = "general game updates:\n";
    string team_a_updates = "team a updates:\n";
    string team_b_updates= "team b updates:\n";
    for(const auto& update : event.get_game_updates()){
        general_game_updates += "   " + update.first + ": " + update.second + '\n';
    }
    for(const auto& update : event.get_team_a_updates()){
        team_a_updates += "   " + update.first + ": " + update.second + '\n';
    }
    for(const auto& update : event.get_team_b_updates()){
        team_b_updates += "   " + update.first + ": " + update.second + '\n';
    }
    body << "team a: " + event.get_team_a_name() + '\n' <<
    "team b: " + event.get_team_a_name() + '\n' <<
    "event name: " + event.get_name() + '\n' <<
    "time: " + event.get_time() + '\n' <<
    general_game_updates <<
    team_a_updates <<
    team_b_updates <<
    "description: \n" + event.get_discription();

    return body.str();
    
};

vector<string> StompProtocol::split(const string& str, char delimiter) {
  vector<string> lines;
  std::stringstream ss(str);
  string line;
  while (std::getline(ss, line, delimiter)) {
    lines.push_back(line);
  }
  return lines;
}


