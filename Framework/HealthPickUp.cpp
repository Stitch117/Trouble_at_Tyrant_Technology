#include "HealthPickUp.h"

HealthPickUp::HealthPickUp(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition):
	Game_Object(renderer, imagepath, startPosition) 
{

}

HealthPickUp::~HealthPickUp()
{

}

void HealthPickUp::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void HealthPickUp::Update()
{

}

void HealthPickUp::Collision(Character* player)
{
	//heal player two health on collision
	player->Damage(-2);
}