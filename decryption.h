#include "utilities.h"

#define BUFFERSIZE 60

typedef struct {
	char* in_file_path;
	char* out_file_path;
	DWORD first_byte_pointer;
	DWORD last_byte_pointer;
	int key;
	char action_flag;
} THREAD_ARGS; //FIXME according to decipher lines

int create_decipher_threads(char* in_file_path, char* out_file_path, LINE_BOUNDARY* line_boundaries_array, int num_of_lines, int encryption_key, int num_of_threads, char action_flag);
DWORD WINAPI decrypt_file(LPVOID lpParam);
void decrypt_string(char* line, int key, int bytes_read);
void encrypt_string(char* line, int key, int bytes_read);
int decrypt_source_to_target(HANDLE source, HANDLE target, int key, char flag);
#pragma once