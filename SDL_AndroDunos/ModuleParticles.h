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
	
	Particle laser1;
	Particle laser1_1;
	Particle laser2_1;
	Particle laser2_2;
	Particle laser2_3;
	Particle laser2_diagonal1;
	Particle laser2_diagonal2;
	Particle laser3;
	Particle laser3_1;
	Particle laser3_2;
	Particle laser3_3;
	Particle laser3_4;
	Particle laser3_5;
	Particle laser3_6;
	Particle laser3_7;
	Particle laser3_8;
	Particle laser4_1;
	Particle laser4_2;
	Particle laser4_3;
	Particle laser4_1_1;
	Particle laser4_2_1;
	Particle laser4_3_1;

	Particle mini_explosion;
	Particle big_explosion;
	Particle ring_explosion;
	Particle explosion_player1;
	Particle explosion_player2;

	Particle enemy_blue;
	
};

#endif // __MODULEPARTICLES_H__