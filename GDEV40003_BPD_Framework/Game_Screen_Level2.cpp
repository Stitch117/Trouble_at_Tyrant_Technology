#include "Game_Screen_Level2.h"
#include "Game_Screen_Level1.h"
#include "GameSceneManager.h"
#include "Texture2D.h"
#include "Collision.h"
#include <iostream>

//Initialise and walls
Game_Object* m_camera2 = nullptr;
Game_Object* m_backcamera2 = nullptr;
Game_Object* m_backwall2 = nullptr;
Game_Object* m_endwall2 = nullptr;
Game_Object* m_topwall2 = nullptr;
Game_Object* m_bottomwall2 = nullptr;

//Initialise UI
Texture2D* m_UIportrait2 = nullptr;
Texture2D* m_pistolBulletUI2 = nullptr;
Texture2D* m_scifiBulletUI2 = nullptr;
Texture2D* m_healthBarBackground2 = nullptr;
Texture2D* m_healthBar2 = nullptr;

//initialise boxes
Box* m_Box2[NUMBOXES];
HealthPickUp* m_healthPickUp2[NUMHEALTHPICKUPS];
BulletPickUp* m_bulletPickUp2[NUMAMMOPICKUPS];
Game_Object* punchHitBoxes2[NUMPUNCHHITBOXES];

Game_Object* scifiPickUp2 = nullptr;

//initialise the player arms 
Game_Object* pistolArmRight2 = nullptr;
Game_Object* pistolArmLeft2 = nullptr;
Game_Object* scifiArmRight2 = nullptr;
Game_Object* scifiArmLeft2 = nullptr;

//initialise the enemies 
Melee_Enemy* m_meleeEnemy2[NUMMELEEENEMIES];
Ranged_Enemy* m_rangedEnemy2[NUMRANGEDENEMIES];
robotGuard* guardEnemy = nullptr;

Bullet* projectiles2[NUMPROJECTILES];
Bullet* enemyProjectiles2[NUMPROJECTILES];

Game_Object* firstFightBox2 = nullptr;
Game_Object* secondFightBox2 = nullptr;
Game_Object* thirdFightBox2 = nullptr;

bool CheckFightActive2();

int movingCounter2 = 0;

Game_Screen_Level2::Game_Screen_Level2(SDL_Renderer* renderer, GameSceneManager* sceneManager) : Game_Screen(renderer, sceneManager)
{
	m_renderer = renderer;
	game_scene_manager = sceneManager;
	SetUpLevel();
}

Game_Screen_Level2::~Game_Screen_Level2()
{
	delete(m_background_texture2);
	delete(m_UIportrait2);
	delete(m_pistolBulletUI2);
	delete(m_scifiBulletUI2);
	delete(my_character2);
	delete(pistolArmRight2);
	delete(pistolArmLeft2);
	delete(scifiArmLeft2);
	delete(scifiArmRight2);
	delete(m_camera2);
	delete(m_backwall2);
	delete(m_endwall2);
	delete(m_backcamera2);
	delete(m_topwall2);
	delete(m_bottomwall2);
	delete(m_healthBar2);
	delete(m_healthBarBackground2);
	delete(firstFightBox2);
	delete(secondFightBox2);
	delete(thirdFightBox2);

	for (int i = 0; i < NUMBOXES; i++)
	{
		delete(m_Box2[i]);
		m_Box2[i] = nullptr;
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp2[i]);
		m_healthPickUp2[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp2[i]);
		m_bulletPickUp2[i] = nullptr;
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		delete(projectiles2[i]);
		projectiles2[i] = nullptr;
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		delete(enemyProjectiles2[i]);
		enemyProjectiles2[i] = nullptr;
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		delete(punchHitBoxes2[i]);
		punchHitBoxes2[i] = nullptr;
	}
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		delete(m_meleeEnemy2[i]);
		m_meleeEnemy2[i] = nullptr;
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		delete(m_rangedEnemy2[i]);
		m_rangedEnemy2[i] = nullptr;
	}

	if (guardEnemy != nullptr)
	{
		delete(guardEnemy);
		guardEnemy = nullptr;
	}

	m_background_texture2 = nullptr;
	m_UIportrait2 = nullptr;
	m_pistolBulletUI2 = nullptr;
	m_scifiBulletUI2 = nullptr;
	my_character2 = nullptr;
	pistolArmRight2 = nullptr;
	pistolArmLeft2 = nullptr;
	scifiArmLeft2 = nullptr;
	scifiArmRight2 = nullptr;
	m_camera2 = nullptr;
	m_backwall2 = nullptr;
	m_endwall2 = nullptr;
	m_backcamera2 = nullptr;
	m_topwall2 = nullptr;
	m_bottomwall2 = nullptr;
	m_healthBar2 = nullptr;
	m_healthBarBackground2 = nullptr;
	firstFightBox2 = nullptr;
	secondFightBox2 = nullptr;
	thirdFightBox2 = nullptr;
}

