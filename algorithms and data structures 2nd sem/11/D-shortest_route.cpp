#include <fstream>
#include <vector>

using namespace std;
struct Edge {
    long long weight;
    long long next;
};
const long long Max = 8e18;
long long n, m, s, first; // n - вершин, m - ребер, s - выделенная вершина
vector<vector<Edge>> graph; // список смежности графа
vector<long long> distances;
vector<bool> Cycle;
vector<bool> Visited; // помечаем все вершины, до которых можем дойти из S

void DFS(long long v) {
    Visited[v] = true; // все исходящие вершины помечает посещенными
    for (auto &i : graph[v]) 
        if (!Visited[i.next])
            DFS(i.next);
}

void DFS_Cycle(long long v) {
    Cycle[v] = true;
    for (auto &i : graph[v]) 
        if (!Cycle[i.next]) // все исходящие вершины помечает Cycle
            DFS_Cycle(i.next);
}

void FordBellman() {
    for (long long i = 0; i < n; i++) 
        for (long long j = 0; j < n; j++) 
            for (auto &edge : graph[j]) 
                if (distances[edge.next] > distances[j] + edge.weight) {
                    distances[edge.next] = min(Max, distances[j] + edge.weight);
                    if (i == n - 1 and Visited[edge.next]) // во вторую итерацию все исходящие помечает Cycle
                        DFS_Cycle(edge.next); // если мы пошли по циклу
                }
}

int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");

    fin >> n >> m >> s;
    s--;
    graph.resize(n);
    distances.resize(n, Max);
    Cycle.resize(n, false);
    Visited.resize(n, false);

    Edge temp; // временный экземпляр
    for (long long i = 0; i < m; i++) {
        fin >> first >> temp.next >> temp.weight;
        temp.next--; // заполняем вектор 
        graph[first - 1].push_back(temp);
    }
    distances[s] = 0;
    DFS(s);
    FordBellman();
    for (long long i = 0; i < n; i++) {
		if (Cycle[i] || distances[i] < -Max)
            fout << "-\n"; // нет кратчайшего пути
        else if (!Visited[i])
            fout << "*\n"; // нет пути
        else 
            fout << distances[i] << "\n"; // иначе расстояние
    }
    return 0;
}