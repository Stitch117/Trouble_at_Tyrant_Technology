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


class Texture2D;
class Character;
class Game_Screen_Level1 : Game_Screen
{
private:
	GameSceneManager* game_scene_manager = nullptr;

	Texture2D* m_background_texture = nullptr;

	Character* my_character = nullptr;

	GameText* m_pistolAmmoText = nullptr;
	GameText* m_scifiAmmoText = nullptr;

private:
	bool SetUpLevel(); 

	float backwallposition = 10.0f;
	float backgorundposition = 0.0f;
	float endwallposition = 2052.0f;

public:
	Game_Screen_Level1(SDL_Renderer* renderer, GameSceneManager* sceneManager);
	~Game_Screen_Level1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveLeft(SDL_Renderer* renderer, float ammount);
	void MoveRight(SDL_Renderer* renderer, float ammount); 
	bool CheckFightActive();
};
