#ifndef __ENEMY_COLUMN_H__
#define __ENEMY_COLUMN_H__

#include "Enemy.h"

class Enemy_Column : public Enemy
{
private:

	Animation immobil;

	int original_y = 0;

public:

	Enemy_Column(int x, int y);
};

#endif // __ENEMY_COLUMN_H__
#pragma once
