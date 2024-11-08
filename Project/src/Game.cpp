// David Strikaitis c00283152
#include "Game.h"

Game::Game()
{
	m_canvas = std::make_shared<Canvas>();
	m_colourPicker = std::make_shared<ColourPicker>();
	m_colourPicker->setCanvas(m_canvas);
}

Game::~Game()
{
}

void Game::Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	// initialise window and game
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1280, 800, "Pixel Art");
	SearchAndSetResourceDir("resources");

	m_canvas->init();
	m_colourPicker->init();
}

void Game::Run()
{
	// game loop
	while (!WindowShouldClose())
	{
		// updates
		Update();

		// drawing
		BeginDrawing();
		ClearBackground(BLACK);
		Render();
		EndDrawing();
	}
	CloseWindow();
}

void Game::Update()
{
	// avoid overlap clicks
	if(!m_colourPicker->update())
		m_canvas->update();

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		
	}
}

void Game::Render()
{
	m_canvas->render();
	m_colourPicker->render();
}
