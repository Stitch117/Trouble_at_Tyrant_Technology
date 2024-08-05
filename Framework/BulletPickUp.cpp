#include "BulletPickUp.h"


BulletPickUp::BulletPickUp(SDL_Renderer * renderer, std::string imagepath, Vector2D startPosition, int type) :
	Game_Object(renderer, imagepath, startPosition) 
{
	m_type = type;
}

BulletPickUp::~BulletPickUp()
{

}

void BulletPickUp::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE); 
}

void BulletPickUp::Update()
{
	
}

void BulletPickUp::Collision(Character* player, int type)
{
	//add number to ammo count
	if (type == 1)
	{
		player->PickUpAmmo(type, 5);
	}
	else if (type == 2)
	{
		player->PickUpAmmo(type, 3);
	}
}