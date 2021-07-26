#include <fstream>
#include <vector>
using namespace std;

vector<pair<string, string>> array[100001];

unsigned search(vector<pair<string, string>> temp, string value) {
    for (unsigned i = 0; i < temp.size(); i++)
    //если слово нашлось в ячейке, возвращаем порядковый номер
        if (temp[i].first == value)
            return i;
    return 0;
}

int getHash(string value) {
    int hash = 0;
    for(char i : value)
        hash = 17 * hash + (int)i;
        //создаем хеш, каждый символ умножаем хэш на 17 и складываем номер символа
    return abs(hash % 100001);
    //приводим к размерности
}

int main() {
    ifstream fin("map.in");
    ofstream fout("map.out");
    string input;
    while (fin >> input) {
        if (input == "put") {
            string x, y;
            fin >> x >> y;
            int i = getHash(x);
            //нашли позицию в массиве
            unsigned j = search(array[i], x);
            //нашли место в ячейке
            if (!array[i].empty() && array[i][j].first == x)
                array[i][j].second = y;
                //ставим значение с
            if (array[i].empty() || array[i][j].first != x)
                array[i].emplace_back(x, y);
                //добавляем оба ключа один в first, другой в second
        }
        else if (input == "delete") {
            string x;
            fin >> x;
            int i = getHash(x);
            unsigned j = search(array[i], x);
            if (!array[i].empty() && array[i][j].first == x) {
                swap(array[i][j], array[i][array[i].size() - 1]);
                //если нашли элемент, меняем с последним, удаляем последний
                array[i].pop_back();
            }
        }
        else if (input == "get") {
            string x;
            fin >> x;
            int i = getHash(x);
            unsigned j = search(array[i], x);
            if (!array[i].empty() && array[i][j].first == x) {
              //нашли элемент и вывели
                fout << array[i][j].second << '\n';
            }
            else
                fout << "none\n";
        }
    }
}