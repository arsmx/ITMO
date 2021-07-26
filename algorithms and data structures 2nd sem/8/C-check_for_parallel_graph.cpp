#include <fstream>
using namespace std;

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  
  int n, m, row, col;
  fin >> n >> m;
  int matrix[n][n];
  // обнуляем пустую матрицу
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  for (int i = 0; i < m; i++) {
    fin >> row >> col; // проверка, содержит ли граф хоть одно параллельное ребро
    if (matrix[row - 1][col - 1] == 1 || matrix[col - 1][row - 1] == 1) { // - если мы уже записывали ребро
      fout << "YES"; // с этими вершинами и записываем еще раз - выдаем ответ да
      return 0;
    }
    matrix[row - 1][col - 1] = 1;
  }

  fout << "NO";
  return 0;
}