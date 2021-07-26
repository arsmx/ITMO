#include <iostream>
#include <vector>

// 1. all_of - возвращает true, если все элементы диапазона удовлетворяют
// некоторому предикату. Иначе false
// 2. any_of - возвращает true, если хотя бы один из элементов диапазона
// удовлетворяет некоторому предикату. Иначе false
// 3. none_of - возвращает true, если все элементы диапазона не удовлетворяют
// некоторому предикату. Иначе false
// 4. one_of - возвращает true, если ровно один элемент диапазона удовлетворяет
// некоторому предикату. Иначе false
// 5. is_sorted - возвращает true, если все элементы диапазона находятся в
// отсортированном порядке относительно некоторого критерия
// 6. is_partitioned - возвращает true, если в диапазоне есть элемент, делящий все
// элементы на удовлетворяющие и не удовлетворяющие некоторому предикату.
// Иначе false.
// 7. find_not - находит первый элемент, не равный заданному
// 8. find_backward - находит первый элемент, равный заданному, с конца
// 9. is_palindrome - возвращает true, если заданная последовательность является
// палиндромом относительно некоторого условия. Иначе false.

// Каждый алгоритм должен быть выполнен в виде шаблонной функции,
// позволяющей взаимодействовать со стандартными контейнерами STL с
// помощью итераторов. Предикаты, условия, операторы сравнения
// должны быть параметризованы.
// При сдаче работы требуется продемонстрировать работу алгоритмов как
// на стандартных, так и на пользовательских типах данных, например
// CPoint, CRational, далее работает ваша индивидуальная (не
// “коллективная”) фантазия.

using namespace std;

struct shopping_list {
    bool is_bought; // куплено ли
    string name; // предмет
};

template <typename T>
bool over(T first, T second) {
    return first > second;
}

template <typename T>
bool over2 (T t) {
    return t > 2;
}

template <typename T>
bool in_order(T t, T t1) {
    if (t == t1 - 1)
        return true;
    else
        return t == t1 + 1;
}

template <typename T>
bool is_5(T t) {
    return t == 5;
}

template <typename T>
bool purchased(T x) {
    return x.is_bought;
}

template <typename T, typename F>
bool all_of(const T& begin, const T& end, F compare) {
    for (T Start = begin; Start != end; Start++)
        if (!compare(*Start))
            return false;
    return true;
}

template <typename T, typename F>
bool any_of(const T& begin, const T& end, F compare) {
    for (T Start = begin; Start != end; Start++)
        if (compare(*Start))
            return true;
    return false;
}

template <typename T, typename F>
bool none_of (const T& begin, const T& end, F compare) {
    for (T Start = begin; Start != end; Start++)
        if (compare(*Start))
            return false;
    return true;
}

template <typename T, typename F>
bool one_of (const T& begin, const T& end, F compare) {
    int count = 0;
    for (T Start = begin; Start != end; Start++)
        if (compare(*Start))
            count++;
    if (count == 1)
        return true;
    else
        return false;
}

template <typename T, typename F>
bool is_sorted (const T& begin, const T& end, F compare) {
    for (T Start = begin; Start != end-1; Start++)
        if (!compare(*Start, *(Start + 1)))
            return false;
    return true;
}

template <typename T, typename F>
bool is_partitioned(const T& begin, const T& end, F compare) {
    for (T Start = begin; Start != end; Start++)
        if (compare(*Start) == compare(*end))
            return false;
    return true;
}

template <typename T, typename T2>
T2 find_not(const T& begin, const T& end, T2 item) {
    for (T Start = begin; Start != end; Start++)
        if (item != *Start)
            return *Start;
    return item;
}

template <typename T, typename T2>
T2 find_backward(const T& begin, const T& end, T2 item) {
    int count = 0;
    for (T End = end - 1; End >= begin; End--) {
        count++;
        if (*End == item)
            return count;
    }
    return 0;
}

template <typename T, typename F>
bool is_palindrome(const T& begin, const T& end, F compare) {
    bool result;
    T Start = begin;
    T End = end -1;
    while (Start < End) {
        if (compare(*Start, *End)) {
            Start++;
            End--;
            result = true;
        }
        else
            return false;
    }
    return result;
}

int main() {
    vector <int> a = { 7, 6, 5, 4, 3, 2 };
    vector <shopping_list> S = { {0, "Apples"},
                                 {1, "Bananas"} };
    cout << "any_of shopping_list purchased " << any_of(S.begin(), S.end(), purchased<shopping_list>)<< "\n";

    cout << "all_of " << all_of(a.begin(), a.end(), over2<int>) << "\n";
    cout << "any_of " << any_of(a.begin(), a.end(), is_5<int>)<< "\n";
    cout << "none_of " << none_of(a.begin(), a.end(), over2<int>) << "\n";
    cout << "one_of " << one_of(a.begin(), a.end(), is_5<int>)<< "\n";
    cout << "is_sorted " << is_sorted(a.begin(), a.end(), in_order<int>) << "\n";
    cout << "is_partitioned " << is_partitioned(a.begin(), a.end(), over2<int>) << "\n";
    cout << "find_not " << find_not(a.begin(), a.end(), 2) << "\n";
    cout << "find_backward " << find_backward(a.begin(), a.end(), 7) << "\n";
    cout << "is palindrome " << is_palindrome(a.begin(), a.end(), over<int>) << "\n";
    return 0;
}