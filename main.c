//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Caesar

#include "utilities.h"
#include "decryption.h"


/// comments for us:
/// main only extracts the input and calls other functions accordingly
int main(int argc, char* argv[]) {
	int path_length, encryption_key, num_of_threads, num_of_lines, create_decipher_threads_status;

	LINE_BOUNDARY* line_boundaries_array;
	char* in_file_path, * out_file_path;
	char action_flag;
	if (argc != 5) {
		printf("incorrect number of arguments");
		exit(-1);
	}
	in_file_path = argv[1];
	path_length = strlen(argv[1]) + 1;
	encryption_key = atoi(argv[2]);
	num_of_threads = atoi(argv[3]);
	action_flag = argv[4][1];
	out_file_path = cut_string_revese(in_file_path, path_length, '\\');
	if (action_flag == 'd')
		strcat_s(out_file_path, path_length + EXTRA_CHARS, "decrypted.txt");
	else //since we can assume -e or -d are always present
		strcat_s(out_file_path, path_length + EXTRA_CHARS, "encrypted.txt");
	num_of_lines = get_num_of_lines_in_file(in_file_path);
	if (num_of_lines == 0) {
		printf("file is empty");
		exit(-1);
	}
	line_boundaries_array = (LINE_BOUNDARY*)(malloc(sizeof(LINE_BOUNDARY) * num_of_lines));
	create_decipher_threads_status = create_decipher_threads(in_file_path, out_file_path, line_boundaries_array, num_of_lines, encryption_key, num_of_threads, action_flag);
	if (create_decipher_threads_status == EXIT_FAILURE) // create_decipher_threads failed
	{
		free(out_file_path);
		free(line_boundaries_array);
		printf("create_decipher_threads failed");
		return(EXIT_FAILURE);
	}
	//create_decipher_threads succeeded
	//Free all mallocs
	free(out_file_path);
	free(line_boundaries_array);
	printf("success");
	return 0;
}