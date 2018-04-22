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

#endif // __ENEMY_HORIZONTALROCKET_H__
