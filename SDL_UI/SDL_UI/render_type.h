#pragma once

enum RENDER_TYPE {
	RENDER_TYPE_TEXT,
	RENDER_TYPE_RECTANGLE,
};

typedef struct {
	enum RENDER_TYPE type;
	void* data;

} render_type;

render_type* render_type_create();
void render_type_destroy();

void render_type_draw(render_type* renderType);

