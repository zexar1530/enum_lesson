#include <thread>
#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;

static inline void f1() {
    this_thread::sleep_for(100ms);
    for (unsigned int i{}; i < 10000; i++)
        i += 100;
    cout << "Function 1 ";
}

static inline void f2() {
    this_thread::sleep_for(200ms);
    for (unsigned int i{}; i < 10000; i++)
        i += 100;

    cout << "Function 2 ";
}

static inline void f3(bool _done) {
    this_thread::sleep_for(200ms);
    for (unsigned int i{}; i < 10000; i++)
        i += 100;
    cout << "Function 3 ";
}

template<class Func>    // класс потокобезопасной очереди
class safe_queue {
public:
    safe_queue() = default; //конструктор и деструктор по умолчанию
    ~safe_queue() = default;

    void push(Func f) {
        unique_lock<mutex> l(m);
        q.push(f);
    }

    void front() {
        unique_lock<mutex> l(m);
        if (!q.empty()) {
            q.front()();
            q.pop();
        }
    }

    bool empty() {
        unique_lock<mutex> l(m);
        return q.empty();
    }

private:
    mutex m;
    queue<Func> q;
};

class thread_pool {
public:
    thread_pool() : done(false) {           //конструктор пула
        unsigned int const thread_count = thread::hardware_concurrency()-3; //отнимем 3 на всякий))))
        try {
            for (unsigned i = 0; i < thread_count; ++i) {
                threads.push_back(thread(&thread_pool::work, this)); //создаем потоки из work
            }
        }
        catch (...) {
            done = true; //если что то не так то тормозим work() и передаем исключение дальше
            throw;
        }
    }

    ~thread_pool() {
        done = true;    //при разрушении обьекта тормозим work()
    }

    template<class Func>        //принимаем функцию и отправляем в очередь
    void submit(Func f, bool _done = false) {
        work_queue.push(function<void()> (f));
    }

    void poolJoin() {
        for (auto& t : threads)
            t.join();
    }

    inline void stop() {
        done = true;
    }

private:
    mutex m;
    atomic_bool done;       //flag
    safe_queue<function<void()>> work_queue;  //наша очередь
    vector<thread> threads; //наши потоки

    void work() {
        while (!done && !work_queue.empty()) {             //Посоветуйте как выйти из цикла потоков
        /*for (int i{}; i < 10; i++) {*/
            if (!work_queue.empty()) {  //если очередь не пуста то работаем
                work_queue.front();     //заспускаем функцию
                unique_lock<mutex> l(m);
                cout << "\tThread " << this_thread::get_id() << endl;
            }
            else {
                this_thread::yield();   //если пуста то пусть поток покурит)))))
            }
        }
    }
};

int main()
{
    {
        thread_pool pool;   //создали наш обьект и потоки
        pool.submit(f1);
        pool.submit(f2);
        pool.submit(f1);
        pool.submit(f2);
        pool.submit(f1);
        pool.submit(f2);
        pool.submit(f1);
        pool.submit(f2);
        pool.poolJoin();
        pool.stop();
    }
    this_thread::sleep_for(5000ms);
    cout << "end!!!!!!!!\n";
    return 0;
}

