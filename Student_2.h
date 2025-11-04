#ifndef STUDENT2_H
#define STUDENT2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void bubble_sort_double(double* arr, int size);
void swap_double(double* a, double* b);
void sort_numbers(double* numbers, int count);
double calculate_mean(const double* numbers, int count);
double calculate_median(double* numbers, int count);
void find_min_max(const double* numbers, int count, double* min, double* max);
int convert_numbers(const char** number_strings, const int* bases, int count, double* results);
int validate_and_convert_number(const char* number_str, int base, double* result);
void print_sorted_results(const double* numbers, int count);
void print_statistics(double min, double max, double mean, double median);
void student2_analyze(const char** number_strings, const int* bases, int count);

#endif // STUDENT2_H

/*Bubble sorting of an array of double values*/
void bubble_sort_double(double* arr, int size) {
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (*(arr + j) > *(arr + j + 1))
				swap_double(arr + j, arr + j + 1);
}

/*Exchanging two values of the double type*/
void swap_double(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

/*Sorting an array of double numbers in ascending order*/
void sort_numbers(double* numbers, int count) {
	bubble_sort_double(numbers, count);
}

/*Calculating the arithmetic mean*/
double calculate_mean(const double* numbers, int count) {
	if (count == 0) return 0.0;

	double sum = 0.0;
	for (int i = 0; i < count; i++)
		sum += *(numbers + i);
	return sum / count;
}

/*Calculating the median of an array of double numbers*/
double calculate_median(double* numbers, int count) {
	if (count == 0) return 0.0;

	double* temp = (double*)malloc(count * sizeof(double));
	if (!temp)
		return 0.0;

	for (int i = 0; i < count; i++)
		*(temp + i) = *(numbers + i);
	sort_numbers(temp, count);

	double median;
	if (count % 2 == 0)
		median = (*(temp + count / 2 - 1) + *(temp + count / 2)) / 2.0;
	else
		median = *(temp + count / 2);

	free(temp);
	return(median);
}

/*Calculating the minimum and maximum values
of an array of double numbers*/
void find_min_max(const double* numbers, int count, double* min, double* max) {
	if (count == 0) {
		*min = *max = 0.0;
		return;
	}

	*min = *max = *(numbers);
	for (int i = 1; i < count; i++) {
		if (*(numbers + i) > *max)
			*max = *(numbers + i);
		if (*(numbers + i) < *min)
			*min = *(numbers + i);
	}
}

/*Ñonverts a single number to the decimal system*/
int validate_and_convert_number(const char* number_str, int base, double* result) {
	if (!number_str || base < 2 || base > 16)
		return 0;

	const char* dot = strchr(number_str, '.');
	double value = 0.0;

	if (dot) {
		for (const char* p = number_str; p < dot; p++) {
			int digit;
			if (*p >= '0' && *p <= '9')
				digit = *p - '0';
			else if (*p >= 'A' && *p <= 'F')
				digit = *p - 'A' + 10;
			else if (*p >= 'a' && *p <= 'f')
				digit = *p - 'a' + 10;
			else
				return 0;

			if (digit >= base) return 0;
			value = value * base + digit;
		}

		double frac = 0.0;
		double divisor = base;
		for (const char* p = dot + 1; *p; p++) {
			int digit;
			if (*p >= '0' && *p <= '9')
				digit = *p - '0';
			else if (*p >= 'A' && *p <= 'F')
				digit = *p - 'A' + 10;
			else if (*p >= 'a' && *p <= 'f')
				digit = *p - 'a' + 10;
			else
				return 0;

			if (digit >= base)
				return 0;
			frac += digit / divisor;
			divisor *= base;
		}
		value += frac;
	}
	else {
		for (const char* p = number_str; *p; p++) {
			int digit;
			if (*p >= '0' && *p <= '9')
				digit = *p - '0';
			else if (*p >= 'A' && *p <= 'F')
				digit = *p - 'A' + 10;
			else if (*p >= 'a' && *p <= 'f')
				digit = *p - 'a' + 10;
			else
				return 0;

			if (digit >= base)
				return 0;
			value = value * base + digit;
		}
	}
	*result = value;
	return 1;
}
/*Converts all numbers in the array to the decimal
system, displays the number of successfully
converted numbers, and fills the results array*/
int convert_numbers(const char** number_strings, const int* bases, int count, double* results) {
	int success_count = 0;
	for (int i = 0; i < count; i++) {
		double val;
		if (validate_and_convert_number(number_strings[i], bases[i], &val))
			*(results + success_count++) = val;
		else
			printf("Conversion error: %s (the basis %d)\n", number_strings[i], bases[i]);
	}
	return success_count;
}

/*Outputs a sorted array of numbers*/
void print_sorted_results(const double* numbers, int count) {
	printf("Sorted: ");
	for (int i = 0; i < count; i++) {
		printf("%.6g", numbers[i]);
		if (i < count - 1)
			printf(", ");
	}
	printf("\n");
}

/*Displays the minimum, maximum, mean, and median values*/
void print_statistics(double min, double max, double mean, double median) {
	printf("Min: %.6g, Max: %.6g, Mean: %.6g, Median: %.6g\n", min, max, mean, median);
}

/*Main function*/
void student2_analyze(const char** number_strings, const int* bases, int count) {
	if (count <= 0 || count > 100) {
		printf("Incorrect number of numbers.\n");
		return;
	}

	double numbers[100];
	int success_count = convert_numbers(number_strings, bases, count, numbers);

	if (success_count == 0) {
		printf("There is no correct data for analysis.\n");
		return;
	}

	sort_numbers(numbers, success_count);

	double min, max;
	find_min_max(numbers, success_count, &min, &max);
	double mean = calculate_mean(numbers, success_count);
	double median = calculate_median(numbers, success_count);

	print_sorted_results(numbers, success_count);
	print_statistics(min, max, mean, median);
}