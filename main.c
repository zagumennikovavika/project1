#include <stdio.h>
#include "student1.h"

int main(void) {
    int src_base = 10;
    int dest_base = 2;
    const char* number = "13";
    
    char* result = student1_process(src_base, dest_base, number);
    if (result != NULL) {
        printf("Результат преобразования: %s\n", result);
        free(result);  
    } else {
        puts("Ошибка преобразования!");
    }

    return 0;
}