void Game_Screen_Level2::Render()
{
	//draw the background
	m_background_texture2->Render(Vector2D(backgorundposition2, 0.0), SDL_FLIP_NONE);
	//draw the UI
	m_UIportrait2->Render(Vector2D(20, 20), SDL_FLIP_NONE);
	m_pistolBulletUI2->Render(Vector2D(22, 108), SDL_FLIP_NONE);
	m_scifiBulletUI2->Render(Vector2D(20, 139), SDL_FLIP_NONE);
	m_pistolAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_pistolAmmoText->RenderAt(my_character2->getAmmoCountPistolSTR(my_character2->pistolAmmoCount), 50, 100);
	m_scifiAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_scifiAmmoText->RenderAt(my_character2->getAmmoCountSciFiSTR(my_character2->scifiAmmoCount), 50, 130);
	m_healthBarBackground2->Render(Vector2D(85, 30), SDL_FLIP_NONE);
	
	//Initialise health bar reacting to player health amount 
	switch (my_character2->GetHealth())
	{
	case 10:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth(), m_healthBar2->GetHeight());
		break;
	case 9:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.9, m_healthBar2->GetHeight());
		break;
	case 8:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.8, m_healthBar2->GetHeight());
		break;
	case 7:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.7, m_healthBar2->GetHeight());
		break;
	case 6:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.6, m_healthBar2->GetHeight());
		break;
	case 5:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.5, m_healthBar2->GetHeight());
		break;
	case 4:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.4, m_healthBar2->GetHeight());
		break;
	case 3:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.3, m_healthBar2->GetHeight());
		break;
	case 2:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.2, m_healthBar2->GetHeight());
		break;
	case 1:
		m_healthBar2->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar2->GetWidth() * 0.1, m_healthBar2->GetHeight());
		break;
	default:;
	}

	//draw the arm, only when alive and nto damaged as it messes up damage flash aniamtion
	if (my_character2->m_damaged != true && my_character2->GetHealth() >= 0)
	{
		if (my_character2->getDirection() == FACING_RIGHT)
		{
			if (my_character2->currentWeapon == my_character2->weapons[1])
			{
				pistolArmRight2->SetPosition(Vector2D(my_character2->GetPosition().x + 25, my_character2->GetPosition().y + 34));
				pistolArmRight2->Render();
			}
			else if (my_character2->currentWeapon == my_character2->weapons[2])
			{
				scifiArmRight2->SetPosition(Vector2D(my_character2->GetPosition().x + 25, my_character2->GetPosition().y + 34));
				scifiArmRight2->Render();
			}
		}
		else if (my_character2->getDirection() == FACING_LEFT)
		{
			if (my_character2->currentWeapon == my_character2->weapons[1])
			{
				pistolArmLeft2->SetPosition(Vector2D(my_character2->GetPosition().x - 5, my_character2->GetPosition().y + 34));
				pistolArmLeft2->Render();
			}
			else if (my_character2->currentWeapon == my_character2->weapons[2])
			{
				scifiArmLeft2->SetPosition(Vector2D(my_character2->GetPosition().x - 5, my_character2->GetPosition().y + 34));
				scifiArmLeft2->Render();
			}
		}
	}

	my_character2->Render();

	if (scifiPickUp2 != nullptr)
	{
		scifiPickUp2->Render();
	}

	m_backwall2->Render();
	m_endwall2->Render();
	m_bottomwall2->Render();
	m_topwall2->Render();

	if (m_camera2 != nullptr)
	{
		m_camera2->Render();
	}
	if (m_backcamera2 != nullptr)
	{
		m_backcamera2->Render();
	}

	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box2[i] != nullptr)
		{
			m_Box2[i]->Render();
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp2[i] != nullptr)
		{
			m_bulletPickUp2[i]->Render();
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp2[i] != nullptr)
		{
			m_healthPickUp2[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles2[i] != nullptr)
		{
			projectiles2[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles2[i] != nullptr)
		{
			enemyProjectiles2[i]->Render();
		}
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		if (punchHitBoxes2[i] != nullptr)
		{
			punchHitBoxes2[i]->Render();
		}
	}
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		if (m_meleeEnemy2[i] != nullptr)
		{
			m_meleeEnemy2[i]->Render();
		}
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		if (m_rangedEnemy2[i] != nullptr)
		{
			m_rangedEnemy2[i]->Render();
		}
	}
	if (guardEnemy != nullptr)
	{
		guardEnemy->Render();
	}

	if (firstFightBox2 != nullptr)
	{
		firstFightBox2->Render();
	}
	if (secondFightBox2 != nullptr)
	{
		secondFightBox2->Render();
	}
	if (thirdFightBox2 != nullptr)
	{
		thirdFightBox2->Render();
	}
}

