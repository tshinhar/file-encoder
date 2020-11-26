#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>


#define EXTRA_CHARS 20

typedef struct {
	int first_byte_index;
	int last_byte_index;
} LINE_BOUNDARY;

void check_malloc(const void* pointer);
char* cut_string_revese(char* string, int string_length, char cutting_point);
int get_num_of_lines_in_file(char* file_path);
int get_num_bytes_per_line(char* file_path, int* bytes_per_line_array);
void calc_line_boundaries(int *bytes_per_line_array, int num_of_lines, LINE_BOUNDARY *line_boundaries_array);
#pragma once
