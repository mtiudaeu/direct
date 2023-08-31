#include "ui_file.h"

#include <stdio.h>


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

}