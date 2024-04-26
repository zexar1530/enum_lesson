
#include <vector>
#include <locale>
#include <sstream>
#include <fstream>
#include <iostream>
#include "IniParser.h"


static bool iskey(const std::wstring c) {
    return isalnum(c[0], std::locale("Russian")) || ispunct(c[0]);    //если цифра, буква или знак пунктуации то true
}

static bool isval(const std::wstring c) {
    return isalnum(c[0], std::locale("Russian")) || ispunct(c[0]) || isblank(c[0]);  //добавляем пробел или табуляцию
}

IniParser::IniParser(const std::string& path) {

    enum class State {          //флаги чтения
        init,       
        section,
        key,
        value,
        skipline    
    } state = State::init;  //по умолчанию

    std::wifstream f(path);              //Открываем файл
    if (!f.is_open()) {
        throw std::runtime_error("Файл не найден или ошибка открытия");
    }

    std::vector<wchar_t> buf;          //ставил int and unsigned char все равно с русским не помогает!
    std::wstring section, key;
    std::wstring c;

    //лямбда формирования сообщения об ошике
    //очень нравится использовать лямбду)))), хотя мог бы просто кидать Throw, хотя второй вариант проще
    auto err = [&f, &c, &path](const std::string& section) {
        std::ostringstream strm;
        strm << "Неверный символ '" << static_cast<char>(c[0]) << "'(" << static_cast<int>(c[0]) << ") в флаге = " << section << ", в файле " << path << ":" << f.tellg();
        throw std::runtime_error(strm.str());
        };

    while (f.get(c[0])) {
        switch (state) {
        case State::skipline:   //если конец строки то флаг Init
            if (c[0] == '\n') {
                state = State::init;
            }
            break;
        case State::init:
            if (c[0] == ';') {         //если комментарий то читаем до конца строки
                state = State::skipline;
            }
            else if (c[0] == '[') {        //флаг в начало секции
                state = State::section;
            }
            else if (std::isspace(c[0])) {
                //пробелы просто пропускаю не меняя флаг
            }
            else if (iskey(c)) {    //если цифра буква пунктуация то добавляем в вектор и меняем флаг
                state = State::key;
                buf.push_back(c[0]);
            }
            else {
                err("init");
            }
            break;
        case State::section:
            if (c[0] == ']') {                                        //если конец секции
                section = std::wstring(buf.begin(), buf.end());      //копируем имя, очищаем вектор, меняем флаг и крутим до конца строки
                buf.clear();
                state = State::skipline;
            }
            else if (isval(c)) {
                buf.push_back(c[0]);   //если цифра буква или проел то добавляем в вектор
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
            else if (iskey(c)) { //ключ считаю без пробела
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
                    if (buf.empty()) throw std::runtime_error("Нет значения");
                }
                catch (const std::runtime_error& e)
                {
                    std::cout << e.what();
                    std::wcout << " в " << section << " " << key << std::endl;
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
                //просто пропуск
            }
            else {
                err("value");
            }
            break;
        }
    }
    if (state != State::init) {
        err("Достигнут конец файла");
    }
}
