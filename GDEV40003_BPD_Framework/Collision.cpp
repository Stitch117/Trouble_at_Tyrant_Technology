#include "Collision.h"
#include "Character.h"

//initialise  instance to null
Collision* Collision::m_instance = nullptr;

Collision::Collision()
{

}

Collision::~Collision()
{
	m_instance = nullptr;
}

Collision* Collision::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collision;
	}
	return m_instance;
}

bool Collision::Box(Rect2D rect1, Rect2D rect2)
{
	//check for collision on each side 
	if (rect1.x + (rect1.width / 2) > rect2.x &&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}
	return false;	
}
