#include <fstream>

using namespace std;
typedef struct apex {
    int value;
    int height = 1;
    apex* Parent = nullptr;
} apex;

int main() {
    ifstream fin("height.in");
    ofstream fout("height.out");
    int n, lChild, rChild, max_height = 0;
    fin >> n;
    apex a[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i].value >> lChild >> rChild;
        a[lChild - 1].Parent = &a[i];
        a[rChild - 1].Parent = &a[i];

        if (a[i].Parent != nullptr)
            a[i].height = a[i].Parent -> height + 1;

        if (a[i].height > max_height)
            max_height = a[i].height;

    }
    fout << max_height;
    fin.close();
    fout.close();
}