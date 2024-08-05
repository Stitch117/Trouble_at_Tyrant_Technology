#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class GameText
{
private:
	void Destroy();

	static bool ttfHasInit;
	static bool InitTTF();

	bool errorEncountered = false; 

protected:
	SDL_Texture* texture = nullptr;
	TTF_Font* font = nullptr;
	SDL_Color color{ 255, 255, 255, 255 };
	SDL_Renderer* renderer = nullptr;

public:
	GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize);
	~GameText();

	bool LoadFont(const std::string& fontPath, unsigned int fontSize);

	void RenderAt(const std::string& text, int x, int y);
	void SetColor(SDL_Color color);
};

