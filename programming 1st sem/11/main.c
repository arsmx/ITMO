/*
Использование заголовочных файлов

Разработать структуру, описывающую геометрическую фигуру на плоскости с помощью её координат, а также функции расчёта площади этой геометрической фигуры и её периметра (длины окружности). Дополнительно разработать функцию, позволяющую создавать структуру моделируемой геометрической фигуры на основании данных, введённых с консоли (самостоятельно определить формат этих вводимых данных). Вид геометрической фигуры и набор её рассчитываемых параметров определяются по номеру варианта.
Разместить программный код функций, рассчитывающих параметры фигуры в отдельном файле исходного текста. Создать заголовочный файл, позволяющий вызывать функции созданного файла исходного текса из других файлов. Разместить в созданном заголовочном файле структуру, описывающую моделируемую геометрическую фигуру. Предусмотреть в созданном заголовочном файле защиту от повторного включения с помощью Include Guard.
Создать файл исходного текста для размещения в нём точки входа. Разработать программный код функции main, создающий экземпляр структуры моделируемой фигуры, а также осуществляющий вызовы созданных функций расчёта параметров этой фигуры. Входные данные для моделирования фигуры вводить с консоли, результаты расчёта параметров фигуры также выводить на консоль.

Геометрическая фигура: прямоугольный треугольник
Расчитать: периметр, площадь
Создать структуру по данным с консоли
*/

#include <stdio.h>
#include "triangle.h"

int main() {
  struct triangle T;
  float AC, BC, AB;

  printf("AC:\n");
  scanf("%f", &AC);
  printf("BC:\n");
  scanf("%f", &BC);
  printf("AB:\n");
  scanf("%f", &AB);

  initialize(&T, AC, BC, AB);
  printf("Perimeter = %f\n", perimeter(T));
  printf("Area = %f\n", area(T));
  return 0;
}