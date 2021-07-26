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
  ifstream fin("search2.in");
  ofstream fout("search2.out");
  string first_string, second_string;
  fin >> first_string >> second_string; //ввод строк 1 и 2
  
  int length_1 = first_string.length(); //записали длину 1 строки
  int length_2 = second_string.length(); //записали длину 2 строки
  vector<int> positions; //позиции вхождений

  vector<int> prefix = prefix_function(first_string + "#" + second_string); //префикс функция, на входе соединяем две строки
  
  for (int i = 0; i < length_2; i++)  //от 0 до длины 2 строки
    if (length_1 == prefix[length_1 + i + 1])  //если длина строки1 равна префиксу [длина1 строки + i + 1]
      positions.push_back(i - length_1 + 2);
  
  fout << positions.size() << endl; //сколько раз встречается
  for (int& i : positions)
  	fout << i << " "; //позиции вхождений с 1
  return 0;
}