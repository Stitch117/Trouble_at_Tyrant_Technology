#include "Main_Menu.h"
#include "Game_Screen.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

Main_Menu::Main_Menu(SDL_Renderer* renderer, GameSceneManager* scene_manager) : Game_Screen(renderer, scene_manager)
{
	m_renderer = renderer;

	game_scene_manager = scene_manager;

	SetUpLevel(); 
}

Main_Menu::~Main_Menu()
{
	delete(m_background_texture);

	m_background_texture = nullptr;
}

void Main_Menu::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void Main_Menu::Update(float deltaTime, SDL_Event e) 
{
	//change to level 1 one pressed e
	switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_e:
			if (game_scene_manager->GetCurrentScreen() == SCREEN_MENU)
			{
				game_scene_manager->ChangeScreen(SCREEN_LEVEL1);
			}
			break;
		default:;
		}
		break;

	//change to level one when pressing start
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 3:
			if (game_scene_manager->GetCurrentScreen() == SCREEN_MENU)
			{
				game_scene_manager->ChangeScreen(SCREEN_LEVEL1);
			}
			break;
		default:;
		}
		break;
	default:;
	}


}

bool Main_Menu::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	//throw error if texture didn't laod properly
	if (!m_background_texture->LoadFromFile("Images/Main Menu.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}