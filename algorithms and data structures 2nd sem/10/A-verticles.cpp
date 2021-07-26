#include <fstream>
using namespace std;
int main() {
    int n = 0 , m = 0, i, temp;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> n >> m;
    int *array = new int [n];
    for(i = 0; i < n; i++)
      array[i] = 0; 
    for(i = 0 ; i < 2 * m; i++) { // 2*m так как для каждого ребра увеличиваем степень
    // в вершине конца и вершине начала
      fin >> temp; // вводим вершину, увеличиваем ей степень
      array[temp - 1]++;
    };
    for(i = 0; i < n; i++)
        fout << array[i] << " ";
    return 0;
		
}