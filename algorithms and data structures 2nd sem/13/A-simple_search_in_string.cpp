#include <fstream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("search1.in");
  ofstream fout ("search1.out");
  string first_string, second_string;
  fin >> first_string >> second_string; //ввод строк 1 и 2

  int length_1 = first_string.length(); //записали длину 1 строки
  int length_2 = second_string.length(); //записали длину 2 строки
  vector<int> positions; //позиции вхождений

  for (int i = 0; i <= length_2 - length_1; i++)
    if (first_string == second_string.substr(i, length_1)) 
      //если строка 1 = строке 2 от позиции i до длины 1 строки
      positions.push_back(i + 1); //записываем позицию входа
    
  fout << positions.size() << endl; //сколько раз встречается
  for (int& i : positions)
  	fout << i << " "; //позиции вхождений с 1
  return 0;
}