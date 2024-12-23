// David Strikaitis c00283152
#ifndef CANVAS_H
#define CANVAS_H

#include "Resources.h"
#include "Colour.h"

enum class ToolSelected
{
	Brush, Eraser, Selector, BoxDraw, boxSelect, boxDrag
};

class Canvas
{
public:
	// constructor / deconstructor
	Canvas(); ~Canvas();

	void init();
	void update();
	void render();

	void setSelectedColour(Colour& t_colour) { m_selectedColour = t_colour; }
	Colour getColour() { return m_selectedColour; }

	void setTool(ToolSelected t_tool) { m_currentTool = t_tool; }

	void saveCurrent();
	void load();
private:
	int mousePixel();
	int mousePixel(Vector2 t_mouse);

	void drawPixel();
	void erasePixel();

	void drawBox(bool m_select);
	void drawOverlay();

	Vector2 startSelect;
	bool selecting = false;

	std::vector<Colour> m_pixels;
	Vector2 m_topRight;
	int m_pixelSize = 1;
	Vector2 m_canvasSize;

	// use for moving the canvas around
	Vector2 m_mousePos;
	Vector2 m_mouseStartPos;
	float m_mouseSpeedFactor = 1.f;

	Colour m_selectedColour;

	ToolSelected m_currentTool;

	std::vector<Colour> selectedPixels;
	Vector2 selectedSize;
	std::vector<Colour> copiedPixels;
	Vector2 copiedSize;
	Vector2 topLeft;
};



#endif // !CANVAS_H
