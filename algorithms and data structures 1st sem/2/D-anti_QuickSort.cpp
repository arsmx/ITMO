#include <iostream>
using namespace std;
long n;

int main() {
  freopen("antiqs.in", "r", stdin);
  freopen("antiqs.out", "w", stdout);
  cin >> n;
  long a[n];
 
  for (long i = 0; i < n; i++)
    a[i] = i + 1;
  for (long i = 0; i < n; i++)
    swap(a[i], a[i / 2]);
  for (long i = 0; i < n; i++)
    cout << a[i] << " ";
}