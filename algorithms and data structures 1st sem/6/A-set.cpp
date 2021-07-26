#include <fstream>
#include <vector>
using namespace std;

vector<int> array[1000001];

unsigned search(vector<int> temp, unsigned value) {
    for (unsigned i = 0; i < temp.size(); i++)
    //ищем элемент в ячейке, если нашли - выводим номер места, нет - 0
        if (temp[i] == value) {
            return i;
        }
    return 0;
}

int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");
    string input;
    while (fin >> input) {
        if (input == "insert") {
            int value;
            fin >> value;
            int i = abs(value % 1000001);
            //привели к размерности
            unsigned j = search(array[i], value);
            if (array[i].empty() || array[i][j] != value)
            //Если элемента нет в ячейке или ячейке пустое, то добавление элемента
                array[i].push_back(value);
        }
        else if (input == "delete") {
            int value;
            fin >> value;
            int i = abs(value % 1000001);
            unsigned j = search(array[i], value);
            if (!array[i].empty() && array[i][j] == value) {
              //Если ячейка существует и элемент существует
                swap(array[i][j], array[i][array[i].size() - 1]);
                //меняем с последним элементом в данной ячейке чтобы его удалить
                array[i].pop_back();
                //удаляем последний
            }
        }
        else if (input == "exists") {
            int value;
            fin >> value;
            int i = abs(value % 1000001);
            unsigned j = search(array[i], value);
            if (!array[i].empty() && array[i][j] == value) {
              //ячейка существует и в ней есть элемент
                fout << "true\n";
            }
            else {
                fout << "false\n";
            }
        }
    }

    return 0;
}