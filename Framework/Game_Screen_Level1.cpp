#include "Game_Screen_Level1.h"
#include <iostream>

//intialise camera and walls
Game_Object* m_camera = nullptr;
Game_Object* m_backcamera = nullptr;
Game_Object* m_backwall = nullptr;
Game_Object* m_endwall = nullptr;
Game_Object* m_topwall = nullptr;
Game_Object* m_bottomwall = nullptr;

//initialising UI
Texture2D* m_UIportrait = nullptr;
Texture2D* m_pistolBulletUI = nullptr;
Texture2D* m_scifiBulletUI = nullptr;
Texture2D* m_healthBarBackground = nullptr;
Texture2D* m_healthBar = nullptr;

//initialise boxes
Box* m_Box[NUMBOXES]; 
HealthPickUp* m_healthPickUp[NUMHEALTHPICKUPS];
BulletPickUp* m_bulletPickUp[NUMAMMOPICKUPS];
Game_Object* punchHitBoxes[NUMPUNCHHITBOXES];

Game_Object* pistolPickUp = nullptr;

//initilaise arms for player holding guns
Game_Object* pistolArmRight = nullptr; 
Game_Object* pistolArmLeft = nullptr; 
Game_Object* scifiArmRight = nullptr; 
Game_Object* scifiArmLeft = nullptr;

//make enemy arrays
Melee_Enemy* m_meleeEnemy[NUMMELEEENEMIES];
Ranged_Enemy* m_rangedEnemy[NUMRANGEDENEMIES];

//make projectile arrays
Bullet* projectiles[NUMPROJECTILES];
Bullet* enemyProjectiles[NUMPROJECTILES];

//make fight boxes
Game_Object* firstFightBox = nullptr;
Game_Object* secondFightBox = nullptr;
Game_Object* thirdFightBox = nullptr;

//counter for moving camera
int movingCounter = 0;

Game_Screen_Level1::Game_Screen_Level1(SDL_Renderer* renderer, GameSceneManager* sceneManager) : Game_Screen(renderer, sceneManager)
{
	m_renderer = renderer;
	game_scene_manager = sceneManager;
	SetUpLevel();
}

Game_Screen_Level1::~Game_Screen_Level1()
{
	//delete all things
	delete(m_background_texture);
	delete(m_UIportrait);
	delete(m_pistolBulletUI);
	delete(m_scifiBulletUI);
	delete(my_character);
	delete(pistolArmRight);
	delete(pistolArmLeft);
	delete(scifiArmLeft);
	delete(scifiArmRight);
	delete(m_camera);
	delete(m_backwall);
	delete(m_endwall);
	delete(m_backcamera);
	delete(m_topwall);
	delete(m_bottomwall);
	delete(m_healthBar);
	delete(m_healthBarBackground);
	delete(pistolPickUp);
	delete(firstFightBox);
	delete(secondFightBox);
	delete(thirdFightBox);

	for (int i = 0; i < NUMBOXES; i++)
	{
		delete(m_Box[i]);
		m_Box[i] = nullptr;
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp[i]);
		m_healthPickUp[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp[i]);
		m_bulletPickUp[i] = nullptr;
	}
	for (int i = 0 ; i < NUMPROJECTILES; i++) 
	{
		delete(projectiles[i]);
		projectiles[i] = nullptr;
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		delete(enemyProjectiles[i]);
		enemyProjectiles[i] = nullptr;
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		delete(punchHitBoxes[i]);
		punchHitBoxes[i] = nullptr;
	}
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		delete(m_meleeEnemy[i]);
		m_meleeEnemy[i] = nullptr;
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		delete(m_rangedEnemy[i]);
		m_rangedEnemy[i] = nullptr;
	}

	//set everything to nullptr
	m_background_texture = nullptr;
	m_UIportrait = nullptr;
	m_pistolBulletUI = nullptr;
	m_scifiBulletUI = nullptr;
	my_character = nullptr;
	pistolArmRight = nullptr;
	pistolArmLeft = nullptr;
	scifiArmLeft = nullptr;
	scifiArmRight = nullptr;
	m_camera = nullptr;
	m_backwall = nullptr;
	m_endwall = nullptr;
	m_backcamera = nullptr;
	m_topwall = nullptr;
	m_bottomwall = nullptr;
	m_healthBar = nullptr;
	m_healthBarBackground = nullptr;
	pistolPickUp = nullptr;
	firstFightBox = nullptr;
	secondFightBox = nullptr;
	thirdFightBox = nullptr;
}

