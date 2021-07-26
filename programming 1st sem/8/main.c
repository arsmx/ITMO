/*
Работа со строками

1. Осуществить конкатенацию (сложение) двух строк.
3. Осуществить сравнение двух строк.
8. Осуществить поиск в строке первого вхождения указанного символа.
10. Осуществить поиск в одной строке любого из множества символов, входящих во вторую
строку.
12. Определить длину отрезка одной строки, не содержащего символы второй строки.
*/
#include <stdio.h>
#include<string.h>


char string1[100], string2[100], string3[100], symbol, *pos;


int main() {
  printf("First string:\n");
  gets(string1);
  printf("Second string:\n");
  gets(string2);
  snprintf(string3, sizeof string1, "%s%s", string1, string2);
  //1
  printf("Concatenation is\n%s\n", string3);
  //3
  if (strcmp (string1, string2)==0)
      printf("Strings are the same\n");
  else
      printf("Strings are different\n");
  //8
  printf("Character to find:\n");
  scanf("%c", &symbol);
  pos = strchr(string1, symbol);
  if (pos==NULL)
      printf("Symbol did not found\n");
  else
      printf("Symbol %c is on #%d position\n", symbol, pos - string1 + 1);
  //10
  for (int i = 0; i < 100; i++) {
      pos = strchr(string1, string2[i]);
      if (pos!=NULL) {
          printf("Symbol %c is on #%d position\n", string2[i], pos - string1 + 1);
          break;
      }
  }
  //12
    for (int i = 0; i < 100; i++) {
        pos = strchr(string1, string2[i]);
        if (pos!=NULL) {
            printf("First %d symbols of first string are identical\n", pos - string1);
            break;
        }
    }
  return 0;
}