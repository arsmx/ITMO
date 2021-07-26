#include <iostream>
using namespace std;
long n, a[100000];
int main()
{
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n / 2; i++) {
        if (i*2 + 2 >= n)
            break;
        if (a[i] > a[i*2 + 1] || a[i] > a[i*2 + 2]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}