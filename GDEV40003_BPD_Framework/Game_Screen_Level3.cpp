#include "Game_Screen_Level3.h"
#include "Game_Screen_Level2.h"
#include "GameSceneManager.h"
#include "Texture2D.h"
#include "Collision.h"
#include <iostream>

//initialise the walls and camera
Game_Object* m_camera3 = nullptr;
Game_Object* m_backcamera3 = nullptr;
Game_Object* m_backwall3 = nullptr;
Game_Object* m_endwall3 = nullptr;
Game_Object* m_topwall3 = nullptr;
Game_Object* m_bottomwall3 = nullptr;

//initialise UI
Texture2D* m_UIportrait3 = nullptr;
Texture2D* m_pistolBulletUI3 = nullptr;
Texture2D* m_scifiBulletUI3 = nullptr;
Texture2D* m_healthBarBackground3 = nullptr;
Texture2D* m_healthBar3 = nullptr;

//initialise the boxes
Box* m_Box3[NUMBOXES];
HealthPickUp* m_healthPickUp3[NUMHEALTHPICKUPS];
BulletPickUp* m_bulletPickUp3[NUMAMMOPICKUPS];
Game_Object* punchHitBoxes3[NUMPUNCHHITBOXES];

//initialise the player arm 
Game_Object* pistolArmRight3 = nullptr;
Game_Object* pistolArmLeft3 = nullptr;
Game_Object* scifiArmRight3 = nullptr;
Game_Object* scifiArmLeft3 = nullptr;

Boss_Enemy* bossEnemy = nullptr;
Game_Object* laser = nullptr;

Bullet* projectiles3[NUMPROJECTILES];
Bullet* enemyProjectiles3[NUMPROJECTILES];

Game_Object* fightBox = nullptr;

bool CheckFightActive3();

int movingCounter3 = 0;

int attackTimer = 0;

Game_Screen_Level3::Game_Screen_Level3(SDL_Renderer* renderer, GameSceneManager* sceneManager) : Game_Screen(renderer, sceneManager)
{
	m_renderer = renderer;
	game_scene_manager = sceneManager;
	SetUpLevel();
}

Game_Screen_Level3::~Game_Screen_Level3()
{
	delete(m_background_texture3);
	delete(m_UIportrait3);
	delete(m_pistolBulletUI3);
	delete(m_scifiBulletUI3);
	delete(my_character3);
	delete(pistolArmRight3);
	delete(pistolArmLeft3);
	delete(scifiArmLeft3);
	delete(scifiArmRight3);
	delete(m_camera3);
	delete(m_backwall3);
	delete(m_endwall3);
	delete(m_backcamera3);
	delete(m_topwall3);
	delete(m_bottomwall3);
	delete(m_healthBar3);
	delete(m_healthBarBackground3);
	delete(fightBox);

	for (int i = 0; i < NUMBOXES; i++)
	{
		delete(m_Box3[i]);
		m_Box3[i] = nullptr;
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp3[i]);
		m_healthPickUp3[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp3[i]);
		m_bulletPickUp3[i] = nullptr;
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		delete(projectiles3[i]);
		projectiles3[i] = nullptr;
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		delete(enemyProjectiles3[i]);
		enemyProjectiles3[i] = nullptr;
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		delete(punchHitBoxes3[i]);
		punchHitBoxes3[i] = nullptr;
	}

	if (bossEnemy != nullptr)
	{
		delete(bossEnemy);
		bossEnemy = nullptr;
	}
	if (laser != nullptr)
	{
		delete(laser);
		laser = nullptr;
	}

	m_background_texture3 = nullptr;
	m_UIportrait3 = nullptr;
	m_pistolBulletUI3 = nullptr;
	m_scifiBulletUI3 = nullptr;
	my_character3 = nullptr;
	pistolArmRight3 = nullptr;
	pistolArmLeft3 = nullptr;
	scifiArmLeft3 = nullptr;
	scifiArmRight3 = nullptr;
	m_camera3 = nullptr;
	m_backwall3 = nullptr;
	m_endwall3 = nullptr;
	m_backcamera3 = nullptr;
	m_topwall3 = nullptr;
	m_bottomwall3 = nullptr;
	m_healthBar3 = nullptr;
	m_healthBarBackground3 = nullptr;
	fightBox = nullptr;
}

