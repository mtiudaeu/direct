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

    if (m_current_game) {

        switch (m_menu_position) {
        case TETRIS:
        {
            game_tetris* game = static_cast<game_tetris*>(m_current_game);
            game->onRender(pRenderTarget, pTextFormat, m_pBlackBrush);
        }
        break;

        case SNAKE:
        {
            game_snake* game = static_cast<game_snake*>(m_current_game);
            game->onRender(pRenderTarget, pTextFormat, m_pBlackBrush);
        }
        break;
        }

        return hr;
    }

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
    if (vkey == VK_ESCAPE) {
       switch (m_menu_position) {
       case TETRIS:
       {
           game_tetris* game = static_cast<game_tetris*>(m_current_game);
           delete game;
           m_current_game = nullptr;
       }
       break;

       case SNAKE:
       {
           game_snake* game = static_cast<game_snake*>(m_current_game);
           delete game;
           m_current_game = nullptr;
       }
       break;
       }
       return;
    }

    if (m_current_game) {

        switch (m_menu_position) {
             case TETRIS:
                {
                    game_tetris* game = static_cast<game_tetris*>(m_current_game);
                    game->onKeyDown(vkey);
                }
                break;

            case SNAKE:
                {
                    game_snake* game = static_cast<game_snake*>(m_current_game);
                    game->onKeyDown(vkey);
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
        if (m_menu_position > 0) {
            m_menu_position--;
        }
        break;

    case VK_DOWN:
        if (m_menu_position < 1) {
            m_menu_position++;
        }

        break;

    case VK_RETURN:
        switch (m_menu_position) {
            case TETRIS:
            {
                m_current_game = new game_tetris();
            }
            break;

            case SNAKE:
            {
                m_current_game = new game_snake();
            }
            break;
        }
        break;
        
    default:
        break;
    }
}