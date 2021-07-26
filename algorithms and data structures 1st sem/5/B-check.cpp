#include <fstream>

using namespace std;
typedef struct apex {
    int value, maximum, minimum;
    apex* Parent = nullptr;
    apex* left_child = nullptr;
    apex* right_child = nullptr;
} apex;

int main() {
    ifstream fin("check.in");
    ofstream fout("check.out");
    int n, lChild, rChild;
    fin >> n;
    apex a[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i].value >> lChild >> rChild;
        if (lChild) {
            a[i].left_child = &a[lChild - 1];
            a[i].left_child -> Parent = &a[i];

        }
        if (rChild) {
            a[i].right_child = &a[rChild - 1];
            a[i].right_child -> Parent = &a[i];
        }
        if (i) {
            if (a[i].Parent == nullptr) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            if (a[i].Parent -> value == a[i].value) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            else if (a[i].Parent -> value > a[i].value && a[i].Parent -> left_child != &a[i]) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            else if (a[i].Parent -> value < a[i].value && a[i].Parent -> right_child != &a[i]) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            else if (a[i].Parent -> value > a[i].value && a[i].value <= a[i].Parent -> minimum) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            else if (a[i].Parent -> value < a[i].value && a[i].value >= a[i].Parent -> maximum) {
                fout << "NO";

                fin.close();
                fout.close();
                return 0;
            }
            if (a[i].Parent -> value > a[i].value) {

                a[i].maximum = a[i].Parent -> value;

                a[i].minimum = a[i].Parent -> minimum;

            }
            else if (a[i].Parent -> value < a[i].value) {

                a[i].minimum = a[i].Parent -> value;

                a[i].maximum = a[i].Parent -> maximum;

            }
        }
        else {
            a[i].minimum = INT32_MIN;
            a[i].maximum = INT32_MAX;
        }
    }
    fout << "YES";
    fin.close();
    fout.close();
}