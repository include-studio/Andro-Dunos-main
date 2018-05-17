#ifndef __ENEMY_WAVINGSHIP_H__
#define __ENEMY_WAVINGSHIP_H__

#include "Enemy.h"

class Enemy_WavingShip2 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	

	Animation fly;
	bool drop;

public:

	Enemy_WavingShip2(int x, int y, bool drop);
	void OnCollision(Collider* collider);
	void Draw(SDL_Texture* sprites);
	int current_time;
	int init_time = 0;
	

	void Move();
};

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
	void Draw(SDL_Texture* sprites);


	void Move();
};

#endif // __ENEMY_WAVESHIP_H__
