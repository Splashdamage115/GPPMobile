#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include "Resources.h"
#include "canvas.h"

struct Button
{
	void init(std::string textureAddress, float x, float y, float sizeX, float sizeY) {
		pos.x = x; pos.y = y;
		size.x = sizeX; size.y = sizeY;
		t = LoadTexture(textureAddress.c_str());
	}
	bool pressed(Vector2 mouse);
	void render() 
	{ 
		DrawTexture(t, pos.x, pos.y, WHITE);
		if(highlighted)
			DrawRectangle(pos.x - 1.f, pos.y - 1.f, size.x + 2.f, size.y + 2.f, Colour(255, 255, 0, 80).rayColor());
	}
	Texture2D t;
	Vector2 pos, size;

private:
	bool highlighted = false;
};

class ToolBar
{
public:
	ToolBar(); ~ToolBar();

	void init();
	bool update();
	void render();

	void setCanvas(std::shared_ptr<Canvas> t_canvas) { m_canvas = t_canvas; }
private:
	std::shared_ptr<Canvas> m_canvas;

	Vector2 m_mousePos;

	Vector2 m_canvasStartPos, m_canvasSize;

	Vector2 selectedToolPos;
	Texture2D highlightTexture;

	Button brush, eraser, save, load, boxSelect, selector, boxDraw;
};

#endif // !TOOL_BAR_H
