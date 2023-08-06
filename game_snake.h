#pragma once

#include <d2d1.h>

struct GameSnake {};

HRESULT GameSnakeOnRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat, ID2D1SolidColorBrush* m_pBrush);
void GameSnakeOnKeyDown(SHORT vkey);


