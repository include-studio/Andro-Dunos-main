#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* back_tx = nullptr;
	SDL_Texture* ground_tx = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect rocks;
	int part_stage = 0;
};

#endif