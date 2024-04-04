
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//вывод сделал двумя способами, можно сделать и через Std::function.
//Хотел узнать ваше мнение какой способ предпочтительнее?

int main()
{
    setlocale(LC_ALL, "rus");

    auto print = [](int& vec) {if ((vec % 2) == 0) cout << vec << " ";
    else {
        vec *= 3;
        cout << vec << " ";
    }
        };

    vector<int> v{ 4, 7, 9, 14, 12 };

    cout << "Входные данные: ";
    for (auto& vec : v) { cout << vec << " "; };

    cout << endl << "Выходные данные: ";
    for_each(v.begin(), v.end(), [](int& vec) {if ((vec % 2) == 0) cout << vec << " ";
        else cout << vec * 3 << " "; });

    cout << endl << "Выходные данные: ";
    for_each(v.begin(), v.end(), print);

    return 0;
}

