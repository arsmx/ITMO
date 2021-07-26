#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> board; // вектор поля, храним в каждой ячейке количество путей, которыми в нее можно прийти
int n, m; // строк, столбцов, x - это м, y - это н

void counter(int y, int x) { // суммирует путь, запускаем с нуля, приходит к концу (но поле инвертировано)
    if (y > -1 and y < n  and x > -1 and x < m) { // если эта точка не за пределами поля
        if (y + 2 < n and x + 1 < m) { // если ход 2 вверх и 1 вправо не вышел за поле
            board[y + 2][x + 1]++; // прибавили счетчик этой ячейки, запускаем функцию от нее
            counter(y + 2, x + 1); // поиск от 2 вверх, 1 вправо
        }
        if (y + 2 < n and x - 1 < m and x - 1 >= 0) { // если ход 2 вверх и 1 влево не вышел за поле
            board[y + 2][x - 1]++;
            counter(y + 2, x - 1); // поиск от 2 вверх, 1 влево
        }
        if (y + 1 < n and x + 2 < m) {
            board[y + 1][x + 2]++;
            counter(y + 1, x + 2); // поиск от 1 вверх, 2 вправо
        }
        if (y - 1 < n and x + 2 < m and y - 1 >= 0) {
            board[y - 1][x + 2]++;
            counter(y - 1, x + 2); // поиск от 1 вниз, 2 вправо
        }
    }
}

int main() {
    ifstream fin("knight2.in");
    ofstream fout("knight2.out");
    fin >> n >> m;
    board.resize(n, vector<int> (m, 0));
    counter(0, 0);
    fout << board[n - 1][m - 1];
    return 0;
}