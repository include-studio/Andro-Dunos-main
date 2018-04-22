#ifndef __ENEMY_MINIMINIBOSS_H__
#define __ENEMY_MINIMINIBOSS_H__

#include "Enemy.h"

class Enemy_MiniMiniBoss : public Enemy
{
private:
	Animation fly;
	int original_y = 0;

public:

	Enemy_MiniMiniBoss(int x, int y);
	//void OnCollision(Collider* collider);

	void Move();

	void Shoot();
};

#endif // __ENEMY_MINIMINIBOSS_H__
