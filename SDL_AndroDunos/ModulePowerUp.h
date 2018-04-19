#ifndef __MODULEPOWERUP_H__
#define __MODULEPOWERUP_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_ITEM 5

struct SDL_Texture;
struct Item {
	Animation anim;
	uint fx = 0;
	iPoint position;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;
};
class ModulePowerUp :public Module {
public:
	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	//update_status Update();
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);

	//void AddItem(const Item& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Item* active[MAX_ACTIVE_ITEM];

public:
	Item BonusB;
	Item life;
	Item gun;

};
#endif // !__MODULEPOWERUP_H__
