#pragma once
#include "Game_Object.h"
#include "Character.h"

class Bullet : public Game_Object
{
protected:
	float m_lifespan;
	bool m_movingRight = false;
	bool m_movingLeft = false;
public:
	int m_type = 0;
	bool alive = false;

	Bullet(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, int type, float lifespan, FACING direction);
	~Bullet();

	void movingRight();
	void movingLeft();

	void Render();
	void Update(FACING direction);
	void Collision(int type);
};

