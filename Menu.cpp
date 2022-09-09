#include "Menu.h"


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

    D2D1_SIZE_F renderTargetSize = pRenderTarget->GetSize();
    
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, -100));
    pRenderTarget->DrawText(
        sc_welcome,
        ARRAYSIZE(sc_welcome) - 1,
        pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush
    );
    

    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 100));
    //pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(0.5f, 0.5f));
    pRenderTarget->DrawText(
        sc_tetris,
        ARRAYSIZE(sc_tetris) - 1,
        pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pBlackBrush
    );

    return hr;
}
