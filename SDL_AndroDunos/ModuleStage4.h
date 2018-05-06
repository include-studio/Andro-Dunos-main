#ifndef __MODULESTAGE4_H__
#define __MODULESTAGE4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStage4 :public Module {
public:
	ModuleStage4();
	~ModuleStage4();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};
#endif // !__MODULESTAGE!_H__