void Game_Screen_Level3::Render()
{
	//draw the background
	m_background_texture3->Render(Vector2D(backgorundposition3, 0.0), SDL_FLIP_NONE);

	//draw the UI
	m_UIportrait3->Render(Vector2D(20, 20), SDL_FLIP_NONE);
	m_pistolBulletUI3->Render(Vector2D(22, 108), SDL_FLIP_NONE);
	m_scifiBulletUI3->Render(Vector2D(20, 139), SDL_FLIP_NONE);
	m_pistolAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_pistolAmmoText->RenderAt(my_character3->getAmmoCountPistolSTR(my_character3->pistolAmmoCount), 50, 100);
	m_scifiAmmoText->SetColor(SDL_Color{ 255,255,255,255 });
	m_scifiAmmoText->RenderAt(my_character3->getAmmoCountSciFiSTR(my_character3->scifiAmmoCount), 50, 130);
	m_healthBarBackground3->Render(Vector2D(85, 30), SDL_FLIP_NONE);

	//player health bar 
	switch (my_character3->GetHealth())
	{
	case 10:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth(), m_healthBar3->GetHeight());
		break;
	case 9:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.9, m_healthBar3->GetHeight());
		break;
	case 8:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.8, m_healthBar3->GetHeight());
		break;
	case 7:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.7, m_healthBar3->GetHeight());
		break;
	case 6:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.6, m_healthBar3->GetHeight());
		break;
	case 5:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.5, m_healthBar3->GetHeight());
		break;
	case 4:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.4, m_healthBar3->GetHeight());
		break;
	case 3:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.3, m_healthBar3->GetHeight());
		break;
	case 2:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.2, m_healthBar3->GetHeight());
		break;
	case 1:
		m_healthBar3->Render(Vector2D(85, 30), SDL_FLIP_NONE, 0, 0, m_healthBar3->GetWidth() * 0.1, m_healthBar3->GetHeight());
		break;
	default:;
	}
	//display the arm for the player
	if (my_character3->m_damaged != true && my_character3->GetHealth() >= 0)
	{
		if (my_character3->getDirection() == FACING_RIGHT)
		{
			if (my_character3->currentWeapon == my_character3->weapons[1])
			{
				pistolArmRight3->SetPosition(Vector2D(my_character3->GetPosition().x + 25, my_character3->GetPosition().y + 34));
				pistolArmRight3->Render();
			}
			else if (my_character3->currentWeapon == my_character3->weapons[2])
			{
				scifiArmRight3->SetPosition(Vector2D(my_character3->GetPosition().x + 25, my_character3->GetPosition().y + 34));
				scifiArmRight3->Render();
			}
		}
		else if (my_character3->getDirection() == FACING_LEFT)
		{
			if (my_character3->currentWeapon == my_character3->weapons[1])
			{
				pistolArmLeft3->SetPosition(Vector2D(my_character3->GetPosition().x - 5, my_character3->GetPosition().y + 34));
				pistolArmLeft3->Render();
			}
			else if (my_character3->currentWeapon == my_character3->weapons[2])
			{
				scifiArmLeft3->SetPosition(Vector2D(my_character3->GetPosition().x - 5, my_character3->GetPosition().y + 34));
				scifiArmLeft3->Render();
			}
		}
	}

	my_character3->Render();
	m_backwall3->Render();
	m_endwall3->Render();
	m_bottomwall3->Render();
	m_topwall3->Render();
	if (m_camera3 != nullptr)
	{
		m_camera3->Render();
	}
	if (m_backcamera3 != nullptr)
	{
		m_backcamera3->Render();
	}
	
	if (bossEnemy != nullptr)
	{
		bossEnemy->Render();
	}
	if (laser != nullptr)
	{
		laser->Render();
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box3[i] != nullptr)
		{
			m_Box3[i]->Render();
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp3[i] != nullptr)
		{
			m_bulletPickUp3[i]->Render();
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp3[i] != nullptr)
		{
			m_healthPickUp3[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles3[i] != nullptr)
		{
			projectiles3[i]->Render();
		}
	}
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles3[i] != nullptr)
		{
			enemyProjectiles3[i]->Render();
		}
	}
	for (int i = 0; i < NUMPUNCHHITBOXES; i++)
	{
		if (punchHitBoxes3[i] != nullptr)
		{
			punchHitBoxes3[i]->Render();
		}
	}
	if (fightBox != nullptr)
	{
		fightBox->Render();
	}
}

