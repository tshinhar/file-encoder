//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Caesar

#include "utilities.h"
#include "decryption.h"

typedef struct {
	char *in_file_path;
	char *out_file_path;
	int first_byte;
	int last_byte;
	int key;
	char action_flag;
} THREAD_ARGS; //FIXME according to decipher lines


/*
DWORD WINAPI decipher_lines(char* file_path, int start_line, int num_lines) { // FIXME
	int line_index = 0;
	FILE* file = fopen(file_path, 'r');
	while (!feof(file))
	{
		if (line_index >= start_line && line_index < start_line + num_lines) {
			print(line_index);
		}
		line_index += 1;
	}
};
*/

/// comments for us:
/// main only extracts the input and calls other functions accordingly
/// calling to threads should be done in the decryption modul by calling a function (instead of decrypt_file here) that will create the threads 
/// the struct (if needed, should be defined in the h file
/// currently all command line arguments are extracted 
int main(int argc, char* argv[]) {
	int path_length, encryption_key , num_of_threads, num_of_lines, num_lines_div_num_threads, num_lines_mod_num_threads, num_lines_deciphered_in_new_thread;
	int* bytes_per_line_array;
	LINE_BOUNDARY *line_boundaries_array;
	char *in_file_path, *out_file_path;
	char action_flag;
	THREAD_ARGS thread_args;
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
	//int next_line_to_decipher = 0;
	printf("%s\n", out_file_path);
	num_of_lines = get_num_of_lines_in_file(in_file_path);
	bytes_per_line_array = (int*)(malloc(sizeof(int)*num_of_lines));
	line_boundaries_array = (int*)(malloc(sizeof(LINE_BOUNDARY) * num_of_lines));
	get_num_bytes_per_line(argv[1], bytes_per_line_array);
	calc_line_boundaries(bytes_per_line_array, num_of_lines, line_boundaries_array);
	num_lines_div_num_threads = num_of_lines / num_of_threads;
	num_lines_mod_num_threads = num_of_lines % num_of_threads;
	//HANDLE* thread_handles = (*HANDLE)(malloc(sizeof(HANDLE) * num_of_threads));
	/*
	for (int i = 0; i < num_of_threads; i++)
	{
		if (i < num_lines_mod_num_threads) {
			num_lines_deciphered_in_new_thread = num_lines_div_num_threads + 1;
		}
		else {
			num_lines_deciphered_in_new_thread = num_lines_div_num_threads;
		}
		for (int j= next_line_to_decipher ; j< next_line_to_decipher+num_lines_deciphered_in_new_thread; j++)
		{
			total_num_of_bytes_for_thread+= bytes_per_line_array[j];
		}
		first_byte = line_boundaries_array[next_line_to_decipher].first_byte_index;// change first_byte and last_byte to be in decrypte_target_to_source (write those values to set file poiner+ EOF pointer)
		last_byte = line_boundaries_array[next_line_to_decipher].first_byte_index + total_num_of_byte_for_thread;
		thread_args = (THREAD_ARGS){ .in_file_path = argv[1], .out_file_path =out_file_path, .first_byte=first_byte, .last_byte =last_byte, .key =encryption_key, .action_flag = action_flag };
		//thread_handles[i] = createThread(NULL, 0, decrypt_file, &thread_args, 0, NULL); // FIXME - what to do with thread_id? 
		/////what decrypt_file sends: decrypt_file(argv[1], encryption_key, out_file_path, first_byte, last_byte, action_flag);//FIXME need to change decrypt_source_to_target to have first_byte and last_byte
		next_line_to_decipher += num_lines_deciphered_in_new_thread;
	}
	//WaitForMultipleObjects(thread_handles); // FIXME
	
	//Free all mallocs
	free(out_file_path);
	free(bytes_per_line_array);
	free(first_byte_index_per_line);
	free(thread_handles);
	printf("sucess");
	*/
}





