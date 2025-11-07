/* student1.h */
#ifndef STUDENT1_H
#define STUDENT1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int char_to_value(char c);
char value_to_char(int value);
void split_number_string(const char* number, char* integer_part, char* fractional_part);
int validate_base(int base);
int validate_number(const char* number, int base);
double string_to_decimal(const char* number, int base);
char* decimal_to_string(double number, int base, int precision);
char* student1_process(int src_base, int dest_base, const char* number);

#endif  /* STUDENT1_H */

/* 3. Auxiliary functions */
int char_to_value(char c) {
    /* Check whether the symbol is a number */
    if (c >= '0' && c <= '9') {
        return c - '0';      
    }
    else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10; 
    }
    else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10; 
    }
    return -1; 
}


char value_to_char(int value) {
    /* Converting a number to a character */
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 15) {
        return 'A' + (value - 10);
    }
    return '?'; 
}

void split_number_string(const char* number, char* integer_part, char* fractional_part) {
    /* Search for a point in a number string */
    const char* point = strchr(number, '.'); 
    if (point == NULL) {
        strcpy(integer_part, number);
        fractional_part[0] = '\0'; 
    } else {
        size_t integer_length = point - number; 
        strncpy(integer_part, number, integer_length);
        integer_part[integer_length] = '\0'; 
        strcpy(fractional_part, point + 1);
    }
}




/* 1. Validation functions */
int validate_base(int base) {   
    if (2 <= base && base <= 16){   
        return 1;
    }
    return 0;
} 

int validate_number(const char* number, int base) {
    if (!validate_base(base)) { 
        return 0;
    }
    
    if (number == NULL || number[0] == '\0') {
        return 0;
    }
    
    int point = 0; 
    int digit_before_point = 0;  
    int digit_after_point = 0;   
    
    for (const char* ptr = number; *ptr != '\0'; ptr++) {
        char ch = *ptr;
        
        if ((ch >= '0' && ch <= '9')) {
            if (ch - '0' >= base) {
                return 0; 
            }
            if (point == 0) {
                digit_before_point = 1;  
            } else {
                digit_after_point = 1;   
            }
        } else if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
            if (tolower(ch) - 'a' + 10 >= base) {
                return 0; 
            }
            if (point == 0) {
                digit_before_point = 1;  
            } else {
                digit_after_point = 1;   
            }
        } else if (ch == '.') {
            point++;
            if (point > 1) {
                return 0; 
            }
        } else {
            return 0; 
        }
    }
    
    if (!digit_before_point) {
        return 0;
    }
    
    if (point > 0 && !digit_after_point) {
        return 0;
    }
    
    return 1; 
}





/* 2. Conversion functions */
double string_to_decimal(const char* number, int base) {
    /* Checking for NULL */
    if (number == NULL) {
        return 0.0;
    }
    /* Skipping the initial spaces */
    while (isspace(*number)) {
        number++;
    }

    /* Checking for an empty string after spaces */
    if (*number == '\0') {
        return 0.0;
    }

    /* Determining the sign of a number */
    int sign = 1;
    if (*number == '+') {
        number++;
    } else if (*number == '-') {
        sign = -1;
        number++;
    }
    
    char integer_part[256] = {0};  
    char fractional_part[256] = {0}; 
    split_number_string(number, integer_part, fractional_part);

    /* Checking that the whole part is not empty */
    if (integer_part[0] == '\0') {
        return 0.0;
    }
    /* Converting the whole part */
    double integer_result = 0.0;
    for (const char* ptr = integer_part; *ptr != '\0'; ptr++) {
        int value = char_to_value(*ptr);
        if (value == -1 || value >= base) {
            return 0.0; 
        }
        integer_result = integer_result * base + value;
    }
    /* Converting the fractional part */
    double fractional_result = 0.0;
    if (strlen(fractional_part) > 0) {
        double k = 1.0 / base;
        for (const char* ptr = fractional_part; *ptr != '\0'; ptr++) {
            int value = char_to_value(*ptr);
            if (value == -1 || value >= base) {
                return 0.0; 
            }
            fractional_result += value * k;
            k /= base; 
        }
    }

    double result = integer_result + fractional_result;
    return sign * result; 
}



char* decimal_to_string(double number, int base, int precision) {

    /* Zero processing */
    if (number == 0.0) {
        char* result;
        if (precision > 0) { 
            result = (char*)malloc(precision + 4); 
            if (result == NULL) return NULL;
            snprintf(result, precision + 4, "0.%.*s", precision, "000000000000");
        } else {
            result = (char*)malloc(2); 
            if (result == NULL) return NULL;
            strcpy(result, "0");
        }
        return result;
    }
    
    /* Checking the sign */
    int sign = 1;
    if (number < 0) {
        sign = -1;
        number = -number;
    }
    
    /* Separation of whole and fractional parts */
    double integer_part_d = (long long)number;
    double fractional_part = number - integer_part_d;

    char integer_buffer[256] = {0};
    int integer_index = 0;

    /* Sequential division to calculate the whole part */
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
    /* Reversal of the whole part */
    for (int i = 0, j = integer_index - 1; i < j; i++, j--) {
        char temp = integer_buffer[i];
        integer_buffer[i] = integer_buffer[j];
        integer_buffer[j] = temp;
    }

    /* Converting the fractional part */
    char fractional_buffer[256];
    int fractional_index = 0;
    double temp_fractional = fractional_part; 
    for (int i = 0; i < precision; ++i) {
        temp_fractional *= base;
        int digit = (int)temp_fractional; 
        fractional_buffer[fractional_index++] = value_to_char(digit);
        temp_fractional -= digit; 
    }

    /* Formation of the final line */
    int total_len = (sign == -1) + integer_index + ((fractional_index > 0) ? fractional_index + 1 : 0) + 1;
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL;
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


/* 4. Main function */
char* student1_process(int src_base, int dest_base, const char* number){
    /* Checking the validity of the bases of number systems*/
    if (!validate_base(src_base) || !validate_base(dest_base)) {
        return strdup("Incorrect bases of number systems");
    }

    /* Checking the validity of the input number */
    if (!validate_number(number, src_base)) {
        return strdup("Incorrect number for the selected number system");
    }
    
    double decimal_value = string_to_decimal(number, src_base); 
    char* converted = decimal_to_string(decimal_value, dest_base, 12); 
    if (converted == NULL) {
        return strdup("Memory allocation error");
    }

    return converted;
} 