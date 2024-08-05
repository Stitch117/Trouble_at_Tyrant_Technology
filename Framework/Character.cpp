#include "Character.h"
#include "constants.h"
#include "Texture2D.h"
#include "Collision.h"

#include <iostream>

//variables for animation
Uint32 sprite;
Uint32 row;

int damagedTimer = 0;

Character::Character(SDL_Renderer* renderer, std::string imagepath, Vector2D start_Position, GameSceneManager* game_scene_manager) :
	Game_Object( renderer, imagepath, start_Position)
{
	//bools fo rmoving smoothly
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_moving_down = false;
	m_moving_up = false;

	m_game_scene_manager = game_scene_manager;
}

Character::~Character()
{

}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		//dead animation
		if (m_dead == true)
		{
			row = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			sprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, sprite * (m_texture->GetWidth() / 6), row * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);

			//go to lose page if charachter is dead
			if (sprite == 5)
			{
				m_game_scene_manager->ChangeScreen(SCREEN_LOSEPAGE);
			}
			
		}
		//damage flash on character
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE, 1 * (m_texture->GetWidth() / 6),
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			damagedTimer++;
			if (damagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}

		//walking animation
		else if (m_attacking == false)
		{
			row = 0;
			m_texture->Render(m_position, SDL_FLIP_NONE, sprite * (this->m_texture->GetWidth() / 6), row * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}

		//punch animation
		else if (m_attacking == true && currentWeapon == weapons[0])
		{
			row = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			sprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_NONE, sprite * (this->m_texture->GetWidth() / 6), row * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);

			//set back to walk after a punch animation
			if (sprite == 5)
			{
				m_attacking = false;
			}
		}
	}
	//same animation but facing other direction
	else
	{
		//dead animation
		if (m_dead == true)
		{
			row = 2;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			sprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, sprite * (m_texture->GetWidth() / 6), row * (m_texture->GetHeight() / 4),
				m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);

			if (sprite == 5)
			{
				m_game_scene_manager->ChangeScreen(SCREEN_LOSEPAGE);
			}

		}
		//damaged animation
		else if (m_damaged == true)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 1 * (m_texture->GetWidth() / 6) - 24,
				3 * (m_texture->GetHeight() / 4), m_texture->GetWidth() / 6, m_texture->GetHeight() / 4);
			damagedTimer++;
			if (damagedTimer % 150 == 0)
			{
				m_damaged = false;
			}
		}
		
		//walking animation
		else if (m_attacking == false)
		{
			row = 0;
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, sprite * (this->m_texture->GetWidth() / 6), row * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
		}
		//punch animation
		else if (m_attacking == true && currentWeapon == weapons[0])
		{ 
			row = 1;
			Uint32 ticks;
			ticks = SDL_GetTicks();
			Uint32 spriteChangeTime = ticks / 150;
			sprite = spriteChangeTime % 6;

			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, sprite * (this->m_texture->GetWidth() / 6), row * (this->m_texture->GetHeight() / 4),
				this->m_texture->GetWidth() / 6 - 24, this->m_texture->GetHeight() / 4);
			//set back to walk after punch
			if (sprite == 5)
			{
				m_attacking = false;
			}
		}
	}
}

int Character::GetHealth()
{
	return health;
}

FACING Character::getDirection()
{
	return m_facing_direction;
}

