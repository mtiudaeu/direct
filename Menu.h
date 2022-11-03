#pragma once

#include <d2d1.h>

class Menu
{
public:
	HRESULT createResources(ID2D1HwndRenderTarget* pRenderTarget);
	void discardResources();

	HRESULT onRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat);

private:
	ID2D1SolidColorBrush* m_pBlackBrush = nullptr;
	int m_menu_position = 0;
};

