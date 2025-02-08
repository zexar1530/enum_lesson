#include "Readconfig.h"

Readconfig::Readconfig(const string& str) {
    parseFile(str);
    cout << "Прочитали файл конфигурации" << endl;
}

void Readconfig::parseFile(const string& name_file) {
    ifstream file(name_file);
    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла конфигурации");
    }

    string section;
    string line;
    stringstream str_stream;

    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
        }
        else {
            string key, value;
            str_stream.clear();
            str_stream << line;

            if (getline(str_stream, key, '=') && getline(str_stream, value)) {
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);

                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                if (!section.empty()) {
                    key = section + "." + key;
                }

                config_data[key] = value;
            }
        }
    }
}

string Readconfig::readValue(const string& key) const {
    auto it = config_data.find(key);
    if (it != config_data.end())
        return it->second;
    throw runtime_error("Не найден ключ или значение в Config.ini");
}