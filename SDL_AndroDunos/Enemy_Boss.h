#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "path.h"

class Fire_Gun;

class Enemy_Boss :public Enemy {
	Path path;
	iPoint original_pos;
	Animation anim;

	int init_time = 0;
	int time = 0;
	Fire_Gun* fire = nullptr;

public:
	Enemy_Boss(int x, int y);
	void OnCollision(Collider*);
	void Draw(SDL_Texture* sprites);
	//void Fire();
	void Dispend();
	void Move();

};

class Fire_Gun {
public:
	iPoint pos;
	Animation anim;

public:
	Fire_Gun(int,int);
	void Position();
	void Shoot();

};

class Enemy_Boss_Destroyed:public Enemy {
	Path path;
	iPoint original_pos;
	Animation anim;

	int init_time = 0;
	int time = 0;

public:
	Enemy_Boss_Destroyed(int x, int y);
	void OnCollision(Collider*);
	void Draw(SDL_Texture* sprites);
	//void Shoot();
	void Move();
};

class Enemy_Boss_Dispend :public Enemy {

};
#endif // !__ENEMY_BOSS_H__
