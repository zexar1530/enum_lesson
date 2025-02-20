#include "PostgreDb.h"

PostgreDb::PostgreDb(const string& host, const string& port, const string& name, const string& user, const string& pass)
    : connectionString("host=" + host + " port=" + port + " dbname=" + name + " user=" + user + " password=" + pass) {
    /*conn = new pqxx::connection(connectionString);
    if (!conn->is_open())
        throw runtime_error("Ошибка БД");*/
    initDb();
    //cout << "Подключились к базе и создали" << endl;
}

PostgreDb::~PostgreDb() {
    //delete conn;
}

void PostgreDb::initDb() {
    pqxx::connection conn(connectionString);
    pqxx::work create_table(conn);
    create_table.exec(
        "CREATE TABLE IF NOT EXISTS doc ("
        "id SERIAL PRIMARY KEY, "
        "addr TEXT NOT NULL UNIQUE, "
        "content TEXT NOT NULL);"
    );

    create_table.exec(
        "CREATE TABLE IF NOT EXISTS words ("
        "id SERIAL PRIMARY KEY, "
        "doc_id INT NOT NULL REFERENCES doc(id) ON DELETE CASCADE, "
        "word TEXT NOT NULL, "
        "count INT NOT NULL);"
    );

    create_table.commit();
}

vector<pair<string, int>> PostgreDb::getDocs(const vector<string>& words) {
    vector<pair<string, int>> total;
    pqxx::connection conn(connectionString);
    pqxx::work query(conn);

    ostringstream s_query;
    s_query << "SELECT d.addr, SUM(w.count) AS total "
        << "FROM doc d "
        << "JOIN words w ON d.id = w.doc_id "
        << "WHERE w.word IN (";

    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) s_query << ", ";
        std::string utf;
        try {
            utf = boost::locale::conv::to_utf<char>(words[i], "Windows-1251");
        }
        catch (const runtime_error& e) {
            utf = words[i];
        }
        s_query << query.quote(utf);
    }
    s_query << ") GROUP BY d.addr "
        << "ORDER BY total DESC "
        << "LIMIT 30;";
    pqxx::result result = query.exec(s_query.str());
    for (const auto& row : result) {
        string addr = row["addr"].as<string>();
        int sum = row["total"].as<int>();
        total.emplace_back(addr, sum);
    }
    return total;
}

int PostgreDb::insertDoc(const std::string& addr, const string& content) {
    string html = content;

    pqxx::connection conn(connectionString);
    pqxx::work insert(conn);

    pqxx::result result = insert.exec(
        "SELECT id FROM doc WHERE addr = " + insert.quote(addr) + ";"
    );

    if (!result.empty()) {
        int documentId = result[0][0].as<int>();
        insert.exec(
        "UPDATE doc SET content = " + insert.quote(html) +
        " WHERE id = " + insert.quote(documentId) + ";"
    );
        insert.commit();
        return documentId;
    }

    result = insert.exec(
        "INSERT INTO doc (addr, content) "
        "VALUES (" + insert.quote(addr) + ", " + insert.quote(html) + ") "
        "RETURNING id;"
    );

        insert.commit();
        return result[0][0].as<int>();
}

void PostgreDb::insertWord(const vector<pair<string, int>>& word_count, int doc_id) {
    pqxx::connection conn(connectionString);
    pqxx::work insert(conn);

    insert.exec(
        "DELETE FROM words WHERE doc_id = " + insert.quote(doc_id) + ";"
    );

    for (const auto& [word, freq] : word_count) {
        insert.exec(
            "INSERT INTO words (doc_id, word, count) "
            "VALUES (" + insert.quote(doc_id) + ", " + insert.quote(word) + ", " + insert.quote(freq) + ");"
        );
    }
    insert.commit();
}
