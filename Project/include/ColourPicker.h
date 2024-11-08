#ifndef COLOURPICKER_H
#define COLOURPICKER_H

#include "Resources.h"
#include "Colour.h"
#include "canvas.h"

class ColourPicker
{
public:
	~ColourPicker();
	void init();
	bool update();
	void render();

	void setCanvas(std::shared_ptr<Canvas> t_canvas) { m_canvas = t_canvas; }
private:
	std::shared_ptr<Canvas> m_canvas;

	Vector2 m_mousePos;

	Vector2 m_canvasStartPos, m_canvasSize;
	float topLeftColourOffset;
	float colourBoxSize;
	float offsetBetweenBoxes;
	int maxWidth;

	std::vector<Colour> m_colours;
	int highlightedBox = 0;
	int selectedBox = 0;
	Image highlightImage;
	Texture2D highlightTexture;
};

#endif // !COLOURPICKER_H
