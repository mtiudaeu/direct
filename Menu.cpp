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
        draw_text_args.scale = .5f;
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
        draw_text_args.y = -0.2f;

        ui::draw_text(draw_text_args);
    }

    //---------------------------------------------------------------------------------
    {
        static const WCHAR sc_text[] = L"Snake";

        draw_text_args.text = sc_text;
        draw_text_args.text_size = ARRAYSIZE(sc_text);
        draw_text_args.scale = .5f;
        draw_text_args.x = 0.0f;
        draw_text_args.y = -0.3f;

        ui::draw_text(draw_text_args);
    }

    D2D1_SIZE_F renderTargetSize = pRenderTarget->GetSize();
    D2D1::Matrix3x2F transform;
    

    //--------------------
    transform = D2D1::Matrix3x2F::Scale(0.5f, 0.5f)
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width / 4), (renderTargetSize.height / 4))
        * D2D1::Matrix3x2F::Translation(0, (2 * renderTargetSize.height / 8));
    pRenderTarget->SetTransform(transform);
    pRenderTarget->DrawRectangle(
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush,
        4.0f // stroke width
    );

    return hr;
}
