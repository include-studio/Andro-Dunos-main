#ifndef __ENEMY_TINYREDSHIP_H__
#define __ENEMY_TINYREDSHIP_H__

#include "Enemy.h"

class Enemy_TinyRedShip : public Enemy					//1rst path UP to DOWN
{
private:
	float wave = 1.0f;
	int original_y = 0;
	int original_x = 0;
	
	iPoint original_pos;
	Animation fly;

public:

	Enemy_TinyRedShip(int x, int y);
	int current_time;
	int init_time = 0;
	void Move();
};

class Enemy_TinyRedShip2 : public Enemy					//path DOWN to UP
{
private:

	float wave = 1.0f;
	int original_y = 0;
	int original_x = 0;
	
	iPoint original_pos;
	Animation fly;
	
public:

	Enemy_TinyRedShip2(int x, int y);
	int current_time;
	int init_time = 0;
	void Move();
};

#endif // __ENEMY_TINYREDSHIP_H__
#pragma once