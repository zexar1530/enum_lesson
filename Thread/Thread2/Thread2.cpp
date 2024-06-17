#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Plus {
public:

	Plus(int core, vector<int>& a, vector<int>& b) :core(core), a(a), b(b) {
		//создаем массив векторов Thread
		//сразу делаем обработку на количество ядер
		int end = (int)a.size();
		int div{ end / core };
		int next{}, next1{};
		for (int i{}; i < core; i++) {
			next1 += div;
			t.push_back(thread(&Plus::startThread, this, ref(a), ref(b), next, next1));
			next += div;
		}
	}

	void startPlus() {	//Запуск наших потоков
		auto start = chrono::high_resolution_clock::now();
		for (auto& t : t) {
			t.join();
		}
		auto fin = chrono::high_resolution_clock::now();
		time = fin - start;
		cout << "\t" << time;
	}
protected:
	void startThread(vector<int>& a, vector<int>& b, int begin, int end) {
		vector<int> temp;
		for (; begin < end; begin++) {
			temp.push_back(a.at(begin) + b.at(begin));
		}
	}

private:
	vector <thread> t;	//vector потоков
	chrono::duration<double> time{}; // time
	int core{};  //количество потоков
	vector<int> a;
	vector<int> b;
};

void TreadPlusVector(vector<int>& a, vector<int>& b, chrono::duration<double>& time, int begin, int end) {
	auto start = chrono::high_resolution_clock::now();
	vector<int> c;
	for (; begin <= end; begin++) {
		c.push_back(a.at(begin) + b.at(begin));
		//a.at(begin) + b.at(begin);
	}
	auto fin = chrono::high_resolution_clock::now();
	time = fin - start;
}

int main()
{
						// Исходные данные
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
	cout << "    \t" << "\t1000" << "\t\t10000" << "\t\t100000" << "\t\t1000000" << endl;

	//--------------один поток----------------------------------
	cout << "Thread 1";
	thread t1(TreadPlusVector, ref(a), ref(b), ref(time1), 0, 999);
	thread t2(TreadPlusVector, ref(c), ref(d), ref(time2), 0, 9999);
	thread t3(TreadPlusVector, ref(e), ref(f), ref(time3), 0, 99999);
	thread t4(TreadPlusVector, ref(g), ref(h), ref(time4), 0, 999999);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout << "\t" << time1 << "\t" << time2 << "\t" << time3 << "\t" << time4 << endl;
	//-------------два потока-----------------------------------
	cout << "Thread 2";
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
	cout << "\t" << time1_1 + time1_2 << "\t" << time2_1 + time2_2 << "\t" << time3_1 + time3_2 << "\t" << time4_1 + time4_2 << endl;
	//------четыре потока новым петодом через вектор потоков---------------------------------
	cout << "Thread 4";
	Plus plus4_1(4, a, b);
	plus4_1.startPlus();
	Plus plus4_2(4, c, d);
	plus4_2.startPlus();
	Plus plus4_3(4, e, f);
	plus4_3.startPlus();
	Plus plus4_4(4, g, h);
	plus4_4.startPlus();
	cout << endl;
	//------Восемь потоков новым петодом через вектор потоков---------------------------------
	cout << "Thread 8";
	Plus plus8(8, a, b);
	plus8.startPlus();
	plus8 = Plus(8, c, d);
	plus8.startPlus();
	plus8 = Plus(8, e, f);
	plus8.startPlus();
	plus8 = Plus(8, g, h);
	plus8.startPlus();
	cout << endl;
	//--------------------Ну и 16 потоков---------------------------------------------------
	cout << "Thread 16";
	Plus plus16(16, a, b);
	plus16.startPlus();
	plus16 = Plus(16, c, d);
	plus16.startPlus();
	plus16 = Plus(16, e, f);
	plus16.startPlus();
	plus16 = Plus(16, g, h);
	plus16.startPlus();
	cout << endl;
	return 0;
}
