#pragma once
#include "constants.h"
#include "Game_Object.h"
#include "Bullet.h"
#include "GameSceneManager.h"

class Character : public Game_Object
{
protected:
	bool m_dead = false;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void MoveUp(float deltaTime);
	virtual void MoveDown(float deltaTime);

private:
	int health = 10;
	FACING m_facing_direction;
	string unlockedWeapons[3] = { "unarmed", "nullptr", "nullptr"};

	GameSceneManager* m_game_scene_manager = nullptr;

public:
	string weapons[3] = { "unarmed", "pistol", "scifi" };
	string currentWeapon = weapons[0];
	float movementSpeed = PLAYERMOVEMENTSPEED;  
	int pistolAmmoCount = 10;
	int scifiAmmoCount = 10;
	int attackCooldown = 500;
	//animation bools
	bool m_attacking = false; 
	bool m_damaged = false;
	//movement bools
	bool m_moving_right;
	bool m_moving_left;
	bool m_moving_up;
	bool m_moving_down;

	Character(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, GameSceneManager* game_scene_manager);
	~Character();

	int GetHealth();
	FACING getDirection();
	void Damage(int damage);
	void PickUpAmmo(int type, int amount);
	void PickUpPistol();
	void PickUpScifi();
	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	string getAmmoCountPistolSTR(int pistolAmmo);
	string getAmmoCountSciFiSTR(int pistolAmmo);

	void changeWeapon(string currentWeapon);

	Rect2D GetCollionBox();
};

