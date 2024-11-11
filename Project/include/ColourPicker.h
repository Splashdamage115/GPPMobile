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
	Texture2D highlightTexture;

	Texture2D circleTexture;
	Vector2 circlePos;
	float circleRad;

	Texture2D selectedCircle;
	Vector2 selectedPosWheel;

	Texture2D darkness;
	Vector2 darknessPos;
	float darknessWidth;

	Vector2 currentColourPos;
	Vector2 currentColourSize;
};

#endif // !COLOURPICKER_H
