#pragma once
#include "constants.h"
#include "Game_Object.h"
#include "Character.h" 
#include "Collision.h"

class robotGuard : public Game_Object
{
private:
	int m_health;
	FACING m_facing_direction;
	Character* m_player = nullptr;
public:
	//bools for animation
	bool m_damaged = false;
	bool m_attackingMelee = false;
	bool m_dying = false;
	bool m_dead = false;

	int guardAttackCooldown;

	float m_speed = 0.1;

	robotGuard(SDL_Renderer* renderer, std::string imagepath, Vector2D start_position, Character* player);
	~robotGuard();

	void Damage(int damage);
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	FACING GetDirection() { return m_facing_direction; }

	Rect2D GetCollionBox();
};
