#include <fstream>
#include <stack>
#include <vector>
using namespace std;

bool deep_first_search(int start, vector<int> & count, vector<vector<int>> const & Binds, stack<int> & Stack) {
	// start - вершина, от которой запускаем поиск
	// count - цвет посещенных, бывает белый 0, серый 1, черный 2, становится черной когда мы нашли все смежные
	// с ней вершины
	// Binds - наш граф, не изменяем его
	// Stack - результат - полученные отсортированные вершины
  count[start] = 1; //отметили серым, как посещенное

  for (int i = 0; i < Binds[start].size(); i++) { // проходим вперед от стартовой вершины
    int connected = Binds[start][i]; // присваиваем следующую соединенную вершину
    if (!count[connected] and !deep_first_search(connected, count, Binds, Stack))
      // если не посещали ту вершину, и поиск находит, там есть цикл
      return false;
    else if (count[connected] == 1)
      return false; // если из серой в серую - значит есть цикл
    // если посещали один раз, то false
  }
  count[start] = 2; 
  Stack.push(start);
  return true; // если true - значит нет цикла
}

int main() {
  ifstream fin("topsort.in");
  ofstream fout("topsort.out");

  int n, m, x, y; // x, y - вершины ребра
  fin >> n >> m;
  vector<vector<int>> binds(n);
  stack<int> Stack;

  for (int i = 0; i < m; i++) {
    fin >> x >> y;
    binds[--x].push_back(--y);
  }
  vector<int> count(binds.size(), 0); //посещали ли мы вершину, заполнен нулями

  for (int i = 0; i < binds.size(); i++) //запускаем deep search от каждой вершины на случай наличия компонент связ > 1
    if (!count[i] and !deep_first_search(i, count, binds, Stack)) { // если не посещали, и есть цикл
      fout << -1; //!count - срабатывает только для первой проверяемой вершины
      return 0;
    } 

  for (int i = 0; i < n; i++) {
    fout << Stack.top() + 1 << " ";
    Stack.pop();
  }
  return 0;
}