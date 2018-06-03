#ifndef __ENEMY_LONGSHIP_H__
#define __ENEMY_LONGSHIP_H__

#include "Enemy.h"

class Enemy_LongShip : public Enemy
{
private:

	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:
	int current_time;
	int init_time = 0;
	Enemy_LongShip(int x, int y);

	void Move();
};




#endif // __ENEMY_LONGSHIP_H__
#pragma once
