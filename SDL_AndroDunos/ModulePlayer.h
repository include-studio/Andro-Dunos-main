#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation upidle;
	Animation up;
	Animation downidle;
	Animation down;
	iPoint position;

	Animation* flames_animation;

	float movVertical;	// Counter for the vertical movement of the ship
	int maxVertical;	// Limit of the counter
};

#endif