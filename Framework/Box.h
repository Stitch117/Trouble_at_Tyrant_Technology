#pragma once
#include "Game_Object.h"
#include "HealthPickUp.h"
#include "BulletPickUp.h"
#include "string"

class Box : public Game_Object
{
private:
	int health = 1;

public:
	Box(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition);
	~Box();

	void Damage(int damage);
	int Death();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

