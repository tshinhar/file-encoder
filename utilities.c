//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

//Description - this modul contains general utilities to be used by the other moduels of the project

#include"utilities.h"

char* cut_string_revese(char* string, int string_length, char cutting_point) {
	int i;
	char* new_string = (char*)malloc(string_length * sizeof(char));
	check_malloc(new_string);
	strcpy_s(new_string, string_length, string);
	for (i = string_length - 2; i>=0; i--)
	{
		if (new_string[i] == cutting_point) {
			new_string[i+1] = '\0';
			break;
		}
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
