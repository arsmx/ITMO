#include <fstream>
using namespace std;

struct stack {
    char value;
    stack *last = NULL;
};

stack* add(char value_to_add, stack* next_element_to_add) {
    stack* temporary = (stack*)malloc(sizeof(stack));
    temporary -> value = value_to_add;
    temporary -> last = next_element_to_add;
    return temporary;
}

int main() {
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");
    for (int i = 0; i < 10000; i++) {
        stack* instance = NULL;
        string input;
        fin >> input;
        if (input.length() == 0) break;

        for (int j = 0; j < input.length() + 1; j++) {
            if (input[j] == '(' || input[j] == '[') {
                instance = add(input[j], instance);
            }
            
            else if (input[j] == ')') {
                if (instance == NULL || instance -> value == '[') {
                    fout << "NO\n";
                    break;
                }
                else
                    instance = instance -> last;
            }

            else if (input[j] == ']') {
                if (instance == NULL || instance -> value == '(') {
                    fout << "NO\n";
                    break;
                } else
                    instance = instance -> last;
            }

            else {
                if (instance == NULL)
                    fout << "YES\n";
                else
                    fout << "NO\n";
            }
        }
    }
  fin.close ();
  fout.close ();
}