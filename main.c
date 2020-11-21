//Authors � Tomer Shinhar 205627524 Yael shwarz 206335010
//Project � Caesar

#include "utilities.h"
#include "decryption.h"



int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("not enought arguments");
		exit(-1);
	}
	int path_length = strlen(argv[1]) + 1, encryption_key = atoi(argv[2]);
	char* out_file_path = cut_string_revese(argv[1], path_length, '\\');
	strcat_s(out_file_path, path_length + EXTRA_CHARS, "decrypted.txt");
	printf("%s\n", out_file_path);
	decrypt_file(argv[1], encryption_key, out_file_path);
	free(out_file_path);
	printf("sucess");
}