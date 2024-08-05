#pragma once
#include "Game_Screen.h"
#include "GameSceneManager.h"
#include "constants.h"
#include "Commons.h"
#include "Game_Object.h"
#include "Character.h"
#include "Texture2D.h"
#include "Collision.h"
#include "Box.h"
#include "GameText.h"
#include "Boss_Enemy.h"

class Texture2D;
class Character;
class Game_Screen_Level3 : Game_Screen
{
private:
	float backwallposition3 = 0.0f;
	float backgorundposition3 = 0.0f;
	float endwallposition3 = 1140.0f;

	GameSceneManager* game_scene_manager = nullptr;

	Texture2D* m_background_texture3 = nullptr;

	Character* my_character3 = nullptr;

	GameText* m_pistolAmmoText = nullptr;
	GameText* m_scifiAmmoText = nullptr;

private:
	bool SetUpLevel();

public:
	Game_Screen_Level3(SDL_Renderer* renderer, GameSceneManager* sceneManager);
	~Game_Screen_Level3();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveLeft(SDL_Renderer* renderer, float ammount);
	void MoveRight(SDL_Renderer* renderer, float ammount);
};

