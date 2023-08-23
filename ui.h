#pragma once

#include <d2d1.h>


//---------------------------------------------------------------------------------
struct ui_draw_text_s {
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;
	const WCHAR* text;
	UINT32 text_size;
	float scale;
	float x;
	float y;
};
void ui_draw_text(const ui_draw_text_s arg);

//---------------------------------------------------------------------------------
struct ui_draw_rectangle_s {
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;
	float width;
	float height;
	float x;
	float y;
	float stroke_width = 2.0f;
};
void ui_draw_rectangle(const ui_draw_rectangle_s arg);