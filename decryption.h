#include "utilities.h"

#define BUFFERSIZE 60

HANDLE create_file(char* file_path, char mode);
int decrypt_source_to_target(HANDLE source, HANDLE target, int key);
void decrypt_string(char* line, int key, int bytes_read);
int decrypt_file(char* input_file_path, int key, char* out_file_path);
#pragma once