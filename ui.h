#pragma once

#include <d2d1.h>

namespace ui {

	//---------------------------------------------------------------------------------
	struct draw_text_s {
		ID2D1HwndRenderTarget* pRenderTarget;
		IDWriteTextFormat* pTextFormat;
		ID2D1SolidColorBrush* pBrush;
		const WCHAR* text;
		UINT32 text_size;
		float scale;
		float x;
		float y;
	};
	void draw_text(const draw_text_s& arg);

	//---------------------------------------------------------------------------------
	struct draw_rectangle_s {
		ID2D1HwndRenderTarget* pRenderTarget;
		IDWriteTextFormat* pTextFormat;
		ID2D1SolidColorBrush* pBrush;
		float scale_x;
		float scale_y;
		float x;
		float y;
	};
	void draw_rectangle(const draw_rectangle_s& arg);

}