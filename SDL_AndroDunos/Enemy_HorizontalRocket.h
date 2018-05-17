#ifndef __ENEMY_HORIZONTALROCKET_H__
#define __ENEMY_HORIZONTALROCKET_H__

#include "Enemy.h"

class Enemy_HorizontalRocket : public Enemy
{
private:
	
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_HorizontalRocket(int x, int y);

	void Move();
};




class Enemy_HorizontalRocket2 : public Enemy
{
private:

	
	int original_y = 0;
	Animation fly;

public:

	Enemy_HorizontalRocket2(int x, int y);

	void Move();
	int current_time;
	int init_time = 0;
};

#endif // __ENEMY_HORIZONTALROCKET_H__
