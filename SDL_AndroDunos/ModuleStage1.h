#ifndef __ModuleStage1_H__
#define __ModuleStage1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStage1 : public Module
{
public:
	ModuleStage1();
	~ModuleStage1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture * stars_tx =nullptr;
	SDL_Texture* back_tx = nullptr;
	SDL_Texture* ground_tx = nullptr;

	//SDL_Rect ground;

	SDL_Rect ground1;
	SDL_Rect ground2;
	SDL_Rect ground3;
	SDL_Rect ground4;
	SDL_Rect ground5;

	SDL_Rect background;

	SDL_Rect rocks;
	SDL_Rect rocks_entry;
	SDL_Rect rocks_escape;

	SDL_Rect star1;
	SDL_Rect star2;
	SDL_Rect star3;
	SDL_Rect star4;
	SDL_Rect star5;
	SDL_Rect star6;
	SDL_Rect star7;

	SDL_Rect planet1;
	SDL_Rect planet2;

	int part_stage = 0;
};

#endif