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

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (m_currentTool == ToolSelected::BoxDraw)
		{
			int selected = mousePixel();
			float xPos = selected % static_cast<int>(m_canvasSize.x);
			float yPos = selected / static_cast<int>(m_canvasSize.x);

			startSelect.x = xPos; startSelect.y = yPos;

			selecting = true;
		}
		if (m_currentTool == ToolSelected::boxSelect)
		{
			int selected = mousePixel();
			float xPos = selected % static_cast<int>(m_canvasSize.x);
			float yPos = selected / static_cast<int>(m_canvasSize.x);

			startSelect.x = xPos; startSelect.y = yPos;

			selectedPixels.clear();

			selecting = true;
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		if (m_currentTool == ToolSelected::Brush)
			erasePixel();
		if (m_currentTool == ToolSelected::Eraser)
			drawPixel();
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (m_currentTool == ToolSelected::BoxDraw)
		{
			// FILL IN ALL BITS BETWEEN M_MOUSEPOS AND MOUSE START
			int selected = mousePixel();
			float xPos = selected % static_cast<int>(m_canvasSize.x);
			float yPos = selected / static_cast<int>(m_canvasSize.x);

			int startX = math::min(startSelect.x, xPos);
			int endX = math::max(xPos, startSelect.x);

			for (int x = startX; x <= endX; x++)
			{
				if (x + (m_canvasSize.y * startSelect.y) >= 0 && x + (m_canvasSize.y * startSelect.y) < m_pixels.size()) {
					m_pixels.at(x + (m_canvasSize.y * startSelect.y)) = m_selectedColour; m_pixels.at(x + (m_canvasSize.y * startSelect.y)).active = true;
				}
				if (x + (m_canvasSize.y * yPos) >= 0 && x + (m_canvasSize.y * yPos) < m_pixels.size()) {
					m_pixels.at(x + (m_canvasSize.y * yPos)) = m_selectedColour; m_pixels.at(x + (m_canvasSize.y * yPos)).active = true;
				}
			}

			int startY = math::min(startSelect.y, yPos);
			int endY = math::max(yPos, startSelect.y);

			for (int y = startY; y <= endY; y++)
			{
				if (y * m_canvasSize.x + startX >= 0 && y * m_canvasSize.x + startX < m_pixels.size()) {
					m_pixels.at(y * m_canvasSize.x + startX) = m_selectedColour; m_pixels.at(y * m_canvasSize.x + startX).active = true;
				}
				if (y * m_canvasSize.x + endX >= 0 && y * m_canvasSize.x + endX < m_pixels.size()) {
					m_pixels.at(y * m_canvasSize.x + endX) = m_selectedColour; m_pixels.at(y * m_canvasSize.x + endX).active = true;
				}
			}

			selecting = false;
		}

		if (m_currentTool == ToolSelected::boxSelect)
		{
			int selected = mousePixel();
			float xPos = selected % static_cast<int>(m_canvasSize.x);
			float yPos = selected / static_cast<int>(m_canvasSize.x);

			int startX = math::min(startSelect.x, xPos);
			int endX = math::max(xPos, startSelect.x);
			int startY = math::min(startSelect.y, yPos);
			int endY = math::max(yPos, startSelect.y);

			for (int x = startX; x <= endX; x++)
			{
				for (int y = startY; y <= endY; y++)
				{
					if (x + (y * m_canvasSize.y) < m_pixels.size() && x + (y * m_canvasSize.y) >= 0){
						selectedPixels.push_back(m_pixels.at(x + (y * m_canvasSize.y)));
					}
				}
			}
			selectedSize.x = endX - startX; selectedSize.y = endY - startY;
			topLeft.x = startX; topLeft.y = startY;

			selecting = false;
			m_currentTool = ToolSelected::boxDrag;
		}
	}
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyReleased(KEY_C))
	{
		if (selectedPixels.size() > 0)
		{
			copiedPixels.clear();
			for (int i = 0; i < selectedPixels.size(); i++)
				copiedPixels.push_back(selectedPixels.at(i));
			copiedSize = selectedSize;
		}
	}
	if (m_currentTool == ToolSelected::boxDrag)
	{
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			m_mouseStartPos = GetMousePosition();

		if (IsKeyReleased(KEY_ENTER))
		{
			{
				int increment = 0;
				m_currentTool = ToolSelected::Brush;

				for (int x = topLeft.x; x <= copiedSize.x + topLeft.x; x++)
				{
					for (int y = topLeft.y; y <= copiedSize.y + topLeft.y; y++)
					{
						if (copiedPixels.at(increment).active && copiedPixels.at(increment).a > 0)
							m_pixels.at(x + (y * m_canvasSize.y)) = copiedPixels.at(increment);
						increment++;
						if (increment >= copiedPixels.size()) return;
					}
				}
			}
		}

		if (IsKeyReleased(KEY_LEFT))
		{
			topLeft.x--;
		}
		if (IsKeyReleased(KEY_RIGHT))
		{
			topLeft.x++;
		}
		if (IsKeyReleased(KEY_UP))
		{
			topLeft.y--;
		}
		if (IsKeyReleased(KEY_DOWN))
		{
			topLeft.y++;
		}
	}
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyReleased(KEY_V))
	{
		int increment = 0;
		m_currentTool = ToolSelected::Brush;

		for (int x = topLeft.x; x <= copiedSize.x + topLeft.x; x++)
		{
			for (int y = topLeft.y; y <= copiedSize.y + topLeft.y; y++)
			{
				if (copiedPixels.at(increment).active && copiedPixels.at(increment).a > 0)
					m_pixels.at(x + (y * m_canvasSize.y)) = copiedPixels.at(increment);
				increment++;
				if (increment >= copiedPixels.size()) return;
			}
		}
	}
}

