
#include <vector>
#include <locale>
#include <sstream>
#include <fstream>
#include <iostream>
#include "IniParser.h"


static bool iskey(const std::wstring c) {
    return isalnum(c[0], std::locale("Russian")) || ispunct(c[0]);    //���� �����, ����� ��� ���� ���������� �� true
}

static bool isval(const std::wstring c) {
    return isalnum(c[0], std::locale("Russian")) || ispunct(c[0]) || isblank(c[0]);  //��������� ������ ��� ���������
}

IniParser::IniParser(const std::string& path) {

    enum class State {          //����� ������
        init,       
        section,
        key,
        value,
        skipline    
    } state = State::init;  //�� ���������

    std::wifstream f(path);              //��������� ����
    if (!f.is_open()) {
        throw std::runtime_error("���� �� ������ ��� ������ ��������");
    }

    std::vector<wchar_t> buf;          //������ int and unsigned char ��� ����� � ������� �� ��������!
    std::wstring section, key;
    std::wstring c;

    //������ ������������ ��������� �� �����
    //����� �������� ������������ ������)))), ���� ��� �� ������ ������ Throw, ���� ������ ������� �����
    auto err = [&f, &c, &path](const std::string& section) {
        std::ostringstream strm;
        strm << "�������� ������ '" << static_cast<char>(c[0]) << "'(" << static_cast<int>(c[0]) << ") � ����� = " << section << ", � ����� " << path << ":" << f.tellg();
        throw std::runtime_error(strm.str());
        };

    while (f.get(c[0])) {
        switch (state) {
        case State::skipline:   //���� ����� ������ �� ���� Init
            if (c[0] == '\n') {
                state = State::init;
            }
            break;
        case State::init:
            if (c[0] == ';') {         //���� ����������� �� ������ �� ����� ������
                state = State::skipline;
            }
            else if (c[0] == '[') {        //���� � ������ ������
                state = State::section;
            }
            else if (std::isspace(c[0])) {
                //������� ������ ��������� �� ����� ����
            }
            else if (iskey(c)) {    //���� ����� ����� ���������� �� ��������� � ������ � ������ ����
                state = State::key;
                buf.push_back(c[0]);
            }
            else {
                err("init");
            }
            break;
        case State::section:
            if (c[0] == ']') {                                        //���� ����� ������
                section = std::wstring(buf.begin(), buf.end());      //�������� ���, ������� ������, ������ ���� � ������ �� ����� ������
                buf.clear();
                state = State::skipline;
            }
            else if (isval(c)) {
                buf.push_back(c[0]);   //���� ����� ����� ��� ����� �� ��������� � ������
            }
            else {
                err("section");
            }
            break;
        case State::key:
            if (c[0] == '=') {
                key = std::wstring(buf.begin(), buf.end());
                buf.clear();
                state = State::value;
            }
            else if (iskey(c)) { //���� ������ ��� �������
                buf.push_back(c[0]);
            }
            else {
                err("key");
            }
            break;
        case State::value:
            if (c[0] == '\n' || c[0] == ';') {
                try
                {
                    if (buf.empty()) throw std::runtime_error("��� ��������");
                }
                catch (const std::runtime_error& e)
                {
                    std::cout << e.what();
                    std::wcout << " � " << section << " " << key << std::endl;
                }
                inimap[section][key] = std::wstring(buf.begin(), buf.end());
                buf.clear();
                if (c[0] == ';') state = State::skipline;
                else state = State::init;
            }
            else if (iskey(c)) {
                buf.push_back(c[0]);
            }
            else if (std::isspace(c[0])) {
                //������ �������
            }
            else {
                err("value");
            }
            break;
        }
    }
    if (state != State::init) {
        err("��������� ����� �����");
    }
}
