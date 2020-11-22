//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

//Description - decryption of the file and creation of the output file

#include "decryption.h"


/// a function to start the threads should be implemented here
/// support functions may be needed as well since we need to set the start and end point for each thread

int decrypt_file(char* input_file_path, int key, char* out_file_path, char flag) {
    // Open the source file
    HANDLE source = create_file(input_file_path, 'r');
    printf("The source file is %s\n", input_file_path);

    // Create a new file
    HANDLE target = create_file(out_file_path, 'w');
    printf("The target file is %s\n", out_file_path);

    // Decrypt and copy to new file
    int status = decrypt_source_to_target(source, target, key, flag);
    // Decryption completed, close handles
    CloseHandle(source);
    CloseHandle(target);

    // Check for errors
    if (status != 0) {
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
                    line[i] = 'A' + ((line[i] - 'A' - key) % 26);
                else
                    line[i] = 'a' + ((line[i] - 'a' - key) % 26);
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
        if(flag == 'd')
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
        return EXIT_FAILURE;
    return 0;
}


HANDLE create_file(char* file_path, char mode) {
    // this function creates a file and returns the handle, mode is indicating read or write
    HANDLE hFile;
    if (mode == 'r') {
        hFile = CreateFileA(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    else
        if (mode == 'w') {
            hFile = CreateFileA(file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        }
    else {
        printf("ERROR: not 'r' or 'w' for file");
        return NULL;
    }

    // Check for error
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Target file not created. Error %u", GetLastError());
        exit(EXIT_FAILURE);
    }
    return hFile;
}