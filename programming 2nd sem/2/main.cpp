#include <iostream>
#include <vector>
using namespace std;

class CPolynomial {
    private:
        vector<float> coefficient;

    public:
        CPolynomial() = default;

    CPolynomial(int j, float a[]) {
        for (int i = 0; i < j; i++)
            coefficient.push_back(a[i]);
    }

    CPolynomial(vector<float> & a) {
        coefficient = a;
    }

    CPolynomial(CPolynomial & a) {
        coefficient = a.coefficient;
    }

    void operator=(const CPolynomial & a) {
        coefficient = a.coefficient;
    }

    bool operator==(const CPolynomial & a) {
        return coefficient == a.coefficient;
    }

    bool operator!=(const CPolynomial & a) {
        return !(coefficient == a.coefficient);
    }

    CPolynomial operator+(const CPolynomial & a) {
        CPolynomial T;
        if (a.coefficient.size() > coefficient.size()) { // прибавляем к большему меньшее
            for (int i = 0; i < coefficient.size(); i++)
                T.coefficient.push_back(a.coefficient[i] + coefficient[i]);
            for (int i = coefficient.size(); i < a.coefficient.size(); i++)
                T.coefficient.push_back(a.coefficient[i]);
        }
        else {
            for (int i = 0; i < a.coefficient.size(); i++) // прибавляем к меньшему большее
                T.coefficient.push_back(a.coefficient[i] + coefficient[i]);
            for (int i = a.coefficient.size(); i < a.coefficient.size(); i++)
                T.coefficient.push_back(coefficient[i]);
        }
        return T;
    }

    CPolynomial operator-(const CPolynomial & a) {
        CPolynomial T;
        if (a.coefficient.size() > coefficient.size()) { // вычитаем из меньшего большее
            for (int i = 0; i < coefficient.size(); i++)
                T.coefficient.push_back(coefficient[i] - a.coefficient[i]);
            for (int i = coefficient.size(); i < a.coefficient.size(); i++)
                T.coefficient.push_back(-a.coefficient[i]); // возвращаем разницу со знаком минус
        }
        else { // из большего меньшее
            for (int i = 0; i < a.coefficient.size(); i++)
                T.coefficient.push_back(coefficient[i] - a.coefficient[i]);
            for (int i = a.coefficient.size(); i < coefficient.size(); i++)
                T.coefficient.push_back(coefficient[i]);
        }
        return T;
    }

    CPolynomial operator-() {
        for (int i = 0; i < coefficient.size(); i++)
            if (coefficient[i])
                coefficient[i]=-coefficient[i];
        return *this;
    }

    CPolynomial operator++() {
        coefficient[0]++;
        return *this;
    }

    CPolynomial operator++(int) {
        ++(coefficient[0]);
        return *this;
    }

    CPolynomial operator--() {
        coefficient[0]--;
        return *this;
    }

    CPolynomial operator--(int) {
        --(coefficient[0]);
        return *this;
    }

    void operator+=(const CPolynomial & a) {
        * this = * this + a;
    }

    void operator-=(const CPolynomial & a) {
        * this = * this - a;
    }

    CPolynomial operator*(const CPolynomial & a) const {
        CPolynomial T;
        for (int i = 0; i < a.coefficient.size() + coefficient.size() - 1; i++)
            T.coefficient.push_back(0);
        for (int i = 0; i < coefficient.size(); i++)
            if (coefficient[i])
                for (int j = 0; j < a.coefficient.size(); j++)
                    T.coefficient[i + j] += coefficient[i] * a.coefficient[j];
        return T;
    }

    CPolynomial operator/(float a) {
        CPolynomial T;
        for (int i = 0; i < coefficient.size(); i++)
            if (coefficient[i])
                coefficient[i]=coefficient[i]/a;
        return *this;
    }

    void operator*=(const CPolynomial & a) {
        * this = * this * a;
    }

    void operator/=(float a) {
        * this = * this / a;
    }

    void operator<<(int j) {
        for (int i = 0; i < j; i++)
            coefficient.insert(coefficient.begin(), 0);
    }

    void operator>>(int j) {
        for (int i = 0; i < j; i++)
            coefficient.erase(coefficient.begin());
    }

    float operator[](int j) {
        return coefficient[j];
    }

    friend istream & operator>>(istream & stream, CPolynomial & T) {
        int quantity, input;
        cout << "Сколько членов задать в полиноме?\n";
        cin >> quantity;
        T.coefficient.clear();
        for (int i = 0; i < quantity; i++) {
            cout << "Введите коэффициент для  Х^" << i << ": " << endl;
            stream >> input;
            T.coefficient.push_back(input);
        }
        return stream;
    }

    friend ostream & operator<<(ostream & stream, CPolynomial & T) {
        for (int i = T.coefficient.size() - 1; i > 0; i--)
            if (T.coefficient[i]) {
                stream << T.coefficient[i] << "X^" << i;
                if (T.coefficient[i - 1] >= 0)
                    cout << " + ";
            }
        stream << T.coefficient[0] << endl;
        return stream;
    }

    ~CPolynomial() = default;
};

int main() {
    system("chcp 65001");
    float a[] = {
        2,
        2,
        2
    };
    float b[] = {
        2,
        2,
        2,
        2
    };
    CPolynomial First(3, a);
    CPolynomial Second(4, b);
    cout << "Первый: " << First;
    cout << "Второй: " << Second;

    cout << "Первый + Второй = ";
    First += Second;
    cout << First;
    cout << "Первый == Второй? " << (First == Second) << endl;
    cout << "Первый == Первый? " << (First == First) << endl;
    cout << "Оператор сдвига влево: ";
    First << 1;
    cout << First;
    First = -First;
    cout << "Первый со знаком минус " << First;
    cin >> First;
    cout << First;
    return 0;
}