#ifndef __ENEMY_BIGSHIP_H__
#define __ENEMY_BIGSHIP_H__

#include "Enemy.h"
#include "path.h"


typedef unsigned char byte;

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
	bool alive = true;
	//float life_nexus;
	int init_time = 0;

	Enemy* wing1;
	Enemy* wing2;
	
	byte getLifeUnits() const { return life; }


	void Move();
};



//Wing1

class Enemy_BigShip2 : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	Animation fly;
	//byte lifeUnits;
public:

	Enemy_BigShip2(int x, int y);
	//void OnCollision(Collider*);
	int WingUp() { return original_pos.y -=2;  }
	int WingDown() { return original_pos.y += 2; }
	void Draw(SDL_Texture* sprites);
	
	bool open_wing1 = true;
	bool open_wing2 = false;
	bool open_wing3 = false;
	bool open_wing4 = false;
	bool open_wing5 = false;

	//byte getLifeUnits() const { return lifeUnits; }
	//void setLifeUnits(byte life) { lifeUnits = life; }

	int current_time;
	int init_time = 0;

	void Move();
	void setLifeUnits(byte lifeUnits) { life = lifeUnits; }

};


//Wing2

class Enemy_BigShip3 : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	Animation fly;
	//byte lifeUnits;

public:


	Enemy_BigShip3(int x, int y);
	//void OnCollision(Collider*);
	void Draw(SDL_Texture* sprites);
	int WingUp() { return original_pos.y -= 2; }
	int WingDown() { return original_pos.y += 2; }

	int current_time;
	int init_time = 0;

	void Move();
	void setLifeUnits(byte lifeUnits) { life = lifeUnits; }

	/*byte getLifeUnits() const { return lifeUnits; }
	void setLifeUnits(byte life) { lifeUnits = life; }*/
};


//void DespawnAllWings(Enemy_BigShip& b,  Enemy_BigShip2& w1,  Enemy_BigShip3& w2) {
//	w1.setLifeUnits(0);
//	w2.setLifeUnits(0);
//}
#endif // __ENEMY_BIGSHIP_H__

