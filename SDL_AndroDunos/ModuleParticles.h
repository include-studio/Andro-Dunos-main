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
enum COLLIDER_TYPE;
enum OWNER {
	OWNER_PLAYER1,
	OWNER_PLAYER2,
	OWNER_ENEMY
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

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
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
	

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, OWNER owner= OWNER_PLAYER1);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	
	Particle laser_1_1_base;
	Particle laser_1_2_fat;
	Particle laser_2_1_front;
	Particle laser_2_1_back;
	Particle laser_2_4;
	Particle laser_2_3_diagonalu;
	Particle laser_2_3_diagonald;
	Particle laser_3_1_0;
	Particle laser_3_2_diagonalupfront;
	Particle laser_3_2_diagonaldownfront;
	Particle laser_3_3_diagonalupback;
	Particle laser_3_3_diagonaldownback;
	Particle laser_3_4_diagonalupfront;
	Particle laser_3_4_diagonaldownfront;
	Particle laser_3_4_diagonaldownback;
	Particle laser_3_4_diagonalupback;
	Particle laser_4_1_1;
	Particle laser_4_1_2;
	Particle laser_4_2_0;
	Particle laser_4_3_1;
	Particle laser_4_4_1;
	Particle laser_4_4_2;

	Particle mini_explosion;
	Particle big_explosion;
	Particle ring_explosion;
	Particle explosion_player1;
	Particle explosion_player2;

	Particle enemy_blue;
	
};

#endif // __MODULEPARTICLES_H__