#include "Melee_Enemy.h"

//animation bools
Uint32 MeleeEnemySprite;
Uint32 MeleeEnemyRow;

int MeleeEnemyDamagedTimer = 0;

Vector2D targetPos = Vector2D(0, 0);

Melee_Enemy::Melee_Enemy(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player) :
	Game_Object(renderer, imagepath, start_position)
{
	m_health = 6;
	m_facing_direction = FACING_LEFT;
	m_player = player;
}

Melee_Enemy::~Melee_Enemy()
{

}

void Melee_Enemy::Damage(int damage)
{
	//play damged aniamtion
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

void Melee_Enemy::Render()
{
	//play animations on facing right
	if (m_facing_direction == FACING_RIGHT)
	{
		//play dying animation
		if (m_dying == true)
		{
			MeleeEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			MeleeEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, MeleeEnemySprite * (m_texture->GetWidth() / 6), MeleeEnemyRow * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			if (MeleeEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//play damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE, 1 * (m_texture->GetWidth() / 6),
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			MeleeEnemyDamagedTimer++;

			if (MeleeEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//play walk animation
		else if (m_attacking == false)
		{
			MeleeEnemyRow = 0; 
			Uint32 ticks; 
			ticks = SDL_GetTicks(); 
			Uint32 spriteChangeTime = ticks / 150; 
			MeleeEnemySprite = spriteChangeTime % 6; 

			m_texture->Render(m_position, SDL_FLIP_NONE, MeleeEnemySprite * (this->m_texture->GetWidth() / 6), MeleeEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}
		//play attack animation
		else if (m_attacking == true)
		{
			MeleeEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			MeleeEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, MeleeEnemySprite * (this->m_texture->GetWidth() / 6), MeleeEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);

			if (MeleeEnemySprite == 5)
			{
				m_attacking = false;
				m_speed = ENEMYSPEED;
			}
		}
	}
	//play animations for facing left
	else
	{
		//play dying animation
		if (m_dying == true)
		{
			MeleeEnemyRow = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			MeleeEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, MeleeEnemySprite * (m_texture->GetWidth() / 6), MeleeEnemyRow * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);

			if (MeleeEnemySprite == 5)
			{
				m_dying = false;
				m_dead = true;
			}

		}
		//play damage flash
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 1 * (m_texture->GetWidth() / 6 - 24),
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6 , m_texture->GetHeight() / 4);
			MeleeEnemyDamagedTimer++;

			if (MeleeEnemyDamagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		//play walk animation
		else if (m_attacking == false)
		{
			MeleeEnemyRow = 0;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			MeleeEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, MeleeEnemySprite * (this->m_texture->GetWidth() / 6), MeleeEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}
		//play attack animation
		else if (m_attacking == true)
		{
			MeleeEnemyRow = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			MeleeEnemySprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, MeleeEnemySprite * (this->m_texture->GetWidth() / 6), MeleeEnemyRow * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);

			if (MeleeEnemySprite == 5)
			{
				m_attacking = false;
				m_speed = ENEMYSPEED;
			}
		}
	}
}

void Melee_Enemy::Update(float deltaTime, SDL_Event e)
{
	if (m_health > 0)
	{
		MeleeAttackCooldown--; //reduce attack cooldown

		//Euclidians to find target pos and move it slowly to target pos
		Vector2D targetPos = m_player->GetPosition();

		float XdifferenceSquared = (targetPos.x - GetPosition().x) * (targetPos.x - GetPosition().x);
		float YdifferenceSquared = (targetPos.y - GetPosition().y) * (targetPos.y - GetPosition().y);
		float EuclideanDistance = sqrt(XdifferenceSquared + YdifferenceSquared);

		float m_distanceX = (targetPos.x - GetPosition().x) / EuclideanDistance;
		float m_distanceY = (targetPos.y - GetPosition().y) / EuclideanDistance;

		//get facing direction
		if (m_distanceX < 0)
		{
			m_facing_direction = FACING_LEFT;
		}
		else if (m_distanceX > 0)
		{
			m_facing_direction = FACING_RIGHT;
		}

		if (m_facing_direction == FACING_LEFT)
		{
			SetPosition(Vector2D(GetPosition().x + m_distanceX * m_speed, GetPosition().y + m_distanceY * m_speed));
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			SetPosition(Vector2D(GetPosition().x + m_distanceX * m_speed, GetPosition().y + m_distanceY * m_speed));

		}
	}
}

Rect2D Melee_Enemy::GetCollionBox()
{
	//return collision of the size fo the sprite box not the whole sprite sheet
	return Rect2D(m_position.x, m_position.y, this->m_texture->GetWidth() / 6 - 24, m_texture->GetHeight() / 4);
}