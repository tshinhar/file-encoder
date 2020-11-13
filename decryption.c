//Authors – Tomer Shinhar 205627524 Yael shwarz 206335010
//Project – Caesar

//Description - decryption of the file and creation of the output file

#include "decryption.h"

#define BUFFERSIZE 60


int decrypt_file(char *input_file_path, int key, char *out_file_path) {
    //thia function gets a file and a key and creates new decrypted file
    char line[BUFFERSIZE];
    HANDLE hFile_input = create_file(input_file_path, 'r');
    HANDLE hFile_output = create_file(out_file_path, 'w');
    while (read_from_file(hFile_input, line) != EOF){
        decrypt_line(line, key);
        write_to_file(hFile_output, line);
    }
    CloseHandle(hFile_input);
    CloseHandle(hFile_output);
    return 0;
}

void decrypt_line(char* line, int key) {
    // this function gets a line and decrypts it according to the given key
    for (int i = 0; i < strlen(line); i++)
    {
        if (isdigit(line[i]) > 0) //if char is digit
            line[i] = '0' + ((line[i] - '0' - key) % 10);
        else
            if (isalpha(line[i]) > 0) {// if char is alph
                if(isupper(line[i]) > 0)
                    line[i] = 'A' + ((line[i] - 'A' - key) % 26);
                else
                    line[i] = 'a' + ((line[i] - 'a' - key) % 26);
            }
    }
}

int read_from_file(HANDLE hFile, char* line) {
    // this function reads from the given file
    DWORD dwBytesRead;
    OVERLAPPED ol = { 0 };
    BOOL bResult = ReadFile(hFile, line, BUFFERSIZE - 1, &dwBytesRead, NULL);
    if (FALSE == bResult)
    {
        printf("ERROR- can't read from file.\n GetLastError=%08x\n", GetLastError());
        CloseHandle(hFile);
        exit(1);
    }
    if (bResult && dwBytesRead == 0)
    {
        return EOF;
    }
    return 0;
}
int write_to_file(HANDLE hFile, char* line) {
    // this function writes the given line to the given file
    DWORD dwBytesToWrite = (DWORD)strlen(line);
    DWORD dwBytesWritten = 0;
    BOOL bErrorFlag = FALSE;

    bErrorFlag = WriteFile(
        hFile,           // open file handle
        line,      // start of data to write
        dwBytesToWrite,  // number of bytes to write
        &dwBytesWritten, // number of bytes that were written
        NULL);            // no overlapped structure

    if (FALSE == bErrorFlag) {
        printf("ERROR - can't write to file.\n");
        return -1;
    }
    return 0;
}

HANDLE create_file(char* file_path, char mode) {
	// this function creates a file and returns the handle, mode is indicating read or write
    HANDLE hFile;
    DWORD dwDesiredAccess = 0;
    DWORD dwCreationDisposition = 0;
    DWORD dwShareMode =0;
    if (mode == 'r') {
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
        dwShareMode = FILE_SHARE_READ;
    }
    else
        if (mode == 'w') {
            dwDesiredAccess = GENERIC_WRITE;
            dwCreationDisposition = CREATE_NEW;
            dwShareMode = 0;
        }
    hFile = CreateFileA(file_path, // name of the file
        dwDesiredAccess,          // open mode
        dwShareMode,             // share mode
        NULL,                   // default security
        dwCreationDisposition,  // create/open
        FILE_ATTRIBUTE_NORMAL,  // normal file
        NULL);                  // no attr. template
    
    if (hFile == INVALID_HANDLE_VALUE){
        printf("ERROR: can't open file \"%s\"\n", file_path);
        exit(-1);
    }

    return hFile;
}