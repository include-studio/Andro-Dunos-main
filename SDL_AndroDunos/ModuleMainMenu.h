#ifndef __MODULESMAINMENU_H__
#define __MODULESMAINMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleMainMenu : public Module
{
	

public:
	ModuleMainMenu();
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * logo_background_tx = nullptr;
	SDL_Texture * logo_andro_tx = nullptr; 
	SDL_Texture * visco_games_tx = nullptr;
	SDL_Texture * press1P_tx = nullptr;
	SDL_Texture * press2P_tx = nullptr;
	SDL_Texture * c1992_tx = nullptr;
	SDL_Texture * num_count_tx = nullptr;


	SDL_Rect logo_background;
	SDL_Rect logo_andro;
	SDL_Rect title_rect;
	SDL_Rect visco_games;
	SDL_Rect c1992;

	Animation Press1P;
	Animation Press2P;
	Animation Num_Count;

	Animation* animationPress1P = nullptr;
	Animation* animationPress2P = nullptr;
	Animation* animationNum_Count = nullptr;

	//Credit
	int credit = 0;
	
};

#endif // __MODULESMAINMENU_H__
