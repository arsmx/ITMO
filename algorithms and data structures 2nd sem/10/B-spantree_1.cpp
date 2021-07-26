#include <fstream>
#include <cmath>
#include <iomanip> // для setprecision
using namespace std;

class CApex {
public:
    int x = 0;
    int y = 0;
    float distToMate(const CApex & second) { // расст до точки, которую подаем
        return sqrt((second.x - x) * (second.x - x) +
        (second.y - y) *(second.y - y)); // выводит гипотенузу по т. пифагора
    };
};

int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
    int n, x, y;
    float result = 0;
    fin >> n;

    CApex Point[n];
    int visited[n];
    float distance[n];

    for (int i = 0; i < n; i++) {
        fin >> x >> y;
        Point[i] = CApex{x, y};
        visited[i] = 0; // не посещали
        if (i > 0) // если это не первая вершина
            distance[i] = Point[0].distToMate(Point[i]); // записываем расстояние до первой
    } // после ввода данных расстояния от первой до всех вершин посчитаны
    visited[0] = 1; // отметили первую посещенной, так как посчитали все расстояния

    for (int j = 1; j < n; j++) { // от второй вершины до последней
        float minimumL = 2147483647;
        int temp = 0; // номер вершины, которую надо будет запомнить
        for(int i = 1; i < n; i++) // для всех вершин, кроме первой
            if (distance[i] < minimumL and !visited[i]) { // дистанция меньше минимума и не посещали
                minimumL = distance[i]; // обновили минимум
                temp = i; // запоминаем ближайшую вершину и расст. до нее, vis=1
            }
        visited[temp] = 1;
        result += minimumL;
        for (int i = 0; i < n; i++)  // от первой до последней вершины
            if (!visited[i])  // если не посещали = не сложили кратчайший путь
                if (Point[temp].distToMate(Point[i]) < distance[i]) // обновляем путь на более короткий
                    distance[i] = Point[temp].distToMate(Point[i]);
    }
    fout << fixed << setprecision(3) << result;
    return 0;
}