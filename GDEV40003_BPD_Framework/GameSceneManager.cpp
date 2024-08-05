#include "GameSceneManager.h"
#include "Game_Screen.h"
#include "Game_Screen_Level1.h"
#include "Game_Screen_Level2.h"
#include "Game_Screen_Level3.h"
#include "Game_Screen_Lose.h"
#include "Game_Screen_Win.h"
#include "Main_Menu.h"

GameSceneManager::GameSceneManager(SDL_Renderer* renderer, SCREENS startscreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;

	//call function to swap screen
	ChangeScreen(startscreen);
}

GameSceneManager::~GameSceneManager()
{
	m_renderer = nullptr;
	delete(m_current_screen);
	m_current_screen = nullptr;
}

void GameSceneManager::Render()
{
	m_current_screen->Render();
}

void GameSceneManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

int GameSceneManager::GetCurrentScreen() const
{
	return ScreenIndex;
}

void GameSceneManager::ChangeScreen(SCREENS new_screen)
{
	//clear old screen
	if (m_current_screen != nullptr)
	{
		delete(m_current_screen);
		m_current_screen = nullptr;
	}
	
	
	Main_Menu* mainTempScreen;
	Game_Screen_Level1* oneTempScreen;
	Game_Screen_Level2* twoTempScreen;
	Game_Screen_Level3* threeTempScreen;
	Game_Screen_Win* winTempScreen;
	Game_Screen_Lose* loseTempScreen;

	//switch into new screen by making  atemp of the new screen and then changing them
	switch (new_screen)
	{
	case SCREEN_MENU:
		mainTempScreen = new Main_Menu(m_renderer, this);
		m_current_screen = (Game_Screen*)mainTempScreen;
		ScreenIndex = SCREEN_MENU;
		mainTempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		oneTempScreen = new Game_Screen_Level1(m_renderer, this);

		m_current_screen = (Game_Screen*)oneTempScreen;
		ScreenIndex = SCREEN_LEVEL1;
		oneTempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		twoTempScreen = new Game_Screen_Level2(m_renderer, this);
		m_current_screen = (Game_Screen*)twoTempScreen;
		ScreenIndex = SCREEN_LEVEL2;
		twoTempScreen = nullptr;
		break;
	case SCREEN_BOSSLEVEL:
		threeTempScreen = new Game_Screen_Level3(m_renderer, this);
		m_current_screen = (Game_Screen*)threeTempScreen;
		ScreenIndex = SCREEN_BOSSLEVEL;
		threeTempScreen = nullptr;
		break;
	case SCREEN_WINPAGE:
		winTempScreen = new Game_Screen_Win(m_renderer, this);
		m_current_screen = (Game_Screen*)winTempScreen;
		ScreenIndex = SCREEN_WINPAGE;
		winTempScreen = nullptr;
		break;
	case SCREEN_LOSEPAGE:
		loseTempScreen = new Game_Screen_Lose(m_renderer, this);
		m_current_screen = (Game_Screen*)loseTempScreen;
		ScreenIndex = SCREEN_LOSEPAGE;
		loseTempScreen = nullptr;
		break;
	default:;
	}
}