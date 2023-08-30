#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720


//mdtmp
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font* font;
	SDL_Surface* text;
	SDL_Color white;
	SDL_Texture* caption;
	SDL_FRect captionRect;
} App;

App app;
bool shouldExit = false;

FILETIME ftCreate, ftAccess, ftWrite, prevFtWrite;

void init(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("UI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	//app.white = { 0xFF, 0xFF, 0xFF, 0 };
	app.white.r = 0xFF;
	app.white.g = 0xFF;
	app.white.b = 0xFF;
	app.white.a = 0x00;

	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}


	const int font_size = 24;
	app.font = TTF_OpenFont("OpenSans.ttf", font_size);

	app.text = TTF_RenderUTF8_Blended(app.font, "test message", app.white);
	app.captionRect.x = 0.0f;
	app.captionRect.y = 0.0f;
	app.captionRect.w = (float)app.text->w;
	app.captionRect.h = (float)app.text->h;
	app.caption = SDL_CreateTextureFromSurface(app.renderer, app.text);

	//mdtmp SDL_DestroySurface(app.text);

}

void uninit(void)
{
	TTF_CloseFont(app.font);
	TTF_Quit();

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	SDL_Quit();
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				shouldExit = true;
				break;

			default:
				break;
		}
	}
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);

	//mdtmp test file
	{


		FILE* tmp =
			CreateFile("test.ui",                // name of the write
				GENERIC_READ,          // open for writing
				0,                      // do not share
				NULL,                   // default security
				OPEN_EXISTING,             // create new file only
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);

		// Retrieve the file times for the file.
		if (!GetFileTime(tmp, &ftCreate, &ftAccess, &ftWrite))
			return;

		CloseHandle(tmp);

		if (CompareFileTime(&prevFtWrite, &ftWrite) == -1)
		{
			prevFtWrite = ftWrite;
		}

	}
}

void presentScene(void)
{

	SDL_SetRenderDrawColor(app.renderer,  0, 0, 0, 255);
	SDL_RenderFillRectF(app.renderer, &app.captionRect);

	SDL_RenderCopyF(app.renderer, app.caption, NULL, &app.captionRect);

	SDL_RenderPresent(app.renderer);
}

int WinMain(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));

	init();

	while (!shouldExit)
	{
		prepareScene();

		doInput();

		presentScene();

		SDL_Delay(16);
	}

	uninit();

	return 0;
}
