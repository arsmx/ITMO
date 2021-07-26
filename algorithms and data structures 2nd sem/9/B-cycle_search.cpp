#include <fstream>
#include <vector>
using namespace std;

vector<int> deep_first_search(vector<vector<int>> & Binds, vector<int> & count, int start) {
  count[start] = 1;
  for (int i = 0; i < Binds[start].size(); i++) {
    int connected = Binds[start][i];
    if (!count[connected]) {
      vector<int> route = deep_first_search(Binds, count, connected); // запускаем поиск от всех смежных вершин
      if (!route.empty()) { // если там не было цикла
        if (route.front() != route.back() or route.size() == 1) { // если маршрут цикла больше чем из двух элементов или из 1
          route.push_back(start); // запихиваем в маршрут старт
          return route;
        }
        else
          return route;
      }
    }
    if (count[connected] == 1) // если из серой в серую, то выводим маршрут
      return {connected, start};
  }
  count[start] = 2; // красим старт в черный, когда разобрали все смежные вершины
  return {};
}

int main() {
  ifstream fin ("cycle.in");
  ofstream fout("cycle.out");
  int n, m, x, y;
  fin >> n >> m;
  vector<vector<int>> Binds = vector<vector<int>> (n);
  for (int i = 0; i < m; i++) {
    fin >> x >> y;
    Binds[--x].push_back(--y);
  }

  vector<int> count = vector<int> (n, 0); // заполнили цвета нулями
  for (int i = 0; i < n; i++) {
    if (!count[i]) { // если вершина белая
      vector<int> route = deep_first_search(Binds, count, i); // запускаем поиск от нее
      if (!route.empty()) { // если маршрут есть 
        fout << "YES\n";
        for (int j = 1; j < route.size(); j++) // выводим маршрут по порядку с конца
          fout << route[route.size() - j] + 1 << ' ';
        return 0;
      }
    }
  }
  fout << "NO";
  return 0;
}