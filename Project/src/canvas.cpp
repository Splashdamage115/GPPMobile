#include "canvas.h"

Canvas::Canvas() { }
Canvas::~Canvas() { }

void Canvas::init()
{
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


}

void Canvas::render()
{
	for (unsigned int i = 0; i < m_pixels.size(); i++) 
	{
		Color c; c.r = m_pixels.at(i).r; c.g = m_pixels.at(i).g; c.b = m_pixels.at(i).b; c.a = m_pixels.at(i).a;
		DrawRectangle(m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize), m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize), m_pixelSize, m_pixelSize, c);
	}
}

