//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Caesar

//Description - this modul contains general utilities to be used by the other moduels of the project

#include"utilities.h"

char* cut_string_revese(char* string, int string_length, char cutting_point) {
	int i;
	char* new_string = (char*)malloc((string_length + EXTRA_CHARS) * sizeof(char));
	check_malloc(new_string);
	strcpy_s(new_string, string_length, string);
	for (i = string_length - 2; i >= 0; i--)
	{
		if (new_string[i] == cutting_point) {
			new_string[i + 1] = '\0';
			break;
		}
		else if (i==0) {		// No cutting point found
			strcpy_s(new_string,1,"");
			break;
		}
	}
	return new_string;
}


void check_malloc(const void* pointer) {
	if (!pointer)
	{
		printf("ERROR - malloc failed\n");
		exit(EXIT_FAILURE);
	}
}


int get_num_of_lines_in_file(char* file_path)
{
	FILE* file_pointer = NULL;
	if (fopen_s(&file_pointer, file_path, "r") != 0)
	{
		printf("couldn't read file");
		exit(EXIT_FAILURE);
	}
	char current_char;
	int lines_count = 0;
	while ((current_char = (char)fgetc(file_pointer)) != EOF) {
		if (current_char == '\n')
			lines_count++;
	}
	lines_count += 1;	// last line does not end with '\n'
	fclose(file_pointer);
	return lines_count;
}


int get_num_bytes_per_line(char* file_path, int *bytes_per_line_array)
{
	FILE* file_pointer = NULL;
	if (fopen_s(&file_pointer, file_path, "r") != 0)
	{
		printf("couldn't read file");
		exit(EXIT_FAILURE);
	}
	char current_char;
	int lines_count = 0;
	int byte_counter = 0;
	while ((current_char = (char)fgetc(file_pointer)) != EOF) {
		byte_counter += 1;
		if (current_char == '\n') {
			bytes_per_line_array[lines_count] = byte_counter;
			byte_counter = 0;
			lines_count++;
		}
	}
	bytes_per_line_array[lines_count] = byte_counter; // last line does not end with \n
	fclose(file_pointer);
}

void calc_line_boundaries(int* bytes_per_line_array, int num_of_lines, LINE_BOUNDARY* line_boundaries_array)
{
	int i;
	for (i = 0; i < num_of_lines; i++) {
		if (i == 0) {
			line_boundaries_array[i].first_byte_index = 0;
		}
		else {
			line_boundaries_array[i].first_byte_index = line_boundaries_array[i-1].last_byte_index + 1;
		}
		line_boundaries_array[i].last_byte_index = line_boundaries_array[i].first_byte_index + bytes_per_line_array[i];
	}
}
