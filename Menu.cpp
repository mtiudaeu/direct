#include "Menu.h"

#include "ui.h"
#include "game_tetris.h"
#include "game_snake.h"

#include <assert.h>

enum E_GAME {
    TETRIS = 0,
    SNAKE,
    END
};

//----------------------------------------------------------------------------------------------------
HRESULT MenuCreateResources(Menu* menu, ID2D1HwndRenderTarget* pRenderTarget) {
    HRESULT hr = pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black),
        &menu->m_pBlackBrush
    );
    if (FAILED(hr)) return hr;

    return hr;
}

//----------------------------------------------------------------------------------------------------
void MenuDiscardResources(Menu* menu) {
    if (menu->m_pBlackBrush) {
        menu->m_pBlackBrush->Release();
        menu->m_pBlackBrush = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------
HRESULT MenuOnRender(Menu* menu, ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* pTextFormat) {
    HRESULT hr = S_OK;

    if (menu->m_current_game) {

        switch (menu->m_menu_position) {
        case TETRIS:
        {
            //mdtmp GameTetris* game = (GameTetris*)menu->m_current_game;
            GameTetrisOnRender(pRenderTarget, pTextFormat, menu->m_pBlackBrush);
        }
        break;

        case SNAKE:
        {
            //mdtmp GameSnake* game = (GameSnake*)menu->m_current_game;
            GameSnakeOnRender(pRenderTarget, pTextFormat, menu->m_pBlackBrush);
        }
        break;
        }

        return hr;
    }

    ui::draw_text_s draw_text_args{
        .pRenderTarget = pRenderTarget,
        .pTextFormat = pTextFormat,
        .pBrush = menu->m_pBlackBrush
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
            .pBrush = menu->m_pBlackBrush,
            .width = .15f,
            .height = .05f,
            .x = 0.f,
            .y = (float)menu->m_menu_position * -0.1f
        };
        ui::draw_rectangle(draw_rectangle_arg);
    }

    return hr;
}

//----------------------------------------------------------------------------------------------------
void MenuOnKeyDown(Menu* menu, SHORT vkey) {
    if (vkey == VK_ESCAPE) {
       switch (menu->m_menu_position) {
       case TETRIS:
       {
           GameTetris* game = (GameTetris*)menu->m_current_game;
           delete game;
           menu->m_current_game = nullptr;
       }
       break;

       case SNAKE:
       {
           GameSnake* game = (GameSnake*)menu->m_current_game;
           delete game;
           menu->m_current_game = nullptr;
       }
       break;
       }
       return;
    }

    if (menu->m_current_game) {

        switch (menu->m_menu_position) {
             case TETRIS:
                {
                    //mdtmp GameTetris* game = (GameTetris*)menu->m_current_game;
                    GameTetrisOnKeyDown(vkey);
                }
                break;

            case SNAKE:
                {
                    //mdtmp GameSnake* game = (GameSnake*)menu->m_current_game;
                    GameSnakeOnKeyDown(vkey);
                }
                break;
        }

        return;
    }

    switch (vkey)
    {
        /*
    case 'S':
        m_drawStroke = !m_drawStroke;
        break;
        */

    case VK_UP:
        if (menu->m_menu_position > 0) {
            menu->m_menu_position--;
        }
        break;

    case VK_DOWN:
        if (menu->m_menu_position < 1) {
            menu->m_menu_position++;
        }

        break;

    case VK_RETURN:
        switch (menu->m_menu_position) {
            case TETRIS:
            {
                menu->m_current_game = new GameTetris();
            }
            break;

            case SNAKE:
            {
                menu->m_current_game = new GameSnake();
            }
            break;
        }
        break;
        
    default:
        break;
    }
}