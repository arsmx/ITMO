#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> list;  //вектор графа
vector<vector<int>> length; //вектор расстояний

void DepthFirstSearch(int current) { //для текущего элемента
  for (int i : list[current])
  	DepthFirstSearch(i); //проходим по всем рекурсивно
  
  for (int i : list[current]) {
    length[current][1] += length[i][0]; // добавляем к весу вершины сумму весов допустимых поддеревьев
    length[current][0] += max(length[i][0], length[i][1]);
  }
}
int main() {
  ifstream fin ("selectw.in");
  ofstream fout ("selectw.out");
  int n, p, w, root; //кол-во вершин графа
  fin >> n; //кол-во вершин графа
  
  list.resize(n + 1); //размер на 1 больше
  length.resize(n + 1, vector<int>(2)); //размер на 1 больше, в линию размер 2

  for (int i = 1; i <= n; i++) {
    fin >> p >> w; //номер предка, число
    list[p].push_back(i);//запись смежности
    if (!p)
		root = i; //запись корня
    length[i][0] = 0; //запись в length 0 и само число
    length[i][1] = w;
  }

  DepthFirstSearch(root); //передаем корень в функцию
  fout << max(length[root][0], length[root][1]); //выводим для корня максимум из его length[1] и length[0]
  return 0;
}