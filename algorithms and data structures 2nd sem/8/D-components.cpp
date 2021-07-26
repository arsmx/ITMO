#include <fstream>
#include <vector>
using namespace std;

void DeepSearch(const vector<vector<int>>& arr, vector<int>& c, int i, int number) {
  c[i] = number; // назначаем вершине номер компоненты, к которой она принадлежит
  // далее всем связанным с ней вершинам нужно назначить этот же номер
  for (int j = 0; j < arr[i].size(); j++) {
    if (!c[arr[i][j]])
      DeepSearch (arr, c, arr[i][j], number);
  }
}

int main() {
  ifstream fin("components.in");
  ofstream fout("components.out");
  
  int n, m, start, end, count = 0; // начало и конец ребра, счет комп. связанн.
  fin >> n >> m; // кол-во вершин и ребер

  vector<vector<int>> arr(n); // создали массив графа, выделили динамическую память под кол-во вершин
  vector<int> components(n, 0); // создали массив для записи номеров компонент с длиной n, заполнили нулями

  for (int i = 0; i < m; i++) {
    fin >> start >> end; // одна и другая вершина, соединенные ребром
    arr[start - 1].push_back(end - 1);
    arr[end - 1].push_back(start - 1);
  }

  for (int i = 0; i < n; i++) {
    if (!components[i])
      DeepSearch(arr, components, i, ++count);
    // если принадлежность к компоненте еще не установлена, поиск и установка принадлежности
    // (вектор со связью вершин, вектор с компонентами, номер ребра, увеличив. кол-во компонент)
  }


  fout << count << endl; // кол-во компонент связности графа
  for (int i = 0; i < n; i++)
    fout << components[i] << " "; // номера компоненты связности
  return 0;
}