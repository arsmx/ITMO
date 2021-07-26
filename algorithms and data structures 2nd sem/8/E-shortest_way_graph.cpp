#include <vector>
#include <queue>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");
    int n, m, start, end, temp[100000] = {0}, distance[100000] = {0};
    fin >> n >> m;
    vector <vector<int>> arr (n);
    queue <int> Queue;
    temp[0] = 1;
    Queue.push(0);
    // m - количество ребер
    for (int i = 0; i < m; i++) {// для каждой вершины в цепочку записываем все ее компоненты
        fin >> start >> end; // (все соединенные с ней вершины)
        arr[start - 1].push_back(end - 1);
        arr[end - 1].push_back(start - 1);
    }

    while (!Queue.empty()) {
        int upper = Queue.front(); // первый элемент в переменную upper
        Queue.pop();
        for (int i = 0; i < arr[upper].size(); i++)
            if (!temp[arr[upper][i]]) { // если temp для вершины из рассматривоемой цепочки
                temp[arr[upper][i]] = 1; // равен нулю, по дефолту - 0, то делаем его единицей
                distance[arr[upper][i]] = distance[upper] + 1; // для вершины из цепочки
                Queue.push(arr[upper][i]); // расстояние равно основная вершина +1
            } // закидываем в очередь рассмотренный элемент чтобы всем из его соединений
    }
    for (int i = 0; i < n; i++)
        fout << distance[i] << " ";
    return 0;
}