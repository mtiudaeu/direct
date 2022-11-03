#include "Menu.h"

#include "ui.h"


//----------------------------------------------------------------------------------------------------
HRESULT Menu::createResources(ID2D1HwndRenderTarget* pRenderTarget) {
    HRESULT hr = pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black),
        &m_pBlackBrush
    );
    if (FAILED(hr)) return hr;

    return hr;
}

//----------------------------------------------------------------------------------------------------
void Menu::discardResources() {
    if (m_pBlackBrush) {
        m_pBlackBrush->Release();
        m_pBlackBrush = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------
HRESULT Menu::onRender(ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat) {
    HRESULT hr = S_OK;

    ui::draw_text_s draw_text_args{
        .pRenderTarget = pRenderTarget,
        .pTextFormat = pTextFormat,
        .pBrush = m_pBlackBrush
    };

    //---------------------------------------------------------------------------------
    { 
        static const WCHAR sc_text[] = L"Welcome!";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = 1.2f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = 0.25f;

        ui::draw_text(draw_text_args);
    }
    
    //---------------------------------------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Tetris";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = .5f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = -0.1f;

        ui::draw_text(draw_text_args);
    }

    //---------------------------------------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Snake";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = .5f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = -0.2f;

        ui::draw_text(draw_text_args);
    }

    //---------------------------------------------------------------------------------
    {
        ui::draw_rectangle_s draw_rectangle_arg{
            .pRenderTarget = pRenderTarget,
            .pTextFormat = pTextFormat,
            .pBrush = m_pBlackBrush
        };
        ui::draw_rectangle(draw_rectangle_arg);
    }

    return hr;
}
