#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	m_canvas.init();
}

void Game::Run()
{
	// initialise window and game
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1280, 800, "Array");
	SearchAndSetResourceDir("resources");

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
	m_canvas.update();
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		
	}
}

void Game::Render()
{
	m_canvas.render();
}
