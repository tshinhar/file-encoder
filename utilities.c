//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
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
	while ((current_char = (char)fgetc(file_pointer)) != EOF){
		if (current_char == '\n')
			lines_count++;
	}
	fclose(file_pointer);
	return lines_count;
}