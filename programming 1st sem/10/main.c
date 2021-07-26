/*
Функции

3. Дано натуральное число n. Разработать функцию формирования массива, элементами которого являются цифры числа n.
5.	Разработать рекурсивную функцию, удаляющую из строки все лишние пробелы. Пробелы считаются лишними, если их подряд идет более двух, если они стоят в конце строки после последней точки, если стоят после открывающегося парного знака препинания.
*/

#include <stdio.h>
#include <string.h>

int n, count = 0, a[100];
float interest_rate;
char string[100] = {"sdf(  dkk { ds[ d  sdfsdf"};


int main() {
  //3
  printf("N:\n");
  scanf("%d", &n);

  while(n) {  
    a[count++] = n % 10; 
    n /= 10;

  } 

  for (int i = 99; i >= 0; i--) {
    if (a[i] != 0) {
      for (int j = i; j >= 0; j--)
        printf("%d ", a[j]);
    i = -1;
    }
  }

  //5
  printf("\nString: %s\n", string);

  for (int i = 0; i < 100; i++) {
      // двойные пробелы
      if (string[i] == ' ' && string[i + 1] == ' ') {
          for (int j = i; j < 99; j++)
              string[j] = string[j + 1];
          i = 0;
      }
      // пробелы после последней точки
      if (string[i] == '.' && string[i + 1] == ' ' && string[i + 2] == "")
          for (int j = i + 1; j < 100; j++)
              string[j] = "";
      // пробелы открывающегося парного знака препинания
      if ((string[i] == '(' || string[i] == '{' || string[i] == '[') && string[i + 1] == ' ') {
          for (int j = i + 1; j < 99; j++)
              string[j] = string[j + 1];
          i = 0;
      }
  }
  printf("\nFixed string:\n%s", string);
  

  return 0;
}