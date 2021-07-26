#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix_function(string str) {
  vector<int> result (str.length(), 0); //вектор длиной с соединенную строку, заполненный 0
  
  for (int i = 1; i < str.length(); i++) { //от 1 до длины соединенной строки
    int k = result[i - 1]; //указатель на i - 1 индекс (сначала = 0)

    while (k > 0 && str[i] != str[k])
		k = result[k - 1]; //присваивание предыдущего значения
    
    if (str[i] == str[k])
		k++; //находим одинаковые вхождения и привавляем значение в префикс функцию
    result[i] = k; //записываем в префикс функцию
  }
  return result;
}

int main() {
  int n; //мощность алфавита
  string s; //строка
  cin >> n >> s;
  s += "#";
  
  vector<int> prefix = prefix_function(s); //нашли прификс функцию для данной строки
  vector<vector<int>> knut_morris(s.length(), vector<int>(n)); //длиной с введенную строку, вниз и вправо 

  for (int i = 0; i < s.length(); i++)  //вправо
    for (char c = 'a'; c < 'a' + n; c++) { //от певого символа до последнего

      if (i == 0 || c == s[i]) //если строка первая или буква равна символу по порядку
        knut_morris[i][c - 'a'] = i + (c == s[i]);  
        //c == s[i] если правда, то 1 иначе 0

      else
	  	knut_morris[i][c - 'a'] = knut_morris[prefix[i - 1]][c - 'a'];
      //automat[i][c - 'a'] i - строка, c - 'a' - столбец по порядку
      //prefix[i - 1] префикс для предыдущей буквы
    }

  for (vector<int>& i : knut_morris) {
    for (int& j : i)
		cout << j << " ";
    cout << endl;
  }
  return 0;
}