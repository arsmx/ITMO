/*
Операции ввода-вывода

Осуществить конкатенацию двух файлов за счёт создания третьего файла.
*/
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE *file_1, *file_2, *file_3;
    file_1 = fopen(argv[1], "rt");
    file_2 = fopen(argv[2], "rt");
    file_3 = fopen(argv[3], "wt");

    char temp, first[80], second[80];
    int i = 0;
    
    while((temp = getc(file_1)) != EOF) {
        first[i] = temp;
        i++;
    }
    first[i] = '\0';
    i = 0;

    while((temp = getc(file_2)) != EOF) {
        second[i] = temp;
        i++;
    }
    second[i] = '\0';

    strcat(first, second);
    fprintf(file_3, "%s", first);
    return 0;
}