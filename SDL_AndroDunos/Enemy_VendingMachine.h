#ifndef __ENEMY_VENDINGMACHINE_H__
#define __ENEMY_VENDINGMACHINE_H__

#include "Enemy.h"

class Enemy_VendingMachine : public Enemy
{
private:


	int original_y = 0;
	int original_x = 0;

	Animation fly;

public:

	Enemy_VendingMachine(int x, int y);

	
	int current_time;
	int init_time = 0;
};


#endif // __ENEMY_VENDINGMACHINE_H__