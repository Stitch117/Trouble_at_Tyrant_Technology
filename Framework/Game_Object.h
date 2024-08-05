#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;

class Texture2D;

class Game_Object
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	Vector2D m_position;
	Texture2D* m_texture = nullptr;

public:
	Game_Object(SDL_Renderer* renderer, string imagepath, Vector2D start_position);
	~Game_Object();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	Rect2D GetCollionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
};

