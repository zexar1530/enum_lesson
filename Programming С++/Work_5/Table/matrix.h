#pragma once

using namespace std;

template<class T>
class Array {
public:
    Array(int row = 0, int col = 0) :row{ row }, col{ col } {           //�����������
        pp_array = new T * [row];
        for (int i{}; i < row; ++i)
            pp_array[i] = new T[col];
    }
    Array(const Array<T>&) = delete;   //������� ����������� �����������. �� ����������� ���������� =
    Array(Array<T>&& mov) {             //����������� ��������
        this->col = mov.col;
        this->row = mov.row;
        pp_array = move(copy.pp_array);
    }
    ~Array() {
        for (int i{}; i < row; ++i)                                     //����������
            delete[] pp_array[i];
        delete[] pp_array;
    }

    class Proxy {                                                       //��������� �����(��������)
    public:
        Proxy(T* p_array, int col) : p_array{ p_array }, col{ col } { }                        //����������� ������ ���������� ������. �������� ��������� �� �������
                                                                        
        T& operator[](int index) {
            if (index >= col) throw runtime_error("����� �� ������� ������� (�������)");
            return p_array[index];              //��������� ������ �� ������ ���������� ����
        }
    private:
        T* p_array; //���������� ������ �� �����, ��� ��� ������ ����� �� ��������, ���� ����� � � �� ����????
        int col{};                                                    
    };
    Array<T>& operator = (const Array<T>& copy) {          //����������� =
        if (this != &copy) {
            for (int i{}; i < row; i++)
                delete[] pp_array[i];
            delete[] pp_array;                      //������� ������ ������
            this->col = copy.col;
            this->row = copy.row;                   //������������� ����� ������ � ������
            pp_array = new T * [row];
            for (int i{}; i < row; i++)
                pp_array[i] = new T[col];         //������� ����� ������
            for (int i{}; i < row; i++)
                for (int j{}; j < col; j++)
                    this->pp_array[i][j] = copy.pp_array[i][j];     //�������� ������
            return *this;
        }
        return *this;
    }
    Proxy operator[](int index) {
        if (index >= row) throw runtime_error("����� �� ������� ������� (������)");
        return Proxy(pp_array[index], col);  //������� �������� � ����������� ��������� �� �������(������ ������). ����� ������ ������� Proxy
    }                                   //����� ��� Proxy[index] � ��������� T&

private:
    int row{}, col{};                   //������, ������� �������
    T** pp_array;                       //��� ��������� ������
};

