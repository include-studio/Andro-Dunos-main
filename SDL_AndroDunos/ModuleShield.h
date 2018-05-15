#ifndef __MODULESHIELD_H__
#define __MODULESHIELD_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

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

	iPoint position1;	//shield1
	iPoint position2;	//shield2

private:
	//Animation position of shields
	Animation s1;//rotating
	Animation s2u;//up
	Animation s2d;//down
	Animation s3;//front
	Animation s4;//back
	SDL_Texture* tx_shield = nullptr;


};
#endif // !__MODULESHIELD_H__
