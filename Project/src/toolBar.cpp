#include "toolBar.h"
#include "SimpleMaths.h"
#define RAYGUI_IMPLEMENTATION
#include "rayGui.h"

ToolBar::ToolBar() { }

ToolBar::~ToolBar() { }

void ToolBar::init()
{
	m_canvasStartPos.x = 0; m_canvasStartPos.y = 0;
	m_canvasSize.x = 64.f; m_canvasSize.y = 800;

	brush.init("brush.png", 16.f, 16.f, 32.f, 32.f);
	eraser.init("eraser.png", 16.f, 64.f, 32.f, 32.f);
	selector.init("colourSelector.png", 16.f, 112.f, 32.f, 32.f);
	boxDraw.init("boxDraw.png", 16.f, 160.f, 32.f, 32.f);
	boxSelect.init("boxSelect.png", 16.f, 208.f, 32.f, 32.f);
	load.init("load.png", 16.f, 256.f, 32.f, 32.f);
	save.init("save.png", 16.f, 304.f, 32.f, 32.f);

	highlightTexture = LoadTexture("highlight.png");
	selectedToolPos = brush.pos;
}

bool ToolBar::update()
{
	m_mousePos = GetMousePosition();

	if (math::coordInBox(m_mousePos, m_canvasStartPos, m_canvasSize))
	{
		if (brush.pressed(m_mousePos))
		{
			m_canvas->setTool(ToolSelected::Brush);
			selectedToolPos = brush.pos;
		}
		if (eraser.pressed(m_mousePos))
		{
			m_canvas->setTool(ToolSelected::Eraser);
			selectedToolPos = eraser.pos;
		}
		if (selector.pressed(m_mousePos))
		{
			m_canvas->setTool(ToolSelected::Selector);
			selectedToolPos = selector.pos;
		}
		if (boxDraw.pressed(m_mousePos))
		{
			m_canvas->setTool(ToolSelected::BoxDraw);
			selectedToolPos = boxDraw.pos;
		}
		if (save.pressed(m_mousePos))
		{
			showMessageBox = true;
			m_canvas->saveCurrent();
		}
		if (load.pressed(m_mousePos))
		{
			m_canvas->load();
		}
		if (boxSelect.pressed(m_mousePos))
		{
			m_canvas->setTool(ToolSelected::boxSelect);
			selectedToolPos = boxSelect.pos;
		}
		return true;
	}
	return false;
}

void ToolBar::render()
{
	DrawRectangleV(m_canvasStartPos, m_canvasSize, Colour(104, 144, 151, 255).rayColor());

	if (showMessageBox)
	{
		Rectangle bound = { 85, 70, 250, 100 };
		int result = GuiMessageBox(bound,
			"#191#Message Box", "Image Saved into output.png", "ok");

		if (result >= 0) showMessageBox = false;
	}


	brush.render();
	eraser.render();
	selector.render();
	boxDraw.render();
	boxSelect.render();
	load.render();
	save.render();

	DrawTexture(highlightTexture, selectedToolPos.x, selectedToolPos.y, WHITE);
}

bool Button::pressed(Vector2 mouse)
{
	if (math::coordInBox(mouse, pos, size)) {
		highlighted = true;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			return true;
	}
	else
		highlighted = false;
	return false;
}
