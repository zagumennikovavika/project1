#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "student1.h"

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

int main() {
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
    return 0;
}