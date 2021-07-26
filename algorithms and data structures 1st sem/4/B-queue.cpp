#include <fstream>
using namespace std;

struct stack {
    long value;
    stack *last = NULL;
};

stack* add(long value_to_add, stack* next_element_to_add) {
    stack* temporary = (stack*)malloc(sizeof(stack));
    temporary -> value = value_to_add;
    temporary -> last = next_element_to_add;
    return temporary;
}

int main() {
    ifstream fin("queue.in");
    ofstream fout("queue.out");
    long n, value;
    char input;
    fin >> n;
    stack* Last_stack = NULL;
    for (int i = 0; i < n; i++) {
        fin >> input;
        if (input == '+') {
            fin >> value;
            Last_stack = add(value, Last_stack);
        }

        else {
            stack* First_stack = Last_stack;

            if (First_stack -> last == NULL) {
                fout << First_stack -> value << "\n";
                Last_stack = NULL;
            }

            else {
                while (First_stack -> last -> last != NULL)
                    First_stack = First_stack -> last;
                fout << First_stack -> last -> value << "\n";
                First_stack -> last = NULL;                
            }
        }
    }
  fin.close ();
  fout.close ();
}