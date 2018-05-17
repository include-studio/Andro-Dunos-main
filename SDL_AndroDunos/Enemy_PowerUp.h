#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "Enemy.h"
#include "path.h"


class Enemy_PowerUp : public Enemy
{
private:
	
	Path path;
	iPoint original_pos;
	Animation left, left_down, left_up, right, transition1, transition2, transition3, transition4;

public:

	int part_power_up = 0;
	Enemy_PowerUp(int x, int y);
	void OnCollision(Collider*);
	void Draw(SDL_Texture* sprites);

	void Move();
};

#endif // __ENEMY_POWERUP_H__

