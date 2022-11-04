#include "game_snake.h"

#include "ui.h"

//----------------------------------------------------------------------------------------------------
HRESULT game_snake::onRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat, ID2D1SolidColorBrush* m_pBrush) {
    HRESULT hr = S_OK;

    ui::draw_text_s draw_text_args{
        .pRenderTarget = pRenderTarget,
        .pTextFormat = pTextFormat,
        .pBrush = m_pBrush
    };

    //--------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Snake";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = 1.2f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = 0.25f;

        ui::draw_text(draw_text_args);
    }

    return hr;
}

//----------------------------------------------------------------------------------------------------
void game_snake::onKeyDown(SHORT vkey) {
    switch (vkey)
    {
    case VK_UP:
        break;

    case VK_DOWN:

        break;
    default:
        break;
    }
}