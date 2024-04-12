#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

/*два вопроса
* почему не работает с простым map?
* как можно сделать проще))))? неужели что бы отсортировать надо копировать в вектор.
* Неужели никак нельзя map<char, int, std::less> применить к [Value]
*/ 

int main()
{
    string str;
    cout << "IN: ";
    getline(cin, str);
    cout << "OUT:\n";
    unordered_map<char, int> c;
    for (const auto& s : str) {
        c[s]++;
    }
    vector<pair<char, int>> vec(c.begin(), c.end());
    sort(vec.begin(), vec.end(), [](pair<char, int> a, pair<char, int> b) {return a.second > b.second; });
    for (const auto& val_key : vec) {
        cout << val_key.first << " : " << val_key.second << endl;
    }

    cout << "-------------------------------------------------------------------------------" << endl;
    set<int, greater<int>> arr;
    cout << "IN: ";
    int i{}, count{};
    cin >> count;
    while (count) {
        cin >> i;
        arr.insert(i);
        count--;
    }
    cout << "OUT:\n";
    for (auto& val : arr) {
        cout << val << endl;
    }
    return 0;
}

