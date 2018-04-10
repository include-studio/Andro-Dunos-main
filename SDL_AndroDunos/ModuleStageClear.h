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

	/*Animation StageClear;

	Animation* animationStageClear = nullptr;*/

	int part_stageClear = 0;
	
	iPoint positionstage;

	SDL_Rect stage_clear;
};
#endif // !__MODULESTAGECLEAR__H__
