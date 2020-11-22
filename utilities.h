#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>


#define EXTRA_CHARS 20


void check_malloc(const void* pointer);
char* cut_string_revese(char* string, int string_lenght, char cutting_point);
int get_num_of_lines_in_file(char* file_path);
#pragma once