void Game_Screen_Level3::Update(float deltaTime, SDL_Event e)
{
	my_character3->Update(deltaTime, e);
	int playerHealth = my_character3->GetHealth();
	//update the boss enemy 
	if (bossEnemy != nullptr)
	{
		bossEnemy->Update(deltaTime, e);
		if (Collision::Instance()->Box(my_character3->GetCollionBox(), bossEnemy->GetCollionBox()) && bossEnemy->bossAttackCooldown <= 0)
		{
			bossEnemy->m_attackingMelee = true;
			bossEnemy->bossAttackCooldown = 1000;
			my_character3->Damage(2);
		}

		if (bossEnemy->GetPosition().y < my_character3->GetPosition().y + 30 &&
			bossEnemy->GetPosition().y > my_character3->GetPosition().y - 30 &&
			bossEnemy->bossAttackCooldown <= 0)
		{
			bossEnemy->m_attackingRanged = true;
		}
		//raged laser attack 
		if (bossEnemy->m_attackingRanged == true)
		{
			attackTimer++;
			if (attackTimer == 450) //spawn at farme 5
			{
				if (bossEnemy->GetDirection() == FACING_LEFT)
				{
					laser = new Game_Object(m_renderer, "Images/Boss Laser.png", Vector2D(bossEnemy->GetPosition().x - 967, bossEnemy->GetPosition().y + 35));
				}
				else
				{
					laser = new Game_Object(m_renderer, "Images/Boss Laser.png", Vector2D(bossEnemy->GetPosition().x + 25, bossEnemy->GetPosition().y + 35));
				}
			}

			if (attackTimer == 750) // delete after frame 6
			{
				delete(laser);
				laser = nullptr;
				bossEnemy->m_attackingRanged = false;
				bossEnemy->m_speed = 0.1;
				bossEnemy->bossAttackCooldown = 1000;
				attackTimer = 0;
			}
		}
		if (bossEnemy->m_dead == true)
		{
			if (game_scene_manager->GetCurrentScreen() == SCREEN_BOSSLEVEL)
			{
				game_scene_manager->ChangeScreen(SCREEN_WINPAGE);
			}
		}
	}

	//damage player on collision with laser 
	if (laser != nullptr)
	{
		if (Collision::Instance()->Box(my_character3->GetCollionBox(), laser->GetCollionBox()))
		{
			my_character3->Damage(1);
		}
	}

	//player attacks 
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//punch
		if (my_character3->currentWeapon == my_character3->weapons[0] && my_character3->attackCooldown <= 0)
		{
			my_character3->attackCooldown = 750;
			my_character3->m_attacking = true;
			if (punchHitBoxes3[0] == nullptr)
			{
				if (my_character3->getDirection() == FACING_RIGHT)
				{
					punchHitBoxes3[0] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(my_character3->GetPosition().x + 42, my_character3->GetPosition().y + 37));
				}
				else if (my_character3->getDirection() == FACING_LEFT)
				{
					punchHitBoxes3[0] = new Game_Object(m_renderer, "Images/hitBox.png",
						Vector2D(my_character3->GetPosition().x - 5, my_character3->GetPosition().y + 37));
				}
				for (int j = 0; j < NUMBOXES; j++)
				{
					if (m_Box3[j] != nullptr)
					{
						if (Collision::Instance()->Box(punchHitBoxes3[0]->GetCollionBox(), m_Box3[j]->GetCollionBox()))
						{
							int tempBoxInt = 0;
							tempBoxInt = m_Box3[j]->Death(); //rand number for pick up
							switch (tempBoxInt)
							{
							case(1):
								for (int k = 0; k < NUMHEALTHPICKUPS; k++)
								{
									if (m_healthPickUp3[k] != nullptr)
									{
										continue;
									}
									m_healthPickUp3[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
										Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15));
									break;
								}
								break;
							case(2):
								for (int k = 0; k < NUMAMMOPICKUPS; k++)
								{
									if (m_bulletPickUp3[k] != nullptr)
									{
										continue;
									}
									m_bulletPickUp3[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
										Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15), 1);
									break;
								}
								break;
							case(3):
								for (int k = 0; k < NUMAMMOPICKUPS; k++)
								{
									if (m_bulletPickUp3[k] != nullptr)
									{
										continue;
									}
									m_bulletPickUp3[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
										Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15), 2);
									break;
								}
								break;
							default:
								break;
							}
							tempBoxInt = 0;

							delete(m_Box3[j]);
							m_Box3[j] = nullptr;
						}
					}
				}
				//check collision with boss
				if (bossEnemy != nullptr)
				{
					if (Collision::Instance()->Box(punchHitBoxes3[0]->GetCollionBox(), bossEnemy->GetCollionBox()))
					{
						bossEnemy->Damage(2);
					}
				}
				delete(punchHitBoxes3[0]);
				punchHitBoxes3[0] = nullptr;
			}
		}
		//spawn projectile 
		for (int i = 0; i < NUMPROJECTILES; i++)
		{

			if (projectiles3[i] == nullptr && my_character3->attackCooldown <= 0)
			{
				my_character3->attackCooldown = 750;
				if (my_character3->currentWeapon == my_character3->weapons[1] && my_character3->pistolAmmoCount > 0)
				{
					if (my_character3->getDirection() == FACING_LEFT)
					{
						projectiles3[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character3->GetPosition().x - 15,
							my_character3->GetPosition().y + 30), 1, 1000, my_character3->getDirection());
						my_character3->pistolAmmoCount--;
					}
					if (my_character3->getDirection() == FACING_RIGHT)
					{
						projectiles3[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character3->GetPosition().x + 50,
							my_character3->GetPosition().y + 30), 1, 1000, my_character3->getDirection());
						my_character3->pistolAmmoCount--;
					}
					projectiles3[i]->alive = true;
					break;
				}
				else if (my_character3->currentWeapon == my_character3->weapons[2] && my_character3->scifiAmmoCount > 0)
				{
					if (my_character3->getDirection() == FACING_LEFT)
					{
						projectiles3[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character3->GetPosition().x - 15,
							my_character3->GetPosition().y + 30), 2, 1000, my_character3->getDirection());
						my_character3->scifiAmmoCount--;
					}
					if (my_character3->getDirection() == FACING_RIGHT)
					{
						projectiles3[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character3->GetPosition().x + 50,
							my_character3->GetPosition().y + 30), 2, 1000, my_character3->getDirection());
						my_character3->scifiAmmoCount--;
					}
					projectiles3[i]->alive = true;
					break;
				}
			}
		}
	}
	//attack controls on evacade
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		if (e.jbutton.button = 1 && my_character3->attackCooldown <= 0)
		{
			my_character3->attackCooldown = 750;
			if (my_character3->currentWeapon == my_character3->weapons[0])
			{
				my_character3->m_attacking = true;
				if (punchHitBoxes3[0] == nullptr)
				{
					if (my_character3->getDirection() == FACING_RIGHT)
					{
						punchHitBoxes3[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character3->GetPosition().x + 42, my_character3->GetPosition().y + 37));
					}
					else if (my_character3->getDirection() == FACING_LEFT)
					{
						punchHitBoxes3[0] = new Game_Object(m_renderer, "Images/hitBox.png",
							Vector2D(my_character3->GetPosition().x - 5, my_character3->GetPosition().y + 37));
					}
					for (int j = 0; j < NUMBOXES; j++)
					{
						if (m_Box3[j] != nullptr)
						{
							if (Collision::Instance()->Box(punchHitBoxes3[0]->GetCollionBox(), m_Box3[j]->GetCollionBox()))
							{
								int tempBoxInt = 0;
								tempBoxInt = m_Box3[j]->Death(); //rand number for pick up
								switch (tempBoxInt)
								{
								case(1):
									for (int k = 0; k < NUMHEALTHPICKUPS; k++)
									{
										if (m_healthPickUp3[k] != nullptr)
										{
											continue;
										}
										m_healthPickUp3[k] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
											Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15));
										break;
									}
									break;
								case(2):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp3[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp3[k] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
											Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15), 1);
										break;
									}
									break;
								case(3):
									for (int k = 0; k < NUMAMMOPICKUPS; k++)
									{
										if (m_bulletPickUp3[k] != nullptr)
										{
											continue;
										}
										m_bulletPickUp3[k] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
											Vector2D(m_Box3[j]->GetPosition().x + 10, m_Box3[j]->GetPosition().y + 15), 2);
										break;
									}
									break;
								default:
									break;
								}
								tempBoxInt = 0;

								delete(m_Box3[j]);
								m_Box3[j] = nullptr;
							}
						}
					}
					delete(punchHitBoxes3[0]);
					punchHitBoxes3[0] = nullptr;
				}
			}
			else
				//spawn projectiles 
			{
				for (int i = 0; i < NUMPROJECTILES; i++)
				{
					if (projectiles3[i] == nullptr && my_character3->attackCooldown <= 0)
					{
						my_character3->attackCooldown = 750;
						if (my_character3->currentWeapon == my_character3->weapons[1] && my_character3->pistolAmmoCount > 0)
						{
							if (my_character3->getDirection() == FACING_LEFT)
							{
								projectiles3[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character3->GetPosition().x - 15,
									my_character3->GetPosition().y + 25), 1, 1000, my_character3->getDirection());
								my_character3->pistolAmmoCount--;
							}
							if (my_character3->getDirection() == FACING_RIGHT)
							{
								projectiles3[i] = new Bullet(m_renderer, "Images/pistol bullet.png", Vector2D(my_character3->GetPosition().x + 45,
									my_character3->GetPosition().y + 25), 1, 1000, my_character3->getDirection());
								my_character3->pistolAmmoCount--;
							}
							projectiles3[i]->alive = true;
							break;
						}
						else if (my_character3->currentWeapon == my_character3->weapons[2] && my_character3->scifiAmmoCount > 0)
						{
							if (my_character3->getDirection() == FACING_LEFT)
							{
								projectiles3[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character3->GetPosition().x - 15,
									my_character3->GetPosition().y + 25), 2, 1000, my_character3->getDirection());
								my_character3->scifiAmmoCount--;
							}
							if (my_character3->getDirection() == FACING_RIGHT)
							{
								projectiles3[i] = new Bullet(m_renderer, "Images/sci-fi bullet.png", Vector2D(my_character3->GetPosition().x + 45,
									my_character3->GetPosition().y + 25), 2, 1000, my_character3->getDirection());
								my_character3->scifiAmmoCount--;
							}
							projectiles3[i]->alive = true;
							break;
						}
					}
				}
			}
		}
	}

	//update projectiles 
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (projectiles3[i] == nullptr)
		{
			continue;
		}
		else if (projectiles3[i]->alive == false)
		{
			delete projectiles3[i];
			projectiles3[i] = nullptr;
			continue;
		}
		projectiles3[i]->Update(my_character3->getDirection());
	}

	//update enemy projectiles 
	for (int i = 0; i < NUMPROJECTILES; i++)
	{
		if (enemyProjectiles3[i] == nullptr)
		{
			continue;
		}
		else if (enemyProjectiles3[i]->alive == false)
		{
			delete enemyProjectiles3[i];
			enemyProjectiles3[i] = nullptr;
			continue;
		}
		enemyProjectiles3[i]->Update(my_character3->getDirection());
	}

	//check collisioon with projectiles 
	for (int k = 0; k < NUMPROJECTILES; k++)
	{
		for (int i = 0; i < NUMBOXES; i++)
		{
			if (m_Box3[i] != nullptr)
			{
				if (projectiles3[k] != nullptr)
				{
					if (Collision::Instance()->Box(projectiles3[k]->GetCollionBox(), m_Box3[i]->GetCollionBox()))
					{
						int tempBoxInt = 0;
						tempBoxInt = m_Box3[i]->Death(); //rand number for pick up
						switch (tempBoxInt)
						{
						case(1):
							for (int j = 0; j < NUMHEALTHPICKUPS; j++) {
								if (m_healthPickUp3[j] != nullptr)
								{
									continue;
								}
								m_healthPickUp3[j] = new HealthPickUp(m_renderer, "Images/Health Pickup.png",
									Vector2D(m_Box3[i]->GetPosition().x + 10, m_Box3[i]->GetPosition().y + 15));
								break;
							}
							break;
						case(2):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp3[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp3[j] = new BulletPickUp(m_renderer, "Images/pistol bullet.png",
									Vector2D(m_Box3[i]->GetPosition().x + 10, m_Box3[i]->GetPosition().y + 15), 1);
								break;
							}
							break;
						case(3):
							for (int j = 0; j < NUMAMMOPICKUPS; j++)
							{
								if (m_bulletPickUp3[j] != nullptr)
								{
									continue;
								}
								m_bulletPickUp3[j] = new BulletPickUp(m_renderer, "Images/sci-fi bullet.png",
									Vector2D(m_Box3[i]->GetPosition().x + 10, m_Box3[i]->GetPosition().y + 15), 2);
								break;
							}
							break;
						default:
							break;
						}
						tempBoxInt = 0;

						delete(m_Box3[i]);
						m_Box3[i] = nullptr;
						delete(projectiles3[k]);
						projectiles3[k] = nullptr;
					}
				}
			}
		}
		if (projectiles3[k] != nullptr)
		{
			if (Collision::Instance()->Box(projectiles3[k]->GetCollionBox(), bossEnemy->GetCollionBox()))
			{
				if (projectiles3[k]->m_type == 1)
				{
					bossEnemy->Damage(2);
				}
				else if (projectiles3[k]->m_type == 2)
				{
					bossEnemy->Damage(4);
				}
				delete(projectiles3[k]);
				projectiles3[k] = nullptr;
			}
		}
		if (enemyProjectiles3[k] != nullptr)
		{
			if (Collision::Instance()->Box(enemyProjectiles3[k]->GetCollionBox(), my_character3->GetCollionBox()))
			{
				if (enemyProjectiles3[k]->m_type == 1)
				{
					my_character3->Damage(2);
				}
				else if (enemyProjectiles3[k]->m_type == 2)
				{
					my_character3->Damage(4);
				}
				delete(enemyProjectiles3[k]);
				enemyProjectiles3[k] = nullptr;
			}
		}
	}

	//check collision health pick up
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp3[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_healthPickUp3[i]->GetCollionBox()))
			{
				m_healthPickUp3[i]->Collision(my_character3);
				delete(m_healthPickUp3[i]);
				m_healthPickUp3[i] = nullptr;
			}
		}
	}

	//check ammo pick up collision
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp3[i] != nullptr)
		{
			if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_bulletPickUp3[i]->GetCollionBox()))
			{
				m_bulletPickUp3[i]->Collision(my_character3, m_bulletPickUp3[i]->m_type);
				delete(m_bulletPickUp3[i]);
				m_bulletPickUp3[i] = nullptr;
			}
		}
	}

	//check fight box collision
	if (fightBox != nullptr)
	{
		if (Collision::Instance()->Box(my_character3->GetCollionBox(), fightBox->GetCollionBox()))
		{
			MoveLeft(m_renderer, 0.4);

			movingCounter3++;
			if (movingCounter3 == 400)
			{
				//spawn boss
				bossEnemy = new Boss_Enemy(m_renderer, "Images/boss Enemy.png", Vector2D(700, 350), my_character3);
				my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
				delete(fightBox);
				fightBox = nullptr;
				movingCounter3 = 0;
			}
		}
	}

	//chck collision with camera movement
	if (m_camera3 != nullptr)
	{
		if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_camera3->GetCollionBox()))
		{
			if (my_character3->m_moving_right == true)
			{
				my_character3->movementSpeed = 0;

				if (CheckFightActive3() == false)
				{
					//move scene left but not the character 
					MoveLeft(m_renderer, 0.15);
					my_character3->SetPosition(Vector2D(my_character3->GetPosition().x + 0.15, my_character3->GetPosition().y));
				}
			}
			else
			{
				my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}

	if (m_backcamera3 != nullptr)
	{
		if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_backcamera3->GetCollionBox()))
		{
			if (my_character3->m_moving_left == true)
			{
				my_character3->movementSpeed = 0;

				if (CheckFightActive3() == false)
				{
					//move scene left but not the character 
					MoveLeft(m_renderer, 0.15);
					my_character3->SetPosition(Vector2D(my_character3->GetPosition().x + 0.15, my_character3->GetPosition().y));
				}
			}
			else
			{
				my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
			}
		}
	}


	if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_backwall3->GetCollionBox()))
	{
		if (my_character3->m_moving_left == true)
		{
			my_character3->movementSpeed = 0;
		}
		else
		{
			my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	else if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_endwall3->GetCollionBox()))
	{
		if (my_character3->m_moving_right == true)
		{
			my_character3->movementSpeed = 0;
		}
		else
		{
			my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
	else if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_topwall3->GetCollionBox()))
	{
		if (my_character3->m_moving_up == true)
		{
			my_character3->movementSpeed = 0;
		}
		else
		{
			my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}

	else if (Collision::Instance()->Box(my_character3->GetCollionBox(), m_bottomwall3->GetCollionBox()))
	{
		if (my_character3->m_moving_down == true)
		{
			my_character3->movementSpeed = 0;
		}
		else
		{
			my_character3->movementSpeed = PLAYERMOVEMENTSPEED;
		}
	}
}

