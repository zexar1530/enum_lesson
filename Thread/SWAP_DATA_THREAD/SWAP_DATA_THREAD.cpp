
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Data {
public:
    Data(int);
    Data() = default;
    Data(const Data&) = delete;
    Data(Data&&) = delete;

    int number{};
    mutex m;
};

Data::Data(int i) :number(i) {};

void FuncSwapLock(Data&, Data&);
void FuncSwapScoped(Data&, Data&);
void FuncSwapUnique(Data&, Data&);

int main()
{
    Data d1(12345);
    Data d2(67890);
    thread t1(&FuncSwapLock, ref(d1), ref(d2));
    thread t2(&FuncSwapScoped, ref(d1), ref(d2));
    thread t3(&FuncSwapUnique, ref(d1), ref(d2));
    t1.join();
    t2.join();
    t3.join();
    return 0;
}

void FuncSwapLock(Data& data1, Data& data2) {
    data1.m.lock();
    data2.m.lock();
    int tmp = data1.number;
    data1.number = data2.number;
    data2.number = tmp;
    cout << "Data1 = " << data1.number << "\t" << "Data2 = " << data2.number << endl;
    data1.m.unlock();
    data2.m.unlock();
};

void FuncSwapScoped(Data& data1, Data& data2) {
    scoped_lock l(data1.m, data2.m);
    int tmp = data1.number;
    data1.number = data2.number;
    data2.number = tmp;
    cout << "Data1 = " << data1.number << "\t" << "Data2 = " << data2.number << endl;
}

void FuncSwapUnique(Data& data1, Data& data2) {
    unique_lock l1(data1.m, defer_lock);
    unique_lock l2(data2.m, defer_lock);
    l1.lock();
    l2.lock();
    int tmp = data1.number;
    data1.number = data2.number;
    data2.number = tmp;
    cout << "Data1 = " << data1.number << "\t" << "Data2 = " << data2.number << endl;
    l1.unlock();
    l2.unlock();
}