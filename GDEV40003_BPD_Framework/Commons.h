#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}

};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;


	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

enum SCREENS
{
	SCREEN_MENU,
	SCREEN_INTRO,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_BOSSLEVEL,
	SCREEN_LOSEPAGE,
	SCREEN_WINPAGE
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

