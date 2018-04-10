#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAMEOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * gameover_tx;
	Animation game_over;

	Animation* Animation_game_over = nullptr;

};

#endif // __MODULEGAMEOVER_H__
