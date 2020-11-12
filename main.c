//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

#include "utilities.h"
#include "decryption.h"


int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("not enought arguments");
		exit(-1);
	}
	int path_length = strlen(argv[1]) + 1, encryption_key = atoi(argv[2]);
	char* file_path = cut_string_revese(argv[1], path_length, '\\');
	strcat_s(file_path, path_length + 20, "\\decrypted.txt");
	create_output_file(file_path); 
	free(file_path);
	printf("sucess");
}
