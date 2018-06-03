//#ifndef __ENEMY_BOSS4_H__
//#define __ENEMY_BOSS4_H__
//
//#include "Enemy.h"
//#include "path.h"
//
//
//typedef unsigned char byte;
//
//class Enemy_Boss4Lift;
//class Enemy_Boss4Head;
//class Enemy_Boss4Enemy;
//class Enemy_Boss4Arm;
//
//class Enemy_Boss4 : public Enemy
//{
//private:
//
//	Path path;
//	iPoint original_pos;
//	Animation wheel;/*Left, Right;*/
//
//
//	Enemy* Lift = nullptr;
//	Enemy* Head = nullptr;
//	Enemy* Enemies = nullptr;
//	//left, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Up-Right, Left, Up-Right, Down, Up-Left, Right, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Up-Right, Down, Right, Left, 
//
//	//void DespawnState1(); //head and enemies
//	//void DespawnHead(); //enemies
//
//public:
//
//	Enemy_Boss4(int x, int y, ENEMY_TYPES type);
//	void OnCollision(Collider*);
//	void Draw(SDL_Texture* sprites);
//
//	int current_time;
//	bool alive = true;
//	//float life_nexus;
//	int init_time = 0;
//
//	byte getLifeUnits() const { return life; }
//
//
//	void Move();
//};
//
//
//
////Arm
//
//class Enemy_Boss4Arm : public Enemy
//{
//private:
//
//	Path path;
//	iPoint original_pos;
//	Animation fire; 
//
//public:
//
//	Enemy_Boss4Arm(int x, int y, ENEMY_TYPES type);
//	//void OnCollision(Collider*);
//	void Draw(SDL_Texture* sprites);
//
//	//byte getLifeUnits() const { return lifeUnits; }
//	//void setLifeUnits(byte life) { lifeUnits = life; }
//
//	int current_time;
//	int init_time = 0;
//
//	void Move();
//	void setLifeUnits(byte lifeUnits) { life = lifeUnits; }
//
//};
//
//
////Head
//
//class Enemy_Boss4Head : public Enemy
//{
//private:
//
//	Path path;
//	iPoint original_pos;
//	Animation open;
//	//byte lifeUnits;
//
//public:
//
//
//	Enemy_Boss4Head(int x, int y, ENEMY_TYPES type);
//	//void OnCollision(Collider*);
//	void Draw(SDL_Texture* sprites);
//
//	int current_time;
//	int init_time = 0;
//
//	void Move();
//	void setLifeUnits(byte lifeUnits) { life = lifeUnits; }
//
//	/*byte getLifeUnits() const { return lifeUnits; }
//	void setLifeUnits(byte life) { lifeUnits = life; }*/
//};
//
////enemy
//
//class Enemy_Boss4Enemy : public Enemy
//{
//private:
//
//	Path path;
//	iPoint original_pos;
//	Animation fly;
//	//byte lifeUnits;
//
//public:
//
//
//	Enemy_Boss4Enemy(int x, int y, ENEMY_TYPES type);
//	//void OnCollision(Collider*);
//	void Draw(SDL_Texture* sprites);
//
//	int current_time;
//	int init_time = 0;
//
//	void Move();
//	void setLifeUnits(byte lifeUnits) { life = lifeUnits; }
//
//	/*byte getLifeUnits() const { return lifeUnits; }
//	void setLifeUnits(byte life) { lifeUnits = life; }*/
//};
//
//#endif // __ENEMY_BOSS4_H__
