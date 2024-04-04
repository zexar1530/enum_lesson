#include <string>
#include <iostream>

using namespace std;

int function(string str, int forbidden_length);

int main()
{
    setlocale(LC_ALL, "rus");
    int l{};                                            //Длинна
    string world;
    std::cout << "Введите запретную длинну: \n";
    cin >> l;
    while (true)
    {
        cout << "Введите слово: ";
        cin >> world;
        try
        {
            cout << "Длинна слова '" << world << "' равна " << function(world, l) << endl;
        }
 //       catch (const char* e) можно и так и так. Со своим классом не стал так как это в другом задании
        catch(const exception& e)
        {
 //           cout << "Выброшено исключение: " << e << endl;
            cout << "Выброшено исключение: " << e.what() << endl;
            cout << "Вы ввели слово неверной длинны! До свидания.";
            break;
        } 
    }
    return 0;
}

int function(string str, int forbidden_length)
{
    if(forbidden_length != str.length()) return str.length();   //усли не равно то возращаем длинну
//    throw "bad_length";  //если равно то выбрасываем исключение bad_length
    throw exception("bad_length");
}
