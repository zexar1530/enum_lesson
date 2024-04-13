
#include <iostream>
#include <vector>

using namespace std;

//template<class T>
//void Sqrt(T& t) {
//	cout << "OUT:\t" << t * t << endl;
//}
//template<>
//void Sqrt(vector<int>& vec) {
//	for (auto& v : vec) { v = v * v; }
//}

template<class Type> Type Sqrt(Type& val) {
	return val * val;
}

template<class TypeVector> vector<TypeVector> Sqrt(vector<TypeVector>& vec) {
	vector<TypeVector> vec_new;
	for (int i{}; i<vec.size(); i++) {
		vec_new.push_back(vec.at(i) * vec.at(i));
	}
	return vec_new;
}

template<class T> T Func(T& t) {			//Почему не разрешает вернуть ссылку T&?
	return{ Sqrt(t) };
}


int main()
{
	/*cout << "IN:\t" << 4 << "\n";
	int i{ 4 };
	Sqrt(i);
	vector<int> vec{ -1, 4, 8 };
	cout << "IN:\t";
	for (auto v : vec) { cout << v << " "; };
	cout << endl;
	Sqrt(vec);
	cout << "OUT:\t";
	for (auto v : vec) { cout << v << " "; };
	return 0;*/

	cout << "IN:\t" << 4 << "\n";
	int i{ 4 };
	auto res{ Func(i) };
	cout << "OUT:\t" << res << endl;
	vector<int> vec{ -1, 4, 8 };
	cout << "IN:\t";
	for (const auto v : vec) { cout << v << " "; };
	cout << endl;
	auto res_vec{ Func(vec) };
	cout << "OUT:\t";
	for (auto v : res_vec) { cout << v << " "; };
	return 0;
}