void Game_Screen_Level1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(backgorundposition, 0.0), SDL_FLIP_NONE);

	//make UI
	m_UIportrait->Render(Vector2D(20, 20), SDL_FLIP_NONE);
	m_pistolBulletUI->Render(Vector2D(22, 108), SDL_FLIP_NONE);
	m_scifiBulletUI->Render(Vector2D(20, 139), SDL_FLIP_NONE);
	m_pistolAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_pistolAmmoText->RenderAt(my_character->getAmmoCountPistolSTR(my_character->pistolAmmoCount), 50, 100);
	m_scifiAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_scifiAmmoText->RenderAt(my_character->getAmmoCountSciFiSTR(my_character->scifiAmmoCount), 50, 130);
	m_healthBarBackground->Render(Vector2D(85, 30), SDL_FLIP_NONE);

	//draw the health bar to have the amount of health
	switch (my_character->GetHealth())
	{
	case 10:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth(), m_healthBar->GetHeight());
		break;
	case 9:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.9, m_healthBar->GetHeight());
		break;
	case 8:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.8, m_healthBar->GetHeight());
		break;
	case 7:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.7, m_healthBar->GetHeight());
		break;
	case 6:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.6, m_healthBar->GetHeight());
		break;
	case 5:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.5, m_healthBar->GetHeight());
		break;
	case 4:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.4, m_healthBar->GetHeight());
		break;
	case 3:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.3, m_healthBar->GetHeight());
		break;
	case 2:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.2, m_healthBar->GetHeight());
		break;
	case 1:
		m_healthBar->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar->GetWidth() * 0.1, m_healthBar->GetHeight());
		break;
	default:;
	}

	//draw arm attached to player
	if (my_character->m_damaged != true && my_character->GetHealth() >= 0)
	{
		if (my_character->getDirection() == FACING_RIGHT)
		{
			if (my_character->currentWeapon == my_character->weapons[1])
			{
				pistolArmRight->SetPosition(Vector2D(my_character->GetPosition().x + 25, my_character->GetPosition().y + 34));
				pistolArmRight->Render();
			}
			else if (my_character->currentWeapon == my_character->weapons[2])
			{
				scifiArmRight->SetPosition(Vector2D(my_character->GetPosition().x + 25, my_character->GetPosition().y + 34));
				scifiArmRight->Render();
			}
		}
		else if (my_character->getDirection() == FACING_LEFT)
		{
			if (my_character->currentWeapon == my_character->weapons[1])
			{
				pistolArmLeft->SetPosition(Vector2D(my_character->GetPosition().x - 5, my_character->GetPosition().y + 34));
				pistolArmLeft->Render();
			}
			else if (my_character->currentWeapon == my_character->weapons[2])
			{
				scifiArmLeft->SetPosition(Vector2D(my_character->GetPosition().x - 5, my_character->GetPosition().y + 34));
				scifiArmLeft->Render();
			}
		}
	}

	my_character->Render();

	if (pistolPickUp != nullptr)
	{
		pistolPickUp->Render();
	}

	//render the four walls
	m_bottomwall->Render();
	m_topwall->Render();
	m_backwall->Render(); 
	m_endwall->Render();

	//render the cameras
	if (m_camera != nullptr)
	{
		m_camera->Render();
	}
	if (m_backcamera != nullptr)
	{
		m_backcamera->Render();
	}

	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box[i] != nullptr)
		{
			m_Box[i]->Render();
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp[i] != nullptr)
		{
			m_bulletPickUp[i]->Render();
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp[i] != nullptr)
		{
			m_healthPickUp[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles[i] != nullptr)
		{
			projectiles[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles[i] != nullptr)
		{
			enemyProjectiles[i]->Render();
		}
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		if (punchHitBoxes[i] != nullptr)
		{
			punchHitBoxes[i]->Render();
		}
	}
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		if (m_meleeEnemy[i] != nullptr)
		{
			m_meleeEnemy[i]->Render();
		}
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		if (m_rangedEnemy[i] != nullptr)
		{
			m_rangedEnemy[i]->Render();
		}
	}

	if (firstFightBox != nullptr)
	{
		firstFightBox->Render();
	}
	if (secondFightBox != nullptr)
	{
		secondFightBox->Render();
	}
	if (thirdFightBox != nullptr)
	{
		thirdFightBox->Render();
	}

}

