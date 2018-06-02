#ifndef __ENEMY_FISHSHIP_H__
#define __ENEMY_FISHSHIP_H__

#include "Enemy.h"
#include "path.h"


class Enemy_FishShip : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	int original_y = 0;
	Animation up, trans, down;
	ENEMY_TYPES type;

public:

	Enemy_FishShip(int x, int y);


	void Move();
	int current_time;
	int init_time = 0;
};




class Enemy_Water : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	int original_y = 0;
	Animation fly, nothing;

public:

	Enemy_Water(int x, int y);


	void Move();
	int current_time;
	int init_time = 0;
};





class Enemy_Water2: public Enemy
{
private:

	Path path;
	iPoint original_pos;
	int original_y = 0;
	Animation fly, nothing;

public:

	Enemy_Water2(int x, int y);


	void Move();
	int current_time;
	int init_time = 0;
};

#endif // __ENEMY_FISHSHIP_H__
#pragma once