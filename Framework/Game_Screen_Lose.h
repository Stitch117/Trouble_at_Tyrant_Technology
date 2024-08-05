#pragma once
#include "Game_Screen.h"
#include "GameSceneManager.h"
#include "Commons.h"

class Texture2D;

class Game_Screen_Lose : Game_Screen
{
private:
	GameSceneManager* game_scene_manager = nullptr;

	Texture2D* m_background_texture = nullptr;

private:
	bool SetUpLevel();

public:
	Game_Screen_Lose(SDL_Renderer* renderer, GameSceneManager* sceneManager);
	~Game_Screen_Lose();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
};
