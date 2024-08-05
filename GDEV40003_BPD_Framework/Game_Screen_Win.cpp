#include "Game_Screen_Win.h"
#include "GameSceneManager.h"
#include "Game_Screen.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

Game_Screen_Win::Game_Screen_Win(SDL_Renderer* renderer, GameSceneManager* sceneManager) : Game_Screen(renderer, sceneManager)
{
	m_renderer = renderer;
	game_scene_manager = sceneManager;
	SetUpLevel();
}

Game_Screen_Win::~Game_Screen_Win()
{
	delete(m_background_texture);

	m_background_texture = nullptr;
}

void Game_Screen_Win::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void Game_Screen_Win::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		//change to menu on pressing e
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_e:
			game_scene_manager->ChangeScreen(SCREEN_MENU);
			break;
		default:;
		}
		break;

		//change to menu when pressing start on evacade
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 3:
			if (game_scene_manager->GetCurrentScreen() == SCREEN_WINPAGE)
			{
				game_scene_manager->ChangeScreen(SCREEN_MENU);
			}
			break;
		default:;
		}
		break;
	default:;
	}

}

bool Game_Screen_Win::SetUpLevel()
{
	//make background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Win Screen.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}