// student1.h
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

#endif // STUDENT1_H

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
    const char* point = strchr(number, '.'); // Search for a point in a number string
    
    if (point == NULL) {
        // If there is no dot, the entire line is an integer part, and the fractional part is empty
        strcpy(integer_part, number);
        fractional_part[0] = '\0'; // Empty line
    } else {
        // Copying the whole part (all the way to the dot)
        size_t integer_length = point - number; // Length of the whole part
        strncpy(integer_part, number, integer_length);
        integer_part[integer_length] = '\0'; // Completing the line
        // Copying the fractional part (everything after the dot)
        strcpy(fractional_part, point + 1);
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
    // Checking for NULL
    if (number == NULL) {
        return 0.0;
    }
    // Skipping the initial spaces
    while (isspace(*number)) {
        number++;
    }

    // Checking for an empty string after spaces
    if (*number == '\0') {
        return 0.0;
    }

    // Checking the sign
    int sign = 1;
    if (*number == '+') {
        number++;
    } else if (*number == '-') {
        sign = -1;
        number++;
    }

    // Checking that there are numbers after the sign
    if (*number == '\0') {
        return 0.0;
    }
    // Arrays for storing whole and fractional parts of a number
    char integer_part[256] = {0};  
    char fractional_part[256] = {0}; 
    split_number_string(number, integer_part, fractional_part);

    // Checking that the whole part is not empty
    if (integer_part[0] == '\0') {
        return 0.0;
    }
    // Converting the whole part
    double integer_result = 0.0;
    for (const char* ptr = integer_part; *ptr != '\0'; ptr++) {
        int value = char_to_value(*ptr);
        if (value == -1 || value >= base) {
            return 0.0; // Invalid character
        }
        integer_result = integer_result * base + value;
    }
    // Converting the fractional part
    double fractional_result = 0.0;
    if (strlen(fractional_part) > 0) {
        double k = 1.0 / base;
        for (const char* ptr = fractional_part; *ptr != '\0'; ptr++) {
            int value = char_to_value(*ptr);
            if (value == -1 || value >= base) {
                return 0.0; // Invalid character
            }
            fractional_result += value * k;
            k /= base; // Reducing the weight for the next figure
        }
    }

    double result = integer_result + fractional_result;
    return sign * result; 
}





char* decimal_to_string(double number, int base, int precision) {

    // Zero processing
    if (number == 0.0) {
        char* result;
        if (precision > 0) { 
            result = (char*)malloc(precision + 4); // "0." + precision digits + '\0'
            if (result == NULL) return NULL;
            snprintf(result, precision + 4, "0.%.*s", precision, "000000000000");
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
    
    // Separation of whole and fractional parts
    double integer_part_d = floor(number);
    double fractional_part = number - integer_part_d;

    // Buffer for the whole part
    char integer_buffer[256] = {0};
    int integer_index = 0;

    // Sequential division to calculate the whole part
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
    // Reversal of the whole part
    for (int i = 0, j = integer_index - 1; i < j; i++, j--) {
        char temp = integer_buffer[i];
        integer_buffer[i] = integer_buffer[j];
        integer_buffer[j] = temp;
    }

    // Converting the fractional part
    char fractional_buffer[256];
    int fractional_index = 0;
    double temp_fractional = fractional_part; // A copy of the fractional part
    for (int i = 0; i < precision; ++i) {
        temp_fractional *= base;
        int digit = (int)temp_fractional; //Take the whole part of the multiplication result
        fractional_buffer[fractional_index++] = value_to_char(digit);
        temp_fractional -= digit; //Remove the whole part, leaving only the fractional part
    }

    // Formation of the final line
    int total_len = (sign == -1) + integer_index + ((fractional_index > 0) ? fractional_index + 1 : 0) + 1;
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    if (sign == -1) {
        result[index++] = '-';
    }
    memcpy(result + index, integer_buffer, integer_index); // Copy the whole part of the number to the final line
    index += integer_index; // Moving the index by the length of the whole part

    if (fractional_index > 0) {
        result[index++] = '.';
        memcpy(result + index, fractional_buffer, fractional_index); // Copying the fractional part to the final line
        index += fractional_index; // Moving the index by the length of the fractional part
    }
    result[index] = '\0'; 

    return result;
}



// 4. Main function
char* student1_process(int src_base, int dest_base, const char* number){
    // Checking the validity of the bases of number systems
    if (!validate_base(src_base) || !validate_base(dest_base)) {
        return strdup("Incorrect bases of number systems");
    }

    // Checking the validity of the input number
    if (!validate_number(number, src_base)) {
        return strdup("Incorrect number for the selected number system");
    }
    
    double decimal_value = string_to_decimal(number, src_base); // Conversion to decimal system 
    char* converted = decimal_to_string(decimal_value, dest_base, 12); // Conversion to the target number system
    if (converted == NULL) {
        return strdup("Memory allocation error");
    }

    return converted;
} 



