#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SDL.h>

class GameSceneManager;

class Game_Screen
{
protected:
	SDL_Renderer* m_renderer = nullptr;


public:
	Game_Screen(SDL_Renderer* renderer, GameSceneManager* sceneManager);
	~Game_Screen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // GAMESCREEN_H	