void Game_Screen_Level2::Update(float deltaTime, SDL_Event e)
{
	my_character2->Update(deltaTime, e);
	int playerHealth = my_character2->GetHealth();

	//update the guard enemye if alive
	if (guardEnemy != nullptr)
	{
		guardEnemy->Update(deltaTime, e);
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), guardEnemy->GetCollionBox()) && guardEnemy->guardAttackCooldown <= 0)
		{
			guardEnemy->m_attackingMelee = true;
			guardEnemy->guardAttackCooldown = 1000;
			my_character2->Damage(3);
		}
		if (guardEnemy->m_dead == true)
		{
			delete(guardEnemy);
			guardEnemy = nullptr;
		}
	}

	//update the melee enemies 
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		if (m_meleeEnemy2[i] != nullptr)
		{
			m_meleeEnemy2[i]->Update(deltaTime, e);

			if (Collision::Instance()->Box(m_meleeEnemy2[i]->GetCollionBox(), my_character2->GetCollionBox()) && m_meleeEnemy2[i]->MeleeAttackCooldown <= 0)
			{
				m_meleeEnemy2[i]->m_speed = 0;
				m_meleeEnemy2[i]->m_attacking = true;

				//draw hitbox on attack
				if (m_meleeEnemy2[i]->GetDirection() == FACING_LEFT)
				{
					punchHitBoxes2[1] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(m_meleeEnemy2[i]->GetPosition().x - 5, m_meleeEnemy2[i]->GetPosition().y + 35));
					m_meleeEnemy2[i]->MeleeAttackCooldown = 2000;
				}
				else if (m_meleeEnemy2[i]->GetDirection() == FACING_RIGHT)
				{
					punchHitBoxes2[1] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(m_meleeEnemy2[i]->GetPosition().x + 42, m_meleeEnemy2[i]->GetPosition().y + 35));
					m_meleeEnemy2[i]->MeleeAttackCooldown = 2000;
				}

				if (Collision::Instance()->Box(punchHitBoxes2[1]->GetCollionBox(), my_character2->GetCollionBox()))
				{
					my_character2->Damage(1);
					delete(punchHitBoxes2[1]);
					punchHitBoxes2[1] = nullptr;
				}
				else
				{
					delete(punchHitBoxes2[1]);
					punchHitBoxes2[1] = nullptr;
				}
			}
		}
	}

	//update ranged enemies 
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		if (m_rangedEnemy2[i] != nullptr)
		{
			m_rangedEnemy2[i]->Update(deltaTime, e);

			if (m_rangedEnemy2[i]->GetPosition().y < my_character2->GetPosition().y + 30 &&
				m_rangedEnemy2[i]->GetPosition().y > my_character2->GetPosition().y - 10 &&
				m_rangedEnemy2[i]->RangedAttackCooldown <= 0)
			{
				m_rangedEnemy2[i]->m_attacking = true;
				m_rangedEnemy2[i]->m_speed = 0;
				if (m_rangedEnemy2[i]->GetDirection() == FACING_LEFT)
				{
					//make projectile 
					for (int j = 0; j < NUMPROJECTILES; j++)
					{
						if (enemyProjectiles2[j] == nullptr)
						{
							enemyProjectiles2[j] = new Bullet(m_renderer, "Images/pistol bullet.png",
								Vector2D(m_rangedEnemy2[i]->GetPosition().x - 15, m_rangedEnemy2[i]->GetPosition().y + 35), 1, 1000, FACING_LEFT);
							m_rangedEnemy2[i]->RangedAttackCooldown = 1500;
							enemyProjectiles2[j]->alive = true;
							break;
						}
					}
				}
				else if (m_rangedEnemy2[i]->GetDirection() == FACING_RIGHT)
				{
					for (int j = 0; j < NUMPROJECTILES; j++)
					{
						if (enemyProjectiles2[j] == nullptr)
						{
							enemyProjectiles2[j] = new Bullet(m_renderer, "Images/pistol bullet.png",
								Vector2D(m_rangedEnemy2[i]->GetPosition().x + 35, m_rangedEnemy2[i]->GetPosition().y + 35), 1, 1000, FACING_RIGHT);
							m_rangedEnemy2[i]->RangedAttackCooldown = 1500;
							enemyProjectiles2[j]->alive = true;
							break;
						}
					}
				}
			}
		}
	}

	//make player attacks 
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (my_character2->currentWeapon == my_character2->weapons[0] && my_character2->attackCooldown <= 0)
		{
			my_character2->attackCooldown = 750;
			my_character2->m_attacking = true;
			if (punchHitBoxes2[0] == nullptr)
			{
				//punch attack hitbox
				if (my_character2->getDirection() == FACING_RIGHT)
				{
					punchHitBoxes2[0] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(my_character2->GetPosition().x + 42, my_character2->GetPosition().y + 37));
				}
				else if (my_character2->getDirection() == FACING_LEFT)
				{
					punchHitBoxes2[0] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(my_character2->GetPosition().x - 5, my_character2->GetPosition().y + 37));
				}
				//chekc hitbox collision with box
				for (int j = 0; j < NUMBOXES; j++)
				{
					if (m_Box2[j] != nullptr)
					{
						if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_Box2[j]->GetCollionBox()))
						{
							int tempBoxInt = 0;
							tempBoxInt = m_Box2[j]->Death(); //rand number for pick up
							switch (tempBoxInt)
							{
							case(1):
								for (int k = 0; k < NUMHEALTHPICKUPS; k++)
								{
									if (m_healthPickUp2[k] != nullptr)
									{
										continue;
									}
									m_healthPickUp2[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
										Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15));
									break;
								}
								break;
							case(2):
								for (int k = 0; k < NUMAMMOPICKUPS; k++)
								{
									if (m_bulletPickUp2[k] != nullptr)
									{
										continue;
									}
									m_bulletPickUp2[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
										Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15), 1);
									break;
								}
								break;
							case(3):
								for (int k = 0; k < NUMAMMOPICKUPS; k++)
								{
									if (m_bulletPickUp2[k] != nullptr)
									{
										continue;
									}
									m_bulletPickUp2[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
										Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15), 2);
									break;
								}
								break;
							default:
								break;
							}
							tempBoxInt = 0;

							delete(m_Box2[j]);
							m_Box2[j] = nullptr;
						}
					}
				}
				//check hitbox collision with melee enemy
				for (int j = 0; j < NUMMELEEENEMIES; j++)
				{
					if (m_meleeEnemy2[j] != nullptr)
					{
						if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_meleeEnemy2[j]->GetCollionBox()))
						{
							m_meleeEnemy2[j]->Damage(2);
						}
					}
				}
				//check hitbox collision with ranged enemies
				for (int j = 0; j < NUMRANGEDENEMIES; j++)
				{
					if (m_rangedEnemy2[j] != nullptr)
					{
						if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_rangedEnemy2[j]->GetCollionBox()))
						{
							m_rangedEnemy2[j]->Damage(2);
						}
					}
				}
				//check hitbox collison with robot guard enemy
				if (guardEnemy != nullptr)
				{
					if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), guardEnemy->GetCollionBox()))
					{
						guardEnemy->Damage(2);
					}
				}
				delete(punchHitBoxes2[0]);
				punchHitBoxes2[0] = nullptr;
			}
		}
		//spanw projectiles 
		for (int i = 0; i < NUMPROJECTILES; i++)
		{

			if (projectiles2[i] == nullptr && my_character2->attackCooldown <= 0)
			{
				my_character2->attackCooldown = 750;
				if (my_character2->currentWeapon == my_character2->weapons[1] && my_character2->pistolAmmoCount > 0)
				{
					if (my_character2->getDirection() == FACING_LEFT)
					{
						projectiles2[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character2->GetPosition().x - 15,
							my_character2->GetPosition().y + 30), 1, 1000, my_character2->getDirection());
						my_character2->pistolAmmoCount--;
					}
					if (my_character2->getDirection() == FACING_RIGHT)
					{
						projectiles2[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character2->GetPosition().x + 50,
							my_character2->GetPosition().y + 30), 1, 1000, my_character2->getDirection());
						my_character2->pistolAmmoCount--;
					}
					projectiles2[i]->alive = true;
					break;
				}
				else if (my_character2->currentWeapon == my_character2->weapons[2] && my_character2->scifiAmmoCount > 0)
				{
					if (my_character2->getDirection() == FACING_LEFT)
					{
						projectiles2[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character2->GetPosition().x - 15,
							my_character2->GetPosition().y + 30), 2, 1000, my_character2->getDirection());
						my_character2->scifiAmmoCount--;
					}
					if (my_character2->getDirection() == FACING_RIGHT)
					{
						projectiles2[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character2->GetPosition().x + 50,
							my_character2->GetPosition().y + 30), 2, 1000, my_character2->getDirection());
						my_character2->scifiAmmoCount--;
					}
					projectiles2[i]->alive = true;
					break;
				}
			}
		}
	}
	//attack cotnrols for the evacade
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		if (e.jbutton.button = 1 && my_character2->attackCooldown <= 0)
		{
			my_character2->attackCooldown = 750;
			if (my_character2->currentWeapon == my_character2->weapons[0])
			{
				my_character2->m_attacking = true;
				if (punchHitBoxes2[0] == nullptr)
				{
					if (my_character2->getDirection() == FACING_RIGHT)
					{
						punchHitBoxes2[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character2->GetPosition().x + 42, my_character2->GetPosition().y + 37));
					}
					else if (my_character2->getDirection() == FACING_LEFT)
					{
						punchHitBoxes2[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character2->GetPosition().x - 5, my_character2->GetPosition().y + 37));
					}
					for (int j = 0; j < NUMBOXES; j++)
					{
						if (m_Box2[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_Box2[j]->GetCollionBox()))
							{
								int tempBoxInt = 0;
								tempBoxInt = m_Box2[j]->Death(); //rand number for pick up
								switch (tempBoxInt)
								{
								case(1):
									for (int k = 0; k < NUMHEALTHPICKUPS; k++)
									{
										if (m_healthPickUp2[k] != nullptr)
										{
											continue;
										}
										m_healthPickUp2[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
											Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15));
										break;
									}
									break;
								case(2):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp2[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp2[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
											Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15), 1);
										break;
									}
									break;
								case(3):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp2[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp2[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
											Vector2D(m_Box2[j]->GetPosition().x + 10, m_Box2[j]->GetPosition().y + 15), 2);
										break;
									}
									break;
								default:
									break;
								}
								tempBoxInt = 0;

								delete(m_Box2[j]);
								m_Box2[j] = nullptr;
							}
						}
					}
					for (int j = 0; j < NUMMELEEENEMIES; j++)
					{
						if (m_meleeEnemy2[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_meleeEnemy2[j]->GetCollionBox()))
							{
								m_meleeEnemy2[j]->Damage(2);
							}
						}
					}
					for (int j = 0; j < NUMRANGEDENEMIES; j++)
					{
						if (m_rangedEnemy2[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes2[0]->GetCollionBox(), m_rangedEnemy2[j]->GetCollionBox()))
							{
								m_rangedEnemy2[j]->Damage(2);
							}
						}
					}
					delete(punchHitBoxes2[0]);
					punchHitBoxes2[0] = nullptr;
				}
			}
			else
			{
				for (int i = 0; i < NUMPROJECTILES; i++)
				{
					if (projectiles2[i] == nullptr && my_character2->attackCooldown <= 0)
					{
						my_character2->attackCooldown = 750;
						if (my_character2->currentWeapon == my_character2->weapons[1] && my_character2->pistolAmmoCount > 0)
						{
							if (my_character2->getDirection() == FACING_LEFT)
							{
								projectiles2[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character2->GetPosition().x - 15,
									my_character2->GetPosition().y + 25), 1, 1000, my_character2->getDirection());
								my_character2->pistolAmmoCount--;
							}
							if (my_character2->getDirection() == FACING_RIGHT)
							{
								projectiles2[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character2->GetPosition().x + 45,
									my_character2->GetPosition().y + 25), 1, 1000, my_character2->getDirection());
								my_character2->pistolAmmoCount--;
							}
							projectiles2[i]->alive = true;
							break;
						}
						else if (my_character2->currentWeapon == my_character2->weapons[2] && my_character2->scifiAmmoCount > 0)
						{
							if (my_character2->getDirection() == FACING_LEFT)
							{
								projectiles2[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character2->GetPosition().x - 15,
									my_character2->GetPosition().y + 25), 2, 1000, my_character2->getDirection());
								my_character2->scifiAmmoCount--;
							}
							if (my_character2->getDirection() == FACING_RIGHT)
							{
								projectiles2[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character2->GetPosition().x + 45,
									my_character2->GetPosition().y + 25), 2, 1000, my_character2->getDirection());
								my_character2->scifiAmmoCount--;
							}
							projectiles2[i]->alive = true;
							break;
						}
					}
				}
			}
		}
	}

	//update the projectile movements 
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles2[i] == nullptr)
		{
			continue;
		}
		else if (projectiles2[i]->alive == false)
		{
			delete projectiles2[i];
			projectiles2[i] = nullptr;
			continue;
		}
		projectiles2[i]->Update(my_character2->getDirection());
	}

	//update enemy projectiles
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles2[i] == nullptr)
		{
			continue;
		}
		else if (enemyProjectiles2[i]->alive == false)
		{
			delete enemyProjectiles2[i];
			enemyProjectiles2[i] = nullptr;
			continue;
		}
		enemyProjectiles2[i]->Update(my_character2->getDirection());
	}

	//check collision of projectile with box
	for (int k = 0; k < NUMPROJECTILES; k++)
	{
		for (int i = 0; i < NUMBOXES; i++)
		{
			if (m_Box2[i] != nullptr)
			{
				if (projectiles2[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles2[k]->GetCollionBox(), m_Box2[i]->GetCollionBox()))
					{
						int tempBoxInt = 0;
						tempBoxInt = m_Box2[i]->Death(); //rand number for pick up
						switch (tempBoxInt)
						{
						case(1):
							for (int j = 0; j < NUMHEALTHPICKUPS; j++) {
								if (m_healthPickUp2[j] != nullptr)
								{
									continue;
								}
								m_healthPickUp2[j] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
									Vector2D(m_Box2[i]->GetPosition().x + 10, m_Box2[i]->GetPosition().y + 15));
								break;
							}
							break;
						case(2):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp2[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp2[j] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
									Vector2D(m_Box2[i]->GetPosition().x + 10, m_Box2[i]->GetPosition().y + 15), 1);
								break;
							}
							break;
						case(3):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp2[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp2[j] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
									Vector2D(m_Box2[i]->GetPosition().x + 10, m_Box2[i]->GetPosition().y + 15), 2);
								break;
							}
							break;
						default:
							break;
						}
						tempBoxInt = 0;

						delete(m_Box2[i]);
						m_Box2[i] = nullptr;
						delete(projectiles2[k]);
						projectiles2[k] = nullptr;
					}
				}
			}
		}

		//check collision with the melee enemies
		for (int i = 0; i < NUMMELEEENEMIES; i++)
		{
			if (m_meleeEnemy2[i] != nullptr)
			{
				if (m_meleeEnemy2[i]->m_dead)
				{
					delete(m_meleeEnemy2[i]);
					m_meleeEnemy2[i] = nullptr;
				}
				if (projectiles2[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles2[k]->GetCollionBox(), m_meleeEnemy2[i]->GetCollionBox()))
					{
						if (projectiles2[k]->m_type == 1)
						{
							m_meleeEnemy2[i]->Damage(2);
						}
						else if (projectiles2[k]->m_type == 2)
						{
							m_meleeEnemy2[i]->Damage(4);
						}
						delete(projectiles2[k]);
						projectiles2[k] = nullptr;
					}
				}
			}
		}

		//check collision with the ranged enemies
		for (int i = 0; i < NUMRANGEDENEMIES; i++)
		{
			if (m_rangedEnemy2[i] != nullptr)
			{
				if (m_rangedEnemy2[i]->m_dead)
				{
					delete(m_rangedEnemy2[i]);
					m_rangedEnemy2[i] = nullptr;
				}
				if (projectiles2[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles2[k]->GetCollionBox(), m_rangedEnemy2[i]->GetCollionBox()))
					{
						if (projectiles2[k]->m_type == 1)
						{
							m_rangedEnemy2[i]->Damage(2);
						}
						else if (projectiles2[k]->m_type == 2)
						{
							m_rangedEnemy2[i]->Damage(4);
						}
						delete(projectiles2[k]);
						projectiles2[k] = nullptr;
					}
				}
			}
		}

		//check th ecollision with projectiels and robot guard
		if (guardEnemy != nullptr && projectiles2[k] != nullptr)
		{
			if (Collision::Instance()->Box(projectiles2[k]->GetCollionBox(), guardEnemy->GetCollionBox()))
			{
				if (projectiles2[k]->m_type == 1)
				{
					guardEnemy->Damage(2);
				}
				else if (projectiles2[k]->m_type == 2)
				{
					guardEnemy->Damage(4);
				}
				delete(projectiles2[k]);
				projectiles2[k] = nullptr;
			}
		}

		//check collision with enemy projectile and player
		if (enemyProjectiles2[k] != nullptr)
		{
			if (Collision::Instance()->Box(enemyProjectiles2[k]->GetCollionBox(), my_character2->GetCollionBox()))
			{
				if (enemyProjectiles2[k]->m_type == 1)
				{
					my_character2->Damage(2);
				}
				else if (enemyProjectiles2[k]->m_type == 2)
				{
					my_character2->Damage(4);
				}
				delete(enemyProjectiles2[k]);
				enemyProjectiles2[k] = nullptr;
			}
		}
	}

	//chekc health pick up collision
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp2[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_healthPickUp2[i]->GetCollionBox()))
			{
				m_healthPickUp2[i]->Collision(my_character2);
				delete(m_healthPickUp2[i]);
				m_healthPickUp2[i] = nullptr;
			}
		}
	}

	//check ammo pick up collision
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp2[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_bulletPickUp2[i]->GetCollionBox()))
			{
				m_bulletPickUp2[i]->Collision(my_character2, m_bulletPickUp2[i]->m_type);
				delete(m_bulletPickUp2[i]);
				m_bulletPickUp2[i] = nullptr;
			}
		}
	}

	//check wepaon pick up for sci-fi gun with player
	if (scifiPickUp2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), scifiPickUp2->GetCollionBox()))
		{
			my_character2->PickUpScifi();
			delete(scifiPickUp2);
			scifiPickUp2 = nullptr;
		}
	}

	//check first fight collision
	if (firstFightBox2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), firstFightBox2->GetCollionBox()))
		{
			MoveLeft(m_renderer, 0.4);

			movingCounter2++;
			if (movingCounter2 == 400)
			{
				m_meleeEnemy2[0] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(700, 250), my_character2);
				m_rangedEnemy2[0] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 400), my_character2);
				my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(firstFightBox2);
				firstFightBox2 = nullptr;
				movingCounter2 = 0;
			}
		}
	}

	//check collision for second fight 
	if (secondFightBox2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), secondFightBox2->GetCollionBox()))
		{
			MoveLeft(m_renderer, 0.4);

			movingCounter2++;
			if (movingCounter2 == 800)
			{
				m_meleeEnemy2[0] = new Melee_Enemy(m_renderer, "Images/melee Enemy.png", Vector2D(650, 250), my_character2);
				m_rangedEnemy2[0] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 400), my_character2);
				m_rangedEnemy2[1] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 250), my_character2);
				my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(secondFightBox2);
				secondFightBox2 = nullptr;
				movingCounter2 = 0;
			}
		}
	}

	//check the collision for the third fight 
	if (thirdFightBox2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), thirdFightBox2->GetCollionBox()))
		{
			MoveLeft(m_renderer, 0.4);

			movingCounter2++;
			if (movingCounter2 == 700)
			{
				m_rangedEnemy2[0] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 400), my_character2);
				m_rangedEnemy2[1] = new Ranged_Enemy(m_renderer, "Images/ranged Enemy.png", Vector2D(700, 250), my_character2);
				guardEnemy = new robotGuard(m_renderer, "Images/robot Guard.png", Vector2D(700, 350), my_character2);
				my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(thirdFightBox2);
				thirdFightBox2 = nullptr;
				movingCounter2 = 0;
			}
		}
	}

	//check collision with camera movement
	if (m_camera2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_camera2->GetCollionBox()))
		{
			if (my_character2->m_moving_right == true)
			{
				my_character2->movementSpeed = 0;

				if (CheckFightActive2() == false)
				{
					//move scene left but not the character 
					MoveLeft(m_renderer, 0.15);
					my_character2->SetPosition(Vector2D(my_character2->GetPosition().x + 0.15, my_character2->GetPosition().y));
				}
			}
			else
			{
				my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}

	//check collision with the camera ot move left
	if (m_backcamera2 != nullptr)
	{
		if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_backcamera2->GetCollionBox()))
		{
			if (my_character2->m_moving_left == true)
			{
				my_character2->movementSpeed = 0;

				if (CheckFightActive2() == false)
				{
					//move scene left but not the character 
					MoveLeft(m_renderer, 0.15);
					my_character2->SetPosition(Vector2D(my_character2->GetPosition().x + 0.15, my_character2->GetPosition().y));
				}
			}
			else
			{
				my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}

	//check collision with the left wall 
	if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_backwall2->GetCollionBox()))
	{
		if (my_character2->m_moving_left == true)
		{
			my_character2->movementSpeed = 0;
		}
		else
		{
			my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	//check collision with end right wall
	else if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_endwall2->GetCollionBox()))
	{
		//change level to level three
		if (game_scene_manager->GetCurrentScreen() == SCREEN_LEVEL2)
		{
			game_scene_manager->ChangeScreen(SCREEN_BOSSLEVEL);
		}
	}
	//check collision on top wall and stop movement 
	else if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_topwall2->GetCollionBox()))
	{
		if (my_character2->m_moving_up == true)
		{
			my_character2->movementSpeed = 0;
		}
		else
		{
			my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	//check collision on bottom wall and stop movement through it 
	else if (Collision::Instance()->Box(my_character2->GetCollionBox(), m_bottomwall2->GetCollionBox()))
	{
		if (my_character2->m_moving_down == true)
		{
			my_character2->movementSpeed = 0;
		}
		else
		{
			my_character2->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
}

bool Game_Screen_Level2::SetUpLevel()
{
	backwallposition2 = 10.0f;
	backgorundposition2 = 0.0f;
	endwallposition2 = 2052.0f;

	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		delete(m_meleeEnemy2[i]);
		m_meleeEnemy2[i] = nullptr;
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		delete(m_rangedEnemy2[i]);
		m_rangedEnemy2[i] = nullptr;
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp2[i]);
		m_healthPickUp2[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp2[i]);
		m_bulletPickUp2[i] = nullptr;
	}
	if (guardEnemy != nullptr)
	{
		delete(guardEnemy);
		guardEnemy = nullptr;
	}

	m_background_texture2 = new Texture2D(m_renderer);
	if (!m_background_texture2->LoadFromFile("Images/Level 2.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_UIportrait2 = new Texture2D(m_renderer);
	if (!m_UIportrait2->LoadFromFile("Images/UI portrait.png"))
	{
		std::cout << "Failed to load UI portrait texture!" << std::endl;
		return false;
	}

	m_pistolBulletUI2 = new Texture2D(m_renderer);
	if (!m_pistolBulletUI2->LoadFromFile("Images/pistol bullet.png"))
	{
		std::cout << "Failed to load UI pistol bullet texture!" << std::endl;
		return false;
	}

	m_scifiBulletUI2 = new Texture2D(m_renderer);
	if (!m_scifiBulletUI2->LoadFromFile("Images/sci-fi bullet.png"))
	{
		std::cout << "Failed to load UI sci-fi bullet texture!" << std::endl;
		return false;
	}

	m_healthBarBackground2 = new Texture2D(m_renderer);
	if (!m_healthBarBackground2->LoadFromFile("Images/Health Bar Background.png"))
	{
		std::cout << "failed to load health bar background texture!" << std::endl;
		return false;
	}

	m_healthBar2 = new Texture2D(m_renderer);
	if (!m_healthBar2->LoadFromFile("Images/Health Bar.png"))
	{
		std::cout << "failed to load health bar texture!" << std::endl;
		return false;
	}

	m_backwall2 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(backwallposition2, 0));
	m_endwall2 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(endwallposition2, 0));
	m_topwall2 = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 205));
	m_bottomwall2 = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 415));

	// make charachter model
	my_character2 = new Character(m_renderer, "Images/Character.png", Vector2D(100, 300), game_scene_manager);
	my_character2->PickUpPistol();

	scifiPickUp2 = new Game_Object(m_renderer, "Images/sci-fi Pickup.png", Vector2D(450, 350));

	pistolArmRight2 = new Game_Object(m_renderer, "Images/Pistol Arm Right.png", Vector2D(my_character2->GetPosition().x, my_character2->GetPosition().y));
	pistolArmLeft2 = new Game_Object(m_renderer, "Images/Pistol Arm Left.png", Vector2D(my_character2->GetPosition().x, my_character2->GetPosition().y));
	scifiArmLeft2 = new Game_Object(m_renderer, "Images/Sci-fi Arm Left.png", Vector2D(my_character2->GetPosition().x, my_character2->GetPosition().y));
	scifiArmRight2 = new Game_Object(m_renderer, "Images/Sci-fi Arm Right.png", Vector2D(my_character2->GetPosition().x, my_character2->GetPosition().y));

	m_camera2 = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(800 - 48, 0));
	m_backcamera2 = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(0, 0));

	m_Box2[0] = new Box(m_renderer, "Images/Box.png", Vector2D(105, 255));
	m_Box2[1] = new Box(m_renderer, "Images/Box.png", Vector2D(250, 255));
	m_Box2[2] = new Box(m_renderer, "Images/Box.png", Vector2D(100, 400));
	m_Box2[3] = new Box(m_renderer, "Images/Box.png", Vector2D(250, 400));
	m_Box2[4] = new Box(m_renderer, "Images/Box.png", Vector2D(300, 400));
	m_Box2[5] = new Box(m_renderer, "Images/Box.png", Vector2D(450, 255));
	m_Box2[6] = new Box(m_renderer, "Images/Box.png", Vector2D(600, 400));
	m_Box2[7] = new Box(m_renderer, "Images/Box.png", Vector2D(950, 400));
	m_Box2[8] = new Box(m_renderer, "Images/Box.png", Vector2D(1000, 400));
	m_Box2[9] = new Box(m_renderer, "Images/Box.png", Vector2D(1200, 400));
	m_Box2[10] = new Box(m_renderer, "Images/Box.png", Vector2D(1500, 400));
	m_Box2[11] = new Box(m_renderer, "Images/Box.png", Vector2D(950, 255));
	m_Box2[12] = new Box(m_renderer, "Images/Box.png", Vector2D(1150, 255));
	m_Box2[13] = new Box(m_renderer, "Images/Box.png", Vector2D(1500, 255));

	m_pistolAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);
	m_scifiAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);

	firstFightBox2 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(250, 0));
	secondFightBox2 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(1100, 0));
	thirdFightBox2 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(1700, 0));

	return true;
}

