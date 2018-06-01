#ifndef __ENEMY_TRIPLECANON_H__
#define __ENEMY_TRIPLECANON_H__

#include "Enemy.h"
#include "path.h"

class Enemy_TripleCanon : public Enemy
{
private:

	Path path;

	int original_y = 0;
	int original_x = 0;
	Animation fly;

public:

	Enemy_TripleCanon(int x, int y);
	void OnCollision(Collider* collider) override;

	void Move();

	void Shoot();
	/*int shot_limit = 20;
	int shot_actual = 0;*/
	int current_time;
	int init_time = 0;
	bool shoot = false;
	float rotation;


	int hp = 6;
};

#endif // __ENEMY_TRIPLECANON_H__
#pragma once
