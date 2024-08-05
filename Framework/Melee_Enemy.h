#pragma once
#include "constants.h"
#include "Game_Object.h"
#include "Character.h" 
#include "Collision.h"

#define ENEMYSPEED 0.07

class Melee_Enemy : public Game_Object
{
private:
	int m_health;
	FACING m_facing_direction;
	Character* m_player = nullptr;
public:
	//bools for animations
	bool m_damaged = false;
	bool m_attacking = false;
	bool m_dying = false;
	bool m_dead = false;

	int MeleeAttackCooldown;

	float m_speed = ENEMYSPEED;

	Melee_Enemy(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player);
	~Melee_Enemy();

	void Damage(int damage);
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	FACING GetDirection() { return m_facing_direction; }

	Rect2D GetCollionBox(); 
};