void Game_Screen_Level1::Update(float deltaTime, SDL_Event e)
{
	//update the character
	my_character->Update(deltaTime, e);
	int playerHealth = my_character->GetHealth();

	//update melee enemies
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		//only update the ones that exist
		if (m_meleeEnemy[i] != nullptr)
		{
			m_meleeEnemy[i]->Update(deltaTime, e);

			//check collision with player and enemy to attack
			if (Collision::Instance()->Box(m_meleeEnemy[i]->GetCollionBox(), my_character->GetCollionBox()) && m_meleeEnemy[i]->MeleeAttackCooldown <= 0)
			{
				m_meleeEnemy[i]->m_speed = 0;
				m_meleeEnemy[i]->m_attacking = true;

				//spawn a hitbox depending on direction
				if (m_meleeEnemy[i]->GetDirection() == FACING_LEFT)
				{
					punchHitBoxes[1] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(m_meleeEnemy[i]->GetPosition().x - 5, m_meleeEnemy[i]->GetPosition().y + 35));
					m_meleeEnemy[i]->MeleeAttackCooldown = 2000;
				}
				else if (m_meleeEnemy[i]->GetDirection() == FACING_RIGHT)
				{
					punchHitBoxes[1] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(m_meleeEnemy[i]->GetPosition().x + 42, m_meleeEnemy[i]->GetPosition().y + 35));
					m_meleeEnemy[i]->MeleeAttackCooldown = 2000;
				}

				//check collision of enemy hitbox with player to do damage and delete afterwards
				if (Collision::Instance()->Box(punchHitBoxes[1]->GetCollionBox(), my_character->GetCollionBox()))
				{
					my_character->Damage(1);
					delete(punchHitBoxes[1]);
					punchHitBoxes[1] = nullptr;
				}
				else
				{
					delete(punchHitBoxes[1]);
					punchHitBoxes[1] = nullptr;
				}
			}
		}
	}
	
	//update the ranged enemeies
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		//check to see if the enemy exists
		if (m_rangedEnemy[i] != nullptr)
		{
			m_rangedEnemy[i]->Update(deltaTime, e);

			//chekc to see if player is within a range of the enemies y position co-ordinate
			if (m_rangedEnemy[i]->GetPosition().y < my_character->GetPosition().y + 30 && 
				m_rangedEnemy[i]->GetPosition().y > my_character->GetPosition().y - 30 &&
				m_rangedEnemy[i]->RangedAttackCooldown <= 0)
			{
				//shoot a projectile
				m_rangedEnemy[i]->m_attacking = true;
				m_rangedEnemy[i]->m_speed = 0;

				//spawn a bullet based on player direction to move in that direction
				if (m_rangedEnemy[i]->GetDirection() == FACING_LEFT)
				{
					for (int j = 0; j < NUMPROJECTILES; j++)
					{
						if (enemyProjectiles[j] == nullptr)
						{
							enemyProjectiles[j] = new Bullet(m_renderer, "Images/pistol bullet.png",
								Vector2D(m_rangedEnemy[i]->GetPosition().x - 15, m_rangedEnemy[i]->GetPosition().y + 35), 1, 1000, FACING_LEFT);
							m_rangedEnemy[i]->RangedAttackCooldown = 1500;
							enemyProjectiles[j]->alive = true;
							break;
						}
					}
				}
				else if (m_rangedEnemy[i]->GetDirection() == FACING_RIGHT)
				{
					for (int j = 0; j < NUMPROJECTILES; j++)
					{
						if (enemyProjectiles[j] == nullptr)
						{
							enemyProjectiles[j] = new Bullet(m_renderer, "Images/pistol bullet.png",
								Vector2D(m_rangedEnemy[i]->GetPosition().x + 35, m_rangedEnemy[i]->GetPosition().y + 35), 1, 1000, FACING_RIGHT);
							m_rangedEnemy[i]->RangedAttackCooldown = 1500;
							enemyProjectiles[j]->alive = true;
							break;
						}
					}
				}
			}
		}
	}

	//player attacks
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//punch 
		if (my_character->currentWeapon == my_character->weapons[0] && my_character->attackCooldown <= 0)
		{
			my_character->attackCooldown = 750;
			my_character->m_attacking = true;
			//spawn a hitbox at punch location based on direction
				if (punchHitBoxes[0] == nullptr)
				{
					if (my_character->getDirection() == FACING_RIGHT)
					{
						punchHitBoxes[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character->GetPosition().x + 42, my_character->GetPosition().y + 37));
					}
					else if (my_character->getDirection() == FACING_LEFT)
					{
						punchHitBoxes[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character->GetPosition().x - 5, my_character->GetPosition().y + 37));
					}
					//check collision of hitbox on all the boxes
					for (int j = 0; j < NUMBOXES; j++)
					{
						if (m_Box[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_Box[j]->GetCollionBox()))
							{
								int tempBoxInt = 0;
								tempBoxInt = m_Box[j]->Death(); //rand number for pick up
								switch (tempBoxInt)
								{
								case(1):
									//make a health pick up
									for (int k = 0; k < NUMHEALTHPICKUPS; k++)
									{
										if (m_healthPickUp[k] != nullptr)
										{
											continue;
										}
										m_healthPickUp[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png", 
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15));
										break;
									}
									break;
								case(2):
									//make an ammo pick up for pistols
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15), 1);
										break;
									}
									break;
								case(3):
									//make an ammo pick up for sci-fi pistol
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15), 2);
										break;
									}
									break;
								default:
									break;
								}
								tempBoxInt = 0;

								//destroy box
								delete(m_Box[j]);
								m_Box[j] = nullptr;
							}
						}
					}
					//check hitbox with melee enemies
					for (int j = 0; j < NUMMELEEENEMIES; j++)
					{
						if (m_meleeEnemy[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_meleeEnemy[j]->GetCollionBox()))
							{
								//do damage on collision
								m_meleeEnemy[j]->Damage(2);
							}
						}
					}
					//check hitbox on ranged enemies
					for (int j = 0; j < NUMRANGEDENEMIES; j++)
					{
						if (m_rangedEnemy[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_rangedEnemy[j]->GetCollionBox()))
							{
								//do damge on collision
								m_rangedEnemy[j]->Damage(2);
							}
						}
					}
					//delete the punch hitbox
					delete(punchHitBoxes[0]);
					punchHitBoxes[0] = nullptr;
			}
		}
		//make a bullet spawn
		for (int i = 0; i < NUMPROJECTILES; i++)
		{

			if (projectiles[i] == nullptr && my_character->attackCooldown <= 0)
			{
				my_character->attackCooldown = 750;
				//make bullet a pistol bullet if current weapon is a pistol and have ammo for it
				if (my_character->currentWeapon == my_character->weapons[1] && my_character->pistolAmmoCount > 0)
				{
					//move left projectile
					if (my_character->getDirection() == FACING_LEFT)
					{
						projectiles[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character->GetPosition().x - 15,
							my_character->GetPosition().y + 30), 1, 1000, my_character->getDirection());
						my_character->pistolAmmoCount--; //reduce ammo count
					}
					//move right projectile
					if (my_character->getDirection() == FACING_RIGHT)
					{
						projectiles[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character->GetPosition().x + 50,
							my_character->GetPosition().y + 30), 1, 1000, my_character->getDirection());
						my_character->pistolAmmoCount--; //reduce ammo count
					}
					projectiles[i]->alive = true;
					break;
				}
				//shoot a sci-fi bullet if have ammo and current weapon is sci-fi pistol
				else if (my_character->currentWeapon == my_character->weapons[2] && my_character->scifiAmmoCount > 0)
				{
					if (my_character->getDirection() == FACING_LEFT)
					{
						projectiles[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character->GetPosition().x - 15,
							my_character->GetPosition().y + 30), 2, 1000, my_character->getDirection());
						my_character->scifiAmmoCount--; //reduce ammo
					}
					if (my_character->getDirection() == FACING_RIGHT)
					{
						projectiles[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character->GetPosition().x + 50,
							my_character->GetPosition().y + 30), 2, 1000, my_character->getDirection());
						my_character->scifiAmmoCount--; //reduce amo
					}
					projectiles[i]->alive = true;
					break; 
				}
			}
		}
	}
	//same attacks but for the evacade
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		if (e.jbutton.button = 1 && my_character->attackCooldown <= 0)
		{
			my_character->attackCooldown = 750;
			if (my_character->currentWeapon == my_character->weapons[0]) //punch
			{
				//hitbox spawn on punch
				my_character->m_attacking = true;
				if (punchHitBoxes[0] == nullptr)
				{
					if (my_character->getDirection() == FACING_RIGHT)
					{
						punchHitBoxes[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character->GetPosition().x + 42, my_character->GetPosition().y + 37));
					}
					else if (my_character->getDirection() == FACING_LEFT)
					{
						punchHitBoxes[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character->GetPosition().x - 5, my_character->GetPosition().y + 37));
					}
					//check hitbox collison on punch
					for (int j = 0; j < NUMBOXES; j++)
					{
						if (m_Box[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_Box[j]->GetCollionBox()))
							{
								int tempBoxInt = 0;
								tempBoxInt = m_Box[j]->Death(); //rand number for pick up
								switch (tempBoxInt)
								{
								case(1):
									for (int k = 0; k < NUMHEALTHPICKUPS; k++)
									{
										if (m_healthPickUp[k] != nullptr)
										{
											continue;
										}
										m_healthPickUp[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15));
										break;
									}
									break;
								case(2):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png", 
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15), 1);
										break;
									}
									break;
								case(3):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png", 
											Vector2D(m_Box[j]->GetPosition().x + 10, m_Box[j]->GetPosition().y + 15), 2);
										break;
									}
									break;
								default:
									break;
								}
								tempBoxInt = 0;

								delete(m_Box[j]);
								m_Box[j] = nullptr;
							}
						}
					}
					//check hitbox colide with melee enemy
					for (int j = 0; j < NUMMELEEENEMIES; j++)
					{
						if (m_meleeEnemy[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_meleeEnemy[j]->GetCollionBox()))
							{
								m_meleeEnemy[j]->Damage(2);
							}
						}
					}
					//check hitbox collide with ranged enmey
					for (int j = 0; j < NUMRANGEDENEMIES; j++)
					{
						if (m_rangedEnemy[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes[0]->GetCollionBox(), m_rangedEnemy[j]->GetCollionBox()))
							{
								m_rangedEnemy[j]->Damage(2);
							}
						}
					}
					delete(punchHitBoxes[0]);
					punchHitBoxes[0] = nullptr;
				}
			}
			else
			{
				for (int i = 0; i < NUMPROJECTILES; i++)
				{
					if (projectiles[i] == nullptr && my_character->attackCooldown <= 0)
					{
						my_character->attackCooldown = 750; 
						//spanw pistol bullet if weapon is pistol and have ammo
						if (my_character->currentWeapon == my_character->weapons[1] && my_character->pistolAmmoCount > 0)
						{
							if (my_character->getDirection() == FACING_LEFT)
							{
								projectiles[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character->GetPosition().x - 15,
									my_character->GetPosition().y + 25), 1, 1000, my_character->getDirection());
								my_character->pistolAmmoCount--;
							}
							if (my_character->getDirection() == FACING_RIGHT)
							{
								projectiles[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character->GetPosition().x + 45,
									my_character->GetPosition().y + 25), 1, 1000, my_character->getDirection());
								my_character->pistolAmmoCount--;
							}
							projectiles[i]->alive = true;
							break;
						}
						//spawn the sci-fi bullet if weapon is same and have ammo
						else if (my_character->currentWeapon == my_character->weapons[2] && my_character->scifiAmmoCount > 0)
						{
							if (my_character->getDirection() == FACING_LEFT)
							{
								projectiles[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character->GetPosition().x - 15,
									my_character->GetPosition().y + 25), 2, 1000, my_character->getDirection());
								my_character->scifiAmmoCount--;
							}
							if (my_character->getDirection() == FACING_RIGHT)
							{
								projectiles[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character->GetPosition().x + 45,
									my_character->GetPosition().y + 25), 2, 1000, my_character->getDirection());
								my_character->scifiAmmoCount--;
							}
							projectiles[i]->alive = true;
							break;
						}
					}
				}
			}
		}
	}

	//check if bulelt lifetime is over and destroy if is
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles[i] == nullptr)
		{
			continue;
		}
		else if (projectiles[i]->alive == false)
		{
			delete projectiles[i];
			projectiles[i] = nullptr;
			continue;
		}
		//update bullet, location and timer
		projectiles[i]->Update(my_character->getDirection());
	}

	//update the enemy projectiles and destroy if lifespan is over
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles[i] == nullptr)
		{
			continue;
		}
		else if (enemyProjectiles[i]->alive == false)
		{
			delete enemyProjectiles[i];
			enemyProjectiles[i] = nullptr;
			continue;
		}
		enemyProjectiles[i]->Update(my_character->getDirection());
	}

	//check collision with projectiles
	for (int k = 0; k < NUMPROJECTILES; k++) 
	{
		for (int i = 0; i < NUMBOXES; i++)
		{
			//check collision with box
			if (m_Box[i] != nullptr)
			{
				if (projectiles[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles[k]->GetCollionBox(), m_Box[i]->GetCollionBox()))
					{							int tempBoxInt = 0;
						tempBoxInt = m_Box[i]->Death(); //rand number for pick up
						switch (tempBoxInt)
						{
						case(1):
							for (int j = 0; j < NUMHEALTHPICKUPS; j++)								{
								if (m_healthPickUp[j] != nullptr)
								{
									continue;
								}
								m_healthPickUp[j] = new HealthPickUp(m_renderer, "Images/Health Pickup.png", 
									Vector2D(m_Box[i]->GetPosition().x + 10, m_Box[i]->GetPosition().y + 15));
								break;
							}
							break;
						case(2):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp[j] = new BulletPickUp(m_renderer, "Images/pistol bullet.png", 
									Vector2D(m_Box[i]->GetPosition().x + 10, m_Box[i]->GetPosition().y + 15), 1);
								break;
							}
							break;
						case(3):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp[j] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
									Vector2D(m_Box[i]->GetPosition().x + 10, m_Box[i]->GetPosition().y + 15), 2);
								break;
							}
							break;
						default:
							break;
						}
						tempBoxInt = 0;

						delete(m_Box[i]);
						m_Box[i] = nullptr;
						delete(projectiles[k]);
						projectiles[k] = nullptr;
					}
				}
			}
		}

		//check collison with melee enemies
		for (int i = 0; i < NUMMELEEENEMIES; i++)
		{
			if (m_meleeEnemy[i] != nullptr)
			{
				//check if killed enemy
				if (m_meleeEnemy[i]->m_dead)
				{
					delete(m_meleeEnemy[i]);
					m_meleeEnemy[i] = nullptr;
				}
				if (projectiles[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles[k]->GetCollionBox(), m_meleeEnemy[i]->GetCollionBox()))
					{
						if (projectiles[k]->m_type == 1)
						{
							m_meleeEnemy[i]->Damage(2); //do 2 damage if pistol
						}
						else if (projectiles[k]->m_type == 2)
						{
							m_meleeEnemy[i]->Damage(4); //do 4 damage if sci-fi
						}
						delete(projectiles[k]);
						projectiles[k] = nullptr;
					}
				}
			}
		}
		//check collision with ranegd enemies
		for (int i = 0; i < NUMRANGEDENEMIES; i++)
		{
			if (m_rangedEnemy[i] != nullptr)
			{
				//check if killed enemy
				if (m_rangedEnemy[i]->m_dead)
				{
					delete(m_rangedEnemy[i]);
					m_rangedEnemy[i] = nullptr;
				}
				if (projectiles[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles[k]->GetCollionBox(), m_rangedEnemy[i]->GetCollionBox()))
					{
						if (projectiles[k]->m_type == 1)
						{
							m_rangedEnemy[i]->Damage(2);
						}
						else if (projectiles[k]->m_type == 2)
						{
							m_rangedEnemy[i]->Damage(4);
						}
						delete(projectiles[k]);
						projectiles[k] = nullptr;
					}
				}
			}
		}
		//check enmye projectile hit player
		if (enemyProjectiles[k] != nullptr)
		{
			if (Collision::Instance()->Box(enemyProjectiles[k]->GetCollionBox(), my_character->GetCollionBox()))
			{
				if (enemyProjectiles[k]->m_type == 1)
				{
					my_character->Damage(2);
				}
				else if (enemyProjectiles[k]->m_type == 2)
				{
					my_character->Damage(4);
				}
				//delete projectile on hitting target
				delete(enemyProjectiles[k]);
				enemyProjectiles[k] = nullptr;
			}
		}
	}

	//check collsion with the health pick up
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character->GetCollionBox(), m_healthPickUp[i]->GetCollionBox()))
			{
				m_healthPickUp[i]->Collision(my_character);
				delete(m_healthPickUp[i]);
				m_healthPickUp[i] = nullptr;
			}
		}
	}

	//check collision ith the ammo pick up
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character->GetCollionBox(), m_bulletPickUp[i]->GetCollionBox()))
			{
				m_bulletPickUp[i]->Collision(my_character, m_bulletPickUp[i]->m_type);
				delete(m_bulletPickUp[i]);
				m_bulletPickUp[i] = nullptr;
			}
		}
	}

	//check collsion with psitol weapon pick up
	if (pistolPickUp != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), pistolPickUp->GetCollionBox()))
		{
			my_character->PickUpPistol();
			delete(pistolPickUp);
			pistolPickUp = nullptr;
		}
	}

	//check collision for first fight initiater
	if (firstFightBox != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), firstFightBox->GetCollionBox()))
		{
			//move the scene left
			MoveLeft(m_renderer, 0.4);

			movingCounter++; 
			if (movingCounter == 400) //stop after 400 iterations of moving
			{
				//spawn enemies for fight
				m_meleeEnemy[0] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(700, 250), my_character);
				m_meleeEnemy[1] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(700, 400), my_character);
				my_character->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(firstFightBox);
				firstFightBox = nullptr;
				movingCounter = 0;
			}
		}
	}

	//check collsion fo rsecond fight
	if (secondFightBox != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), secondFightBox->GetCollionBox()))
 		{
			MoveLeft(m_renderer, 0.4);

			movingCounter++;
			if (movingCounter == 800) //movement counter limit of 800
			{
				//spawn enemies
				m_meleeEnemy[0] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(700, 250), my_character);
				m_rangedEnemy[0] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 400), my_character);
				my_character->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(secondFightBox);
				secondFightBox = nullptr;
				movingCounter = 0;
			}
		}
	}

	//check collision for third fight
	if (thirdFightBox != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), thirdFightBox->GetCollionBox()))
		{
			MoveLeft(m_renderer, 0.4);

			movingCounter++;
			if (movingCounter == 700)
			{
				//spawn enemies
				m_meleeEnemy[0] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(700, 250), my_character);
				m_meleeEnemy[1] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(100, 350), my_character);
				m_rangedEnemy[0] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 400), my_character);
				my_character->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(thirdFightBox);
				thirdFightBox = nullptr;
				movingCounter = 0; 
			}
		}
	}
	//check collision with camera movement
	if (m_camera != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), m_camera->GetCollionBox()))
		{
			if (my_character->m_moving_right == true)
			{
				my_character->movementSpeed = 0;

				if (CheckFightActive() == false)
				{
					//move scene left but not the character 
					MoveLeft(m_renderer, 0.15);
					my_character->SetPosition(Vector2D(my_character->GetPosition().x + 0.15, my_character->GetPosition().y));
				}
			}
			else
			{
				my_character->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}

	if (m_backcamera != nullptr)
	{
		if (Collision::Instance()->Box(my_character->GetCollionBox(), m_backcamera->GetCollionBox()))
		{
			if (my_character->m_moving_left == true)
			{
				my_character->movementSpeed = 0;

				if (CheckFightActive() == false)
				{
					//move scene left but not the character 
					MoveRight(m_renderer, 0.15);
					my_character->SetPosition(Vector2D(my_character->GetPosition().x + 0.15, my_character->GetPosition().y));
				}
			}
			else
			{
				my_character->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}


	if (Collision::Instance()->Box(my_character->GetCollionBox(), m_backwall->GetCollionBox()))
	{
		if (my_character->m_moving_left == true)
		{
			my_character->movementSpeed = 0;
		}
		else
		{
			my_character->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	//check collision on end wall to change scene to next level 
	else if (Collision::Instance()->Box(my_character->GetCollionBox(), m_endwall->GetCollionBox()))
	{
		if (game_scene_manager->GetCurrentScreen() == SCREEN_LEVEL1)
		{
			game_scene_manager->ChangeScreen(SCREEN_LEVEL2);
		}
	}
	//dont allow moving up on collision
	else if (Collision::Instance()->Box(my_character->GetCollionBox(), m_topwall->GetCollionBox())) 
	{
		if (my_character->m_moving_up == true)
		{
			my_character->movementSpeed = 0;
		}
		else
		{
			my_character->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	//dont allow movement down on collision
	else if (Collision::Instance()->Box(my_character->GetCollionBox(), m_bottomwall->GetCollionBox()))
	{
		if (my_character->m_moving_down == true)
		{
			my_character->movementSpeed = 0;
		}
		else
		{
			my_character->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
}

bool Game_Screen_Level1::SetUpLevel()
{
	//reset from a previous play through
	float backwallposition = 10.0f;
	float backgorundposition = 0.0f;
	float endwallposition = 2052.0f;

	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		delete(m_meleeEnemy[i]);
		m_meleeEnemy[i] = nullptr;
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		delete(m_rangedEnemy[i]);
		m_rangedEnemy[i] = nullptr;
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp[i]);
		m_healthPickUp[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp[i]);
		m_bulletPickUp[i] = nullptr;
	}

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level 1.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_UIportrait = new Texture2D(m_renderer);
	if (!m_UIportrait->LoadFromFile("Images/UI portrait.png"))
	{
		std::cout << "Failed to load UI portrait texture!" << std::endl;
		return false;
	}

	m_pistolBulletUI = new Texture2D(m_renderer);
	if (!m_pistolBulletUI->LoadFromFile("Images/pistol bullet.png"))
	{
		std::cout << "Failed to load UI pistol bullet texture!" << std::endl;
		return false;
	}

	m_scifiBulletUI = new Texture2D(m_renderer);
	if (!m_scifiBulletUI->LoadFromFile("Images/sci-fi bullet.png"))
	{
		std::cout << "Failed to load UI sci-fi bullet texture!" << std::endl;
		return false;
	}

	m_healthBarBackground = new Texture2D(m_renderer);
	if (!m_healthBarBackground->LoadFromFile("Images/Health Bar Background.png"))
	{
		std::cout << "failed to load health bar background texture!" << std::endl;
		return false;
	}

	m_healthBar = new Texture2D(m_renderer);
	if (!m_healthBar->LoadFromFile("Images/Health Bar.png"))
	{
		std::cout << "failed to load health bar texture!" << std::endl;
		return false;
	}

	//make collision boxes to keep player in bounds of screen
	m_backwall = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(backwallposition, 0));
	m_endwall = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(endwallposition, 0));
	m_topwall = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 205));
	m_bottomwall = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 415));

	// make charachter model
	my_character = new Character(m_renderer, "Images/Character.png", Vector2D(120, 300), game_scene_manager);

	pistolPickUp = new Game_Object(m_renderer, "Images/pistol Pickup.png", Vector2D(1400, 350));

	pistolArmRight = new Game_Object(m_renderer, "Images/Pistol Arm Right.png", Vector2D(my_character->GetPosition().x, my_character->GetPosition().y));
	pistolArmLeft = new Game_Object(m_renderer, "Images/Pistol Arm Left.png", Vector2D(my_character->GetPosition().x, my_character->GetPosition().y));
	scifiArmLeft = new Game_Object(m_renderer, "Images/Sci-fi Arm Left.png", Vector2D(my_character->GetPosition().x, my_character->GetPosition().y));
	scifiArmRight = new Game_Object(m_renderer, "Images/Sci-fi Arm Right.png", Vector2D(my_character->GetPosition().x, my_character->GetPosition().y));

	m_camera = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(800-48, 0));
	m_backcamera = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(0, 0));

	//make boxes in level locations
	m_Box[0] = new Box(m_renderer, "Images/Box.png", Vector2D(105, 250));
	m_Box[1] = new Box(m_renderer, "Images/Box.png", Vector2D(200, 250));
	m_Box[2] = new Box(m_renderer, "Images/Box.png", Vector2D(100, 400));
	m_Box[3] = new Box(m_renderer, "Images/Box.png", Vector2D(150, 400));
	m_Box[4] = new Box(m_renderer, "Images/Box.png", Vector2D(300, 400));
	m_Box[5] = new Box(m_renderer, "Images/Box.png", Vector2D(450, 250));
	m_Box[6] = new Box(m_renderer, "Images/Box.png", Vector2D(600, 400));
	m_Box[7] = new Box(m_renderer, "Images/Box.png", Vector2D(900, 400));
	m_Box[8] = new Box(m_renderer, "Images/Box.png", Vector2D(1000, 400));
	m_Box[9] = new Box(m_renderer, "Images/Box.png", Vector2D(1200, 400));
	m_Box[10] = new Box(m_renderer, "Images/Box.png", Vector2D(1500, 400));
	m_Box[11] = new Box(m_renderer, "Images/Box.png", Vector2D(950, 250));
	m_Box[12] = new Box(m_renderer, "Images/Box.png", Vector2D(1250, 250));
	m_Box[13] = new Box(m_renderer, "Images/Box.png", Vector2D(1500, 250));

	m_pistolAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);
	m_scifiAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);

	firstFightBox = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(250, 0));
	secondFightBox = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(1100, 0));
	thirdFightBox = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(1700, 0));

	return true;
}

