#pragma once
#include "Game_Object.h"
#include "Character.h"

class HealthPickUp : public Game_Object
{
public:
	HealthPickUp(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition);
	~HealthPickUp();

	void Render();
	void Update();
	void Collision(Character* player);
};

