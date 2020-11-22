//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

#include "utilities.h"
#include "decryption.h"

/// comments for us:
/// main only extracts the input and calls other functions accordingly
/// calling to threads should be done in the decryption modul by calling a function (instead of decrypt_file here) that will create the threads 
/// the struct (if needed, should be defined in the h file
/// currently all command line arguments are extracted 
int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("incorrect number of arguments");
		exit(-1);
	}
	int path_length = strlen(argv[1]) + 1, encryption_key = atoi(argv[2]), num_of_threads = atoi(argv[3]);
	char action_flag = argv[4][1];
	char* out_file_path = cut_string_revese(argv[1], path_length, '\\');
	if(action_flag == 'd')
		strcat_s(out_file_path, path_length + EXTRA_CHARS, "decrypted.txt");
	else //since we can assume -e or -d are always present
		strcat_s(out_file_path, path_length + EXTRA_CHARS, "encrypted.txt");
	printf("%s\n", out_file_path);
	decrypt_file(argv[1], encryption_key, out_file_path, action_flag); // call function to creat threads here
	free(out_file_path);
	printf("sucess");
}