#ifndef __ModuleShieldPlayer2_H__
#define __ModuleShieldPlayer2_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class ModuleShieldPlayer2 :public Module {

public:
	ModuleShieldPlayer2();
	~ModuleShieldPlayer2();

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

	Collider* shield1_col = nullptr;
	Collider* shield2_col = nullptr;

	float rotation = -1.0f;

	int hp = 5;


};
#endif // !__ModuleShieldPlayer2_H__
