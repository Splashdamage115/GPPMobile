#include "ColourPicker.h"
#include "SimpleMaths.h"

ColourPicker::~ColourPicker()
{
	// release the texture (raylib uses C so no smart pointers)
	UnloadTexture(highlightTexture);
}

void ColourPicker::init()
{
	m_canvasStartPos.x = 1050; m_canvasStartPos.y = 0;
	m_canvasSize.x = 300; m_canvasSize.y = 800;

	m_colours.emplace_back(255, 255, 255);

	for (int i = 0; i < 10; i++) {
		m_colours.emplace_back(255, 10, 10); m_colours.emplace_back(10, 255, 10); m_colours.emplace_back(10, 10, 255);
	}

	topLeftColourOffset = 20.0f;
	colourBoxSize = 30.0f;
	offsetBetweenBoxes = 10.f;
	maxWidth = 5;

	highlightTexture = LoadTexture("highlight.png");

	HSV x;
	x.convertColour(Colour(200, 200, 20));
}

// bool used to check clicks inside the menu, this is in case the canvas is behind this menu to avoid overlap
bool ColourPicker::update()
{
	m_mousePos = GetMousePosition();
	// all canvas interactions should take place within this if statement, as it is in focus
	if (math::coordInBox(m_mousePos, m_canvasStartPos, m_canvasSize))
	{
		Vector2 size; size.x = colourBoxSize; size.y = colourBoxSize;
		for (unsigned int i = 0; i < m_colours.size(); i++)
		{
			Vector2 position;
			position.x = m_canvasStartPos.x + topLeftColourOffset + (i % maxWidth * (colourBoxSize + offsetBetweenBoxes));
			position.y = m_canvasStartPos.y + topLeftColourOffset + (i / maxWidth * (colourBoxSize + offsetBetweenBoxes));
			if (math::coordInBox(m_mousePos, position, size))
			{
				highlightedBox = i;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					selectedBox = i;
					m_canvas->setSelectedColour(m_colours.at(i));
				}
				break;
			}
		}

		return true;
	}
	return false;
}

void ColourPicker::render()
{
	DrawRectangleV(m_canvasStartPos, m_canvasSize, Colour(104, 144, 151, 255).rayColor());

	Vector2 size; size.x = colourBoxSize; size.y = colourBoxSize;
	for (unsigned int i = 0; i < m_colours.size(); i++)
	{
		Vector2 position;
		position.x = m_canvasStartPos.x + topLeftColourOffset + (i % maxWidth * (colourBoxSize + offsetBetweenBoxes));
		position.y = m_canvasStartPos.y + topLeftColourOffset + (i / maxWidth * (colourBoxSize + offsetBetweenBoxes));
		DrawRectangleV(position, size, m_colours.at(i).rayColor());

		if (i == highlightedBox)
		{
			Vector2 highlightSize = size; highlightSize.x += 2; highlightSize.y += 2;
			Vector2 highlightPos = position; highlightPos.x -= 1; highlightPos.y -= 1;
			DrawRectangleV(highlightPos, highlightSize, Colour(255,255,0,80).rayColor());
		}
		if (i == selectedBox)
		{
			Vector2 highlightSize = size; highlightSize.x += 2; highlightSize.y += 2;
			Vector2 highlightPos = position; highlightPos.x -= 1; highlightPos.y -= 1;
			DrawTexture(highlightTexture, highlightPos.x, highlightPos.y, WHITE);
		}
	}
}
