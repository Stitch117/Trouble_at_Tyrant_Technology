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
#include "Melee_Enemy.h"
#include "Ranged_Enemy.h"
#include "robotGuard.h"

class Texture2D;
class Character;
class Game_Screen_Level2 : Game_Screen
{
private:
	float backwallposition2 = 10.0f;
	float backgorundposition2 = 0.0f;
	float endwallposition2 = 2052.0f;


	GameSceneManager* game_scene_manager = nullptr;

	Texture2D* m_background_texture2 = nullptr;

	Character* my_character2 = nullptr;

	GameText* m_pistolAmmoText = nullptr;
	GameText* m_scifiAmmoText = nullptr;

private:
	bool SetUpLevel();

public:
	Game_Screen_Level2(SDL_Renderer* renderer, GameSceneManager* sceneManager);
	~Game_Screen_Level2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveLeft(SDL_Renderer* renderer, float ammount);
	void MoveRight(SDL_Renderer* renderer, float ammount);
};

