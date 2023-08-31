#include "render_type.h"

#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//--------------------------------------------------

typedef struct
{
	float x;
	float y;
	float w;
	float h;
} position_component;

typedef struct
{
	position_component positionComponent;
	SDL_Surface* text;
	SDL_Texture* caption;
	SDL_FRect captionRect;
	SDL_Color color;
} text_type;

typedef struct
{
	position_component positionComponent;
} rectangle_type;

//--------------------------------------------------

TTF_Font* fontProvider = 0x0;
const int FONT_SIZE = 24;

//--------------------------------------------------

render_type* render_type_create(enum RENDER_TYPE type)
{
	render_type* renderType = malloc(sizeof(render_type));

	switch (type)
	{
	case RENDER_TYPE_RECTANGLE:
		renderType->data = malloc(sizeof(rectangle_type));
		break;
	case RENDER_TYPE_TEXT:
		renderType->data = malloc(sizeof(text_type));
		break;
	}

	return renderType;
}

void render_type_destroy(render_type* renderType)
{
	//mdtmp assert(renderType);

	free(renderType->data);
	free(renderType);
}


void render_type_draw(struct SDL_Renderer* renderer, render_type* renderType)
{
	SDL_FRect rect;

	switch (renderType->type)
	{
	case RENDER_TYPE_RECTANGLE:
		//mdtmp
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRectF(renderer, &rect);
		break;
	case RENDER_TYPE_TEXT:

		if (!fontProvider)
			fontProvider = TTF_OpenFont("OpenSans.ttf", FONT_SIZE);

		//tmp
		SDL_Color white;
		white.r = 0xFF;
		white.g = 0xFF;
		white.b = 0xFF;
		white.a = 0x00;

		SDL_FRect captionRect;

		text_type* textType = renderType->data;

		if (!textType->text)
		{
			textType->text = TTF_RenderUTF8_Blended(fontProvider, "test message", white);
			captionRect.x = 0.0f;
			captionRect.y = 0.0f;
			captionRect.w = (float)textType->text->w;
			captionRect.h = (float)textType->text->h;
			textType->caption = SDL_CreateTextureFromSurface(renderer, textType->text);

			//mdtmp SDL_DestroySurface(textType->text);
		}

		SDL_RenderCopyF(renderer, textType->caption, NULL, &captionRect);

		break;
	}
}
