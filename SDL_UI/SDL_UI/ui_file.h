#pragma once

#include <windows.h>

typedef struct {
	int ret;
} ui_file;

int ui_file_render(ui_file* uiFile, FILETIME* modifiedTimestamp, WCHAR* fileName);
