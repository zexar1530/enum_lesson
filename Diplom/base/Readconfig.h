#pragma once

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


using namespace std;

class Readconfig {
public:
    Readconfig(const string& str);
    string readValue(const string& key) const;

private:
    void parseFile(const string& name_file);
    unordered_map<string, string> config_data;
};