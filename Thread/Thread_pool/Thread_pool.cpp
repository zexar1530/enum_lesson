#include <thread>
#include <iostream>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

class thread_pool {
    std::atomic_bool done;
    thread_safe_queue<std::function<void()> > work_queue;
    std::vector<std::thread> threads;
    void worker_thread() {
        while (!done) {
            function<void()> task;
            if (work_queue.try_pop(task)) {
                    task();
            }
            else {
                this_thread::yield();
            }
        }
    }

public:
    thread_pool() : done(false) {
        unsigned const thread_count = std::thread::hardware_concurrency();
        try {
            for (unsigned i = 0; i < thread_count; ++i) {
                threads.push_back(thread(&thread_pool::worker_thread, this));
            }
        }
        catch (...) {
            done = true;
            throw;
        }
    }

    ~thread_pool() {
        done = true;
    }

    template<class Function>
    void submit(Function f) {
        work_queue.push(std::function<void()>(f));
    }

};

int main()
{
    std::cout << "Hello World!\n";
}

