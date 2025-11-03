#include <stdio.h>
#include "student1.h"

int main(int src_base, int dest_base, const char* coord) {
    char* result = student1_process(src_base, dest_base, coord);
    if (result != NULL) {
        printf("Результат преобразования: %s\n", result);
        free(result);  
    } else {
        puts("Ошибка преобразования!");
    }

    return 0;
}