//check if any enemy if alive and return true if fight active to stop camera movement 
bool CheckFightActive2()
{
	for (int i = 0; i < NUMMELEEENEMIES; i++)
	{
		if (m_meleeEnemy2[i] != nullptr)
		{
			return true;
		}
	}
	for (int i = 0; i < NUMRANGEDENEMIES; i++)
	{
		if (m_rangedEnemy2[i] != nullptr)
		{
			return true;
		}
	}
	if (guardEnemy != nullptr)
	{
		return true;
	}
	return false;
}

//move the scene to the left 
void Game_Screen_Level2::MoveLeft(SDL_Renderer* renderer, float amount)
{
	m_background_texture2->Render(Vector2D(backgorundposition2 -= amount, 0), SDL_FLIP_NONE);
	m_backwall2->SetPosition(Vector2D(backwallposition2 -= amount, 0));
	m_endwall2->SetPosition(Vector2D(endwallposition2 -= amount, 0));
	my_character2->SetPosition(Vector2D(my_character2->GetPosition().x - amount, my_character2->GetPosition().y));
	my_character2->movementSpeed = 0;
	if (firstFightBox2 != nullptr)
	{
		firstFightBox2->SetPosition(Vector2D(firstFightBox2->GetPosition().x - amount, firstFightBox2->GetPosition().y));
	}
	if (secondFightBox2 != nullptr)
	{
		secondFightBox2->SetPosition(Vector2D(secondFightBox2->GetPosition().x - amount, secondFightBox2->GetPosition().y));
	}
	if (thirdFightBox2 != nullptr)
	{
		thirdFightBox2->SetPosition(Vector2D(thirdFightBox2->GetPosition().x - amount, thirdFightBox2->GetPosition().y));
	}
	if (scifiPickUp2 != nullptr)
	{
		scifiPickUp2->SetPosition(Vector2D(scifiPickUp2->GetPosition().x - amount, scifiPickUp2->GetPosition().y));
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box2[i] != nullptr)
		{
			m_Box2[i]->SetPosition((Vector2D(m_Box2[i]->GetPosition().x - amount, m_Box2[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp2[i] != nullptr)
		{
			m_healthPickUp2[i]->SetPosition((Vector2D(m_healthPickUp2[i]->GetPosition().x - amount, m_healthPickUp2[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp2[i] != nullptr)
		{
			m_bulletPickUp2[i]->SetPosition((Vector2D(m_bulletPickUp2[i]->GetPosition().x - amount, m_bulletPickUp2[i]->GetPosition().y)));
		}
	}
}

//move the scene to the right 
void Game_Screen_Level2::MoveRight(SDL_Renderer* renderer, float amount)
{
	m_background_texture2->Render(Vector2D(backgorundposition2 += amount, 0), SDL_FLIP_NONE);
	m_backwall2->SetPosition(Vector2D(backwallposition2 += amount, 0));
	m_endwall2->SetPosition(Vector2D(endwallposition2 += amount, 0));
	my_character2->SetPosition(Vector2D(my_character2->GetPosition().x + amount, my_character2->GetPosition().y));
	my_character2->movementSpeed = 0;
	if (firstFightBox2 != nullptr)
	{
		firstFightBox2->SetPosition(Vector2D(firstFightBox2->GetPosition().x + amount, firstFightBox2->GetPosition().y));
	}
	if (secondFightBox2 != nullptr)
	{
		secondFightBox2->SetPosition(Vector2D(secondFightBox2->GetPosition().x + amount, secondFightBox2->GetPosition().y));
	}
	if (thirdFightBox2 != nullptr)
	{
		thirdFightBox2->SetPosition(Vector2D(thirdFightBox2->GetPosition().x + amount, thirdFightBox2->GetPosition().y));
	}
	if (scifiPickUp2 != nullptr)
	{
		scifiPickUp2->SetPosition(Vector2D(scifiPickUp2->GetPosition().x + amount, scifiPickUp2->GetPosition().y));
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box2[i] != nullptr)
		{
			m_Box2[i]->SetPosition((Vector2D(m_Box2[i]->GetPosition().x + amount, m_Box2[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp2[i] != nullptr)
		{
			m_healthPickUp2[i]->SetPosition((Vector2D(m_healthPickUp2[i]->GetPosition().x + amount, m_healthPickUp2[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp2[i] != nullptr)
		{
			m_bulletPickUp2[i]->SetPosition((Vector2D(m_bulletPickUp2[i]->GetPosition().x + amount, m_bulletPickUp2[i]->GetPosition().y)));
		}
	}
}