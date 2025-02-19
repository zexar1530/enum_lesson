#pragma once

#include "PostgreDb.h"
#include "Spider.h"
#include "http_server.h"
#include "Readconfig.h"
#include "StaticSpider.h"

#include <iostream>
#include <thread>


class Start {
public:
    Start(const std::string& str);

    void run();

private:
    void runWorker();
    Readconfig configuration;
    PostgreDb db;
    Spider spider;
    shared_ptr<Serv> http_serv;
    thread spiWorker;
    thread serWorker;
};
