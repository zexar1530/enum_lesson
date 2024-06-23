#include <future>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

//----------Create vector and fill. Print this------------------
    vector<int> v;
    for (int i{}; i < 10; i++) {
        v.push_back(rand() % 100);
    }
    for (auto& v : v)
        cout << v << " ";
    cout << "\n\n";

    auto Lymda_Future = [&v](int i, promise<int> p_int) {
        int min = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        p_int.set_value(min);   //возращаем минимальный индекс
        };

//-------------Запускаем основной цикл поиска------------------
    for (int i{}; i < v.size() - 1; i++) {
        promise<int> p_int;
        future<int> future_result = p_int.get_future();
        async(launch::async, Lymda_Future, i, std::move(p_int));
        int min = future_result.get();
        if (i != min)
            swap(v[i], v[min]);         //если индексы не равны то меняем
    }

//---------------Печатаем что получилось------------------
    for (auto& v : v)
        cout << v << " ";
    cout << "\n";

    return 0;
}

