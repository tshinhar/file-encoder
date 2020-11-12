//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

//Description - decryption of the file and creation of the output file

#include "decryption.h"

int write_to_file(FILE* file_ptr, char* line) {
	// this function writes the given line to the given file
	if (EOF == fputs(line, file_ptr))
	{
		printf("Failed to write to file.\n");
		if (fclose(file_ptr) != 0)
		{
			printf("Failed to close file.\n");
			return FAILURE_CODE;
		}
		return FAILURE_CODE;
	}
	return SUCCESS_CODE;
}

int create_output_file(char* file_path) {
	// this function creates output file 
	FILE* file_pointer = NULL;
	if (fopen_s(&file_pointer, file_path, "w") != 0) {
		printf("couldn't open file");
		exit(1);
	}
	if (fclose(file_pointer) != 0){
		printf("Failed to close file.\n");
		return FAILURE_CODE;
	}
	
	return SUCCESS_CODE;
}