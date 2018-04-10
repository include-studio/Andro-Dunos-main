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

	SDL_Rect ground[5];

	SDL_Rect background;

	SDL_Rect rocks;
	SDL_Rect rocks_entry;
	SDL_Rect rocks_escape;

	SDL_Rect star[7];
	struct starposition {
		int starposy[6]{ SCREEN_HEIGHT * 14 / 100 ,SCREEN_HEIGHT * 18 / 100,SCREEN_HEIGHT * 20 / 100 ,SCREEN_HEIGHT * 21 / 100 ,SCREEN_HEIGHT * 28 / 100,SCREEN_HEIGHT * 42 / 100 };
		int starposx[9]{ 269,261,81,45,54,274,43,SCREEN_WIDTH,58 };
	};
	starposition starpos;

	SDL_Rect planet1;
	SDL_Rect planet2;

	int part_stage = 0;
};

#endif