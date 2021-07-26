#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int main() {
    long n, length = 0;
    cin >> n; // лист - список элементов, count - возрастающая последовательность, prev - предыдущий элемент
	// position - индекс элемента, на который заканчивается оптимальная подпоследовательность, result - ответ
    vector<long> list(n), count(n + 2, LONG_MAX), prev(n, -1), position(n + 1), result;
    position[0] = -1; // для удобства вывода ответа назначаем конец равный -1
    count[0] = LONG_MIN; // нулевой эл -бесконечность, остальные +бесконечность
    for (long i = 0; i < n; i++) {
        cin >> list[i];
        if (n == 1) { // на случай одного элемента
            cout << 1 << "\n" << list[i];
            return 0;
        }
        long j = upper_bound(count.begin(), count.end(), list[i]) - count.begin(); // бинарный поиск чтобы
		// в векторе count найти первое число, которое больше либо равно текущего list[i] и обновить его
        if (count[j - 1] < list[i] and list[i] < count[j]) { // текущее число помещается между соседними count [j-1] и [j]
            count[j] = list[i]; // обновляем
            position[j] = i; // сохраняем позицию
            prev[i] = position[j - 1]; // ссылка на предыдущий элемент последовательности
            length = max(length, j); // сохраняем максимальную длину последов.
        }
    }
    cout << length << "\n"; // выводим макс длину
    long p = position[length];
    while (p != -1) { // начиная с последнего элемента ПОДпоследовательности, до первого
        result.push_back(list[p]); // добавляем в ответ крайний элемент
        p = prev[p]; // переназначаем крайним предыдущий к нему
    }
    reverse(result.begin(), result.end()); // разворачиваем вектор ответа
    for (long i : result) // и его выводим
        cout << i << " ";
    return 0;
}