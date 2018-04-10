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

	Animation SNK;

	Animation NeoGeo;

	Animation* animationSNK = nullptr;
	Animation* animationNeoGeo = nullptr;

};

#endif // __MODULESMAINMENU_H__
