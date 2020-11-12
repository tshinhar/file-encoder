//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

//Description - this modul contains general utilities to be used by the other moduels of the project

#include"utilities.h"

char* cut_string_revese(char* string, int string_lenght, char cutting_point) {
	char* new_string = malloc(string_lenght * sizeof(char));
	check_malloc(new_string);
	strcpy_s(new_string, string_lenght, string);
	int i = string_lenght - 1;
	while (new_string[i]) {
		if (new_string[i] == cutting_point) {
			new_string[i] = '\0';
		}
		i--;
	}
	return new_string;
}


void check_malloc(const void* pointer) {
	if (!pointer)
	{
		printf("ERROR - malloc failed\n");
		exit(FAILURE_CODE);
	}
}