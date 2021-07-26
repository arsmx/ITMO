#include <fstream>
#include <vector>
using namespace std;
 
int main() {
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");
    int n, m, s, f, weight;
    fin >> n >> m; // n - вершин и m - ребер
    vector<vector<int>> graph(n, vector<int>(m, 10000)); // список смежности
    for (int i = 0; i < m; i++) {
        fin >> s >> f >> weight; // начало, конец, вес
        graph[s - 1][f - 1] = weight;
    }
 
    for (int i = 0; i < n; i++)
        graph[i][i] = 0; // главная диагональ нули
 
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]); // записываем минимальный путь
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fout << graph[i][j] << " ";
        fout << "\n";
    }
    return 0;
}
