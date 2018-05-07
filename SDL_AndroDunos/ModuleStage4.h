#ifndef __MODULESTAGE4_H__
#define __MODULESTAGE4_H__

#define GROUND4SPEED 1.0f
#define BACKGROUND4SPEED 0.3f

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStage4 :public Module {
public:
	ModuleStage4();
	~ModuleStage4();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture *back_tx = nullptr;
	SDL_Texture *ground_tx = nullptr;

	SDL_Rect back;
	SDL_Rect ground[4];
	SDL_Rect water;

	int stage;


};
#endif // !__MODULESTAGE!_H__
