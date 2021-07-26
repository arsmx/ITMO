#include <fstream>
#include <vector>
using namespace std;

void deep_first_search(vector<vector<int>> & Binds, vector<bool> & count, vector<int> & result, int start) {
  count[start] = true;
  // Если она возвращает true, то есть до вершины можно добраться, то записываем, что мы можем посетить вершину.
  for (int i = 0; i < Binds[start].size(); i++) { // обходим рекурсивно все смежные
    int connected = Binds[start][i];
    if (count[connected] == false)
      deep_first_search(Binds, count, result, connected);
    }
    result.push_back(start);
	// result - отсортированные от конца к началу - исходу
};

bool check(vector<vector<int>> & Binds, int second, int first) {
  for (int i : Binds[second])
    if (i == first) // проверяет что вершины связаны
      return true;
  return false;
};

int main() {
  ifstream fin("hamiltonian.in");
  ofstream fout("hamiltonian.out");

  int n, m, x, y;
  fin >> n >> m;
  vector<vector<int>> Binds(n);
  vector<int> result;
  vector<bool> count(n, false);

  for (int i = 0; i < m; i++) {
    fin >> x >> y;
    Binds[--x].push_back(--y);
  }

  for (int i = 0; i < n; i++) // от каждой вершины запускаем поиск в глубину
    if (!count[i])
      deep_first_search(Binds, count, result, i);
  
  for (int i = n - 1; i > 0; i--) 
    if (!check(Binds, result[i], result[i - 1])) { // берем вершины с конца чтобы проверка была сначала
      fout << "NO"; // если больше одной компоненты связанности - пути не существует
      return 0;
    }
  
  fout << "YES";
  return 0;
}
