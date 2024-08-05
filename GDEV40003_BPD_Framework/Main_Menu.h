#pragma once
#include "Game_Screen.h"
#include "GameSceneManager.h"
#include "Commons.h"

class Texture2D;

class Main_Menu : Game_Screen
{
private:
	Texture2D* m_background_texture = nullptr;

	GameSceneManager* game_scene_manager = nullptr;

private:
	bool SetUpLevel();

public:
	Main_Menu(SDL_Renderer* renderer, GameSceneManager* game_scene_mangaer);
	~Main_Menu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
};

