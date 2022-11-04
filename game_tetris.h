#pragma once

#include <d2d1.h>

class game_tetris
{
public:
	HRESULT onRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat, ID2D1SolidColorBrush* m_pBrush);
	void onKeyDown(SHORT vkey);
};

