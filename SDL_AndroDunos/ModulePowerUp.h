#ifndef __MODULEPOWERUP_H__
#define __MODULEPPOWERUP_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_ITEMS 10

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Item
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;

	Item();
	Item(const Item& p);
	~Item();
	bool Update();
};

class ModulePowerUp : public Module
{
public:
	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddPowerUp(const Item& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Item* active[MAX_ACTIVE_ITEMS];

public:
	Item bonus;
	Item powerup_S;
};

#endif // __MODULEPARTICLES_H__