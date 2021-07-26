#include <fstream>
#include <vector>
using namespace std;

void deep_first_search(vector<vector<int>> const & Binds, vector<int> & result, vector<bool> & count, int start) {
	// result - отсортированные от конца к началу - исходу
  count[start] = true;
  for (int i = 0; i < Binds[start].size(); i++) {
    int connected = Binds[start][i];
    if (!count[connected]) 
      deep_first_search(Binds, result, count, connected);
  }
  result.push_back(start);
}

void flip_deep_first_search(vector<vector<int>> & flip_Binds, vector<int> & comps, vector<bool> & count, int & comps_count, int start) {
	// вектор comps - для каждой вершины храним номер компоненты, к которой она принадлежит
  count[start] = true; // вершина посещена
  comps[start] = comps_count; // присваиваем номер компоненты сильной связанности
  for (int i = 0; i < flip_Binds[start].size(); i++) { // для всех смежных
    int connected = flip_Binds[start][i];
    if (count[connected] == false) // рекурсивно обходим до тупика
      flip_deep_first_search(flip_Binds, comps, count, comps_count, connected);
  }
}

int main() {
  ifstream fin("cond.in");
  ofstream fout("cond.out");
  int n, m, x, y; 
  fin >> n >> m;
  vector<vector<int>> Binds(n);
  vector<vector<int>> flip_Binds(n);
  vector<int> comps(n);
  vector<int> result;
  vector<bool> count(n, false);

  for (int i = 0; i < m; i++) {
    fin >> x >> y;
    Binds[--x].push_back(--y);
    flip_Binds[y].push_back(x);
  }
  
  for (int i = 0; i < n; i++) 
    if (count[i] == false) 
      deep_first_search(Binds, result, count, i);
  count.assign(n, false);
  int comps_count = 1;

  for (int i = 0; i < n; i++) {
    int start = result[n - i - 1]; //инвертированный порядок вершин, начинаем с последней
    if (count[start] == false) { // если не посещали
      flip_deep_first_search(flip_Binds, comps, count, comps_count, start);
      comps_count++; // запускаем перевернутый поиск и всем смежным назначаем данный номер компоненты
    }
  }
  
  fout << --comps_count << "\n"; // вычитаем одну, так как прибавили после крайнего поиска
  for (int i : comps)
    fout << i << " ";
  return 0;
}