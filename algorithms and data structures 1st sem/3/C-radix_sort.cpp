#include <iostream>
using namespace std;

string a[1000], buffer[1000];
long n, m, k;
 
void radixSort(int position) {
    char bufferChar = 'a';
    int count = 0;
    for (int i = 0; i < 26; i++) {
      for (int k = 0; k < n; k++) {
        if (a[k][position] == bufferChar) {
          buffer[count] = a[k];
          count++;
        }
      }
      bufferChar++;
    }
    for (int i = 0; i < n; i++)
        a[i]=buffer[i];
}
 
int main() {
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
      cin >> a[i];

    for (int i = m-1; i >= m-k; i--)
      radixSort(i);
 
    for (int i = 0; i < n; i++)
      cout << a[i] << '\n';
    return 0;
}