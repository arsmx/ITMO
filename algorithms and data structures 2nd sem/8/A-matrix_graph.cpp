#include <fstream>
using namespace std;

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  
  int n, m;
  fin >> n >> m;
  int matrix[n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  int row, col;
  for (int i = 0; i < m; i++) { // вводим каждое из ребер
    fin >> row >> col; // в нужной ячейке ставим единицу
    matrix[row - 1][col - 1] = 1; 
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fout << matrix[i][j] << " ";
    }
    fout << '\n';
  }
  return 0;
}