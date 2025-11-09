#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "student1.h"
#include "student2.h"

/*student1*/
void test_char_to_value() {
    printf("Testing char_to_value\n");
    assert(char_to_value('0') == 0);
    assert(char_to_value('4') == 4);
    assert(char_to_value('A') == 10);
    assert(char_to_value('F') == 15);
    assert(char_to_value('a') == 10);
    assert(char_to_value('f') == 15);
    assert(char_to_value('Z') == -1);
    assert(char_to_value('z') == -1);
    printf("char_to_value tests passed!\n");
}

void test_value_to_char() {
    printf("Testing value_to_char\n");
    assert(value_to_char(0) == '0');
    assert(value_to_char(4) == '4');
    assert(value_to_char(10) == 'A');
    assert(value_to_char(15) == 'F');
    assert(value_to_char(-1) == '?');
    assert(value_to_char(16) == '?');
    printf("value_to_char tests passed!\n");
}

void test_validate_base() {
    printf("Testing validate_base\n");
    assert(validate_base(2) == 1);
    assert(validate_base(8) == 1);
    assert(validate_base(10) == 1);
    assert(validate_base(16) == 1);
    assert(validate_base(1) == 0);
    assert(validate_base(19) == 0);
    assert(validate_base(0) == 0);
    assert(validate_base(-1) == 0);
    printf("validate_base tests passed!\n");
}

void test_validate_number() {
    printf("Testing validate_number\n");
    assert(validate_number("1101", 2) == 1);
    assert(validate_number("345", 10) == 1);
    assert(validate_number("BCD", 16) == 1);
    assert(validate_number("123.45", 10) == 1);
    assert(validate_number("1010.101", 2) == 1);

    assert(validate_number("ABZ", 16) == 0);
    assert(validate_number("3", 2) == 0);
    assert(validate_number("123.ABC", 10) == 0);
    assert(validate_number("12..34", 10) == 0);
    assert(validate_number("123.", 10) == 0);
    assert(validate_number(".123", 10) == 0);
    assert(validate_number("", 10) == 0);
    assert(validate_number(".", 10) == 0);
    assert(validate_number(" ", 10) == 0);
    assert(validate_number("\t\t", 10) == 0);
    printf("validate_number tests passed!\n");
}

void test_split_number_string() {
    printf("Testing split_number_string\n");

    char integer[100], fractional[100];

    split_number_string("456", integer, fractional);
    assert(strcmp(integer, "456") == 0);
    assert(strcmp(fractional, "") == 0);

    split_number_string("12345.6789", integer, fractional);
    assert(strcmp(integer, "12345") == 0);
    assert(strcmp(fractional, "6789") == 0);

    split_number_string(".123", integer, fractional);
    assert(strcmp(integer, "") == 0);
    assert(strcmp(fractional, "123") == 0);

    split_number_string("999", integer, fractional);
    assert(strcmp(integer, "999") == 0);
    assert(strcmp(fractional, "") == 0);

    printf("split_number_string tests passed!\n");
}

void test_string_to_decimal() {
    printf("Testing string_to_decimal\n");

    assert(string_to_decimal("1101", 2) == 13.0);
    assert(string_to_decimal("255", 10) == 255.0);
    assert(string_to_decimal("FF", 16) == 255.0);

    assert(fabs(string_to_decimal("101.1", 2) - 5.5) < 1e-10);
    assert(fabs(string_to_decimal("0.25", 10) - 0.25) < 1e-10);
    assert(fabs(string_to_decimal("C.8", 16) - 12.5) < 1e-10);

    assert(string_to_decimal("-1101", 2) == -13.0);
    assert(fabs(string_to_decimal("-255.5", 10) - (-255.5)) < 1e-10);
    assert(fabs(string_to_decimal("-FF.C", 16) - (-255.75)) < 1e-10);

    assert(string_to_decimal("+1101", 2) == 13.0);
    assert(fabs(string_to_decimal("0.01", 10) - 0.01) < 1e-10);
    assert(fabs(string_to_decimal("A.B", 16) - 10.6875) < 1e-10);
    printf("string_to_decimal tests passed!\n");
}

void test_decimal_to_string() {
    printf("Testing decimal_to_string\n");

    char* result;

    result = decimal_to_string(13.0, 2, 0);
    assert(strcmp(result, "1101") == 0);
    free(result);

    result = decimal_to_string(255.0, 16, 0);
    assert(strcmp(result, "FF") == 0);
    free(result);

    result = decimal_to_string(10.5, 2, 4);
    assert(strstr(result, "1010.1") != NULL);
    free(result);

    result = decimal_to_string(0.25, 10, 3);
    assert(strstr(result, "0.250") != NULL);
    free(result);

    result = decimal_to_string(1023.0, 16, 0);
    assert(strcmp(result, "3FF") == 0);
    free(result);

    result = decimal_to_string(0.125, 2, 4);
    assert(strstr(result, "0.001") != NULL);
    free(result);

    result = decimal_to_string(0.0, 10, 2);
    assert(strcmp(result, "0") == 0 || strcmp(result, "0.00") == 0);
    free(result);

    result = decimal_to_string(-13.0, 2, 0);
    assert(strcmp(result, "-1101") == 0);
    free(result);

    result = decimal_to_string(-255.0, 16, 0);
    assert(strcmp(result, "-FF") == 0);
    free(result);

    printf("decimal_to_string tests passed!\n");
}

