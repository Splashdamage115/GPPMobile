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
	maxHeight = 10;

	m_colours.emplace_back(255, 255, 255);

	topLeftColourOffset = 20.0f;
	colourBoxSize = 30.0f;
	offsetBetweenBoxes = 10.f;
	maxWidth = 5;

	highlightTexture = LoadTexture("highlight.png");

	circlePos.x = m_canvasStartPos.x + 120; circlePos.y = m_canvasStartPos.y + 600;
	circleRad = 100.f;
	circleTexture = LoadTexture("hsv.png");

	selectedCircle = LoadTexture("Selector.png");

	darkness = LoadTexture("BWramp.png");
	darknessWidth = 200.f;
	darknessPos.x = m_canvasStartPos.x + 20; darknessPos.y = m_canvasStartPos.y + 720;

	currentColourPos.x = m_canvasStartPos.x + 20; currentColourPos.y = m_canvasStartPos.y + 440;
	currentColourSize.x = 200; currentColourSize.y = 40;

	darknessSelection = LoadTexture("BWselector.png");
	BWpos.x = darknessPos.x + currentColourSize.x; BWpos.y = darknessPos.y + (currentColourSize.y / 2.f);

	addPos.x = currentColourPos.x + currentColourSize.x - 34.f; addPos.y = currentColourPos.y + (currentColourSize.y / 2.f) - 16.f;
	addTexture = LoadTexture("AddButton.png");
}

// bool used to check clicks inside the menu, this is in case the canvas is behind this menu to avoid overlap
bool ColourPicker::update()
{
	drawAdd = true;
	for (unsigned int i = 0; i < m_colours.size(); i++)
	{
		if (m_colours.at(i) == m_canvas->getColour())
		{
			drawAdd = false;
			break;
		}
	}
	

	m_mousePos = GetMousePosition();
	// all canvas interactions should take place within this if statement, as it is in focus
	if (math::coordInBox(m_mousePos, m_canvasStartPos, m_canvasSize))
	{
		Vector2 size; size.x = colourBoxSize; size.y = colourBoxSize;
		for (unsigned int i = startDrawH; i < m_colours.size(); i++)
		{
			int a = i - startDrawH;
			Vector2 position;
			position.x = m_canvasStartPos.x + topLeftColourOffset + (a % maxWidth * (colourBoxSize + offsetBetweenBoxes));
			position.y = m_canvasStartPos.y + topLeftColourOffset + (a / maxWidth * (colourBoxSize + offsetBetweenBoxes));
			if (math::coordInBox(m_mousePos, position, size))
			{
				highlightedBox = i;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					selectedBox = i;
					m_canvas->setSelectedColour(m_colours.at(i));
				}
				break;
				return true;
			}
		}
		if (math::coordInCircle(m_mousePos, circlePos, circleRad))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				HSV selected;
				selected.s = (math::distance(m_mousePos, circlePos) / circleRad) * 100.f; // convert it to a percentage
				selected.h = math::displacementToDegrees(math::displacement(circlePos, m_mousePos));
				selected.v = ((BWpos.x - darknessPos.x) / darknessWidth) * 100.f;
				m_canvas->setSelectedColour(selected.toColour());

				selectedPosWheel = m_mousePos;
			}
		}
		else if (math::coordInBox(m_mousePos.x, m_mousePos.y, darknessPos.x, darknessPos.y, darknessWidth, 40.f))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
			{
				BWpos.x = m_mousePos.x;

				HSV selected; selected.convertColour(m_canvas->getColour());
				selected.v = ((BWpos.x - darknessPos.x) / darknessWidth) * 100.f;
				m_canvas->setSelectedColour(selected.toColour());
			}
		}
		else if (math::coordInBox(m_mousePos.x, m_mousePos.y, currentColourPos.x, currentColourPos.y, darknessWidth, 40.f))
		{
			if (drawAdd)
			{
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					m_colours.push_back(m_canvas->getColour());
				}
			}
		}
		else
		{
			if (GetMouseWheelMove() < 0)
			{
				if(startDrawH + maxWidth < m_colours.size() / maxWidth)
					startDrawH += maxWidth;
			}
			else if (GetMouseWheelMove() > 0)
			{
				if (startDrawH >= maxWidth)
					startDrawH -= maxWidth;
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
	for (unsigned int i = startDrawH; i < m_colours.size(); i++)
	{
		int a = i - startDrawH;
		if (a + 1 > maxHeight * maxWidth)
			break;

		Vector2 position;
		
		position.x = m_canvasStartPos.x + topLeftColourOffset + (a % maxWidth * (colourBoxSize + offsetBetweenBoxes));
		position.y = m_canvasStartPos.y + topLeftColourOffset + (a / maxWidth * (colourBoxSize + offsetBetweenBoxes));
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

	DrawRectangleV(currentColourPos, currentColourSize, m_canvas->getColour().rayColor());

	if (drawAdd)
	{
		DrawTexture(addTexture, addPos.x, addPos.y, WHITE);

		if (math::coordInBox(m_mousePos.x, m_mousePos.y, currentColourPos.x, currentColourPos.y, darknessWidth, 40.f))
		{
			DrawRectangle(currentColourPos.x - 1.f, currentColourPos.y - 1.f, currentColourSize.x + 2.f, currentColourSize.y + 2.f, Colour(255, 255, 0, 80).rayColor());
		}
	}

	DrawTexture(circleTexture, circlePos.x - circleRad, circlePos.y - circleRad, WHITE);
	DrawTexture(selectedCircle, selectedPosWheel.x - 5.f, selectedPosWheel.y - 5.f, WHITE);

	DrawTexture(darkness, darknessPos.x, darknessPos.y, WHITE);
	DrawTexture(darknessSelection, BWpos.x - 5, BWpos.y - 25, WHITE);
}
