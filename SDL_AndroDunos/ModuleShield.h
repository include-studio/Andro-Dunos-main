#ifndef __MODULESHIELD_H__
#define __MODULESHIELD_H__

#include "Module.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleShield :public Module {

public: 
	ModuleShield();
	~ModuleShield();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

public:

	iPoint position;
	SDL_Texture* tx_shield = nullptr;


};
#endif // !__MODULESHIELD_H__
