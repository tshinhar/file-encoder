#include "utilities.h"

HANDLE create_file(char* file_path, char mode);
int write_to_file(HANDLE hFile, char* line);
void decrypt_line(char* line, int key);
int decrypt_file(char* input_file_path, int key, char* out_file_path);
int read_from_file(HANDLE hFile, char* line);
#pragma once
