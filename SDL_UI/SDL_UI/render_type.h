#pragma once

struct SDL_Renderer;

enum RENDER_TYPE {
	RENDER_TYPE_TEXT,
	RENDER_TYPE_RECTANGLE,
};

typedef struct {
	enum RENDER_TYPE type;
	void* data;

} render_type;

render_type* render_type_create(enum RENDER_TYPE type);
void render_type_destroy(render_type* renderType);

void render_type_draw(struct SDL_Renderer* renderer, render_type* renderType);

