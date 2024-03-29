#include "Main.h"

HWND m_hwnd = NULL;
ID2D1Factory* m_pD2DFactory = NULL;
IWICImagingFactory* m_pWICFactory = NULL;
IDWriteFactory* m_pDWriteFactory = NULL;
ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
IDWriteTextFormat* m_pTextFormat = NULL;
Menu m_menu;

//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    LPSTR /*lpCmdLine*/,
    int /*nCmdShow*/
    )
{
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            if (SUCCEEDED(Initialize()))
            {
                RunMessageLoop();
            }

            // UnInitialize
            SafeRelease(&m_pD2DFactory);
            SafeRelease(&m_pDWriteFactory);
            SafeRelease(&m_pRenderTarget);
            SafeRelease(&m_pTextFormat);
        }
        CoUninitialize();
    }


    return 0;
}


//----------------------------------------------------------------------------------------------------
HRESULT Initialize()
{
    HRESULT hr;
    hr = CreateDeviceIndependentResources();
    if (FAILED(hr)) return hr;
    
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = sizeof(LONG_PTR);
    wcex.hInstance     = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName  = NULL;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = L"D2DDemoApp";

    RegisterClassEx(&wcex);

    FLOAT dpiX, dpiY;
    dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
    dpiY = dpiX;

    m_hwnd = CreateWindow(
        L"D2DDemoApp",
        L"Direct2D Demo Application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
        static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
        NULL,
        NULL,
        HINST_THISCOMPONENT,
        NULL
        );
    hr = m_hwnd ? S_OK : E_FAIL;
    if (FAILED(hr)) return hr;
        
    ShowWindow(m_hwnd, SW_SHOWNORMAL);

    UpdateWindow(m_hwnd);

    return hr;
}

//----------------------------------------------------------------------------------------------------
HRESULT CreateDeviceIndependentResources()
{
    static const WCHAR msc_fontName[] = L"Verdana";
    static const FLOAT msc_fontSize = 50;
    HRESULT hr;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    if (FAILED(hr)) return hr;

    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(m_pDWriteFactory),
        reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
        );    
    if (FAILED(hr)) return hr;

    hr = m_pDWriteFactory->CreateTextFormat(
        msc_fontName,
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        msc_fontSize,
        L"", //locale
        &m_pTextFormat
        );
    if (FAILED(hr)) return hr;

    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return hr;
}

//----------------------------------------------------------------------------------------------------
HRESULT CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (m_pRenderTarget) return hr;

    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top
        );

    hr = m_pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size),
        &m_pRenderTarget
        );
    if (FAILED(hr)) return hr;

    MenuCreateResources(&m_menu, m_pRenderTarget);

    return hr;
}

//----------------------------------------------------------------------------------------------------
void DiscardDeviceResources()
{
    MenuDiscardResources(&m_menu);

    SafeRelease(&m_pRenderTarget);
}

//----------------------------------------------------------------------------------------------------
void RunMessageLoop()
{
    MSG msg = {};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            PAINTSTRUCT ps;
            BeginPaint(m_hwnd, &ps);

            OnRender();
            EndPaint(m_hwnd, &ps);
        }
    }
}

//----------------------------------------------------------------------------------------------------
HRESULT OnRender()
{
    HRESULT hr;

    hr = CreateDeviceResources();
    if (FAILED(hr)) return hr;
    
    if (m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED) return hr;

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    MenuOnRender(&m_menu, m_pRenderTarget, m_pTextFormat);

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    hr = m_pRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }    

    return hr;
}

//----------------------------------------------------------------------------------------------------
void OnResize(UINT width, UINT height)
{
    if (!m_pRenderTarget) return;

    D2D1_SIZE_U size;
    size.width = width;
    size.height = height;

    // Note: This method can fail, but it's okay to ignore the
    // error here -- it will be repeated on the next call to
    // EndDraw.
    m_pRenderTarget->Resize(size);
}


//----------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)
    {
        //mdtmp LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        //mdtmp DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            //mdtmp reinterpret_cast<LONG_PTR>(pDemoApp)
            NULL
            );

        return 1;
    }
    
    LRESULT result = 0;
    //mdtmp DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(
    ::GetWindowLongPtrW(
        hwnd,
        GWLP_USERDATA
    );
            //mdtmp);

    bool wasHandled = false;

    //mdtmp if (pDemoApp)
    {
        switch (message)//TODO mdtmp Grab Hotkeys
        {
        case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                OnResize(width, height);
            }
            wasHandled = true;
            result = 0;
            break;
        case WM_KEYDOWN:
            {
                OnKeyDown(static_cast<SHORT>(wParam));
            }

            PostMessage(hwnd, WM_PAINT, 0, 0);

            result = 0;
            wasHandled = true;
            break;

        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            wasHandled = true;
            result = 1;
            break;
        }
    }

    if (!wasHandled)
    {
        result = DefWindowProc(hwnd, message, wParam, lParam);
    }
    

    return result;
}

//----------------------------------------------------------------------------------------------------
void OnKeyDown(SHORT vkey) {
    MenuOnKeyDown(&m_menu, vkey);
}
