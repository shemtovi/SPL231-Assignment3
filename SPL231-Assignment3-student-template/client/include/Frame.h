#pragma once
#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::string;
using std::unordered_map;

class Frame
{
private:
    string commandLine;
    unordered_map<string, string> headers;
    string body;
    static vector<string> split(const string& str, char delimiter);
    int receiptNum;

public:
    Frame(string &commandLine, unordered_map<string, string> &headers, string &body);
    ~Frame();
    string toString();
    static Frame toFrame(string &convert);
    static int getNextReceiptNum();
    string getCommandLine();
    unordered_map<string, string> getHeaders();
    string getBody();
};

