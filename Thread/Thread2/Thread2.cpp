#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

void TreadPlusVector(vector<int>& a, vector<int>& b, chrono::duration<double>& time, int begin, int end) {
	auto start = chrono::high_resolution_clock::now();
	vector<int> c;
	for (; begin <= end; begin++) {
		c.push_back(a.at(begin) + b.at(begin));
	}
	auto fin = chrono::high_resolution_clock::now();
	time = fin - start;
}

int main()
{
	vector<thread> t;							// Исходные данные
	vector<int> a = vector<int>(1000, 100);
	vector<int> b = vector<int>(1000, 100);
	vector<int> c = vector<int>(10000, 100);
	vector<int> d = vector<int>(10000, 100);
	vector<int> e = vector<int>(100000, 100);
	vector<int> f = vector<int>(100000, 100);
	vector<int> g = vector<int>(1000000, 100);
	vector<int> h = vector<int>(1000000, 100);
	chrono::duration<double> time1, time2, time3, time4;

	cout << "Number of harward cores " << thread::hardware_concurrency() << endl; // Количество потоков
	cout << "\t\t" << "1000\t\t" << "10000\t" << "100000 \t" << "  1000000" << endl;

	//--------------один поток----------------------------------
	cout << "Thread 1 ";
	thread t1(TreadPlusVector, ref(a), ref(b), ref(time1), 0, 999);
	thread t2(TreadPlusVector, ref(c), ref(d), ref(time2), 0, 9999);
	thread t3(TreadPlusVector, ref(e), ref(f), ref(time3), 0, 99999);
	thread t4(TreadPlusVector, ref(g), ref(h), ref(time4), 0, 999999);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout << "\t" << time1 << " " << time2 << " " << time3 << " " << time4 << endl;
	//-------------два потока-----------------------------------
	cout << "Thread 2 ";
	chrono::duration<double> time1_1, time1_2, time2_1, time2_2, time3_1, time3_2, time4_1, time4_2;
	thread t1_1(TreadPlusVector, ref(a), ref(b), ref(time1_1), 0, 499);
	thread t1_2(TreadPlusVector, ref(a), ref(b), ref(time1_2), 500, 999);
	thread t2_1(TreadPlusVector, ref(c), ref(d), ref(time2_1), 0, 4999);
	thread t2_2(TreadPlusVector, ref(c), ref(d), ref(time2_2), 5000, 9999);
	thread t3_1(TreadPlusVector, ref(e), ref(f), ref(time3_1), 0, 49999);
	thread t3_2(TreadPlusVector, ref(e), ref(f), ref(time3_2), 50000, 99999);
	thread t4_1(TreadPlusVector, ref(g), ref(h), ref(time4_1), 0, 499999);
	thread t4_2(TreadPlusVector, ref(g), ref(h), ref(time4_2), 500000, 999999);
	t1_1.join();
	t1_2.join();
	t2_1.join();
	t2_2.join();
	t3_1.join();
	t3_2.join();
	t4_1.join();
	t4_2.join();
	cout << "\t" << time1_1 + time1_2 << " " << time2_1 + time2_2 << " " << time3_1 + time3_2 << " " << time4_1 + time4_2 << endl;
	return 0;
}
