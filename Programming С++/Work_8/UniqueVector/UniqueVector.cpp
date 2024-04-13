#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void StringToVector(string& str, vector<int>& vec);

int main()
{
    cout << "IN: ";
    string str;
    vector<int> vec;
    getline(cin, str);
    cout << "OUT: ";
    StringToVector(str, vec);
    for (const auto& v : vec)
        cout << " " << v;
    return 0;
}

void StringToVector(string& str, vector<int>& vec)
{
    for (auto it{ str.begin() }; it != str.end(); it++) {
        if (*it == ' ') continue;                                    //если пробел то переходим к следующему
        else vec.push_back(((int)*it)-((int)'0')); //не делаю проверку на числа и считаю что все числа от 0 до 9 как в примере
    }
    sort(vec.begin(), vec.end());                       //сортируем
    auto it = unique(vec.begin(), vec.end());           //причесываем
    vec.erase(it, vec.end());                           //удаляем причесанное))))
}
