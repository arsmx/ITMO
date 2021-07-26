#include <fstream>
#include <vector>
using namespace std;
  
int main() {
    ifstream fin("knapsack.in");
    ofstream fout("knapsack.out");
  
    int n, s; // н - кол-во слитков, с - сумма, которую стремимся набрать
    fin >> s >> n;
    vector<int> golden_weight(n); // вектор масс слитков
	vector<bool> get_sum(s + 1, false); // можем ли мы получить сумму равную номеру ячейки в векторе
	get_sum[0] = true; // нулем слитков можем набрать сумму = 0
    for (int i = 0; i < n; i++) 
        fin >> golden_weight[i];

	for (int j = 0; j < n; j++) // для всех слитков
		for (int i = s; i >= golden_weight[j]; i--) // для каждого слитка спускаемся от вместимости рюкзака до веса этого слика
			if (get_sum[i - golden_weight[j]]) // если мы уже набирали сумму в рюкзаке на массу этого слитка меньше
				get_sum[i] = true; // то можем набрать и эту сумму
	while (!get_sum[s]) // находим максимальную сумму, которую можем набрать
		s--; 
    fout << s;
    return 0;
}