void Canvas::drawBox(bool m_select)
{
	int selected = mousePixel();
	float xPos = selected % static_cast<int>(m_canvasSize.x);
	float yPos = selected / static_cast<int>(m_canvasSize.x);

	int startX = math::min(startSelect.x, xPos);
	int endX = math::max(xPos, startSelect.x);

	float xP = 0.f, yP = 0.f;
	int i = 0;

	for (int x = startX; x <= endX; x++)
	{
		i = x + (m_canvasSize.y * startSelect.y);
		xP = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		yP = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if(!m_select)
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, m_selectedColour.rayColor());
		else
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, Colour(255,255,255,80).rayColor());

		i = x + (m_canvasSize.y * yPos);
		xP = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		yP = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if (!m_select)
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, m_selectedColour.rayColor());
		else
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, Colour(255, 255, 255, 80).rayColor());
	}

	int startY = math::min(startSelect.y, yPos);
	int endY = math::max(yPos, startSelect.y);

	for (int y = startY; y <= endY; y++)
	{
		i = y * m_canvasSize.x + startX;
		xP = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		yP = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if (!m_select)
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, m_selectedColour.rayColor());
		else
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, Colour(255, 255, 255, 80).rayColor());

		i = y * m_canvasSize.x + endX;
		xP = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		yP = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if (!m_select)
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, m_selectedColour.rayColor());
		else
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, Colour(255, 255, 255, 80).rayColor());
	}
}

void Canvas::drawOverlay()
{
	for (int x = topLeft.x; x <= selectedSize.x + topLeft.x; x++)
	{
		for (int y = topLeft.y; y <= selectedSize.y + topLeft.y; y++)
		{
			int i = x + (y * static_cast<int>(m_canvasSize.x));
			float xP = m_topRight.x + x * m_pixelSize;
			float yP = m_topRight.y + y * m_pixelSize;
			DrawRectangle(xP, yP, m_pixelSize, m_pixelSize, Colour(255,255,255,80).rayColor());
		}
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

	if (selecting)
	{
		if (m_currentTool == ToolSelected::BoxDraw)
		{
			drawBox(false);
		}
		if (m_currentTool == ToolSelected::boxSelect)
		{
			drawBox(true);
		}
	}
	if(m_currentTool == ToolSelected::boxDrag)
		drawOverlay();
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

int Canvas::mousePixel(Vector2 t_mouse)
{
	for (unsigned int i = 0; i < m_pixels.size(); i++)
	{
		float xPos = m_topRight.x + (i % static_cast<int>(m_canvasSize.x) * m_pixelSize);
		float yPos = m_topRight.y + (i / static_cast<int>(m_canvasSize.x) * m_pixelSize);

		if (math::coordInBox(t_mouse.x, t_mouse.y, xPos, yPos, static_cast<float>(m_pixelSize), static_cast<float>(m_pixelSize)))
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

	m_pixels.resize(image.width * image.height);

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
