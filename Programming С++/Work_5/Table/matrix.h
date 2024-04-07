#pragma once

using namespace std;

template<class T>
class Array {
public:
    Array(int row = 0, int col = 0) :row{ row }, col{ col } {           //конструктор
        pp_array = new T * [row];
        for (int i{}; i < row; ++i)
            pp_array[i] = new T[col];
    }
    Array(const Array<T>&) = delete;   //удаляем конструктор копирования. На копирование перегрузим =
    Array(Array<T>&& mov) {             //конструктор переноса
        this->col = mov.col;
        this->row = mov.row;
        pp_array = move(copy.pp_array);
    }
    ~Array() {
        for (int i{}; i < row; ++i)                                     //деструктор
            delete[] pp_array[i];
        delete[] pp_array;
    }

    class Proxy {                                                       //кастомный класс(обвертка)
    public:
        Proxy(T* p_array, int col) : p_array{ p_array }, col{ col } { }                        //конструктор нашего кастомного класса. передаем указатель на колонки
                                                                        
        T& operator[](int index) {
            if (index >= col) throw runtime_error("Выход за пределы массива (столбцы)");
            return p_array[index];              //возращаем ссылку на данные шаблонного типа
        }
    private:
        T* p_array; //деструктор писать не будем, так как память здесь не выделяем, хотя может я и не прав????
        int col{};                                                    
    };
    Array<T>& operator = (const Array<T>& copy) {          //перегружаем =
        if (this != &copy) {
            for (int i{}; i < row; i++)
                delete[] pp_array[i];
            delete[] pp_array;                      //убиваем старый массив
            this->col = copy.col;
            this->row = copy.row;                   //устанавливаем новые строки и столцы
            pp_array = new T * [row];
            for (int i{}; i < row; i++)
                pp_array[i] = new T[col];         //Создаем новый массив
            for (int i{}; i < row; i++)
                for (int j{}; j < col; j++)
                    this->pp_array[i][j] = copy.pp_array[i][j];     //копируем данные
            return *this;
        }
        return *this;
    }
    Proxy operator[](int index) {
        if (index >= row) throw runtime_error("Выход за пределы массива (строки)");
        return Proxy(pp_array[index], col);  //сначала передаем в конструктор указатель на колонки(индекс строки). Затем возрат обьекта Proxy
    }                                   //затем уже Proxy[index] и возращает T&

private:
    int row{}, col{};                   //строки, колонки таблицы
    T** pp_array;                       //наш двумерный массив
};

