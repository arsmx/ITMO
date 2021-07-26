#include <iostream>
#include <algorithm>
#include "buffer.cpp"


using namespace std;
int main() {
    system("chcp 65001");
    cout << "\nЗададим буфер с Capacity = 4\n" << "Добавим в конец три числа: 12, 24, 48\n";
    CCircleBuffer <int> Temp(4);
    Temp.push_back(12);
    Temp.push_back(24);
    Temp.push_back(48);
    Temp.show();

    cout << "Добавим еще два числа: 7, 9\n";
    Temp.push_back(7);
    Temp.push_back(9);
    Temp.show();

    cout << "Установим capacity = 6\n";
    cout << "Добавим два числа: 11, 13" << endl;
    Temp.resize(6);
    Temp.push_back(11);
    Temp.push_back(13);
    Temp.show();

    cout << "Установим capacity = 3\n";
    Temp.resize(3);
    Temp.show();

    cout << "Удалим крайний элемент\n";
    Temp.pop_back();
    Temp.show();

    cout << "Удалим первое число\n" ;
    Temp.show();

    cout << "Добавим в начало два числа: 15, 17\n";
    Temp.pop_front();
    Temp.push_front(15);
    Temp.push_front(17);
    Temp.show();

    cout << "Установим первое число = 23\n";
    Temp.set(Temp.begin(), 23);
    Temp.show();

    cout << "Установим крайнее число = 144\n";
    Temp.set(Temp.end() - 1, 144);
    Temp.show();

    cout << "Установим число с индексом 1 = 121\n";
    Temp.set(Temp.begin() + 1, 121);
    Temp.show();

    cout << "Применим реверс\n";
    reverse(Temp.begin(), Temp.end());
    Temp.show();

    return 0;
}