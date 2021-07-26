#include <fstream>

using namespace std;
struct apex {
	int value;
	apex* left_child;
	apex* right_child;

  explicit apex(int i) {
    value = i;
    left_child = right_child = NULL;

  }
};


apex* Insert(apex *root, int value) {

	if(!root)
    //если мы спустились по дереву достаточно глубоко, то вставляем элемент, возвращаем дерево
		root = new apex(value);
	else if(value <= root -> value)
    //меньше корня - идем влево
		root -> left_child = Insert(root -> left_child, value);
	else
		root -> right_child = Insert(root -> right_child, value);
	return root;
}
int Search(apex* root, int value) {
  //аналогично спускаемся в дерево, пока не найдем нужный элемент или пустоту
	if(!root)
    return 0;
	else if(root -> value == value)
    return 1;
	else if(value <= root -> value)
		return Search(root -> left_child, value);
	else
		return Search(root -> right_child, value);
}

apex* Minimum(apex* root) {
  //вытаскиваем минимальный элемент
	while(root -> left_child != NULL)
    root = root -> left_child;
	return root;
}

struct apex* Delete(struct apex *root, int value) {
	if(!root)
    return root;
	else if (value < root -> value)
    root -> left_child = Delete(root -> left_child, value);
    //меньше - влево, иначе вправо
	else if (value > root -> value)
    root -> right_child = Delete(root -> right_child, value);
	else {
		//нашли элемент для удаления, нет потомков
		if(root -> left_child == NULL && root -> right_child == NULL) {
			root = NULL;
		}
		// один потомок
		else if(root -> left_child == NULL) {
			struct apex *temp = root;
			root = root -> right_child;
      //если у удаляемого элемента есть правый или левый потомок, то тот переходит на место элемента
		}
		else if(root -> right_child == NULL) {
			struct apex *temp = root;
			root = root -> left_child;
		}
		// два потомка
		else {
			struct apex *temp = Minimum(root -> right_child);
 
			root -> value = temp -> value;
			root -> right_child = Delete(root -> right_child,temp -> value);
		}
	}
	return root;
}

void Prevous_Next(apex* root, apex*& prev, apex*& next_, int value) {
    if (!root)
      return;
    if (root -> value == value) {
      //если ключ, которому ищем след. и пред. элемент, равен корню
      //для value ищем предыдушщий элемент
        if (root -> left_child != NULL) {
          //левый потомок есть
            apex* temporary = root -> left_child;
            //рассматриваем левое поддерево
            //предыдущим элементом является самый дальний элемент правой ветви
            while (temporary -> right_child)
                temporary = temporary -> right_child;
            prev = temporary ;
        }
        if (root -> right_child != NULL) {
          //то же
          //след. элемент это самый дальний элемент левой ветви
            apex* temporary = root -> right_child;
            while (temporary -> left_child)
                temporary = temporary -> left_child;
            next_ = temporary ;
        }
        return ;
    }
    // если ключ меньше корня, то идем в левое поддерево
    if (root -> value > value) {
        next_ = root;
        //задаем next элемент для левого поддерева равным его родителю
        Prevous_Next(root -> left_child, prev, next_, value);
    }
    else { // правое поддерево
        prev = root;
        Prevous_Next(root -> right_child, prev, next_, value);
    }
}
int main() {
  ifstream fin("bstsimple.in");
  ofstream fout("bstsimple.out");
	apex* root = NULL;
	string input;
	int value;
  apex* prev = NULL, *next_ = NULL;
	while (fin >> input) {
        fin >> value;
        //красивее было на свитч кейсах написать, но я понял об этом слишком поздно
        if (input == "insert") {
            if(!Search(root, value))
              root = Insert(root, value);
        }
        if (input == "delete") {
            root = Delete(root, value);
        }
        if (input == "exists") {
            if(Search(root, value))
                fout << "true\n";
            else
                fout << "false\n";
        }
         if (input == "next") {
          apex* prev = NULL, *next_ = NULL;
          Prevous_Next(root, prev, next_, value);
          if (next_)
            fout << next_ -> value << "\n";
          else
            fout << "none\n";
        }
        if (input == "prev") {
        apex* prev = NULL, *next_ = NULL;
        Prevous_Next(root, prev, next_, value);
        if (prev)
            fout << prev -> value << "\n";
        else
            fout << "none\n";
        }
    }
}
