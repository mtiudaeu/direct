#pragma once

#include <d2d1.h>

struct Menu {
	ID2D1SolidColorBrush* m_pBlackBrush = NULL;
	int m_menu_position = 0;
	void* m_current_game = NULL;
};

HRESULT MenuCreateResources(Menu* menu, ID2D1HwndRenderTarget* pRenderTarget);
void MenuDiscardResources(Menu* menu);

HRESULT MenuOnRender(Menu* menu, ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat);

void MenuOnKeyDown(Menu* menu, SHORT vkey);
