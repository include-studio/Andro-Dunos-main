#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 200

struct SDL_Texture;
struct Collider;
struct Enemy;
enum COLLIDER_TYPE;
enum OWNER {
	OWNER_PLAYER1,
	OWNER_PLAYER2,
	OWNER_ENEMY
};
enum ID {
	NONIMPORTANT,
	BOMB,
	BOMB_DELAY
};

struct Particle
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;
	OWNER owner_type;
	int hp = 1;
	ID id;
	int follow;
	Enemy* targetE = nullptr;


	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
	Enemy* FindE(iPoint pos);
	iPoint ShootPl(iPoint pos);
	bool blue_followDown = false;
	bool blue_followUp = false;
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, OWNER owner= OWNER_PLAYER1, ID id=NONIMPORTANT);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	
	Particle laser_1_1_base;
	Particle laser_1_2_fat;
	Particle laser_1_6;
	
	Particle laser_2_1_front;
	Particle laser_2_1_back;
	Particle laser_2_4;
	Particle laser_2_7_fat;
	Particle laser_2_3_diagonalu;
	Particle laser_2_3_diagonald;
	Particle laser_2_3_diagonaluthin;
	Particle laser_2_3_diagonaldthin;
	
	Particle laser_3_1_0;
	Particle laser_3_2_diagonalupfront;
	Particle laser_3_2_diagonaldownfront;
	Particle laser_3_3_diagonalupback;
	Particle laser_3_3_diagonaldownback;
	Particle laser_3_4_diagonalupfront;
	Particle laser_3_4_diagonaldownfront;
	Particle laser_3_4_diagonaldownback;
	Particle laser_3_4_diagonalupback;
	Particle laser_3_5_diagonalupfront;
	Particle laser_3_5_diagonaldownfront;
	Particle laser_3_5_diagonaldownback;
	Particle laser_3_5_diagonalupback;
	Particle laser_3_6_diagonalupfront;
	Particle laser_3_6_diagonaldownfront;
	Particle laser_3_6_diagonaldownback;
	Particle laser_3_6_diagonalupback;
	Particle laser_3_7_diagonalupfront;
	Particle laser_3_7_diagonaldownfront;
	Particle laser_3_7_diagonaldownback;
	Particle laser_3_7_diagonalupback;

	Particle laser_4_1_1;
	Particle laser_4_1_2;
	Particle laser_4_2_0;
	Particle laser_4_3_1;
	Particle laser_4_4_1;
	Particle laser_4_4_2;
	Particle laser_4_5_1;
	Particle laser_4_5_2;
	Particle laser_4_6;
	Particle laser_4_7_1;
	Particle laser_4_7_2;

	Particle bomb_1_1;
	Particle bomb_1_2;
	Particle bomb_2_1;
	Particle bomb_2_2;
	Particle bomb_2_3;
	Particle bomb_2_4;
	Particle bomb_3_1;
	Particle bomb_3_2;
	Particle bomb_3_3;
	Particle bomb_3_4;
	Particle bomb_4_1;
	Particle bomb_4_2;
	Particle bomb_4_3;
	Particle bomb_4_4;

	Particle missile;
	Particle missile2;

	Particle mini_explosion;
	Particle big_explosion;
	Particle ring_explosion;
	Particle explosion_player1;
	Particle explosion_player2;

	Particle enemy_blue;
	Particle enemy_blue_up;
	Particle enemy_blue_down;

	Particle enemy_yellow_laser;

	Particle enemy_blue_laser;
	
};

#endif // __MODULEPARTICLES_H__