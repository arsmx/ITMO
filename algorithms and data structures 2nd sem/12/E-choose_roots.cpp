#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> list; //вектор с графом
vector<vector<int>> length;  //вектор с расстояниями

void DepthFirstSearch(int current) { //для текущего элемента
  length[current][0] = 0;  //отмечаем рекурсивно для всех вершин length
  length[current][1] = 1;

  for (int i = 0; i < list[current].size(); i++)
    DepthFirstSearch(list[current][i]); //проходим по всем рекурсивно

	//от предпоследних снизу вершин слева направо идем по всем смежным с ними вершинам и записываем в
	 //length[current][1] - значение length[смежной вершины][0], а в length[current][1] - максимум из length[1] и length[0] смежной вершины
  
  for (int i = 0; i < list[current].size(); i++) { // добавляем к весу вершины сумму весов допустимых поддеревьев внуков
    length[current][1] += length[list[current][i]][0];
    length[current][0] += max(length[list[current][i]][0], length[list[current][i]][1]); //max(length[смежная вершина][0], length[смежная вершина][1])
  }
}

int main() {
  int n, num = 0, root = 0, value;
  cin >> n; //количество вершин
  list.resize(n); //задаем размер n
  length.resize(n, vector<int>(2)); //размер n, в ширину 2

  for (int i = 0; i < n; i++) {
    cin >> value; //номер предка
    if (value) //запись смежности
      list[value - 1].push_back(i);
    else
		root = i; //запись корня
  }

  DepthFirstSearch(root); //поиск в глубину от корня
  cout << max(length[root][0], length[root][1]); //выводим для корня максимум из его length[1] и length[0]
  return 0;
}