#include <iostream>
using namespace std;

long n, a[300000], b[300000];

void mergeSort(long left, long right){
    if (left < right){
        long mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (a[left + i] > a[mid + 1 + j]) {
                b[i + j] = a[mid + 1 + j];
                j++;
            } else {
                b[i + j] = a[left + i];
                i++;
            }
        }
        while (left + i <= mid){
            b[i + j] = a[left + i];
            i++;
        }
 
        while (mid + 1 + j <= right){
            b[i + j] = a[mid + 1 + j];
            j++;
        }
 
        for (i = 0; i < right - left + 1; i++)
            a[left + i] = b[i];
    }
}

int main() {
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);
  cin >> n;

  for (int i = 0; i < n; i++)
    cin >> a[i];

  mergeSort(0, n - 1);

  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
}
