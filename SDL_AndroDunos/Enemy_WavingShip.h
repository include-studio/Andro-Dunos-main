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
	bool drop;

public:

	Enemy_WavingShip(int x, int y, bool drop);
	void OnCollision(Collider* collider);

	void Move();
};

#endif // __ENEMY_WAVESHIP_H__
