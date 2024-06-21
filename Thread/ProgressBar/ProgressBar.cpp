
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include "Timer.h"

using namespace std;

mutex m1, m2;

void ProgressBar(int row) {
    m1.lock();
    cout << row << "\t" << this_thread::get_id() << "\t" << endl;
    m1.unlock();
    auto start = chrono::high_resolution_clock::now();
    for (int i{}; i < 12; i++) {
        this_thread::sleep_for(500ms);
        m2.lock();
        this_thread::sleep_for(300ms);
        consol_parameter::SetPosition(i + 16, row + 1);
        consol_parameter::SetColor(0, 1);
        cout << " ";
        m2.unlock();
    }
    auto fin = chrono::high_resolution_clock::now();
    lock_guard<mutex> l(m2);
    consol_parameter::SetColor(15, 0);
    consol_parameter::SetPosition(30, row + 1);
    cout << chrono::duration_cast<chrono::duration<double>>(fin - start).count() * 1000 << "ms";
};

void MakeThread(int count) {
    thread* t = new thread[count];
    for (int i=0; i < count; i++) {
        t[i] = thread(&ProgressBar, i);
    }
    for (int i{}; i < count; i++) {
        t[i].join();
    }
    delete[]t;
}
int main()
{
    cout << "#\t" << "id\t" << "Progress Bar\t" << "Time\n";
    MakeThread(3);
    cout << "\n\n\n";
    return 0;
}


