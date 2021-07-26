/*
1
Использовать перечислимый тип для хранения названий дней недели (месяцев, и т.п.). Вывести на консоль значение целого числа, соответствующее указанному в варианте задания элементу перечисления.
Виды электрических ламп (накаливания, дневного света, галогенные и т.п.).
Отобразить: Галогенная лампа.

2
Разработать структуру, описывающую координаты и другие требуемые параметры простейшей геометрической фигуры (отрезок прямой, прямоугольник, квадрат, треугольник, окружность) с расчётом одного из её параметров (периметра, площади, длины окружности и т.п.). Исходные данные для расчёта указать в тексте программы.
Результат расчёта вывести на консоль.
Фигура: Треугольник

3
Разработать битовое поле, описывающее состояния элементов прибора. Ввести с консоли число в 16-ричной системе счисления, преобразовать его в битовое поле за счёт использования объединения. Вывести на консоль состояния элементов прибора, соответствующие состоянию битов во введённом числе.
Прибор: Card-reader. Элементы: включён, активна карта SD, активна карта Compact Flash, активна карта MemoyStick.

*/

#include <stdio.h> 
#include <math.h> 

struct squares { 

int x; 
int y; 
int side; 
}; 

enum lamps {
  Светодиодная,
  Галогенная,
  Энергосберегающая,
};

struct coords {int x, y;};

struct triangle {
  int side_1, side_2, side_3, perimeter;
  struct coords apex1, apex2, apex3;
};

union card_reader {
  unsigned input;
  struct {
    unsigned active : 1;
    unsigned sd_card_active : 1;
    unsigned compact_flash_ready : 1;
    unsigned memory_stick_ready : 1;
  };
};

typedef union card_reader states; 

int main(void) {
  printf("Лампа: %d\n", Галогенная);
  struct triangle a;
  a.side_1 = 3;
  a.side_2 = 4;
  a.side_3 = 5;
  a.apex1.x = 1;
  a.apex1.y = 1;
  a.apex2.x = 4;
  a.apex2.y = 1;
  a.apex3.x = 4;
  a.apex3.y = 5;
  a.perimeter = a.side_1 + a.side_2 + a.side_3;
  printf("Периметр треугольника: %d\n", a.perimeter);
  
  states s; 
  scanf("%x", &s.input); 
  printf("Active: %d\n", s.active); 
  printf("SD card active: %d\n", s.sd_card_active); 
  printf("Compact Flash ready: %d\n", s.compact_flash_ready); 
  printf("Memory Stick ready: %d\n", s.memory_stick_ready);

  return 0;
}
