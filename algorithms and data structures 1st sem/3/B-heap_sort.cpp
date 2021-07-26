#include <iostream>
using namespace std;
long n, a[100000];

void sift(int length, int i) {
    int higher = i;
    int lChild = i*2 + 1;
    int rChild = i*2 + 2;
    if (lChild < length && a[lChild] > a[i])
      higher = lChild;
    if (rChild < length && a[rChild] > a[higher])
      higher = rChild;
    if (higher != i) {
        swap(a[i], a[higher]);
        sift(length , higher);
    }
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> a[i];

    // первоначальное сортирующее дерево
    for (int i = n / 2; i >= 0; i--)
      sift(n, i);
    
    // перемещаем максимумы в конец
    for (int i = n - 1; i >= 0; i--) {
      swap(a[0], a[i]);
      sift(i, 0);
    }
    
    for (int i = 0; i < n; i++)
      cout << a[i] << ' ';
    return 0;
}