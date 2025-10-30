// student1.h
#ifndef STUDENT1_H
#define STUDENT1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


// 3. Auxiliary functions
int char_to_value(char c) {
    // Check whether the symbol is a number
    if (c >= '0' && c <= '9') {
        return c - '0';      // Returning the numeric value of the digit
    }
    // Check if the character is a capital letter A-F
    else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10; // The letters A-F correspond to the numbers 10-15
    }
    // Check if the character is a lowercase letter a-f
    else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10; // The letters a-f also correspond to the numbers 10-15
    }
    return -1; // Incorrect character
}


char value_to_char(int value) {
    // Converting a number to a character
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 15) {
        return 'A' + (value - 10);
    }
    return '?'; // Incorrect value
}

void split_number_string(const char* number, char* integer_part, char* fractional_part) {
    const char* dot_position = strchr(number, '.'); // Search for a point in a number string
    
    if (dot_position == NULL) {
        // If there is no dot, the entire line is an integer part, and the fractional part is empty
        strcpy(integer_part, number);
        fractional_part[0] = '\0'; // Empty line
    } else {
        // Copying the whole part (all the way to the dot)
        size_t integer_length = dot_position - number; // Length of the whole part
        strncpy(integer_part, number, integer_length);
        integer_part[integer_length] = '\0'; // Completing the line
        // Copying the fractional part (everything after the dot)
        strcpy(fractional_part, dot_position + 1);
    }
}













// 1. Validation functions
int validate_base(int base) {   
    if (2 <= base && base <= 16){   
        return 1;
    }
    return 0;
} 

int validate_number(const char* number, int base) {
    if (!validate_base(base)) { // Checking the validity of the foundation
        return 0;
    }
    int point = 0; // Point count counter
    for (const char* ptr = number; *ptr != '\0'; ptr++) {
        char ch = *ptr;
        // Checking valid characters
        if ((ch >= '0' && ch <= '9')) {
            if (ch - '0' >= base) {
                return 0; // The number is larger than allowed in this number system
            }
        } else if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
            if (tolower(ch) - 'a' + 10 >= base) {
                return 0; // The letter is larger than allowed in this number system
            }
        } else if (ch == '.') {
            point++;
            if (point > 1) {
                return 0; // More than one point
            }
        } else {
            return 0; // Unsupported character
        }
    }
    return 1; // If everything is correct
}








// 2. Conversion functions
double string_to_decimal(const char* number, int base) {
    // Skipping the initial spaces
    while (isspace(*number)) {
        number++;
    }
    // Checking the sign
    int sign = 1;
    if (*number == '+') {
        number++;
    } else if (*number == '-') {
        sign = -1;
        number++;
    }
    
     char integer_part[256], fractional_part[256];
    split_number_string(number, integer_part, fractional_part);

    double integer_result = 0.0;
    for (const char* ptr = integer_part; *ptr != '\0'; ptr++) {
        int value = char_to_value(*ptr);
        if (value == -1 || value >= base) {
            return 0.0;
        }
        integer_result = integer_result * base + value;
    }

    double fractional_result = 0.0;
    if (strlen(fractional_part) > 0) {
        double multiplier = 1.0 / base;
        for (const char* ptr = fractional_part; *ptr != '\0'; ptr++) {
            int value = char_to_value(*ptr);
            if (value == -1 || value >= base) {
                return 0.0;
            }
            fractional_result += value * multiplier;
            multiplier /= base;
        }
    }

    double result = integer_result + fractional_result;
    return sign * result; 
}





char* decimal_to_string(double number, int base, int precision) {
    // Checking whether the passed argument is an undefined number 
    if (isnan(number)) {
        char* result = (char*)malloc(4);  // Allocate 4 bytes of memory
        strcpy(result, "NaN"); // Writing the string "NaN" to the allocated memory area
        return result;
    }
    // Checking a number for infinity
    if (isinf(number)) {
        if (number > 0) { // Positive infinity
            char* result = (char*)malloc(4);  // "Inf" + '\0' = 4 bytes
            strcpy(result, "Inf");
            return result;
        } else {
            // Negative infinity
            char* result = (char*)malloc(5);  // "-Inf" + '\0' = 5 bytes
            strcpy(result, "-Inf");
            return result;
        }
    } 
    // Zero processing
    if (number == 0.0) {
        char* result;
        if (precision > 0) { 
            result = (char*)malloc(precision + 4); // "0." + precision digits + '\0'
            if (result == NULL) return NULL;
            sprintf(result, "0.%.*s", precision, "000000000000"); 
        } else {
            result = (char*)malloc(2); // "0" + '\0'
            if (result == NULL) return NULL;
            strcpy(result, "0");
        }
        return result;
    }
    
    // Checking the sign
    int sign = 1;
    if (number < 0) {
        sign = -1;
        number = -number;
    }
    
    // Целая и дробная части числа
    double integer_part_d = floor(number);
    double fractional_part = number - integer_part_d;

    // Буфер для хранения целых значений
    char integer_buffer[256] = {0};
    int integer_index = 0;

    // Последовательное деление для вычисления целой части
    long integer_part = (long)integer_part_d;
    if (integer_part == 0) {
        integer_buffer[integer_index++] = '0';
    } else {
        while (integer_part > 0) {
            int remainder = integer_part % base;
            integer_buffer[integer_index++] = value_to_char(remainder);
            integer_part = integer_part / base;
        }
    }
     // Разворот целой части вручную без функции
    for (int i = 0, j = integer_index - 1; i < j; i++, j--) {
        char temp = integer_buffer[i];
        integer_buffer[i] = integer_buffer[j];
        integer_buffer[j] = temp;
    }

    // Дробная часть (переводим в нужную систему счисления)
    char fractional_buffer[256];
    int fractional_index = 0;
    double temp_fractional = fractional_part;
    for (int i = 0; i < precision; ++i) {
        temp_fractional *= base;
        int digit = (int)temp_fractional;
        fractional_buffer[fractional_index++] = value_to_char(digit);
        temp_fractional -= digit;
    }

    // Подготавливаем итоговую строку
    int total_len = (sign == -1) + integer_index + ((fractional_index > 0) ? fractional_index + 1 : 0) + 1;
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    if (sign == -1) {
        result[index++] = '-';
    }
    memcpy(result + index, integer_buffer, integer_index);
    index += integer_index;

    if (fractional_index > 0) {
        result[index++] = '.';
        memcpy(result + index, fractional_buffer, fractional_index);
        index += fractional_index;
    }
    result[index] = '\0';

    return result;
}






















// 4. Main function
char* student1_process(int src_base, int dest_base, const char* number){
    // Checking the validity of the bases of number systems
    if (!validate_base(src_base) || !validate_base(dest_base)) {
        return "Incorrect bases of number systems";
    }

    // Checking the validity of the input number
    if (!validate_number(number, src_base)) {
        return "Incorrect number for the selected number system";
    }

    // Conversion to decimal system
    double decimal_value = string_to_decimal(number, src_base);

    // Conversion to the target number system
    char* converted = decimal_to_string(decimal_value, dest_base, 12);

    return converted;
}



#endif // STUDENT1_H