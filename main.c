#include <stdio.h>
#include "student1.h"

int main(void) {
    int src_base = 3;
    int dest_base = 12;
    const char* number = "120.11";

    char* result = student1_process(src_base, dest_base, number);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);  
    } else {
        puts("Error occurred during conversion.");
    }

    return 0;
}