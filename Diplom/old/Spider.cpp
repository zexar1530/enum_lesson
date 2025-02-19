#include "Spider.h"

Spider::Spider(PostgreDb& db, const string& addr, int passage)
        : db(db), addr(addr), passage(passage) {
    threads_count = thread::hardware_concurrency() - 1;
    cout << "Spider создан" << endl;
}

vector<pair<string, int>> Spider::index(const string& content) {
    string str = removeHtml(content);

    unordered_map<string, int> word_count;
    istringstream ss(str);
    string word;

    while (ss >> word) {
        if (word.length() >= 3 && word.length() <= 32) {
            word_count[word]++;
        }
    }
    vector<pair<string, int>> vec_word(word_count.begin(), word_count.end());

    sort(vec_word.begin(), vec_word.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second;});
    return vec_word;
}

string Spider::removeHtml(const string& content) {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> ws;
    wstring txt = ws.from_bytes(content);
    txt = regex_replace(txt, wregex(L"<(script|style|noscript|iframe)[^>]*>[\\s\\S]*?</\\1>", regex_constants::icase), L" ");
    txt = regex_replace(txt, wregex(L"<!--.*?-->"), L" ");
    txt = regex_replace(txt, wregex(L"<[^>]*>"), L" ");
    txt = regex_replace(txt, wregex(L"[\"{\\}\\[\\]:]+"), L" ");
    txt = regex_replace(txt, wregex(L"\\b[a-zA-Z0-9_]+_[a-zA-Z0-9_]+\\b"), L" ");
    txt = std::regex_replace(txt, wregex(L"[^\\w\\s-]"), L" ");
    txt = regex_replace(txt, wregex(L"\\s+"), L" ");
    locale loc("ru_RU.UTF-8");
    for (auto& c : txt) {
        c = tolower(c);
    }
    string res = ws.to_bytes(txt);
    return res;
}

void Spider::run() {
    try {
        {
            lock_guard<mutex> l(LnkMutex);
            taskLnk.push({ addr, 0 });
        }

        condition.notify_all();
        for (int i = 0; i < threads_count; ++i) {
            threads.emplace_back(&Spider::worker, this);
        }
        for (auto& t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }
    catch (const exception& e) {
        throw runtime_error("Ошибка запуска Spider......");
    }
}

void Spider::worker() {
    try {
        while (true) {
            Link task;
            {
                unique_lock<mutex> l(LnkMutex);
                condition.wait(l, [this]() {
                    return !taskLnk.empty() || stopWorkers;
                    });

                if (stopWorkers && taskLnk.empty()) {
                    break;
                }

                if (!taskLnk.empty()) {
                    task = taskLnk.front();
                    taskLnk.pop();
                    ++work;
                }
                else 
                    continue;
            }

            if (task.passage >= passage) {
                {
                    lock_guard<mutex> l(LnkMutex);
                    --work;
                    if (taskLnk.empty() && work == 0) {
                        stopWorkers = true;
                        condition.notify_all();
                    }
                }
                continue;
            }

            {
                lock_guard<mutex> l(mtx);
                if (visited_addr.count(task.addr)) {
                    {
                        lock_guard<mutex> l(LnkMutex);
                        --work;
                        if (taskLnk.empty() && work == 0) {
                            stopWorkers = true;
                            condition.notify_all();
                        }
                    }
                    continue;
                }
                visited_addr.insert(task.addr);
            }

            Links parsedAddr = StaticSpider::parse(task.addr);
            string content = StaticSpider::readHtml(parsedAddr);

            if (content.empty()) {
                {
                    lock_guard<mutex> l(LnkMutex);
                    --work;
                    if (taskLnk.empty() && work == 0) {
                        stopWorkers = true;
                        condition.notify_all();
                    }
                }
                continue;
            }

                int doc_id = db.insertDoc(task.addr, content);
                auto word_count = index(content);
                db.insertWord(word_count, doc_id);
                if (task.passage < passage - 1) {
                    auto links = StaticSpider::readLinks(content, task.addr);
                    {
                        addLinks(links, task.passage + 1);
                    }
                    condition.notify_all();
                }
            
            {
                lock_guard<mutex> l(LnkMutex);
                --work;
                if (taskLnk.empty() && work == 0) {
                    stopWorkers = true;
                    condition.notify_all();
                }
            }
        }
    }
    catch (const std::exception& e){
        throw runtime_error("Ошибка Worker....");
    }
}

void Spider::addLinks(const vector<string>& links, int _passage) {
    lock_guard<mutex> l(LnkMutex);
    for (const auto& ls : links) {
        if (visited_addr.find(ls) == visited_addr.end()) {
            taskLnk.push({ ls, _passage });
        }
    }
    condition.notify_all();
}
