#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

class Turn
{
public:
	Turn(unsigned int);
	~Turn();
	void countClient() {
		for (int i{}; i < 10; i++) {		// 10 Clients +
			this_thread::sleep_for(1000ms);
			count++;
			cout << "Turn of client +1 " << count << endl;
		}
	};
	void countOperator() { 
		for (int i{}; i < 10; i++) {	
			this_thread::sleep_for(2000ms);
			count -= 2;
			cout << "Turn of client -2 " << count << endl;
		} 
	};

private:
	unsigned int count{};
};

Turn::Turn(unsigned int count) :count (count)  {};
Turn::~Turn() {};

int main()
{
	Turn turn{ 20 };  //20 уже в очереди
		thread t1(&Turn::countClient, ref(turn));
		thread t2([&turn]() {turn.countOperator(); }); //попробовал лямбду
		t1.join();
		t2.join();
    cout << "Hello World!\n";
	return 0;
}
