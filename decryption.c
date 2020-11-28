//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Caesar

//Description - decryption of the file and creation of the output file

#include "decryption.h"
#include "utilities.h"

//globle variable
HANDLE Semaphore_gun;

int create_decipher_threads(char* in_file_path, char* out_file_path, LINE_BOUNDARY* line_boundaries_array, int num_of_lines, int encryption_key, int num_of_threads, char action_flag)
{   // this function creates the threads for the decryption
    DWORD first_byte_pointer, last_byte_pointer;
    THREAD_ARGS thread_args;
    int* bytes_per_line_array;
    int next_line_to_decipher = 0, num_lines_div_num_threads, num_lines_mod_num_threads, total_num_of_bytes_for_thread, num_lines_deciphered_in_new_thread, wait_mul_objects;
    num_lines_div_num_threads = num_of_lines / num_of_threads;
    num_lines_mod_num_threads = num_of_lines % num_of_threads;
    HANDLE file_handle = create_file(in_file_path, 'r');
    if (file_handle == NULL)
        return EXIT_FAILURE;
    HANDLE* thread_handles = (HANDLE*)(malloc(sizeof(HANDLE) * num_of_threads));
    if (check_malloc(thread_handles) != 0){// there was an error with thread_handles
        CloseHandle(file_handle);
        free(thread_handles); //should just be free since there's only malloc so far (haven't created threads yet)
        return EXIT_FAILURE;
    }
    bytes_per_line_array = (int*)(malloc(sizeof(int) * num_of_lines));
    if (check_malloc(bytes_per_line_array) != 0){ // bytes_per_line_array
        CloseHandle(file_handle);
        close_handles_of_threads(thread_handles, num_of_threads);
        free(thread_handles);
        return EXIT_FAILURE;
    }
    int get_num_bytes_per_line_status = get_num_bytes_per_line(in_file_path, bytes_per_line_array);
    int calc_line_boundaries_status = calc_line_boundaries(bytes_per_line_array, num_of_lines, line_boundaries_array);
    Semaphore_gun = CreateSemaphore(NULL, 0, num_of_threads, NULL);
    if (calc_line_boundaries_status != 0 || Semaphore_gun == NULL || get_num_bytes_per_line_status != 0){ // if any of the 3 functions errors out
        printf("Error setting up parameters\n");
        CloseHandle(file_handle);
        free(bytes_per_line_array);
        close_handles_of_threads(thread_handles, num_of_threads);
        free(thread_handles);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_of_threads; i++){
        total_num_of_bytes_for_thread = 0;
        if (i < num_lines_mod_num_threads) {
            num_lines_deciphered_in_new_thread = num_lines_div_num_threads + 1;
        }
        else {
            num_lines_deciphered_in_new_thread = num_lines_div_num_threads;
        }
        for (int j = next_line_to_decipher; j < next_line_to_decipher + num_lines_deciphered_in_new_thread; j++){
            total_num_of_bytes_for_thread += bytes_per_line_array[j];
        }
        first_byte_pointer = SetFilePointer(file_handle, line_boundaries_array[next_line_to_decipher].first_byte_index, NULL, FILE_BEGIN);
        last_byte_pointer = SetFilePointer(file_handle, (line_boundaries_array[next_line_to_decipher].first_byte_index + total_num_of_bytes_for_thread), NULL, FILE_BEGIN);
        thread_args = (THREAD_ARGS){ .in_file_path = in_file_path, .out_file_path = out_file_path, .first_byte_pointer = first_byte_pointer, .last_byte_pointer = last_byte_pointer, .key = encryption_key, .action_flag = action_flag };
        thread_handles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)decrypt_file, &thread_args, 0, NULL);
        printf("thread %d created \n", i);
        if (thread_handles[i] == NULL){ // CreatThread failed
            printf("thread %d faild \n", i);
            CloseHandle(file_handle);
            CloseHandle(Semaphore_gun);
            free(bytes_per_line_array);
            close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles" (could be that only one of the thread handles has failed, and the rest needs to be released)
            free(thread_handles);
            return EXIT_FAILURE;
        }
        next_line_to_decipher += num_lines_deciphered_in_new_thread;
    }
    ReleaseSemaphore(Semaphore_gun, num_of_threads, NULL);
    wait_mul_objects = WaitForMultipleObjects(num_of_threads, thread_handles, true, 20000); // 20 seconds
    if (wait_mul_objects != WAIT_OBJECT_0)//if WaitForMultipleObjects failed
    {
        printf("wait failed faild\n");
        CloseHandle(file_handle);
        CloseHandle(Semaphore_gun);
        free(bytes_per_line_array);
        close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles"
        free(thread_handles);
        return EXIT_FAILURE;
    }
    //Free all mallocs/handles
    CloseHandle(file_handle);
    CloseHandle(Semaphore_gun);
    free(bytes_per_line_array);
    close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles"
    free(thread_handles);
    return 0;
}


