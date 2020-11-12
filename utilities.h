#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS_CODE ((int)(0))
#define FAILURE_CODE ((int)(-1))
#define EXRTA_CHARECTERS 6
#define COMMAND_CHARECTERS 9

void check_malloc(const void* pointer);
char* cut_string_revese(char* string, int string_lenght, char cutting_point);
#pragma once