void test_student1_process() {
    printf("Testing student1_process\n");

    char* result;

    result = student1_process(10, 2, "13");
    assert((result, "1101"));
    free(result);

    result = student1_process(2, 10, "1101");
    assert((result, "13"));
    free(result);

    result = student1_process(10, 16, "255");
    assert((result, "FF"));
    free(result);

    result = student1_process(10, 2, "10.5");
    assert(strstr(result, "1010.1") != NULL);
    free(result);

    result = student1_process(1, 10, "123");
    assert(strcmp(result, "Incorrect bases of number systems") == 0);
    free(result);

    result = student1_process(10, 17, "123");
    assert(strcmp(result, "Incorrect bases of number systems") == 0);
    free(result);

    result = student1_process(2, 10, "102");
    assert(strcmp(result, "Incorrect number for the selected number system") == 0);
    free(result);

    printf("student1_process tests passed!\n");
}

void test_main() {
    printf("Testing the main functionality\n");

    char* result;

    result = student1_process(3, 12, "102.11");
    printf("Ternary '102.11' in duodecimal system: %s\n", result);
    free(result);

    result = student1_process(8, 16, "45.3");
    printf("Octal '45.3' in hexadecimal system: %s\n", result);
    free(result);

    result = student1_process(16, 10, "D.F");
    printf("Hexadecimal 'D.F' in decimal system: %s\n", result);
    free(result);

    result = student1_process(2, 10, "1011.01");
    printf("Binary '1011.01' in decimal system: %s\n", result);
    free(result);

    result = student1_process(10, 2, "31.75");
    printf("Decimal '31.75' in binary system: %s\n", result);
    free(result);

    printf("Main tests completed!\n");
}

/*student2*/
void test_sort_numbers() {
    printf("Testing sort_numbers\n");
    /*Normal array*/
    double arr_1[] = { 5.2, 1.1, 3.3, 2.8, 4.2 };
    int count = 5;
    sort_numbers(arr_1, count);
    for (int i = 0; i < count - 1; i++)
        assert(*(arr_1 + i) <= *(arr_1 + i + 1));

    /*Empty array*/
    double arr_2[] = { 0 };
    count = 0;
    sort_numbers(arr_2, count);
    for (int i = 0; i < count - 1; i++)
        assert(*(arr_2 + i) <= *(arr_2 + i + 1));

    /*There are equal values*/
    double arr_3[] = { 5.23512, 8.56, 5.23512, 5.23512, 6.0 };
    count = 5;
    sort_numbers(arr_3, count);
    for (int i = 0; i < count - 1; i++)
        assert(*(arr_3 + i) <= *(arr_3 + i + 1));

    printf("sort_numbers tests passed!\n");
}

void test_calculate_mean() {
    printf("Testing calculate_mean\n");
    /*Integer values*/
    double arr_1[] = { 2.0, 4.0, 6.0, 8.0 };
    double mean = calculate_mean(arr_1, 4);
    assert(mean == 5.0);

    /*Not just integer values*/
    double arr_2[] = { 0.55, 3.45, 7.124, 8.957 };
    mean = calculate_mean(arr_2, 4);
    assert(fabs(mean - 5.02025) < 1e-10);

    /*Empty array*/
    double arr_3[] = { 0 };
    mean = calculate_mean(arr_3, 0);
    assert(!mean);

    printf("calculate_mean tests passed!\n");
}

void test_calculate_median() {
    printf("Testing calculate_median\n");
    /*An even number of elements*/
    double arr_1[] = { 5.23, 2.14, 8.735, 1.444, 4.877 };
    assert(calculate_median(arr_1, 5) == 4.877);

    /*An odd number of elements*/
    double arr_2[] = { 9832.4561, 56454.311, 1567.5445, 87.024 };
    assert(fabs(calculate_median(arr_2, 4) - 5700.0003) < 1e-10);

    /*Empty array*/
    double arr_3[] = { 0 };
    assert(!(arr_3, 0));
    printf("calculate_median tests passed!\n");

}

