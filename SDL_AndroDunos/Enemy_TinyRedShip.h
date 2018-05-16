#ifndef __ENEMY_TINYREDSHIP_H__
#define __ENEMY_TINYREDSHIP_H__

#include "Enemy.h"
#include "path.h"


class Enemy_TinyRedShip : public Enemy
{
private:
	float wave = 1.0f;
	int original_y = 0;
	int original_x = 0;

	Path path;
	iPoint original_pos;
	Animation left, right, right_go;

public:

	Enemy_TinyRedShip(int x, int y);
	void Shoot();
	bool shoot = 0;
	void Move();
	int current_time;
	int init_time = 0;
};

#endif // __ENEMY_TINYREDSHIP_H__
#pragma once