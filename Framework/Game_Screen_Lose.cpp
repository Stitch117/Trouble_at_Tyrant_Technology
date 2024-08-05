#include "Game_Screen_Lose.h"
#include "GameSceneManager.h"
#include "Game_Screen.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

Game_Screen_Lose::Game_Screen_Lose(SDL_Renderer* renderer, GameSceneManager* sceneManager) : Game_Screen(renderer, sceneManager)
{
	m_renderer = renderer;
	game_scene_manager = sceneManager;
	SetUpLevel();
}

Game_Screen_Lose::~Game_Screen_Lose()
{
	delete(m_background_texture);

	m_background_texture = nullptr;
}

void Game_Screen_Lose::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void Game_Screen_Lose::Update(float deltaTime, SDL_Event e)
{
	// make it go to menu on pressing e
	switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_e:
			game_scene_manager->ChangeScreen(SCREEN_MENU); 
			break;
		default:;
		}
		break;

		//make it go to the menu when pressing start on the evacade
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 3:
			if (game_scene_manager->GetCurrentScreen() == SCREEN_LOSEPAGE)
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

bool Game_Screen_Lose::SetUpLevel()
{
	//make backgorund texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Lose Screen.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}