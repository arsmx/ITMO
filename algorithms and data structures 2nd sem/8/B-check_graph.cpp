#include <fstream>
using namespace std;

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  
  int n;
  fin >> n;
  int m[n][n];

  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++) 
      fin >> m[i][j];
  // n - размерность матрицы 
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++)  // i==j - проверка на соединение вершины самой с собой - петли
      if (m[i][j] == 1) // для каждой ячейки матрицы проверяем, одинаково ли значение в противоположной стороне
        if (m[j][i] != 1 || i == j) { // с противоположной стороны - она должна быть отражена по 
          fout << "NO"; // главной диагонали, главная диагональ должна быть нулевая
          return 0;
        }

  fout << "YES";
  return 0;
}