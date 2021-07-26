#include <fstream>
#include <vector>
using namespace std;

 
void deep_first_search(int start, vector<vector<int>> & Binds, vector<int> & count, bool & check) {
	// check - ответ задания - двудольный или нет
  for (int i = 0; i < Binds[start].size(); i++) {
    int connected = Binds[start][i];
    if (count[connected] == -1) {
      if (count[start] == 1)
        count[connected] = 2; // назначаем индекс 2
      else
        count[connected] = 1;
      deep_first_search(connected, Binds, count, check);
    }
    else if (count[connected] == count[start]) {
      check = false; // 
      break;
    }
  }
}
 
int main() {
  ifstream fin("bipartite.in");
  ofstream fout("bipartite.out");
  bool check = true; // будущий ответ
  int n, m, x, y;
  fin >> n >> m;
  vector<vector<int>> Binds(n); //тут хранится граф
  vector<int> count(n, -1); //пометка 1 или 2
 
  for (int i = 0; i < m; i++) {
    fin >> x >> y; //начало и конец ребра
    Binds[--x].push_back(--y);
    Binds[y].push_back(x);
  }

  for (int i = 1; i < Binds.size(); i++)
    if (count[i] == -1) { //для каждой непомеченой вершины поиск в глубину
      count[i] = 1;
      deep_first_search(i, Binds, count, check);
    }

  if (check)
    fout << "YES"; //если check так и остался true, то двудольный
  else
    fout << "NO"; //иначе не двудольный
  return 0;
}