void test_find_min_max() {
    printf("Testing find_min_max\n");

    double min, max;

    /*Ordinary*/
    double arr_1[] = { 10.12, 2.1, 30.23, 4.984, 25.004 };
    find_min_max(arr_1, 5, &min, &max);
    assert(min == 2.1);
    assert(max == 30.23);

    /*Empty array*/
    double arr_2[] = { 0 };
    find_min_max(arr_2, 0, &min, &max);
    assert(!min);
    assert(!max);

    printf("find_min_max tests passed!\n");
}

void test_validate_and_convert_number() {
    printf("Testing validate_and_convert_number\n");

    double result;

    /*Normal*/
    assert(validate_and_convert_number("1101.1", 2, &result));
    assert(fabs(result - 13.5) < 1e-10);

    assert(validate_and_convert_number("A.B", 16, &result));
    assert(fabs(result - 10.6875) < 1e-10);

    assert(validate_and_convert_number("25.75", 10, &result));
    assert(fabs(result - 25.75) < 1e-10);

    /*Error*/
    assert(!validate_and_convert_number("19", 0, &result));

    assert(!validate_and_convert_number("G", 16, &result));

    printf("validate_and_convert_number tests passed!\n");
}

void test_convert_numbers() {
    printf("Testing convert_numbers\n");

    const char* nums[] = { "105.7", "1D.A", "1101.101", "25.75" };
    int bases[] = { 8, 16, 2, 10 };
    double results[4];
    int success = convert_numbers(nums, bases, 4, results);

    assert(success == 4);
    assert(fabs(results[0] - 69.875) < 1e-10);
    assert(fabs(results[1] - 29.625) < 1e-10);
    assert(fabs(results[2] - 13.625) < 1e-10);
    assert(fabs(results[3] - 25.75) < 1e-10);

    printf("convert_numbers tests passed!\n");
}

void test_student2_analyze() {
    printf("Testing student2_analyze (integration test)\n");

    /*Normal*/
    const char* nums_1[] = { "15.7", "D.A", "1101.101", "25.75", "19" };
    int bases_1[] = { 8, 16, 2, 10, 8 };
    int count = 5;

    printf("\n\nTest 1\n\nInput:\nNums: {15.7, D.A, 1101.101, 25.75, 19}\nBases: {8, 16, 2, 10, 8}");
    printf("\n\nOutput:\n");
    student2_analyze(nums_1, bases_1, count);

    /*Errors in the bases*/
    const char* nums_2[] = { "15.7", "D.A", "1101.101", "25.75", "19" };
    int bases_2[] = { 1, 2, 2, 2, 20 };
    count = 5;

    printf("\n\nTest 2\n\nInput:\nNums: {15.7, D.A, 1101.101, 25.75, 19}\nBases: {1, 2, 2, 2, 20}");
    printf("\n\nOutput:\n");
    student2_analyze(nums_2, bases_2, count);

    /*Errors in the numbers*/
    const char* nums_3[] = { "19.7", "D.A", "1101.101", "25.75A", "19" };
    int bases_3[] = { 8, 16, 2, 10, 10 };
    count = 5;

    printf("\n\nTest 3\n\nInput:\nNums: {19.7, D.A, 1101.101, 25.75A, 19}\nBases: {8, 16, 2, 10, 10}");
    printf("\n\nOutput:\n");
    student2_analyze(nums_3, bases_3, count);

    /*Empty arrays*/
    const char* nums_4[] = { 0 };
    int bases_4[] = { 0 };
    count = 0;

    printf("\n\nTest 4\n\nInput:\nNums: {}\nBases: {}");
    printf("\n\nOutput:\n");
    student2_analyze(nums_4, bases_4, count);

    /*Normal*/
    const char* nums_5[] = { "219.A", "BAD.1", "123.321", "345.75A", "8000.0008", "32.2" };
    int bases_5[] = { 13, 16, 5, 11, 9, 4 };
    count = 6;

    printf("\n\nTest 5\n\nInput:\nNums: {219.A, BAD.1, 123.321, 345.75A, 8000.0008, 32.2}\nBases: {13, 16, 5, 11, 9, 4}");
    printf("\n\nOutput:\n");
    student2_analyze(nums_5, bases_5, count);

    printf("\nstudent2_analyze test completed!\n");
}


int main() {
    /*student1*/
    printf("Starting tests for student1 functions\n\n");

    test_char_to_value();
    test_value_to_char();
    test_validate_base();
    test_validate_number();
    test_split_number_string();
    test_string_to_decimal();
    test_decimal_to_string();
    test_student1_process();
    test_main();

    printf("\nAll tests passed successfully!\n");

    /*student2*/
    printf("\nStarting tests for student2 functions\n\n");

    test_sort_numbers();
    test_calculate_mean();
    test_calculate_median();
    test_find_min_max();
    test_validate_and_convert_number();
    test_convert_numbers();
    test_student2_analyze();

    printf("\nAll tests passed successfully!\n");

    return 0;
}