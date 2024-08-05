#include "GameText.h"

//check if the text file has loaded
bool GameText::ttfHasInit = false;

GameText::GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize)
{
	//error check for the text load
	if (!InitTTF())
	{
		std::cerr << "Couldn't initialise ttf; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return;
	}

	this->renderer = renderer;

	//load the font
	this->LoadFont(fontPath, fontSize);
}

GameText::~GameText()
{
	Destroy();	
}

bool GameText::InitTTF()
{
	if (ttfHasInit)
	{
		return true;
	}

	return (TTF_Init() >= 0);
}

bool GameText::LoadFont(const std::string& fontPath, unsigned int fontSize)
{
	this->font = TTF_OpenFont(fontPath.c_str(), fontSize);

	//throw out an error if fon didn't load
	if (!this->font)
	{
		std::cerr << "Couldn't load font from path " << fontPath << "; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return false;
	}

	return true;
}

void GameText::SetColor(SDL_Color color)
{
	this->color = color;
}

void GameText::RenderAt(const std::string& text, int x, int y)
{
	if (errorEncountered)
	{
		return;
	}

	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	//display text to screen
	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);

	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);

	SDL_Rect renderRect{ x,y,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);
}

void GameText::Destroy()
{
	delete(this);
}
