#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//перегрузил функцию через ссылку на контейнер и через итераторы
template<class T>
void print_container(const T& con) {
    for (const auto& c : con) cout << c << ", ";
    cout << endl;
}

template<class I>
void print_container(I it_b, I it_e) {
    for_each(it_b, it_e, [](const auto& c) {cout << c << ", "; });
    cout << endl;
};

int main()
{
    set<string> test_set = { "one", "two", "three", "four" };               //по ссылке контейнер
    print_container(test_set);

    list <string> test_list = { "one", "two", "three", "four" };           //через итератор
    print_container(test_list.begin(), test_list.end());

    vector<string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector);

    vector<int> test_vector_int = { 1, 2, 3, 4 };
    print_container(test_vector_int.begin(), test_vector_int.end());
    return 0;
}