bool Game_Screen_Level3::SetUpLevel()
{
	backwallposition3 = 0.0f;
	backgorundposition3 = 0.0f;
	endwallposition3 = 1140.0f;

	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		delete(m_healthPickUp3[i]);
		m_healthPickUp3[i] = nullptr;
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		delete(m_bulletPickUp3[i]);
		m_bulletPickUp3[i] = nullptr;
	}
	if (bossEnemy != nullptr)
	{
		delete(bossEnemy);
		bossEnemy = nullptr;
	}
	if (laser != nullptr)
	{
		delete(laser);
		laser = nullptr;
	}

	m_background_texture3 = new Texture2D(m_renderer);
	if (!m_background_texture3->LoadFromFile("Images/Level 3.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_UIportrait3 = new Texture2D(m_renderer);
	if (!m_UIportrait3->LoadFromFile("Images/UI portrait.png"))
	{
		std::cout << "Failed to load UI portrait texture!" << std::endl;
		return false;
	}

	m_pistolBulletUI3 = new Texture2D(m_renderer);
	if (!m_pistolBulletUI3->LoadFromFile("Images/pistol bullet.png"))
	{
		std::cout << "Failed to load UI pistol bullet texture!" << std::endl;
		return false;
	}

	m_scifiBulletUI3 = new Texture2D(m_renderer);
	if (!m_scifiBulletUI3->LoadFromFile("Images/sci-fi bullet.png"))
	{
		std::cout << "Failed to load UI sci-fi bullet texture!" << std::endl;
		return false;
	}

	m_healthBarBackground3 = new Texture2D(m_renderer);
	if (!m_healthBarBackground3->LoadFromFile("Images/Health Bar Background.png"))
	{
		std::cout << "failed to load health bar background texture!" << std::endl;
		return false;
	}

	m_healthBar3 = new Texture2D(m_renderer);
	if (!m_healthBar3->LoadFromFile("Images/Health Bar.png"))
	{
		std::cout << "failed to load health bar texture!" << std::endl;
		return false;
	}

	//make collision boxes to keep player in bounds of screen
	m_backwall3 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(backwallposition3, 0));
	m_endwall3 = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(endwallposition3, 0));
	m_topwall3 = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 205));
	m_bottomwall3 = new Game_Object(m_renderer, "Images/Top Walls.png", Vector2D(0, 415));

	// make charachter model
	my_character3 = new Character(m_renderer, "Images/Character.png", Vector2D(100, 300), game_scene_manager);
	my_character3->PickUpPistol();
	my_character3->PickUpScifi();

	pistolArmRight3 = new Game_Object(m_renderer, "Images/Pistol Arm Right.png", Vector2D(my_character3->GetPosition().x, my_character3->GetPosition().y));
	pistolArmLeft3 = new Game_Object(m_renderer, "Images/Pistol Arm Left.png", Vector2D(my_character3->GetPosition().x, my_character3->GetPosition().y));
	scifiArmLeft3 = new Game_Object(m_renderer, "Images/Sci-fi Arm Left.png", Vector2D(my_character3->GetPosition().x, my_character3->GetPosition().y));
	scifiArmRight3 = new Game_Object(m_renderer, "Images/Sci-fi Arm Right.png", Vector2D(my_character3->GetPosition().x, my_character3->GetPosition().y));

	m_camera3 = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(800 - 48, 0));
	m_backcamera3 = new Game_Object(m_renderer, "Images/Camera Box.png", Vector2D(0, 0));

	m_Box3[0] = new Box(m_renderer, "Images/Box.png", Vector2D(105, 250));
	m_Box3[1] = new Box(m_renderer, "Images/Box.png", Vector2D(250, 250));
	m_Box3[2] = new Box(m_renderer, "Images/Box.png", Vector2D(100, 400));
	m_Box3[3] = new Box(m_renderer, "Images/Box.png", Vector2D(150, 400));
	m_Box3[4] = new Box(m_renderer, "Images/Box.png", Vector2D(300, 400));
	m_Box3[5] = new Box(m_renderer, "Images/Box.png", Vector2D(450, 250));
	m_Box3[6] = new Box(m_renderer, "Images/Box.png", Vector2D(600, 400));
	m_Box3[7] = new Box(m_renderer, "Images/Box.png", Vector2D(900, 400));
	m_Box3[8] = new Box(m_renderer, "Images/Box.png", Vector2D(950, 250));

	m_pistolAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);
	m_scifiAmmoText = new GameText(m_renderer, "fonts/arialbd.ttf", 24);

	fightBox = new Game_Object(m_renderer, "Images/Side Walls.png", Vector2D(250, 0));

	return true;
}

