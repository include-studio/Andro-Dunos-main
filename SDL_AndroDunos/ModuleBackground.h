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
	
	SDL_Texture * stars_tx =nullptr;
	SDL_Texture* back_tx = nullptr;
	SDL_Texture* ground_tx = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect rocks;
	SDL_Rect star1;
	SDL_Rect star2;
	SDL_Rect star3;
	SDL_Rect star4;
	SDL_Rect star5;
	SDL_Rect star6;
	SDL_Rect star7;
	int part_stage = 0;
};

#endif