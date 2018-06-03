#ifndef __ENEMY_COOLSHIP_H__
#define __ENEMY_COOLSHIP_H__

#include "Enemy.h"

class Enemy_CoolShip : public Enemy
{
private:

	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_CoolShip(int x, int y);
	void Shoot();
	void Move();
	int current_time;
	int init_time = 0;
	bool shoot = false;
};


#endif // __ENEMY_COOLSHIP_H__
#pragma once
