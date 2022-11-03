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

    //--------------------------------------------------
    { 
        static const WCHAR sc_text[] = L"Welcome!";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = 1.2f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = 0.25f;

        ui::draw_text(draw_text_args);
    }
    
    //--------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Tetris";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = .5f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = -0.0f;

        ui::draw_text(draw_text_args);
    }

    //--------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Snake";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = .5f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = -0.1f;

        ui::draw_text(draw_text_args);
    }

    //--------------------------------------------------
    {
        ui::draw_rectangle_s draw_rectangle_arg{
            .pRenderTarget = pRenderTarget,
            .pTextFormat = pTextFormat,
            .pBrush = m_pBlackBrush,
            .width = .15f,
            .height = .05f,
            .x = 0.f,
            .y = (float)m_menu_position * -0.1f
        };
        ui::draw_rectangle(draw_rectangle_arg);
    }

    return hr;
}

//----------------------------------------------------------------------------------------------------
void Menu::onKeyDown(SHORT vkey) {
    switch (vkey)
    {
        /*
    case 'A':
        m_antialiasMode =
            (m_antialiasMode == D2D1_ANTIALIAS_MODE_ALIASED) ?
            D2D1_ANTIALIAS_MODE_PER_PRIMITIVE :
            D2D1_ANTIALIAS_MODE_ALIASED;
        break;

    case 'R':
        m_useRealizations = !m_useRealizations;
        break;

    case 'G':
        m_autoGeometryRegen = !m_autoGeometryRegen;
        break;

    case 'S':
        m_drawStroke = !m_drawStroke;
        break;
        */

    case VK_UP:
        if (m_menu_position > 0) {
            m_menu_position--;
        }
        break;

    case VK_DOWN:
        if (m_menu_position < 1) {
            m_menu_position++;
        }

        break;

    default:
        break;
    }
}