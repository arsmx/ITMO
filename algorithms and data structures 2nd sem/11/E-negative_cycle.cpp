#include <fstream>
#include <vector>
#define Max 8e18
using namespace std;

struct Edge {
	int start, next;
    long long weight;
};

int main() {
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");
    long long n, weight, v;
    fin >> n;
    vector<Edge> graph;
	vector<int> route;
	vector<long long> distances(n, Max);
	vector<long long> prevous(n, -1);
    for (int i = 0; i < n; i++) // вводим ребра: начало, конец, вес
        for (int j = 0; j < n; j++) {
            fin >> weight;
            if (weight != 1e9)
                graph.push_back({i, j, weight});
        }

    v = -1;
    distances[0] = 0;
    for (int i = 0; i < n; i++) {
        v = -1;
        for (auto &j : graph) 
            if (distances[j.start] + j.weight < distances[j.next]) {
                distances[j.next] = distances[j.start] + j.weight;
                prevous[j.next] = j.start; // шаг назад в маршруте
                if (i == n - 1)
                    v = j.next; // в последнюю итерацию назначаем v последней вершиной
            }
    }

    if (v == -1)
        fout << "NO\n";
    else {
		for (int i = 0; i < n; i++)
			v = prevous[v]; // теперь v первая вершина цикла
        route.push_back(v);
    	long long temp = prevous[v]; // положили в маршрут, назначили вершину перед ней
        while (temp != v) { // пока не замкнулся цикл
			route.insert(route.begin() + 1, temp); // вставлям в начало маршрута, после первой
            temp = prevous[temp]; // переходим к предыдущей
        }
        route.push_back(v); // в конец маршрута снова первая вершина
        fout << "YES\n";
       	fout << route.size() << endl;
        for (long long i : route)
            fout << i + 1 << ' ';
    }
    return 0;
}