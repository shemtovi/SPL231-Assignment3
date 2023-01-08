#pragma once
#include "Frame.h"
#include "User.h"
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;



Frame::Frame(string &commandLine, unordered_map<string, string> &headers, string &body): commandLine(commandLine), headers(headers), body(body){
    receiptNum = getNextReceiptNum();
};

string Frame::toString(){
    string output = "";
    output = output + commandLine + '\n';
    for(auto header: headers){
        output = output + header.first + ":" + header.second + '\n';
    }
    output = output + '\n';
    output = output + body;
    output = output + '\0';
    return output;
};



vector<string> Frame::split(const string& str, char delimiter) {
  vector<string> lines;
  std::stringstream ss(str);
  string line;
  while (std::getline(ss, line, delimiter)) {
    lines.push_back(line);
  }
  return lines;
}