//check if any enemy is not nullptr
bool Game_Screen_Level1::CheckFightActive()
{
for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		if (m_meleeEnemy[i] != nullptr)
		{
			return true;
		}
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		if (m_rangedEnemy[i] != nullptr)
		{
			return true;
		}
	}
	return false;
}

//move the scnee left by an amount
void Game_Screen_Level1::MoveLeft(SDL_Renderer* renderer, float amount)
{
	m_background_texture->Render(Vector2D(backgorundposition -= amount, 0), SDL_FLIP_NONE);
	m_backwall->SetPosition(Vector2D(backwallposition -= amount, 0));
	m_endwall->SetPosition(Vector2D(endwallposition -= amount, 0));
	my_character->SetPosition(Vector2D(my_character->GetPosition().x - amount, my_character->GetPosition().y));
	my_character->movementSpeed = 0;
	if (firstFightBox != nullptr)
	{
		firstFightBox->SetPosition(Vector2D(firstFightBox->GetPosition().x - amount, firstFightBox->GetPosition().y));
	}
	if (secondFightBox != nullptr)
	{
		secondFightBox->SetPosition(Vector2D(secondFightBox->GetPosition().x - amount, secondFightBox->GetPosition().y));
	}
	if (thirdFightBox != nullptr)
	{
		thirdFightBox->SetPosition(Vector2D(thirdFightBox->GetPosition().x - amount, thirdFightBox->GetPosition().y));
	}
	if (pistolPickUp != nullptr)
	{
		pistolPickUp->SetPosition(Vector2D(pistolPickUp->GetPosition().x - amount, pistolPickUp->GetPosition().y));
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box[i] != nullptr)
		{
			m_Box[i]->SetPosition((Vector2D(m_Box[i]->GetPosition().x - amount, m_Box[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp[i] != nullptr)
		{
			m_healthPickUp[i]->SetPosition((Vector2D(m_healthPickUp[i]->GetPosition().x - amount, m_healthPickUp[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp[i] != nullptr)
		{
			m_bulletPickUp[i]->SetPosition((Vector2D(m_bulletPickUp[i]->GetPosition().x - amount, m_bulletPickUp[i]->GetPosition().y)));
		}
	}
}

//move the scene right by an amount
void Game_Screen_Level1::MoveRight(SDL_Renderer* renderer, float amount)
{
	m_background_texture->Render(Vector2D(backgorundposition += amount, 0), SDL_FLIP_NONE);
	m_backwall->SetPosition(Vector2D(backwallposition += amount, 0));
	m_endwall->SetPosition(Vector2D(endwallposition += amount, 0));
	my_character->SetPosition(Vector2D(my_character->GetPosition().x - amount, my_character->GetPosition().y));
	my_character->movementSpeed = 0;
	if (pistolPickUp != nullptr)
	{
		pistolPickUp->SetPosition(Vector2D(pistolPickUp->GetPosition().x + amount, pistolPickUp->GetPosition().y));
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box[i] != nullptr)
		{
			m_Box[i]->SetPosition((Vector2D(m_Box[i]->GetPosition().x + amount, m_Box[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp[i] != nullptr)
		{
			m_healthPickUp[i]->SetPosition((Vector2D(m_healthPickUp[i]->GetPosition().x + amount, m_healthPickUp[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp[i] != nullptr)
		{
			m_bulletPickUp[i]->SetPosition((Vector2D(m_bulletPickUp[i]->GetPosition().x + amount, m_bulletPickUp[i]->GetPosition().y)));
		}
	}
	if (secondFightBox != nullptr)
	{
		secondFightBox->SetPosition(Vector2D(secondFightBox->GetPosition().x + amount, secondFightBox->GetPosition().y));
	}
	if (thirdFightBox != nullptr)
	{
		thirdFightBox->SetPosition(Vector2D(thirdFightBox->GetPosition().x + amount, thirdFightBox->GetPosition().y));
	}
}