#include <fstream>
#include <vector>
using namespace std;

vector<int> prefix_function(string strings) {
  vector<int> result (strings.length(), 0); //вектор длиной с соединенную строку, заполненный 0
  
  for (int i = 1; i < strings.length(); i++) { //от 1 до длины соединенной строки
    int k = result[i - 1]; //указатель на i - 1 индекс (сначала = 0)
    while (k > 0 and strings[i] != strings[k])
		k = result[k - 1]; //присваивание предыдущего значения
    
    if (strings[i] == strings[k])
		k++; //находим одинаковые вхождения и привавляем значение в префикс функцию
    result[i] = k; //записываем в префикс функцию
  }
  return result;
}

int main() {
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");
  string input;
  fin >> input;
  vector<int> prefix = prefix_function(input);
  
  for (int& i : prefix)
  	fout << i << " ";
  return 0;
}