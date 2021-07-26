#include <vector>
#include <queue>
#include <fstream>
using namespace std;
 
vector <char> search(vector <vector<char>>& field, pair <int, int> start, pair<int, int> finish) {
    vector <vector<vector<char>>> temp(field.size(), vector <vector<char>>(field[0].size())); // для каждой точки храним маршрут до нее
    // задали цепочку маршрута для каждой точки поля
    queue <pair<int, int>> Queue;
    Queue.push(start);
    while (!Queue.empty()) { // пока очередь не пустая
        pair <int, int> temp_pair = Queue.front(); // в temp_pair записали координаты стартовой точки
        Queue.pop();
        if (temp_pair.first == finish.first && temp_pair.second == finish.second)
            return temp[temp_pair.second][temp_pair.first]; // если рассматриваемая точка = финиш, выводим маршрут до нее
         
        if (temp_pair.second > 0 && field[temp_pair.second - 1][temp_pair.first] != '#'
        && temp[temp_pair.second - 1][temp_pair.first].empty() ) {
          // вверх можно - координаты начинаются от нуля, там не решетка
            temp[temp_pair.second - 1][temp_pair.first] = temp[temp_pair.second][temp_pair.first];
            // записываем в верхнюю точку текущий маршрут и приплюсовываем последний ход - вверх
            temp[temp_pair.second - 1][temp_pair.first].push_back('U');
            Queue.push(make_pair(temp_pair.first, temp_pair.second - 1)); // верхний элемент - в очередь
        }
 
        if (temp_pair.second < field.size() - 1 && field[temp_pair.second + 1][temp_pair.first] != '#'
            && temp[temp_pair.second + 1][temp_pair.first].empty() ) { // вниз можно, цепочка маршрута еще пустая
            temp[temp_pair.second + 1][temp_pair.first] = temp[temp_pair.second][temp_pair.first];
            temp[temp_pair.second + 1][temp_pair.first].push_back('D'); // тоже приплюсовываем
            Queue.push(make_pair(temp_pair.first, temp_pair.second + 1));
        }
 
        if (temp_pair.first > 0 && field[temp_pair.second][temp_pair.first - 1] != '#'
            && temp[temp_pair.second][temp_pair.first - 1].empty() ) { // влево
            temp[temp_pair.second][temp_pair.first - 1] = temp[temp_pair.second][temp_pair.first];
            temp[temp_pair.second][temp_pair.first - 1].push_back('L');
            Queue.push(make_pair(temp_pair.first - 1, temp_pair.second));
        }
 
        if (temp_pair.first < field[temp_pair.first].size() - 1
        && field[temp_pair.second][temp_pair.first + 1] != '#'
            && temp[temp_pair.second][temp_pair.first + 1].empty() ) { // вправо
            temp[temp_pair.second][temp_pair.first + 1] = temp[temp_pair.second][temp_pair.first];
            temp[temp_pair.second][temp_pair.first + 1].push_back('R');
            Queue.push(make_pair(temp_pair.first + 1, temp_pair.second));
        }
    }
    return vector <char>(); // возвращаем пустой вектор, если к финишу прийти не удалось
}
 
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;
    vector <vector<char>> field(n, vector<char>(m)); // задаем двумерный массив n на m
    pair <int, int> start, finish; // х и у для точки старта и финиша
 
    for (int i = 0; i < n; i++) { // записываем все поле, точки старта и финиша
        for (int j = 0; j < m; j++) {
            fin >> field[i][j]; // j - х, i - y
            if (field[i][j] == 'S') {
                start.first = j;
                start.second = i;
            }
            if (field[i][j] == 'T') {
                finish.first = j;
                finish.second = i;
            }
        }
    }
 
    vector <char> path = search(field, start, finish); // через поиск записываем маршрут в path
    switch(path.size()) {
      case 0:
        fout << -1;
        break;
      default:
        fout << path.size() << endl;
        for (char direction : path) // выводим длину пути, выводим маршрут
            fout << direction;
    }
    return 0;
}
