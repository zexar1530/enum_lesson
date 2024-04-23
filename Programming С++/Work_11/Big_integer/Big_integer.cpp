#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigInteger {
private:
    vector<unsigned int> digit;         //вектор положительного числа из чисел. со знаком большого числа заморачиваться не буду)
public:
    BigInteger() {};                                                        //пустой конструктор
    BigInteger(string str) {
        for (auto it{ str.begin() }; str.end() != it; it++) {
            digit.push_back(((unsigned int)*it) - ((unsigned int)'0'));   //переводим в vector
        }
        reverse(digit.begin(), digit.end());
    }

   BigInteger(const BigInteger& copy){
       cout << "Конструктор копирования\n";
       digit = copy.digit;
   }

   BigInteger(BigInteger&& moved) noexcept {     //конструктор перемещения
       this->digit = move(moved.digit);
       cout << "Конструктор перемещения\n";
   }

   BigInteger& operator = (BigInteger&& moved) noexcept { //перемещающий оператор
       cout << "Оператор перемещения\n";
       this->digit = move(moved.digit);
    //   *this = move(moved);
       return *this;
   }

   BigInteger& operator = (BigInteger& copy) {      //копирующий оператор сделал как перемещающийся
       cout << "Оператор копирования\n";            //не получается вызвать оператор перемещения((((
       this->digit = move(copy.digit);              //Неужели постоянно надо использовать move для
       return *this;                                //преобоазования lvalue в rvalue?
   }

   BigInteger operator+ (const BigInteger& a) {
       unsigned int flag{};
       unsigned int tmp{};
       BigInteger temp;
       for (size_t i{ }; i < (digit.size() > a.digit.size() ? digit.size() : a.digit.size()); i++){
           if (i >= digit.size())
               tmp = flag + 0 + a.digit[i];
           else if (i >= a.digit.size())
               tmp = flag + digit[i] + 0;
           else
               tmp = flag + digit[i] + a.digit[i];

           flag = tmp / 10;
           tmp = tmp % 10;
           temp.digit.push_back(tmp);
       }
       if (flag != 0)temp.digit.push_back(flag);
       return temp;
   }

   vector<unsigned int> getVec() const {
       return digit;
   }

   ~BigInteger() {}
};

ostream& operator<<(ostream& strm, const BigInteger& a) {
    auto vec = a.getVec();
    reverse(vec.begin(), vec.end());
    string str;
    for (auto value : vec) {
        str += to_string(value);
    }
    strm << str;
    return strm;
}

int main()
{
    setlocale(LC_ALL, "rus");
    BigInteger a("114575");
    BigInteger b{ "78524" };
    auto c = a + b;
    cout << c << endl;
    BigInteger x("114575");
    BigInteger y;
    y = std::move(x);
    return 0;
  
}

