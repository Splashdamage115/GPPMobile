// David Strikaitis c00283152
#include "canvas.h"
#include "SimpleMaths.h"
#include "StbImageWrite.h"

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
	m_mousePos = GetMousePosition();

	// scroll canvas in / out
	if (GetMouseWheelMove() > 0) { m_pixelSize++; }
	else if (GetMouseWheelMove() < 0) { m_pixelSize--; }
	// scroll in / out

	// moving the canvas around
	if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
	{
		m_mouseStartPos = GetMousePosition();
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
	{
		Vector2 newPos; newPos.x = m_mouseStartPos.x - m_mousePos.x; newPos.y = m_mouseStartPos.y - m_mousePos.y;

		m_mouseStartPos = newPos;

		newPos.x *= m_mouseSpeedFactor; newPos.y *= m_mouseSpeedFactor;
		m_topRight.x = m_topRight.x - newPos.x; m_topRight.y = m_topRight.y - newPos.y;
		m_mouseStartPos = GetMousePosition();
	}
	// !moving canvas

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
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
				if (m_currentTool == ToolSelected::Brush)
					drawPixel();
				if (m_currentTool == ToolSelected::Eraser)
					erasePixel();
				if (m_currentTool == ToolSelected::Selector)
					m_selectedColour = m_pixels.at(pos);
			}
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		if (m_currentTool == ToolSelected::Brush)
			erasePixel();
		if (m_currentTool == ToolSelected::Eraser)
			drawPixel();
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

void Canvas::drawPixel()
{
	int pos = mousePixel();

	m_pixels.at(pos) = m_selectedColour;
	m_pixels.at(pos).active = true;
}

void Canvas::erasePixel()
{
	int pos = mousePixel();
	if (pos != -1) 
	{
		m_pixels.at(pos).active = false;
		m_pixels.at(pos) = Colour(255, 255, 255, 0);
	}

}

void Canvas::saveCurrent()
{
	// int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);

	uint8_t image_data[32 * 32 * 4];

	for (int i = 0; i < m_pixels.size(); i++) {
		image_data[i * 4 + 0] = m_pixels.at(i).r;// Red 
		image_data[i * 4 + 1] = m_pixels.at(i).g;// Green 
		image_data[i * 4 + 2] = m_pixels.at(i).b;// Blue
		image_data[i * 4 + 3] = m_pixels.at(i).a;// alpha
	}
	stbi_write_png("output.png", 32, 32, 4, image_data, sizeof(uint8_t) * 4 * 32);
}

void Canvas::load()
{
	Image image = LoadImage("output.png");
	if (image.data == NULL)
	{ 
		std::cout << "couldnt find image" << std::endl;
		return;
	}

	uint8_t* pixelData = (uint8_t*)image.data;

	for (int i = 0; i < image.width * image.height; ++i) 
	{ 
		m_pixels[i].r = pixelData[i * 4 + 0];
		m_pixels[i].g = pixelData[i * 4 + 1];
		m_pixels[i].b = pixelData[i * 4 + 2];
		m_pixels[i].a = pixelData[i * 4 + 3];
	}
	UnloadImage(image);
}
