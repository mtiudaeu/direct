#pragma once

#include <d2d1.h>

struct GameTetris{};

HRESULT GameTetrisOnRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat, ID2D1SolidColorBrush* m_pBrush);
void GameTetrisOnKeyDown(SHORT vkey);


