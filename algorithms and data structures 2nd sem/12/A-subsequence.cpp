#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    long long n, max_count = 0, max_pos;
    cin >> n;
    vector<long long> list(n), count(n, 1), prev(n, -1), result;
    for (long long i = 0; i < n; i++) {
        cin >> list[i]; // вводим
        if (n == 1) { // если один элемент, его и выводим
            cout << 1 << "\n" << list[i];
            return 0;
        }
        for (long long j = 0; j < i; j++) // если предыдущий элемент меньше этого
            if (list[j] < list[i] and (1 + count[j] > count[i])) { // и его длина последовательности
                count[i] = 1 + count[j]; // больше чем текущая, то назначаем его длину + 1
                prev[i] = j; // запоминаем предыдущий к текущему
                if (count[i] > max_count) { // сохраняем максимальную длину последовательности
                    max_count = count[i]; // и позицию ее последнего элемента
                    max_pos = i;
                }
            }
 
    }
    cout <<"\n" << max_count << "\n"; // выводим макс длину
    while (max_pos != -1) { // начиная с последнего элемента ПОДпоследовательности, до первого
        result.push_back(list[max_pos]); // добавляем в ответ крайний элемент
        max_pos = prev[max_pos]; // переназначаем крайним предыдущий к нему
    }
    reverse(result.begin(), result.end()); // разворачиваем вектор ответа
    for (long long i : result) // и выводим
        cout << i << " ";
    return 0;
}