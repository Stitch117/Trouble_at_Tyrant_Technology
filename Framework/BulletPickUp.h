#pragma once
#include "Game_Object.h"
#include "Character.h"

class BulletPickUp : public Game_Object
{
public:
	int m_type = 0;

	BulletPickUp(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, int type);
	~BulletPickUp();

	void Render();
	void Update();
	void Collision(Character* player, int type);
};

