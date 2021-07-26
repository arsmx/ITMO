#include <fstream> 
#include <vector>
using namespace std;
 
vector <double> pos;
 
double Garland_search(int n) {
      double left = 0, right = pos[0];
      while (right - left > 1e-9) {
        int i;
        pos[1] = (left + right) / 2;
            for (i = 2; i < n; i++) {
                  pos[i] = 2*pos[i - 1] - pos[i - 2] + 2;
                  if (pos[i] < 0) {
                left = pos[1];
                        break;
                  }
            }
            if (pos[i] >= 0)
            right = pos[1];
      }
      return pos[n - 1];
}
 
int main() {
    ifstream fin("garland.in");
    ofstream fout("garland.out");
     
  int n;
    fin >> n;
    pos.resize(n);
    fin >> pos[0];
 
    fout.precision(2);
    fout << fixed << Garland_search(n);
     
    fin.close ();
    fout.close ();
    return 0;
}