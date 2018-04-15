#ifndef __MODULESNEOGEO_H__
#define __MODULESNEOGEO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleNeoGeo : public Module
{
public:
	ModuleNeoGeo();
	~ModuleNeoGeo();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * neogeo;
	SDL_Texture * snk;
	SDL_Texture * machine;

	SDL_Rect copyright;
	SDL_Rect white;
	SDL_Rect black;

	Animation SNK;
	Animation NeoGeo;
	Animation Machine1;
	Animation Machine2;

	Animation* animationSNK = nullptr;
	Animation* animationNeoGeo = nullptr;
	Animation* animationMachine1 = nullptr;
	Animation* animationMachine2 = nullptr;

	int W_alph;
	int current_time = 0;
	int init_time = 0;
	bool music_pasued = false;
	
};

#endif // __MODULESMAINMENU_H__
