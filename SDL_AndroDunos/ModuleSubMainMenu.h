#ifndef __MODULESUBMAINMENU_H__
#define __MODULESUBMAINMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2point.h"

struct SDL_Texture;

class ModuleSubMainMenu : public Module
{
public:
	ModuleSubMainMenu();
	~ModuleSubMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* logo_andro_tx = nullptr;
	SDL_Texture* visco_games_tx = nullptr;
	SDL_Texture* c1992_tx = nullptr;

	SDL_Rect logo_andro;
	SDL_Rect title_rect;
	SDL_Rect visco_games;
	SDL_Rect c1992;

	SDL_Texture * insert_tx;
	SDL_Rect Insert_Rect;
	Animation insert;
	Animation* animationInsert = nullptr;

	int current_time;
	int init_time;

	//Credit
	int credit = 0;
};

#endif // __MODULESUBMAINMENU_H__
