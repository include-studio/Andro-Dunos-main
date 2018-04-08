#ifndef __MODULESTAGE2_H__
#define __MODULESTAGE2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStage2 :public Module{
public:
	ModuleStage2();
	~ModuleStage2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture * ground_tx = nullptr;
	SDL_Texture* back_tx = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
};
#endif // !__MODULESTAGE2_H__
