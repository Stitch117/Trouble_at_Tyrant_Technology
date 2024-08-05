#pragma once
#ifndef _TEXTURED2D_H
#define _TEXTURED2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D
{
private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_width;
	int m_height;


public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, int startX = 0, int startY = 0, Uint32 width = -1, Uint32 height = 0, double angle = 0.0);

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
};

#endif //_TEXTURED2D_H	

