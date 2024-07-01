#include <vector>
#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <thread>

//using namespace std;

////void f(int& data) {
////	data += 1;
////}
////
////template<class Iter, class Func>
////void ParallelForEach(Iter first, Iter last, Func f) {
////
////	unsigned long long length = distance(first, last);
////
////	if (!length)
////		return;
////
////	if (length < 2) {
////		for_each(first, last, f);
////	}
////	else {
////		Iter mid = first + length / 2;
////		future<void> result = async(&ParallelForEach<Iter, Func>, first, mid, f);
////		ParallelForEach(mid, last, f);
////		result.get();
////	}
////
////}
//void f(vector<int>::iterator& i) {
//    *i += 2;
//    i++;
//}
//
////template<class Iter,class Func>
////void ForE(Iter begin, Iter end, Func f) {
////    while (begin!=end)
////    {
////        f(begin);
////    }
////}
//
//
//template<class Iter>
//void ForE(Iter begin, Iter end, void (*FUN)(vector<int>::iterator, vector<int>::iterator)){
//    FUN(begin, end);
//}
//
//int main()
//{
//    //------------заполняем вектор-------------------------
//    vector<int> v(11, 2);
//    for (auto& i : v)
//        cout << i << " ";
//    cout << "\n\n";
//
//    auto Lymda = [](vector<int>::iterator begin, vector<int>::iterator end) {
//        while (begin != end)
//            f(begin);
//        };
//
//    //ParallelForEach(v.begin(), v.end(), f);
//    ForE(v.begin(), v.end(), Lymda);
//
//    for (auto& i : v)
//        cout << i << " ";
//    cout << "\n\n";
//
//    return 0;
//}

std::vector<int> data;
std::condition_variable data_cond;
std::mutex m;

void thread_func1()
{
	std::cout << "000000000\n";
	std::unique_lock <std::mutex> lock(m);
	data.push_back(10);
	data_cond.notify_one();
	data.push_back(20);
	std::cout << "111111111\n";
}

void thread_func2()
{
	std::cout << "22222222222\n";
	std::unique_lock<std::mutex> lock(m);
	data_cond.wait(lock, false/*[] {
		return !data.empty();
		}*/);
	std::cout << data.back() << std::endl;
	std::cout << data.front() << std::endl;
}

int main()
{
	std::thread th1(thread_func1);
	std::thread th2(thread_func2);
	th1.join();
	th2.join();
}
