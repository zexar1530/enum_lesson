#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Observer {			//Наблюдатель интерфейс
public:
	virtual void onWarning(const string& message) {};
	virtual void onError(const string& message) {};
	virtual void onFatalError(const string& message) {};
};

class Observed {			//Наблюдаемый
private:
	vector<Observer*> observers; //вектор указателей на наблюдателя
public:
	~Observed() {
		for (auto observe : observers) {
			delete observe;					//у меня здесь вопрос????
			observe = nullptr;				//может тут можно без delete, достаточно присвоить nullptr? 
		}									//конечно так vector<shared_ptr<Observer>> было бы проще))))
	}

	void Add(Observer* observer) {
		observers.push_back(observer);
	}

	void warning() {
		for (auto observer : observers) {
			observer->onWarning("Warning");
		}
	}

	void error() {
		for (auto observer : observers) {
			observer->onError("Error");
		}
	}

	void fatalError() {
		for (auto observer : observers) {
			observer->onFatalError("FatalError");
		}
	}
};

//Наблюдатель консоль
class Console : public Observer {
public:
	void onWarning(const string& message) override {
		cout << message << endl;
	}
};
//файл
class File : public Observer {
private:
	fstream file;
public:
	File(const string& fname) {
		file.open(fname, fstream::app);
		if (!file.is_open()) {
			throw runtime_error("Can't open file");
		}
	}

	~File() {
		file.close();
	}

	void onError(const std::string& message) override {
		file << message;
	}
};
//консоль - файл
class FatalError : public Observer {
private:
	fstream file;
public:
	FatalError(const string& fname) {
		file.open(fname, fstream::app);
		if (!file.is_open()) {
			throw runtime_error("Can't open file");
		}
	}

	~FatalError() {
		file.close();
	}

	void onFatalError(const std::string& message) override {
		cout << message << endl;
		file << message;
	}
};

int main() {
	try {
		//создаем наблюдаемый обьект
		Observed observed;
		//добавляем указателей на наблюдателей
		observed.Add(new Console());
		observed.Add(new File("file1.txt"));
		observed.Add(new FatalError("file2.txt"));
		//уведомляем наблюдателей
		observed.fatalError();
		observed.warning();
		observed.error();
	}
	catch (runtime_error& e) {
		cout << e.what();
	}

	return 0;
}