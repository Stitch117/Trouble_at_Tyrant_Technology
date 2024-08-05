#include "robotGuard.h"
#include<iostream>

//animation bools
Uint32 guardEnemySprite;
Uint32 guardEnemyRow;

int guardEnemyDamagedTimer = 0;

Vector2D guardTargetPos = Vector2D(0, 0);

robotGuard::robotGuard(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player) :
	Game_Object(renderer, imagepath, start_position)
{
	m_health = 10;
	m_facing_direction = FACING_LEFT;
	m_player = player;
}

robotGuard::~robotGuard()
{

}

void robotGuard::Damage(int damage)
{
	//play damage flash
	if (damage > 0)
	{
		m_damaged = true;
	}

	m_health -= damage;

	//play dying animation
	if (m_health <= 0)
	{
		m_dying = true;
	}
}

void robotGuard::Render()
{
	//play aniamtions on facign right
	if (m_facing_direction == FACING_RIGHT)
	{
		//play dying animation
		if (m_dying == true)
		{
			guardEnemyRow = 3;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, guardEnemySprite * (m_texture->GetWidth() / 6), guardEnemyRow * (m_texture->GetHeight() / 5),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);

			//set dead at end of dying
			if (guardEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//play damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE, 1 * (m_texture->GetWidth() / 6),
				4 * (m_texture->GetHeight() / 5), m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);
			guardEnemyDamagedTimer++;

			if (guardEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//play melee attack animation
		else if (m_attackingMelee == true)
		{
			guardEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, guardEnemySprite * (this->m_texture->GetWidth() / 6), guardEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);
			
			//resets the speed after attacking
			if (guardEnemySprite == 5)
			{
				m_attackingMelee = false;
				m_speed = 0.1;
			}
		}
		//play walk animation
		else if (m_attackingMelee == false)
		{
			guardEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, guardEnemySprite * (this->m_texture->GetWidth() / 6), guardEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);
		}
	}
	//play animation facing left
	else
	{
		//play dying animation
		if (m_dying == true)
		{
			guardEnemyRow = 3;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, guardEnemySprite * (m_texture->GetWidth() / 6), guardEnemyRow * (m_texture->GetHeight() / 5),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);

			//set dead at end of animation
			if (guardEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//play daage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 1 * (m_texture->GetWidth() / 6 - 24),
				4 * (m_texture->GetHeight() / 5), m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);
			guardEnemyDamagedTimer++;

			if (guardEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//play attack animation
		else if (m_attackingMelee == true)
		{
			guardEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, guardEnemySprite * (this->m_texture->GetWidth() / 6), guardEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);

			if (guardEnemySprite == 5)
			{
				m_attackingMelee = false;
				m_speed = 0.1;
			}
		}
		//play walk animation
		else if (m_attackingMelee == false)
		{
			guardEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			guardEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, guardEnemySprite * (this->m_texture->GetWidth() / 6), guardEnemyRow * (this->m_texture->GetHeight() / 50),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);
		}
	}
}

void robotGuard::Update(float deltaTime, SDL_Event e)
{
	if (m_health > 0)
	{
		guardAttackCooldown--; //reduce the attack cooldown

		//Euclideans to find target pos
		Vector2D rangedTargetPos = m_player->GetPosition();

		float XdifferenceSquared = (rangedTargetPos.x - GetPosition().x) * (rangedTargetPos.x - GetPosition().x);
		float YdifferenceSquared = (rangedTargetPos.y - GetPosition().y) * (rangedTargetPos.y - GetPosition().y);
		float EuclideanDistance = sqrt(XdifferenceSquared + YdifferenceSquared);

		float m_distanceX = (rangedTargetPos.x - GetPosition().x) / EuclideanDistance;
		float m_distanceY = (rangedTargetPos.y - GetPosition().y) / EuclideanDistance;

		//get facing direction
		if (m_distanceX < 0)
		{
			m_facing_direction = FACING_LEFT;
		}
		else if (m_distanceX > 0)
		{
			m_facing_direction = FACING_RIGHT;
		}

		SetPosition(Vector2D(GetPosition().x + m_distanceX * m_speed, GetPosition().y + m_distanceY * (m_speed * 2)));
	}
}

Rect2D robotGuard::GetCollionBox() 
{
	return Rect2D(m_position.x, m_position.y, this->m_texture->GetWidth() / 6 - 24, m_texture->GetHeight() / 5);
}