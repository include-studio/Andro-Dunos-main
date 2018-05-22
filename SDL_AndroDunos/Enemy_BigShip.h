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
	bool shoot = false;

	void Move();
};

#endif // __ENEMY_BIGSHIP_H__
