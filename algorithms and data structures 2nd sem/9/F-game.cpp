#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
 
void deep_first_search(int start, vector<vector<int>> & Binds, vector<int> & result) {
    for (int i = 0; i < Binds[start].size(); i++) { // проверяем смежные вершины
        int connected = Binds[start][i];
        if (result[connected] == -1) // если ее еще не проверяли запускаем поиск от нее
          deep_first_search(connected, Binds, result);
    }

    for (int i = 0; i < Binds[start].size(); i++) { // проверяем смежные вершины
        int connected = Binds[start][i];
        result[start] = max(result[start], (result[connected] + 1) % 2); // 0 => 1; 1 => 0; -1 => 0;
    } // значение стартовой позиции = большее из (-1 и смежной инвертированной)
    if (result[start] == -1)
      result[start] = 0; // только для вершины у которой нет выхода - нет смежных
}
 
int main() {
    ifstream fin("game.in");
    ofstream fout("game.out");

    int n, m, start_pos, x, y;
    fin >> n >> m >> start_pos;
    vector <vector<int>> Binds(n);
    vector<int> result(n, -1); // вектор ответов состоит из количества вершин, заполнен -1

    for (int i = 0; i < m; i++) { // от нуля до количества ребер вводим каждое ребро
        fin >> x >> y;
        Binds[--x].push_back(--y);
    }

    deep_first_search(--start_pos, Binds, result); // запускаем поиск от стартовой позиции фишки

    switch (result[start_pos]) { // если вектор результата на стартовой позиции содержит 1 - выиграл 1
    case 1:
      fout << "First player wins";
      return 0;
    }
    fout << "Second player wins"; 
    return 0;
}
