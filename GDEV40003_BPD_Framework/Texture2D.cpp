#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;


// make a 2D texture
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Texture2D::~Texture2D() 
{
	//get rid of old texture
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	m_texture = nullptr;

	//load the image into the texture
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//colour key image
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);

		//show error for failed load
		if (m_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}

		SDL_FreeSurface(p_surface);
	}

	return m_texture != nullptr;
}

void Texture2D::Free()
{
	//check for a texture and remove it
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_height = 0;
		m_width = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, int startX, int startY, Uint32 width, Uint32 height, double angle)
{

	// set renderer location
	if (width == -1)
	{
		SDL_Rect renderLocation = { new_position.x,new_position.y, m_width, m_height };

		SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
	}
	else
	{
		SDL_Rect srcrect = { startX, startY, width, height }; 
		SDL_Rect renderLocation = { new_position.x,new_position.y, width, height }; 
		
		SDL_RenderCopyEx(m_renderer, m_texture, &srcrect, &renderLocation, angle, nullptr, flip);
	}

}
