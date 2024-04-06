#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class SumCount {
private:
    int count{};
    int sum{};
public:
    void operator()(int val) {
        if (!(val % 3)) {
            count++;
            sum += val;
        }
    }
    int get_sum() {
        return sum;
    }
    int get_count() {
        return count;
    }
};

int main()
{
    //через лямбду проще но надо две лишние переменные [&count,&sum](int val){if (!(val % 3)) {count++;sum += val;}}
    //функтор конечно удобен тем что хранит данные в полях класса
    setlocale(LC_ALL, "rus");
    vector<int> vec{ 4,1,3,6,25,54 };
    /*int count{}, sum{};*/
    /*for_each(vec.cbegin(), vec.cend(), [&count, &sum](int val) {if (!(val % 3)) { count++; sum += val; }}); 
    cout << sum << endl; //но красивее лямбда)))))
    cout << count;*/
    SumCount s = for_each(vec.cbegin(), vec.cend(), SumCount());
    cout << s.get_sum() << endl;
    cout << s.get_count();          
    return 0;
}

