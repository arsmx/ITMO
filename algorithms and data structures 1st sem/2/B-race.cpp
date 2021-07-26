#include <fstream>
#include <string>
 
using namespace std;
 
struct FullData {
    string Nation;
    string Name;
};

FullData input[100000], result[100000];

void mergeSort(long left, long right){
    if (left < right){
        long mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (input[left + i].Nation > input[mid + 1 + j].Nation) {
                result[i + j] = input[mid + 1 + j];
                j++;
            } else {
                result[i + j] = input[left + i];
                i++;
            }
        }
        while (left + i <= mid){
            result[i + j] = input[left + i];
            i++;
        }
 
        while (mid + 1 + j <= right){
            result[i + j] = input[mid + 1 + j];
            j++;
        }
 
        for (i = 0; i <= right - left; i++)
            input[left + i] = result[i];
    }
}
int main() {
    ifstream fin("race.in");
    ofstream fout("race.out");
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> input[i].Nation >> input[i].Name;
    }
    mergeSort(0, n-1);
    string buffer;
    for (int i = 0; i < n; ++i) {
        if (buffer != input[i].Nation) {
            fout << "=== " << input[i].Nation << " ===\n";
            buffer = input[i].Nation;
        }
        fout << input[i].Name << "\n";
    }
    fin.close();
    fout.close();
}