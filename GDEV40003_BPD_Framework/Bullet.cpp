#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, std::string imagepath, Vector2D start_Position, int type, float lifespan, FACING direction) :
	Game_Object(renderer, imagepath, start_Position) 
{
	m_lifespan = lifespan;
	m_type = type;
	//get direction to move
	if (direction == FACING_LEFT)
	{
		this->m_movingLeft = true;
	}
	else if (direction == FACING_RIGHT)
	{
		this->m_movingRight = true;
	}
}

Bullet::~Bullet()
{
	m_movingLeft = false;
	m_movingRight = false;
}

void Bullet::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Bullet::movingRight()
{
	this->SetPosition(Vector2D(GetPosition().x + 0.5, GetPosition().y));
}

void Bullet::movingLeft()
{
	this->SetPosition(Vector2D(GetPosition().x - 0.5, GetPosition().y));
}

void Bullet::Update(FACING direction)
{
	this->m_lifespan -= 1; //have a timer for it to die when reaching 0
	if (this->m_lifespan <= 0)
	{
		this->alive = false;
	}

	if (m_movingLeft == true)
	{
		movingLeft();
	}
	else if (m_movingRight == true)
	{
		movingRight();
	}
}

void Bullet::Collision(int type)
{

}