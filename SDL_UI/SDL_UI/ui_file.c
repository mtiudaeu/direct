#include "ui_file.h"

#include <stdio.h>

#define BUFFER_SIZE 1024

int ui_file_render(ui_file* uiFile, FILETIME* modifiedTimestamp, WCHAR* fileName)
{
	//mdtmp assert(modifiedTimestamp);

	FILETIME ftCreate, ftAccess, ftWrite;
	FILE* file =
		CreateFile(fileName,       // name of the write
			GENERIC_READ,          // open for writing
			0,                     // do not share
			NULL,                  // default security
			OPEN_EXISTING,         // create new file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);

	if (file == INVALID_HANDLE_VALUE) {
		perror("Error opening file");
		return 1;
	}

	// Retrieve the file times for the file.
	if (!GetFileTime(file, &ftCreate, &ftAccess, &ftWrite))
		return 1;

	if (CompareFileTime(modifiedTimestamp, &ftWrite) == -1)
	{
		*modifiedTimestamp = ftWrite;
	}

	CloseHandle(file);

	return 0;
}

int create_render_type(FILE* file) 
{
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, totalBytesRead = 0;
    BOOL eof = FALSE;

    // Step 3 and 4: Read and process the file line by line
    while (!eof) {
        if (!ReadFile(file, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
            perror("Error reading file");
            break;
        }

        if (bytesRead == 0) {
            eof = TRUE; // Reached end of file
            continue;
        }

        // Step 4: Parse the buffer for lines
        for (DWORD i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                // Process the line (you can print it, store it, etc.)
                buffer[i] = '\0'; // Null-terminate the line
                printf("Line: %s\n", buffer);
            }
        }

        // Move any remaining data to the beginning of the buffer
        if (!eof && bytesRead < BUFFER_SIZE) {
            memmove(buffer, buffer + bytesRead, BUFFER_SIZE - bytesRead);
        }

        totalBytesRead += bytesRead;
    }

}