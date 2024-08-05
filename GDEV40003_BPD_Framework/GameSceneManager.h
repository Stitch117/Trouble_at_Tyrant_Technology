#pragma once
#include <SDL.h>
#include "Commons.h"
#include <iostream>

class Game_Screen;

class GameSceneManager
{
private:
	SDL_Renderer* m_renderer = nullptr;
	Game_Screen* m_current_screen = nullptr;
	int ScreenIndex;

public:
	GameSceneManager(SDL_Renderer* renderer, SCREENS startscreen);
	~GameSceneManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);
	int GetCurrentScreen() const;
};

