#ifndef __ENEMY_MINIMINIBOSS_H__
#define __ENEMY_MINIMINIBOSS_H__

#include "Enemy.h"
#include "path.h"

class Enemy_MiniMiniBoss : public Enemy
{
private:

	Path path;
	
	int original_y = 0;
	Animation fly;

public:

	Enemy_MiniMiniBoss(int x, int y);
	//void OnCollision(Collider* collider) override;

	void Move();

	void Shoot();
	/*int shot_limit = 20;
	int shot_actual = 0;*/
	int current_time;
	int init_time = 0;
	bool shoot = 0;

	int hp = 6;
};

#endif // __ENEMY_MINIMINIBOSS_H__
