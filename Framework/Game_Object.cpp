#include "Game_Object.h"
#include "Texture2D.h"

Game_Object::Game_Object(SDL_Renderer* renderer, string imagepath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	//display an error if not loaded correctly
	if (!m_texture->LoadFromFile(imagepath))
	{
		std::cout << "Failed to load texture!" << std::endl;
	}


}

Game_Object::~Game_Object()
{
	m_renderer = nullptr;
}

void Game_Object::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Game_Object::Update(float deltaTime, SDL_Event e)
{

}

void Game_Object::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Game_Object::GetPosition()
{
	return m_position;
}
