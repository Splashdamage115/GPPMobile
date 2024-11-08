// David Strikaitis c00283152
#include "canvas.h"
#include "SimpleMaths.h"

Canvas::Canvas() { }
Canvas::~Canvas() { }

void Canvas::init()
{
	m_selectedColour = Colour(255, 255, 255, 255);

	m_topRight.x = 100; m_topRight.y = 100;
	m_pixelSize = 10;
	m_canvasSize.x = 32; m_canvasSize.y = 32;

	for (int x = 0; x < m_canvasSize.x; x++)
	{
		for (int y = 0; y < m_canvasSize.y; y++)
		{
			m_pixels.emplace_back(rand() % 256, rand() % 256, rand() % 256);
		}
	}
}

void Canvas::update()
{
	if (GetMouseWheelMove() > 0)
	{
		m_pixelSize++;
	}
	else if (GetMouseWheelMove() < 0)
	{
		m_pixelSize--;
	}
	// moving the canvas around
	if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
	{
		m_mouseStartPos = GetMousePosition();
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
	{
		m_mousePos = GetMousePosition();

		Vector2 newPos; newPos.x = m_mouseStartPos.x - m_mousePos.x; newPos.y = m_mouseStartPos.y - m_mousePos.y;

		m_mouseStartPos = newPos;

		newPos.x *= m_mouseSpeedFactor; newPos.y *= m_mouseSpeedFactor;
		m_topRight.x = m_topRight.x - newPos.x; m_topRight.y = m_topRight.y - newPos.y;
		m_mouseStartPos = GetMousePosition();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		m_mousePos = GetMousePosition();

		int pos = mousePixel();
		if (pos != -1) 
		{
			// change colour to selected code
			if (IsKeyDown(KEY_LEFT_ALT))
			{
				m_selectedColour = m_pixels.at(pos);
			}
			// set colour of pixel
			else
			{
				m_pixels.at(pos) = m_selectedColour;
				m_pixels.at(pos).active = true;
			}
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		m_mousePos = GetMousePosition();
		// get the pixel the mouse is highlighting
		int pos = mousePixel();
		if (pos != -1) m_pixels.at(pos).active = false;
	}
}

void Canvas::render()
{
	int flipBit = 0;
	float x = 0, y = 0;

	for (unsigned int i = 0; i < m_pixels.size(); i++) 
	{
		if (i % static_cast<int>(32) == 0) { if (flipBit == 0) flipBit = 1; else flipBit = 0; }

		Color c = m_pixels.at(i).rayColor();
		x = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		y = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		DrawRectangle(x, y, m_pixelSize, m_pixelSize, (i % 2 == flipBit) ? Colour(85, 85, 85, 255).rayColor() : Colour(166, 166, 166, 255).rayColor());

		if (m_pixels.at(i).active) DrawRectangle(x, y, m_pixelSize, m_pixelSize, c);
	}
}

int Canvas::mousePixel()
{
	for (unsigned int i = 0; i < m_pixels.size(); i++)
	{
		float xPos = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		float yPos = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if(math::coordInBox(m_mousePos.x, m_mousePos.y, xPos, yPos, static_cast<float>(m_pixelSize), static_cast<float>(m_pixelSize)))
		{
			return i;
		}
	}
	return -1;
}

