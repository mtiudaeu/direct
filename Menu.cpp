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

    static const WCHAR sc_welcome[] = L"Welcome!";
    static const WCHAR sc_tetris[] = L"Tetris";
    static const WCHAR sc_snake[] = L"Snake";

    static const WCHAR sc_example[] = L"Example Middle";

    D2D1_SIZE_F renderTargetSize = pRenderTarget->GetSize();
    D2D1::Matrix3x2F transform;
    
    //--------------------
    transform = D2D1::Matrix3x2F::Translation(0, -(renderTargetSize.height / 4));
    pRenderTarget->SetTransform(transform);
    pRenderTarget->DrawText(
        sc_welcome,
        ARRAYSIZE(sc_welcome) - 1,
        pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush
    );
    


    //--------------------
    transform = D2D1::Matrix3x2F::Scale(0.5f, 0.5f) 
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width / 4), (renderTargetSize.height / 4))
        * D2D1::Matrix3x2F::Translation(0, (renderTargetSize.height / 8));
    pRenderTarget->SetTransform(transform);
    pRenderTarget->DrawText(
        sc_tetris,
        ARRAYSIZE(sc_tetris) - 1,
        pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush
    );

    //--------------------
    transform = D2D1::Matrix3x2F::Scale(0.5f, 0.5f)
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width / 4), (renderTargetSize.height / 4))
        * D2D1::Matrix3x2F::Translation(0, (2 * renderTargetSize.height / 8));
    pRenderTarget->SetTransform(transform);
    pRenderTarget->DrawText(
        sc_snake,
        ARRAYSIZE(sc_snake) - 1,
        pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush
    );

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

    //-------------------
    ui::draw_text_s example{
        .pRenderTarget = pRenderTarget,
        .pTextFormat = pTextFormat,
        .pBrush = m_pBlackBrush,
        .text = sc_example,
        .text_size = ARRAYSIZE(sc_example)
    };
    ui::draw_text(example);
       

    return hr;
}
