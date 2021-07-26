#include <fstream>
using namespace std;

struct root {
    root * left, * right, * parent;
    int value, balance_count = 0, height = 1;
    root() {
        value = INT32_MIN;
        left = right = parent = nullptr;
    }
};


int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n, left, right;
    fin >> n;
    if (n == 0)
        return 0;
    root* array[n];
    for (int i = 0; i < n; i++)
        array[i] = new root();
    for (int i = 0; i < n; i++) {
        fin >> array[i] -> value >> left >> right;
        if (left) {
            //в родителя запишем указатель на левого потомка
            array[i] -> left = array[left - 1]; // left - 1 т.к. в задаче нумерация от единицы
            //в левого потомка запишем указатель на родителя
            array[left - 1] -> parent = array[i];
        }
        if (right) {
            array[i] -> right = array[right - 1];
            array[right - 1] -> parent = array[i];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        //проходим дерево снизу вверх
        int max_height = 0; //тут храним максимальную высоту
        if (array[i] -> right) {
            array[i] -> balance_count = array[i] -> right -> height;
            //в счетчик баланса запишем высоту правой ветви
            if (array[i] -> right -> height > max_height)
                //если высота ветви больше максимальной, то запишем ее в максимальную
                max_height = array[i] -> right -> height;
        }
        if (array[i] -> left) {
            array[i] -> balance_count -= array[i] -> left -> height;
            //от счетчика баланса отнимаем высоту левой ветви
            //баланс = расстояние между правой и левой ветвями
            if (array[i] -> left -> height > max_height)
                //сохраняем максимальную высоту
                max_height = array[i] -> left -> height;
        }
        array[i] -> height = max_height + 1;
    }
    for (int i = 0; i < n; i++) {
        fout << array[i] -> balance_count << '\n';
    }
}