#include "Ranged_Enemy.h"

//animation bools
Uint32 RangedEnemySprite;
Uint32 RangedEnemyRow;

int RangedEnemyDamagedTimer = 0;

Vector2D rangedTargetPos = Vector2D(0, 0);

Ranged_Enemy::Ranged_Enemy(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player) :
	Game_Object(renderer, imagepath, start_position)
{
	m_health = 4;
	m_facing_direction = FACING_LEFT;
	m_player = player;
}

Ranged_Enemy::~Ranged_Enemy()
{

}

void Ranged_Enemy::Damage(int damage)
{
	//play damaged animation
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

void Ranged_Enemy::Render()
{
	//facing right animations
	if (m_facing_direction == FACING_RIGHT)
	{
		//dying animtion
		if (m_dying == true)
		{
			RangedEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, RangedEnemySprite * (m_texture->GetWidth() / 6), RangedEnemyRow * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			if (RangedEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE, 1 * (m_texture->GetWidth() / 6),
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			RangedEnemyDamagedTimer++;

			if (RangedEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//attack aniamtion
		else if (m_attacking == true)
		{
			RangedEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, RangedEnemySprite * (this->m_texture->GetWidth() / 6), RangedEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);

			if (RangedEnemySprite == 5)
			{
				m_attacking = false;
				m_speed = ENEMYSPEED;
			}
		}
		//walk aniamtion
		else if (m_attacking == false)
		{
			RangedEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, RangedEnemySprite * (this->m_texture->GetWidth() / 6), RangedEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}
	}
	//play facing left animation
	else
	{
		//dying animation
		if (m_dying == true)
		{
			RangedEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, RangedEnemySprite * (m_texture->GetWidth() / 6), RangedEnemyRow * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);

			if (RangedEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 1 * (m_texture->GetWidth() / 6 - 24),
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			RangedEnemyDamagedTimer++;

			if (RangedEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//attacking animation
		else if (m_attacking == true)
		{
			RangedEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, RangedEnemySprite * (this->m_texture->GetWidth() / 6), RangedEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 12, this->m_texture->GetHeight() / 4);

			if (RangedEnemySprite == 5)
			{
				m_attacking = false;
				m_speed = ENEMYSPEED;
			}
		}
		//walk aniamtion
		else if (m_attacking == false)
		{
			RangedEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			RangedEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, RangedEnemySprite * (this->m_texture->GetWidth() / 6), RangedEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}
	}
}

void Ranged_Enemy::Update(float deltaTime, SDL_Event e)
{
	if (m_health > 0)
	{
		RangedAttackCooldown--; //reduce attack cooldown

		//Euclideans to fid target pos and distance
		Vector2D rangedTargetPos = m_player->GetPosition();

		float XdifferenceSquared = (rangedTargetPos.x - GetPosition().x) * (rangedTargetPos.x - GetPosition().x);
		float YdifferenceSquared = (rangedTargetPos.y - GetPosition().y) * (rangedTargetPos.y - GetPosition().y);
		float EuclideanDistance = sqrt(XdifferenceSquared + YdifferenceSquared);

		//move to wards target pos slowly
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
		
		SetPosition(Vector2D(GetPosition().x, GetPosition().y + m_distanceY * (m_speed*2)));
	}
}

Rect2D Ranged_Enemy::GetCollionBox()
{
	return Rect2D(m_position.x, m_position.y, this->m_texture->GetWidth() / 6 - 24, m_texture->GetHeight() / 4);
}