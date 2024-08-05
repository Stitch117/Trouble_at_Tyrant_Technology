#include "SDL.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "constants.h"
#include "Texture2D.h"	
#include "Commons.h"
#include "GameSceneManager.h"
#include <iostream>

using namespace std;

//Global Variables:
GameSceneManager* game_screen_manager = nullptr;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

float windowPosX = 100;
float windowPosY = 100;

//function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* argv[])
{
	if (InitSDL())
	{
		//intialise everything
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0)
		{
			cout << "SDL could not inititait! SDL error: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			bool quit = false;
			//load Main Menu
			game_screen_manager = new GameSceneManager(g_renderer, SCREEN_MENU); //load main menu first
			// set the time
			g_old_time = SDL_GetTicks();

			SDL_JoystickOpen(1);

			while (!quit)
			{
				Render();
				quit = Update();

			}
		}
	}

	CloseSDL();

	return 0;
}

// set up SDL
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL did not initiate. Error:" << SDL_GetError();
		return false;
	}
	else
	{
		// setup passed, create the window
		g_window = SDL_CreateWindow("Game Engine creation window",
			windowPosX,
			windowPosY,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//create renderer
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			// load the PNG
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initiate. Error: " << IMG_GetError();
				return false;
			}
		}
		else 
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
		} 


		// check the window was made
		if (g_window == nullptr)
		{
			// the window did not initiate
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}



void CloseSDL() 
{
	// release the window
	SDL_DestroyWindow(g_window);

	g_window = nullptr;

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release the texture
	delete g_texture;
	g_texture = nullptr;

	// clear scene manager level
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//quit the program
	SDL_Quit();
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	//event handler
	SDL_Event e;

	//get event recieved
	SDL_PollEvent(&e);

	//handle for events:
	switch (e.type)
	{
		// press the X to quit
	case SDL_QUIT:
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}

//render an image
void Render()
{
	//clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);
}

