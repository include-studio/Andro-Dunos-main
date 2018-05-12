#ifndef __ENEMY_GREENMINISHIP_H__
#define __ENEMY_GREENMINISHIP_H__

#include "Enemy.h"

class Enemy_GreenMiniShip : public Enemy
{
private:

	
	int original_y = 0;
	Animation fly;

public:

	Enemy_GreenMiniShip(int x, int y);

	void Move();
};

#endif // __ENEMY_GREENMINISHIP_H__
#pragma once
