/*
Циклы и ветвления

3.	Преобразовать цифру, введённую с консоли в строку,  содержащую числительное, соответствующее этой цифре. Результат вывести на консоль.
5.	Вывести на консоль состояние банковского счёта по истечении каждого полного месяца, при нахождении средств на счёте в течение введённого с консоли количества месяцев. Годовую процентную ставку и начальную сумму на счёте ввести с консоли. Моделируемый счёт является счётом с ежемесячной выплатой процентов и последующей капитализацией, а также не предусматривает частичное снятие средств.
*/
#include <stdio.h>
#include <string.h>
int n, start_money;
float interest_rate;
char number[100];
const char *str[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const char *str10[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const char *str100[] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};


int main() {
  //3
  printf("Number:\n");
  scanf("%d", &n);
  if (n < 10) {
    strcpy(number, str[n]);
    printf("Number is: %s\n", number);
  }
  else if (n < 20) {
    strcpy(number, str10[n % 10]);
    printf("Number is:\n%s\n", number);
  }
  else if (n < 100) {
    strcpy(number, str100[n / 10]);
    printf("Number is:\n%s-", number);
    strcpy(number, str[n % 10]);
    printf("%s\n", number);
  }
  else
    printf("Number is over 99\n");
  //5
  printf("Interest rate:\n");
  scanf("%f", &interest_rate);
  printf("Start money:\n");
  scanf("%d", &start_money);
  int m = n;
  while(m > 0){
    start_money += start_money * (interest_rate / 1200);
    m--; 
  }
    
  printf("Money after %d months:\n%d", n, start_money);

  return 0;
}