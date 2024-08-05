#include "Box.h"
#include "constants.h"
#include "Texture2D.h"

Box::Box(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition) :
	Game_Object(renderer, imagepath, startPosition) 
{

}

Box::~Box()
{

}

void Box::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Box::Update(float deltaTime, SDL_Event e)
{

}

void Box::Damage(int damage)
{
	health -= damage;
}

int Box::Death()
{
	srand((unsigned) time(NULL)* 400); //set seed of rand to the current timestamp
	float i = rand() % 6;

	//return an integer that will correspong to a specific pick up being dropped
	if (i == 5)
	{
		return 3;
	}
	else if (i == 3 || i == 4)
	{
		return 2;
	}
	else if (i == 1 || i == 2)
	{
		return 1;
	}
	
	return 0;
}