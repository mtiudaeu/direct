#pragma once

#include <windows.h>
#include "render_type.h"

typedef struct {
	int ret;
	render_type* renderType;
} ui_file;

int ui_file_render(ui_file* uiFile, FILETIME* modifiedTimestamp, WCHAR* fileName);
