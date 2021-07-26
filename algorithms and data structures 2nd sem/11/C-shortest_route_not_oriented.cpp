#include <fstream>
#include <vector>
#include <set>
#include <limits.h>
using namespace std;
 
int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");
 
    int n, m, s, f, weight;
    fin >> n >> m; // n - вершин, m - ребер
    vector<vector<pair<int, int>>> graph(n); // список смежности с расстояниями - верш, {смеж верш, вес}
    for (int i = 0; i < m; i++) {
        fin >> s >> f >> weight;
        graph[s - 1].push_back(make_pair(f - 1, weight)); // список смежности, к началу ребра задаем конечную вершину и вес
        graph[f - 1].push_back(make_pair(s - 1, weight)); // к концу так же
    }
 
    vector<int> distances(n, INT_MAX); // вектор расстояний заполнен максимумами
    distances[0] = 0;
    set<pair<int, int>> Set; // в контейнере Set все элементы сразу сортируются по возрастанию
    Set.insert(make_pair(0, 0));
 
    while (!Set.empty()) {
        pair<int, int> pointer = *Set.begin(); // указатель на первый элемент
        Set.erase(Set.begin()); // удаляем первый элемент
        for (pair<int,int> i : graph[pointer.second]) // для смежных верш. для данной и их весов
            if (distances[i.first] > pointer.first + i.second) { // если записано большее расстояние, чем от предыдущ вершины + вес этой
                Set.erase(make_pair(distances[i.first], i.first));
                distances[i.first] = pointer.first + i.second; // перезаписываем меньшее = расст до предыдущ. + вес следующего ребра
                Set.insert(make_pair(distances[i.first], i.first)); // вставляем расстояние и вершину
            }
    }
 
    for (int i : distances)
        fout << i << " ";
    return 0;
}