DWORD WINAPI decrypt_file(LPVOID lpParam)
{   // this function is the thread, it gets the files and pointers and calls decryption for them
    int wait_obj = WaitForSingleObject(Semaphore_gun, 5000);// wait 5 seconds for other threads
    if(wait_obj != WAIT_OBJECT_0){//if wait failed
        printf("Timeout wating for other threads");
        return EXIT_FAILURE;
    }
    THREAD_ARGS* thread_args;
    thread_args = (THREAD_ARGS*)lpParam;
    char* input_file_path = thread_args->in_file_path;
    char* out_file_path = thread_args->out_file_path;
    DWORD first_byte_pointer = thread_args->first_byte_pointer;
    DWORD last_byte_pointer = thread_args->last_byte_pointer;
    int key = thread_args->key;
    char flag = thread_args->action_flag;

    // Open the source file
    HANDLE source = create_file(input_file_path, 'r');
    if (source == NULL)
        return EXIT_FAILURE;
    printf("The source file is %s\n", input_file_path);

    // Create a new file
    HANDLE target = create_file(out_file_path, 'w');
    if (target == NULL) {
        CloseHandle(source);
        return EXIT_FAILURE;
    }
    printf("The target file is %s\n", out_file_path);

    // Decrypt and copy to new file
    int status = decrypt_source_to_target(source, target, key, flag);
    // Decryption completed, close handles
    CloseHandle(source);
    CloseHandle(target);

    // Check for errors
    if(status != 0) {
        DeleteFileA(out_file_path);
        return EXIT_FAILURE;
    }
    // success
    return 0;
}

void decrypt_string(char* line, int key, int bytes_read) {
    // this function gets a line and decrypts it according to the given key
    for (int i = 0; i < bytes_read; i++)
    {
        if (isdigit(line[i]) > 0) //if char is digit
            line[i] = '0' + ((line[i] - '0' - key) % 10);
        else
            if (isalpha(line[i]) > 0) {// if char is alph
                if (isupper(line[i]) > 0)
                {
                    if ((line[i] - 'A' - key) < 0)
                        line[i] = 'A' + ((line[i] - 'A' - key + 26) % 26);
                    else
                        line[i] = 'A' + ((line[i] - 'A' - key) % 26);
                }
                else
                {
                    if ((line[i] - 'a' - key) < 0)
                        line[i] = 'a' + ((line[i] - 'a' - key + 26) % 26);
                    else
                        line[i] = 'a' + ((line[i] - 'a' - key) % 26);
                }
            }
    }
}


void encrypt_string(char* line, int key, int bytes_read) {
    // this function gets a line and encrypts it according to the given key
    for (int i = 0; i < bytes_read; i++)
    {
        if (isdigit(line[i]) > 0) //if char is digit
            line[i] = '0' + ((line[i] - '0' + key) % 10);
        else
            if (isalpha(line[i]) > 0) {// if char is alph
                if (isupper(line[i]) > 0)
                    line[i] = 'A' + ((line[i] - 'A' + key) % 26);
                else
                    line[i] = 'a' + ((line[i] - 'a' + key) % 26);
            }
    }
}


int decrypt_source_to_target(HANDLE source, HANDLE target, int key, char flag) {
    // the function reads from source, decrypts the string and writes it to target
    char buff[BUFFERSIZE];
    DWORD dwBytesRead, dwBytesWritten;

    // Copy contents
    bool ok = true;
    do {
        // Read file, check for error
        if (!ReadFile(source, buff, sizeof(buff), &dwBytesRead, NULL)) {
            printf("Source file not read from. Error %u", GetLastError());
            ok = false;
            break;
        }

        // Check for EOF reached
        if (dwBytesRead == 0) {
            break;
        }
        // Send string to decryption or encryption
        if (flag == 'd')
            decrypt_string(buff, key, (int)dwBytesRead);
        else
            encrypt_string(buff, key, (int)dwBytesRead);

        // Write file, check for error
        if (!WriteFile(target, buff, dwBytesRead, &dwBytesWritten, NULL)) {
            printf("Target file not written to. Error %u", GetLastError());
            ok = false;
            break;
        }
    } while (true);
    // Check errors
    if (!ok)
        return 1;
    return 0;
}