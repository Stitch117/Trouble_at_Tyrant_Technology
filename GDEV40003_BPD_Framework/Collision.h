#pragma once
#include "Commons.h"
#include "Game_Object.h"

class Character;
class Collision
{
private:
	Collision();

	static Collision* m_instance;

public:
	~Collision();

	static Collision* Instance();

	bool Box(Rect2D rect1, Rect2D rect2);
};

	