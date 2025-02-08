#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <stdexcept>
#include <vector>
#include <boost/locale.hpp>

using namespace std;

class PostgreDb {
private:
    pqxx::connection* conn;
    string connectionString;
    void initDb();

public:
    PostgreDb(const string& host, const string& port, const string& name,
        const string& user, const string& pass);
    ~PostgreDb();

    vector<pair<string, int>> getDocs(const vector<string>& words);
    int insertDoc(const string& addr, const string& content);
    void insertWord(const vector<pair<string, int>>& word_count, int doc_id);
};
