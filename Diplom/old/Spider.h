#pragma once

#include "PostgreDb.h"
#include "Readconfig.h"
#include "StaticSpider.h"
#include <condition_variable>
#include <queue>
#include <mutex>
#include <unordered_set>
#include <vector>
#include <thread>

struct Link {
    string addr;
    int passage;
};

class Spider {
public:
    Spider(PostgreDb& db, const string& addr, int passage);
    void run();

private:
    void worker();
    void addLinks(const vector<string>& links, int passage);
    string removeHtml(const string& content);
    vector<pair<string, int>> index(const string& content);

    mutex LnkMutex;
    mutex mtx;
    condition_variable condition;
    string addr;
    vector<thread> threads;
    queue<Link> taskLnk;
    unordered_set<string> visited_addr;
    bool stopWorkers = false;
    int passage;
    int threads_count;
    int work{};
    PostgreDb& db;   
};