#ifndef __MODULESTAGECLEAR_H__
#define __MODULESTAGECLEAR_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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
	int part_stageClear = 0;
	SDL_Rect stage_clear;
};
#endif // !__MODULESTAGECLEAR__H__
