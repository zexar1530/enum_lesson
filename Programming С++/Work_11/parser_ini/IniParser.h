#pragma once

#include <unordered_map>
#include <map>
#include <string>

class IniParser {

public:
    IniParser(const std::string& path);

    template<class T>           //ну и намучался я с шаблонами, пока их в заголовочном не разместил
    T get(const std::string key, const std::string section) {
        return inimap.at(section).at(key);
    }

    template<>
    int get(const std::string key, const std::string section) {
        return std::stoi(inimap.at(section).at(key));
    }
 
    /*template<>
    double IniParser::get(const std::string& key, const std::string& section) {
        return std::stod(inimap.at(section).at(key));
    }*/

private:
    using SectionMap = std::map<std::string, std::string>;
    using IniMap = std::map<std::string, SectionMap>;

    IniMap inimap;
};




