#include <stdio.h>
#include <string.h>

void create_(char* file_name, int files_count, char* files[]) {
    FILE *file;
    file = fopen(file_name, "w");
    unsigned char file_name_length;
    unsigned int body_size;
    int i, j;
    for (i = 0; i < files_count; i++) {
        file_name_length = strlen(files[i]);
        fputc(file_name_length, file);

        int file_name_length_int = (int)file_name_length;
        for (j = 0; j < file_name_length_int; j++)
            fputc(files[i][j], file);

        FILE *for_archive;
        for_archive = fopen(files[i], "r");
        fseek(for_archive, 0, SEEK_END);

        body_size = ftell(for_archive); //установили конец файла
        fseek(for_archive, 0, SEEK_SET);
        fwrite(&body_size, sizeof(unsigned int), 1, file); //тут сохраняем размер файла
        for (j = 0; j < body_size; j++) //
            fputc(getc(for_archive), file);
    }
}

void extract_(char* file_name) {
    FILE *file;
    file = fopen(file_name, "r");
    fseek(file, 0, SEEK_END); // указатель на конец файла
    unsigned int end_of_file = ftell(file);
    fseek(file, 0, SEEK_SET);
    int i;

    while(ftell(file) < end_of_file) {
        unsigned int size = getc(file);
        char name_of_file[size];
        for (i = 0; i < size; i++)
            name_of_file[i] = getc(file); // записали имя файла

        fread(&size, sizeof(unsigned int), 1, file); //записали размер содержимого файла
        FILE *extracting_file;
        extracting_file = fopen(name_of_file, "w");
        for (i = 0; i < size; i++)
            fputc(getc(file), extracting_file);
        fclose(extracting_file);
    }
}

void list_(char* file_name){
    FILE *file;
    file = fopen(file_name, "r");
    fseek(file, 0, SEEK_END);
    unsigned int end_of_file = ftell(file);
    fseek(file, 0, SEEK_SET);
    int i;

    while(ftell(file) < end_of_file) {
        unsigned int size = getc(file);
        char name_of_file[size];
        for (i = 0; i < size; i++)
            name_of_file[i] = getc(file);
        printf("%s\n", name_of_file);
        fread(&size, sizeof(unsigned int), 1, file);
        fseek(file, size, SEEK_CUR);
    }
}

int main (int argc, char* argv[]) {
    char normal_file[11] = "--file";
    char create[8] = "--create";
    char extract[9] = "--extract";
    char list[6] = "--list";
    char file_name[20];

    strcpy(file_name, argv[2]);
    if (argc > 4) {
        int files_count = argc - 4;
        create_(file_name, files_count, &argv[4]);
    }
    else if (!(strcmp(argv[3], "--extract")))
        extract_(file_name);
    else
        list_(file_name);
    printf("done.\n");
    return 0;
}