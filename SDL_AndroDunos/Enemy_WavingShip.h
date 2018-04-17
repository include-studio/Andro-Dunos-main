#ifndef __ENEMY_WAVINGSHIP_H__
#define __ENEMY_WAVINGSHIP_H__

#include "Enemy.h"

class Enemy_WavingShip : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_WavingShip(int x, int y);

	void Move();
};

#endif // __ENEMY_REDBIRD_H__
