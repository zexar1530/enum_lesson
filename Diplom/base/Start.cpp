#include "Start.h"

Start::Start(const std::string& str) : configuration(str),
    db(
        configuration.readValue("database.host"),
        configuration.readValue("database.port"),
        configuration.readValue("database.name"),
        configuration.readValue("database.user"),
        configuration.readValue("database.password")
    ),
    spider(
        db,
        configuration.readValue("spider.url"),
        stoi(configuration.readValue("spider.passage"))
    ),
    http_serv(std::make_shared<Serv>(db, stoi(configuration.readValue("server.server_port")))) {}

void Start::run() {
    try {
        cout << "Начинаем....." << std::endl;

        spiWorker = thread(&Start::runWorker, this);

        serWorker = thread(&Serv::run, http_serv.get());


        cout << "Сервер запущен....Enter для выхода" << endl;
        cout << "127.0.0.1:8080" << endl;

        cin.get();
        http_serv->stop();

        if (spiWorker.joinable()) {
            spiWorker.join();
        }

        if (serWorker.joinable()) {
            serWorker.join();
        }
    }
    catch (const exception& e) {
        throw runtime_error("Ошибка запуска RUN");
    }
}

void Start::runWorker() {
    try {
        spider.run();
    }
    catch (const exception& e) {
        throw runtime_error("Ошибка здесь");
    }
}
