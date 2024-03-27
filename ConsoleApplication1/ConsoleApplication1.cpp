
//#include <iostream>
//#include <fstream>
//#include <stack>
//
//using namespace std;
//
//void Dfs(int** graph, int* arr, int ver, int size, stack<int>& res);
//
//int main() {
//    setlocale(LC_ALL, "rus");
//    int size{};
//    ifstream in("in.txt");
//    in >> size;
//    int** graph = new int* [size] {}; //граф
//    int* arr{ new int[size] {} };     //массив посещенных вершин
//    for (int j{}; j < size; j++)       //Создаем массив
//        graph[j] = new int[size] {};
//    for (int i{}; i < size; i++)        //заполняем массив
//        for (int j{}; j < size; j++)
//            in >> graph[i][j];
//    in.close();                         //закрываем файл
//
//    cout << "Порядок обхода вершин: ";
//    stack<int> res;
//
//    for (int i{}; i < size; i++) {
//        if (arr[i]==0) 
//            Dfs(graph, arr, i, size, res);
//    }
//
//    while (!res.empty()) {
//        cout << res.top() << " ";
//        res.pop();
//    }
//
//    //-------------------освоббождаем память-----------------------
//    delete[] arr;
//    for (int i{}; i < size; i++)
//        delete[] graph[i];
//    delete[] graph;
//    return 0;
//}
//
//void Dfs(int** graph, int* arr, int ver, int size, stack<int>& res)
//{
////    cout << ver + 1 << " ";
//    arr[ver] = 1;
//    for (int i{}; i < size; i++) {
//        if ((graph[ver][i] != 0)&&(!arr[i])) {
//            Dfs(graph, arr, i, size, res);
//        }
//    }
//    res.push(ver + 1);
//}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MyStruct
{
    string name;
    int score;
};

//bool comparator(const MyStruct& l, const MyStruct& r) {
//    return l.score > r.score;
//}

int main()
{
    vector<MyStruct> vec{ {"Alex", 55},{"Igor", 87},{"Alena", 69} };
    sort(vec.begin(), vec.end(), [](const MyStruct& a, const MyStruct& b) {return a.score > b.score; });
    for (const auto& v : vec) cout << v.name << " " << v.score << endl;
    return 0;
}
