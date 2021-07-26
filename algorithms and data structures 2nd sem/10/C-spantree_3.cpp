#include <algorithm>
#include <fstream>
#include <vector>
#define ll long long
using namespace std;

vector <ll> UDset; // система непересекающихся множеств

ll find(ll i) { // возвращает представителя подмножества
    if (UDset[i] == i)
      return i;
    return UDset[i] = find(UDset[i]); // если не равен номеру, идем в тот номер, пока не найдем равный номеру
}

bool united(pair<ll, ll> i) { // проверяем принадлежность конца и начала ребра к одному множеству
    return find(i.first) == find(i.second);
}

void unite(pair<ll, ll> i) { // объединяет два подмножества в первое
    i.first = find(i.first);
    i.second = find(i.second);
    if (i.first != i.second) // если начало и конец не равны
        UDset[i.first] = i.second; // записали результат конца в начало
}

int main() {
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");

    ll n, m, start, finish, weight, result = 0;
    fin >> n >> m;
    UDset.resize(n + 1); // задаем размер вектора множеств, начинается с единицы
    vector <pair <ll, pair <ll, ll>>> edgesData; // тут храним ребра и вес
    for (ll i = 0; i < m; i++) { // вводим начало, конец и вес
        fin >> start >> finish >> weight;
        edgesData.push_back({ weight, {start, finish} });
    }
    sort(edgesData.begin(), edgesData.end()); // сортируем по весу от меньшего
    for (ll i = 1; i <= n; i++) // элемент массива равен его номеру - множеств столько, сколько вершин
        UDset[i] = i;
    for (auto& i : edgesData) {
        if (!united(i.second)) { // если начало и конец ребра в разных множествах
            unite(i.second); // соединить - записать конец в начало - записать конец в множество начала
            result += i.first; // плюсуем вес ребра в результат
        }
    }
    fout << result << "\n";
	return 0;
}