void Character::MoveLeft(float deltaTime)
{
	//move left over time and change sprite for animation
	Uint32 ticks = 0;
	ticks = SDL_GetTicks();
	Uint32 spriteChangeTime = ticks / 150;
	sprite = spriteChangeTime % 6;
	m_position.x -= deltaTime * movementSpeed;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{ 
	Uint32 ticks = 0;
	ticks = SDL_GetTicks();
	Uint32 spriteChangeTime = ticks / 150;
	sprite = spriteChangeTime % 6;
	m_position.x += deltaTime * movementSpeed;
	m_facing_direction = FACING_RIGHT;
}

void Character::MoveUp(float deltaTime)
{
	Uint32 ticks = 0;
	ticks = SDL_GetTicks();
	Uint32 spriteChangeTime = ticks / 150;
	sprite = spriteChangeTime % 6;
	m_position.y -= deltaTime * movementSpeed;
}

void Character::MoveDown(float deltaTime)
{
	Uint32 ticks = 0;
	ticks = SDL_GetTicks(); 
	Uint32 spriteChangeTime = ticks / 150;
	sprite = spriteChangeTime % 6;
	m_position.y += deltaTime * movementSpeed;
}



void Character::Update(float deltaTime, SDL_Event e)
{	
	attackCooldown--; //reduce player attack cooldownn

	//move the character
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	else if (m_moving_up)
	{
		MoveUp(deltaTime);
	}
	else if (m_moving_down)
	{
		MoveDown(deltaTime);
	}

	//player controls
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_w:
			m_moving_up = true;
			break;
		case SDLK_s:
			m_moving_down = true;
			break;
		case SDLK_r:
			changeWeapon(currentWeapon);
			break;
		default:;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			m_moving_right = false;
			break;
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_w:
			m_moving_up = false;
			break;
		case SDLK_s:
			m_moving_down = false;
			break;
		default:;
		}
		break;


	//Evacade controls for player
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 15:
			m_moving_right = true;
			break;
		case 14:
			m_moving_left = true;
			break;
		case 13:
			m_moving_up = true;
			break;
		case 16:
			m_moving_down = true;
			break;
		case 2:
			changeWeapon(currentWeapon);
			break;
		default:;
		}
		break;

	case SDL_JOYBUTTONUP:
		switch (e.jbutton.button)
		{
		case 15:
			m_moving_right = false;
			break;
		case 14:
			m_moving_left = false;
			break;
		case 13:
			m_moving_up = false;
			break;
		case 16:
			m_moving_down = false;
			break;
		default:;
		}
		break;
	default:;
	}
}

void Character::Damage(int damage)
{
	//play damaged animation
	if (damage > 0)
	{
		m_damaged = true;
	}

	health -= damage;

	//set a max health of 10
	if (health > 10)
	{
		health = 10;
	}

	//play daed aniamtion
	if (health <= 0)
	{
		m_dead = true;
	}
}

void Character::PickUpAmmo(int type, int amount)
{
	//add ammo to the player ammo count
	if (type == 1)
	{
		pistolAmmoCount += amount;
	}

	else if (type == 2)
	{
		scifiAmmoCount += amount;
	}
}

string Character::getAmmoCountPistolSTR(int pistolAmmo)
{
	return to_string(pistolAmmo);
}

string Character::getAmmoCountSciFiSTR(int scifiAmmo)
{
	return to_string(scifiAmmo);
}

void Character::PickUpPistol()
{
	//add pistol to the owned weapons
	unlockedWeapons[1] = "pistol";
	currentWeapon = weapons[1];
}

void Character::PickUpScifi()
{
	unlockedWeapons[2] = "scifi";
	currentWeapon = weapons[2];
}

void Character::changeWeapon(string currentweapon)
{
	//check to see of you own the pistol to swap to it
	if (currentweapon == weapons[0] && unlockedWeapons[1] != "nullptr")
	{
		currentWeapon = weapons[1];
	}
	//check to see if you own the sci-fi pistol to swap to that
	else if (currentweapon == weapons[1] && unlockedWeapons[2] != "nullptr")
	{
		currentWeapon = weapons[2];
	}
	//check to see if you have the sci-fi pistol out, or the pistol and the user doesn't own the sci-fi pistol
	else if (currentweapon == weapons[2] ||
		currentweapon == weapons[1] && unlockedWeapons[2] == "nullptr")
	{
		currentWeapon = weapons[0];
	}
}

Rect2D Character::GetCollionBox() 
{ 
	return Rect2D(m_position.x, m_position.y, this->m_texture->GetWidth() / 6 - 24, m_texture->GetHeight() / 4);
}