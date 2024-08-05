#include "Game_Screen.h"
#include "GameSceneManager.h"

Game_Screen::Game_Screen(SDL_Renderer* renderer, GameSceneManager* sceneManager)
{
	m_renderer = renderer; 
}

Game_Screen::~Game_Screen()
{
	m_renderer = nullptr;
}

void Game_Screen::Render()
{

}

void Game_Screen::Update(float deltaTime, SDL_Event e)
{

}
