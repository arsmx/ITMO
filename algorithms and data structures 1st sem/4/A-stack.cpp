#include <fstream>
using namespace std;
 
struct stack {
    int value;
    stack *next;
};
 
stack* add(int value_to_add, stack* next_element_to_add) {
    stack* temporary = (stack*)malloc(sizeof(stack));
    temporary -> value = value_to_add;
    temporary -> next = next_element_to_add;
    return temporary;
}
 
int main() {
    ifstream fin ("stack.in");
    ofstream fout ("stack.out");
    int n, value;
    fin >> n;
    char input;
    stack* instance;
    for (int i = 0; i < n; i++) {
        fin >> input;
        if (input == '+') {
            fin >> value;
            instance = add(value, instance);
        }
        else {
            fout << instance -> value << "\n";
            instance = instance -> next;
        }
    }
    fin.close ();
    fout.close ();
}