//#include <future>
//#include <iostream>
//#include <random>
//#include <algorithm>
//#include <vector>
//
//using namespace std;
//
//int main()
//{
//    srand(static_cast<unsigned int>(time(0)));
//
////----------Create vector and fill. Print this------------------
//    vector<int> v;
//    for (int i{}; i < 10; i++) {
//        v.push_back(rand() % 100);
//    }
//    for (auto& v : v)
//        cout << v << " ";
//    cout << "\n\n";
//
//    auto Lymda_Future = [&v](int i, promise<int> p_int) {
//        int min = i;
//        for (int j = i + 1; j < v.size(); j++) {
//            if (v[j] < v[min]) {
//                min = j;
//            }
//        }
//        p_int.set_value(min);   //возращаем минимальный индекс
//        };
//
////-------------Запускаем основной цикл поиска------------------
//    for (int i{}; i < v.size() - 1; i++) {
//        promise<int> p_int;
//        future<int> future_result = p_int.get_future();
//        async(launch::async, Lymda_Future, i, std::move(p_int));
//        int min = future_result.get();
//        if (i != min)
//            swap(v[i], v[min]);         //если индексы не равны то меняем
//    }
//
////---------------Печатаем что получилось------------------
//    for (auto& v : v)
//        cout << v << " ";
//    cout << "\n";
//
//    return 0;
//}

#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
using namespace std;

// Class that represents a simple thread pool 
class ThreadPool {
public:
	// // Constructor to creates a thread pool with given 
	// number of threads 
	ThreadPool(size_t num_threads
		= thread::hardware_concurrency())
	{

		// Creating worker threads 
		for (size_t i = 0; i < num_threads; ++i) {
			threads_.emplace_back([this] {
				while (true) {
					function<void()> task;
					// The reason for putting the below code 
					// here is to unlock the queue before 
					// executing the task so that other 
					// threads can perform enqueue tasks 
					{
						// Locking the queue so that data 
						// can be shared safely 
						unique_lock<mutex> lock(
							queue_mutex_);

						// Waiting until there is a task to 
						// execute or the pool is stopped 
						cv_.wait(lock, [this] {
							return !tasks_.empty() || stop_;
							});

						// exit the thread in case the pool 
						// is stopped and there are no tasks 
						if (stop_ && tasks_.empty()) {
							return;
						}

						// Get the next task from the queue 
						task = move(tasks_.front());
						tasks_.pop();
					}

					task();
				}
				});
		}
	}

	// Destructor to stop the thread pool 
	~ThreadPool()
	{
		{
			// Lock the queue to update the stop flag safely 
			unique_lock<mutex> lock(queue_mutex_);
			stop_ = true;
		}

		// Notify all threads 
		cv_.notify_all();

		// Joining all worker threads to ensure they have 
		// completed their tasks 
		for (auto& thread : threads_) {
			thread.join();
		}
	}

	// Enqueue task for execution by the thread pool 
	void enqueue(function<void()> task)
	{
		{
			unique_lock <std::mutex> lock(queue_mutex_);
			tasks_.emplace(move(task));
		}
		cv_.notify_one();
	}

private:
	// Vector to store worker threads 
	vector<thread> threads_;

	// Queue of tasks 
	queue<function<void()> > tasks_;

	// Mutex to synchronize access to shared data 
	mutex queue_mutex_;

	// Condition variable to signal changes in the state of 
	// the tasks queue 
	condition_variable cv_;

	// Flag to indicate whether the thread pool should stop 
	// or not 
	bool stop_ = false;
};

int main()
{
	// Create a thread pool with 4 threads 
	ThreadPool pool(4);

	// Enqueue tasks for execution 
	for (int i = 0; i < 25; ++i) {
		pool.enqueue([i] {
			cout << "Task " << i << " is running on thread "
				<< this_thread::get_id() << endl;
			// Simulate some work 
			this_thread::sleep_for(
				chrono::milliseconds(300));
			});
	}

	return 0;
}

