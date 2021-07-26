#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

// Алгоритм Дейкстры
int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");
    int n, s, f, input, next;
    fin >> n >> s >> f; // n - кол-во вершин, s - начальная вершина, f - конечная вершина
    vector<vector<pair<int, int>>> graph(n); // для кажого ребра список смежности - вес и соответств. ребро
    for (int i = 0; i < n; i++) // считываем матрицу смежности
        for (int j = 0; j < n; j++) {
            fin >> input;
            if (i != j and input != -1) // если это не петля (вершина сама с собой) и ребро есть
                graph[i].push_back(make_pair(input, j)); // начало ребра, {вес и конец ребра}
        }
 
    vector<long long> distances(n, LLONG_MAX); // вектор расстояний, заполнен максимумами
    distances[s - 1] = 0; // установили расстояние для стартовой вершины
    vector<bool> used(n); // вектор пройденных вершин
    for (int i = 0; i < n; i++) { // для каждой строки матрицы
        int v = -1; // записываем номер минимальной вершины
        for (int j = 0; j < n; j++) // найдем вершину с минимальным расстоянием
            if (!used[j] and (v == -1 || distances[j] < distances[v])) // если не пройдена и найдена минимальная
                v = j; // для каждого элемента строки перезаписываем номер минимальной вершины
        used[v] = true; // отмечаем, вершину просмотренной
 
        for (int j = 0; j < graph[v].size(); j++) { // для каждой смежной вершины
            next = graph[v][j].second; // номер конечной вершины ребра 
			int weight = graph[v][j].first; // вес этого ребра
            if (distances[next] > distances[v] + weight) // если получилось дойти более коротким путем, чем был записан
                distances[next] = distances[v] + weight; // перезаписываем более короткий
        }
    }
	switch (distances[f - 1]) {
		case LLONG_MAX: // если до последней вершины дойти не получилось, -1
			fout << -1;
			break;
		default:
		fout << distances[f - 1]; // иначе выводим расстояние до нее
	}
    return 0;
}