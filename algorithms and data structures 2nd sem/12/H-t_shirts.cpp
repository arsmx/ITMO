#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n; 
  vector <int> colors(n); //вектор с цветами
  vector<vector <long long>> result (n, vector<long long>(n));  // ответ n на n
 
  for (int i = 0; i < n; i++) {
    cin >> colors[i]; 
    result[i][i] = 1; //диагональ заполняем единицами
  }

  for (int length = 1; length < n; length++) //для всей длины последовательности
    for (int i = 0; i + length < n; i++) {
      long long tmp = i + length;
      if (colors[i] != colors[tmp])
	  	result[i][tmp] = (result[i + 1][tmp] + result[i][tmp - 1] - result[i + 1][tmp - 1] + 1000000000) % 1000000000;
      else
	  	result[i][tmp] = (result[i + 1][tmp] + result[i][tmp - 1] + 1) % 1000000000;
    }

  cout << result[0][n - 1] % 1000000000 << "\n"; //вывод правой верхней ячейки
  return 0;
}