#pragma once

#include <unordered_map>
#include <map>
#include <string>

class IniParser {

public:
    IniParser(const std::string& path);

    template<class T>           //�� � ��������� � � ���������, ���� �� � ������������ �� ���������
    T get(const std::wstring& key, const std::wstring& section) {
        return inimap.at(section).at(key);
    }

    template<>
    int get(const std::wstring& key, const std::wstring& section) {
        return std::stoi(inimap.at(section).at(key));
    }
 
    template<>
    double get(const std::wstring& key, const std::wstring& section) {
        return std::stod(inimap.at(section).at(key));
    }

private:
    using SectionMap = std::map<std::wstring, std::wstring>;
    using IniMap = std::map<std::wstring, SectionMap>;

    IniMap inimap;
};




