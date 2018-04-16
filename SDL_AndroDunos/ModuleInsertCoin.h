#ifndef __MODULEINSERTCOIN_H__
#define __MODULEINSERTCOIN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2point.h"

struct SDL_Texture;

class ModuleInsertCoin : public Module
{
public:
	ModuleInsertCoin();
	~ModuleInsertCoin();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * insert_tx;

	SDL_Rect Insert_Rect;
	SDL_Rect white;
	SDL_Rect black;

	Animation insert;
	
	Animation* animationInsert = nullptr;
	

	int current_time;
	int init_time;

	int W_alph;
	//Credit
	int credit = 0;
};

#endif // __MODULEINSERTCOIN_H__
