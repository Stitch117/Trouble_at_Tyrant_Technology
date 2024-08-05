#include "Boss_Enemy.h"
#include<iostream>

//aniamtion variables
Uint32 bossEnemySprite;
Uint32 bossEnemyRow;

int bossEnemyDamagedTimer = 0;

Vector2D bossTargetPos = Vector2D(0, 0);

Boss_Enemy::Boss_Enemy(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player) :
	Game_Object(renderer, imagepath, start_position)
{
	m_health = 20;
	m_facing_direction = FACING_LEFT;
	m_player = player;
}

Boss_Enemy::~Boss_Enemy()
{

}

void Boss_Enemy::Damage(int damage)
{
	if (damage > 0)
	{
		//play damaged aniamtion
		m_damaged = true;
	}

	m_health -= damage;

	if (m_health <= 0)
	{
		//play dying animation
		m_dying = true;
	}
}

void Boss_Enemy::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		//animation for dying
		if (m_dying == true)
		{
			bossEnemyRow = 3; //row 3 of sprite sheet
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6; //get timer to change sprite every 150ms

			//render the spicific part of the sprite sheet
			m_texture->Render(m_position, SDL_FLIP_NONE, bossEnemySprite * (m_texture->GetWidth() / 6), bossEnemyRow * (m_texture->GetHeight() / 5),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);

			// set dead if at end of dying animation
			if (bossEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}

		//play damaged animation
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE, 1 * (m_texture->GetWidth() / 6),
				4 * (m_texture->GetHeight() / 5), m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);
			bossEnemyDamagedTimer++; //be damaged for 150ms

			if (bossEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}

		//play ranged atatck animation
		else if (m_attackingRanged == true)
		{
			bossEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6, this->m_texture->GetHeight() / 5);
		}

		//play melee attack animation
		else if (m_attackingMelee == true)
		{
			bossEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);

			if (bossEnemySprite == 5)
			{
				m_attackingMelee = false;
				m_speed = 0.1; // reduce speed and set back whilst attacking
			}
		}

		//if not attacking then walk animation will play
		else if (m_attackingMelee == false && m_attackingRanged == false)
		{
			bossEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);
		}
	}
	//same animations player but facing the otherr direction
	else
	{
		//dying animation
		if (m_dying == true)
		{
			bossEnemyRow = 3;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, bossEnemySprite * (m_texture->GetWidth() / 6), bossEnemyRow * (m_texture->GetHeight() / 5),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);

			if (bossEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 1 * (m_texture->GetWidth() / 6 - 24),
				4 * (m_texture->GetHeight() / 5), m_texture->GetWidth() / 6, m_texture->GetHeight() / 5);
			bossEnemyDamagedTimer++;

			if (bossEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//ranged attack
		else if (m_attackingRanged == true)
		{
			bossEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);

			if (bossEnemySprite == 5)
			{
				m_speed = 0.1;
			}
		}
		//melee attack animation
		else if (m_attackingMelee == true)
		{
			bossEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 5),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);

			if (bossEnemySprite == 5)
			{
				m_attackingMelee = false;
				m_speed = 0.1;
			}
		}
		//walk animation
		else if (m_attackingMelee == false && m_attackingRanged == false)
		{
			bossEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			bossEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, bossEnemySprite * (this->m_texture->GetWidth() / 6), bossEnemyRow * (this->m_texture->GetHeight() / 50),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 5);
		}
	}
}

void Boss_Enemy::Update(float deltaTime, SDL_Event e)
{
	if (m_health > 0)
	{
		bossAttackCooldown--; //reduce attack cooldown


		//euclidians to find the target position
		Vector2D rangedTargetPos = m_player->GetPosition();

		float XdifferenceSquared = (rangedTargetPos.x - GetPosition().x) * (rangedTargetPos.x - GetPosition().x);
		float YdifferenceSquared = (rangedTargetPos.y - GetPosition().y) * (rangedTargetPos.y - GetPosition().y);
		float EuclideanDistance = sqrt(XdifferenceSquared + YdifferenceSquared);

		//divide distance down to make it move pixel by pixel
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

		//move boss towards the players y position but staying at same x position
		SetPosition(Vector2D(GetPosition().x, GetPosition().y + m_distanceY * (m_speed * 2)));
	}
}

Rect2D Boss_Enemy::GetCollionBox()
{
	//return the texture box size for the sprite being shown, not the whole texture
	return Rect2D(m_position.x, m_position.y, this->m_texture->GetWidth() / 6 - 24, m_texture->GetHeight() / 5);
}