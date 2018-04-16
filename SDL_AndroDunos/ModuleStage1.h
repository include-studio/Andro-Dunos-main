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

	SDL_Rect ground[5];

	SDL_Rect background;

	SDL_Rect rocks;
	SDL_Rect rocks_entry;
	SDL_Rect rocks_escape;

	struct starposition {
		int starposy;
		int starposx;
		float speed;
		SDL_Rect star;
	};
	starposition star[9];
	int starpos[9];

	SDL_Rect planet1;
	SDL_Rect planet2;

	struct camera_limit {
		int xi;
		int xf;
		int yi;
		int yf;
	};
	camera_limit camera_limit;
	int part_stage = 0;
	int ground_cont = 0;
};

#endif