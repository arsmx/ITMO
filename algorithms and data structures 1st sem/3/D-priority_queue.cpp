#include <iostream>
using namespace std;

long num, x, y, n = 0;
string title;
pair <long, long> a[1000000];

void siftDown(int i) {
  int lower = i;
  int lChild = i*2 + 1;
  int rChild = i*2 + 2;
  if (lChild < n && a[lChild].first < a[i].first)
    lower = lChild;
  if (rChild < n && a[rChild].first < a[lower].first)
    lower = rChild;
  if (lower != i) {
    swap(a[i], a[lower]);
    siftDown(lower);
  }
}

void siftUp(int i) {
  if (i != 0){
    if (a[i].first < a[(i - 1) / 2].first){
      swap(a[i], a[(i - 1) / 2]);
      siftUp((i - 1) / 2);
    }
  }
}

int find(int j) {
  for (int i = 0; i < n; i++)
    if (a[i].second == j)
      return i;
}

int main() {
  freopen("priorityqueue.in", "r", stdin);
  freopen("priorityqueue.out", "w", stdout);
  int i = 0;
  while (cin >> title) {
    i++;
    if (title.length() == 0)
      break;
    if (title == "push") {
      cin >> num;
      a[n].first = num;
      a[n].second = i;
      siftUp(n);
      n++;
    }
    else if (title == "extract-min") {
      if (n == 0)
        cout << "*\n";
      else {
        cout << a[0].first << "\n";
        swap(a[0], a[n - 1]);
        n--;
        siftDown(0);
      }

    }
    else if (title == "decrease-key") {
      cin >> x >> y;
      int j = find(x);
      a[j].first = y;
      if (j != 0 && a[j].first < a[(j - 1) / 2].first)
          siftUp(j);
      else
          siftDown(j);

    }
    else
      break;
  }
  return 0;
}