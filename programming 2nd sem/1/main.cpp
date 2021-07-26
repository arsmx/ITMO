#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class CPoint {
private:
    float x;
    float y;

public:
    //Установка значений
    CPoint(float new_x, float new_y) {
        x = new_x;
        y = new_y;
    }

    //Конструктор по умолчанию, без параметров
    CPoint() {
        x = 0;
        y = 0;
    }

    //Конструктор копирования
    CPoint(const CPoint& copy) {
        x = copy.get_x(); //копирование значенмй
        y = copy.get_y();
    }

    //Оператор присваивания
    CPoint& operator = (const CPoint& other) {
        if (&other == this)
            return *this;
        //в двух строках выше мы проверяем, что не пытаемся присвоить себе самого себя
        x = other.get_x();
        y = other.get_y();
        return *this;

    }

    //Установить новые значения
    void SetCoordinates(float new_x, float new_y) {
        x = new_x;
        y = new_y;
    }

    //Методы, возвращающие значения полей
    float get_x() const {
        return x;
    }

    float get_y() const {
        return y;
    }
};

class CPolygonalLine {
protected:
    static float DistanceCount(CPoint &p1, CPoint &p2) {
        return sqrt((p1.get_x() - p2.get_x()) * (p1.get_x() - p2.get_x())
                    + (p1.get_y() - p2.get_y()) * (p1.get_y() - p2.get_y()));
    }

    vector <CPoint> Line;

public:
    //конструктор по умолч
    CPolygonalLine() {
        CPoint arr[2];
        arr[0].SetCoordinates(1,1);
        arr[1].SetCoordinates(3,3);
        Line.push_back(arr[0]);
        Line.push_back(arr[1]);
    }

    //Конструктор, установка значений
    CPolygonalLine(CPoint arr[], int num) {
        for (int i = 0; i < num; i++) {
            Line.push_back(arr[i]);
        }
    }

    //Конструктор копирования
    explicit CPolygonalLine(const vector<CPoint>& other) {
        Line = other;
    }

    //Оператор присваивания
    virtual CPolygonalLine& operator = (const vector<CPoint>& other) {
        Line = other;
        return *this;
    }

    //Расчет длины линии
    float LengthCount () {
        float length = 0;
        for (int i = 0; i < Line.size() - 1; i++)
            length += DistanceCount(Line[i], Line[i + 1]);
        return length;
    }

};

class CClosedPolygonalLine : public CPolygonalLine {
public:
    //Конструктор по умолчанию
    CClosedPolygonalLine() {
        CPoint arr[3];
        arr[0].SetCoordinates(1,1);
        arr[1].SetCoordinates(3,3);
        arr[2].SetCoordinates(5,5);
        Line.push_back(arr[0]);
        Line.push_back(arr[1]);
        Line.push_back(arr[2]);
    }

    //Конструктор
    CClosedPolygonalLine(CPoint arr[], int num) : CPolygonalLine(arr, num) {}

    //Конструктор копирования
    explicit CClosedPolygonalLine(vector<CPoint>& other) : CPolygonalLine(other) {}

    //Оператор присваивания
    CClosedPolygonalLine& operator = (const vector<CPoint>& other) override {
        Line = other;
        return *this;
    }

    //Расчет периметра
    float PerimeterCount () {
        float len = CPolygonalLine::LengthCount();
        len += DistanceCount(Line[0], Line[Line.size() - 1]);
        return len;
    }
};

class CPolygon : public CClosedPolygonalLine {
public:
    //Конструктор по умолчанию
    CPolygon() : CClosedPolygonalLine() {}

    //Конструктор
    CPolygon(CPoint arr[], int num) : CClosedPolygonalLine(arr, num) {}

    //конструктор копирования
    explicit CPolygon(vector<CPoint>& other) : CClosedPolygonalLine(other) {}

    //Оператор присваивания
    CPolygon& operator = (const vector<CPoint>& other) override {}

    float AreaCount() {
        float area = 0;
        for (int i = 0; i < Line.size() - 1; i++) {
                area += Line[i].get_x() * Line[i + 1].get_y()
                        - Line[i + 1].get_x() * Line[i].get_y();
        }
        return abs(area) / 2;
    }
};

class CTriangle : public CPolygon {
public:
    //Конструктор по умолчанию
    CTriangle() : CPolygon() {}

    //Конструктор
    explicit CTriangle(CPoint arr[], int num = 3) : CPolygon(arr, num) {}

    //Конструктор копирования
    explicit CTriangle(vector<CPoint>& other) : CPolygon(other) {}

    //Оператор присваивания
    CTriangle& operator = (const vector<CPoint>& other) override {}
};

class CTrapezoid : public CPolygon {
public:
    //Конструктор по умолчанию
    CTrapezoid() {
        CPoint array[4];
        array[0].SetCoordinates(1,1);
        array[1].SetCoordinates(3,3);
        array[2].SetCoordinates(5,5);
        array[3].SetCoordinates(7,7);
        Line.push_back(array[0]);
        Line.push_back(array[1]);
        Line.push_back(array[2]);
        Line.push_back(array[3]);
    }

    //Конструктор
    explicit CTrapezoid(CPoint arr[], int num = 4) : CPolygon(arr, num) {}

    //Конструктор копирования
    explicit CTrapezoid(vector<CPoint>& other) : CPolygon(other) {}

    //Оператор присваивания
    CTrapezoid& operator = (const vector<CPoint>& other) override {}
};

class CRegularPolygon : public CPolygon {
public:
    //Конструктор по умолчанию
    CRegularPolygon() {
        CPoint array[4];
        array[0].SetCoordinates(1,1);
        array[1].SetCoordinates(3,3);
        array[2].SetCoordinates(5,5);
        array[3].SetCoordinates(7,7);
        Line.push_back(array[0]);
        Line.push_back(array[1]);
        Line.push_back(array[2]);
        Line.push_back(array[3]);
    }

    //Конструктор
    CRegularPolygon(CPoint arr[], int num) : CPolygon(arr, num) {}

    //Конструктор копирования
    explicit CRegularPolygon(vector<CPoint>& other) : CPolygon(other) {}

    //Оператор присваивания
    CRegularPolygon& operator = (const vector<CPoint>& other) override {}
};

int main(int argc, char **argv) {
    const int num = 4;
    CPoint p1(1,1),
        p2(2,2),
        p3(3,3),
        p4(4,4);
    CPoint arr[num] = {p1, p2, p3, p4};

    CPolygon *array[4];
    array[0] = new CPolygon(arr, 4);
    array[1] = new CRegularPolygon(arr, 4);
    array[2] = new CTrapezoid(arr, 4);
    array[3] = new CTriangle(arr, 3);

    for (auto & i: array) {
        cout << "Perimeter = " << i -> PerimeterCount() << endl;
        cout << "Area = " << i -> AreaCount() << endl << endl;
    }
    return 0;
}
