#ifndef __ENEMY_BIGSHIP_H__
#define __ENEMY_BIGSHIP_H__

#include "Enemy.h"
#include "path.h"


class Enemy_BigShip : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	Animation fly, fly2;/*Left, Right, Up_Right, Down, Up_Left;*/
	//left, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Up-Right, Left, Up-Right, Down, Up-Left, Right, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Up-Right, Down, Right, Left, 
public:

	
	Enemy_BigShip(int x, int y);
	void OnCollision(Collider*);
	void Draw(SDL_Texture* sprites);
	void Shoot();
	void Shoot_yellow();
	bool shoot1 = true;
	bool shoot1_sub = false;
	bool shoot2 = false;
	bool shoot3 = false;
	bool shoot3_sub = false;
	bool shoot4 = false;
	bool yellow1 = true;
	bool yellow1_sub = false;
	bool yellow2 = false;
	bool yellow2_sub = false;
	bool yellow3 = false;
	bool yellow3_sub = false;
	bool yellow4 = false;
	bool yellow4_sub = false;
	int current_time;
	int init_time = 0;

	void Move();
};

#endif // __ENEMY_BIGSHIP_H__
