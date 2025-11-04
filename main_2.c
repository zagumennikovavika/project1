#include <stdio.h>
#include "Student_2.h"

int main(void) {
    // Пример входных данных
    const char* numbers[] = { "15.7", "D.A", "1101.101", "25.75", "1B", "10" };
    const int bases[] = { 8, 16, 2, 10, 16, 2 };
    int count = 6;

    printf("Analysis of telemetry data\n");
    student2_analyze(numbers, bases, count);

    return 0;
}
