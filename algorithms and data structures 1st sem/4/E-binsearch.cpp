#include <fstream>
using namespace std;

int binSearch(int array[], int left, int right, int i) {
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(array[mid] == i)
            return mid;
        if(array[mid] > i)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}


int main() {
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");
    int n, *array;
    fin >> n;
    array = new int[n];

    for(int i = 0; i < n; i++)
        fin >> array[i];

    int m, j;
    fin >> m;
    int request[m];

    for(int i = 0; i < m; i++) {
        fin >> request[i];
        j = binSearch(array, 0, n - 1, request[i]);
        int left = j, right = j;
        if (j == -1)
            fout << j << " " << j << "\n";
        else {
            while(array[left - 1] == array[left])
                left--;
            while(array[right + 1] == array[right])
                right++;
            fout << left + 1 << " " << right + 1 << "\n";
        }
    }
    fin.close ();
    fout.close ();
}