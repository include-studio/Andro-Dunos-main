#ifndef __MODULESTAGE4_H__
#define __MODULESTAGE4_H__

#define GROUND4SPEED 1.0f
#define BACKGROUND4SPEED 0.3f

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2point.h"


struct SDL_Texture;

class ModuleStage4 :public Module {
public:
	ModuleStage4();
	~ModuleStage4();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	
	SDL_Texture *back_tx = nullptr;
	SDL_Texture *ground_tx = nullptr;
	SDL_Texture *backlight_tx = nullptr;

	SDL_Rect back;
	SDL_Rect ground[4];
	SDL_Rect water_rect;
	SDL_Rect groundColumn;

	iPoint positionGroundColumn;

	Animation water;
	Animation* animation_water = nullptr;
	Animation backlight;
	bool light = false;

	int stage;
	int time_music = 0;
	int time_backAnim = 0;
	int time_preAnim = 0;
	int init_time = 0;
	bool intro_bgm = true;

	};

#endif // !__MODULESTAGE4!_H__
