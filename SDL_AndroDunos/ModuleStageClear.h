#ifndef __MODULESTAGECLEAR_H__
#define __MODULESTAGECLEAR_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "p2point.h"


struct SDL_Texture;

class ModuleStageClear:public Module {
public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * stage_clear_tx = nullptr;
	SDL_Texture * small_blue_tx = nullptr;

	SDL_Rect small_blue;
	SDL_Rect stage_clear;

	Animation StageClear;
	Animation* animationStageClear = nullptr;

	int part_stageClear = 0;
	int current_time = 0;
	int init_time = 0;

	iPoint positionstage;
	iPoint position_small_blue;
	
};
#endif // !__MODULESTAGECLEAR__H__
