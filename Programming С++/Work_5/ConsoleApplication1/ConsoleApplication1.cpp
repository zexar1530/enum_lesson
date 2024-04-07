#include<iostream>

using namespace std;

template<class T>
class ArrayOfArrays {
public:
    ArrayOfArrays() {
        _arrayofarrays = new T* [10];
        for (int i = 0; i < 10; ++i)
            _arrayofarrays[i] = new T[10];
    }

    class Proxy {
    public:
        Proxy(T* _array) : _array(_array) { }

        T& operator[](int index) {
            return _array[index];
        }
    private:
        T* _array;
    };

    Proxy operator[](int index) {
        return Proxy(_arrayofarrays[index]);
    }

private:
    T** _arrayofarrays;
};
int main()
{
    ArrayOfArrays<float> arr; 
    auto val{ arr[3][2] };
    cout << val<<endl;
    arr[3][2] = 5.1;
    cout << arr[3][2];
    return 0;
}