bool CheckFightActive3()
{
	if (bossEnemy != nullptr)
	{
		return true;
	}
	return false;
}

void Game_Screen_Level3::MoveLeft(SDL_Renderer* renderer, float amount)
{
	m_background_texture3->Render(Vector2D(backgorundposition3 -= amount, 0), SDL_FLIP_NONE);
	m_backwall3->SetPosition(Vector2D(backwallposition3 -= amount, 0));
	m_endwall3->SetPosition(Vector2D(endwallposition3 -= amount, 0));
	my_character3->SetPosition(Vector2D(my_character3->GetPosition().x - amount, my_character3->GetPosition().y));
	my_character3->movementSpeed = 0;
	fightBox->SetPosition(Vector2D(fightBox->GetPosition().x - amount, fightBox->GetPosition().y));
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box3[i] != nullptr)
		{
			m_Box3[i]->SetPosition((Vector2D(m_Box3[i]->GetPosition().x - amount, m_Box3[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp3[i] != nullptr)
		{
			m_healthPickUp3[i]->SetPosition((Vector2D(m_healthPickUp3[i]->GetPosition().x - amount, m_healthPickUp3[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp3[i] != nullptr)
		{
			m_bulletPickUp3[i]->SetPosition((Vector2D(m_bulletPickUp3[i]->GetPosition().x - amount, m_bulletPickUp3[i]->GetPosition().y)));
		}
	}
}

void Game_Screen_Level3::MoveRight(SDL_Renderer* renderer, float amount)
{
	m_background_texture3->Render(Vector2D(backgorundposition3 += amount, 0), SDL_FLIP_NONE);
	m_backwall3->SetPosition(Vector2D(backwallposition3 += amount, 0));
	m_endwall3->SetPosition(Vector2D(endwallposition3 += amount, 0));
	my_character3->SetPosition(Vector2D(my_character3->GetPosition().x + amount, my_character3->GetPosition().y));
	my_character3->movementSpeed = 0;
	if (fightBox != nullptr)
	{
		fightBox->SetPosition(Vector2D(fightBox->GetPosition().x + amount, fightBox->GetPosition().y));
	}
	for (int i = 0; i < NUMBOXES; i++)
	{
		if (m_Box3[i] != nullptr)
		{
			m_Box3[i]->SetPosition((Vector2D(m_Box3[i]->GetPosition().x + amount, m_Box3[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMHEALTHPICKUPS; i++)
	{
		if (m_healthPickUp3[i] != nullptr)
		{
			m_healthPickUp3[i]->SetPosition((Vector2D(m_healthPickUp3[i]->GetPosition().x + amount, m_healthPickUp3[i]->GetPosition().y)));
		}
	}
	for (int i = 0; i < NUMAMMOPICKUPS; i++)
	{
		if (m_bulletPickUp3[i] != nullptr)
		{
			m_bulletPickUp3[i]->SetPosition((Vector2D(m_bulletPickUp3[i]->GetPosition().x + amount, m_bulletPickUp3[i]->GetPosition().y)));
		}
	}
}