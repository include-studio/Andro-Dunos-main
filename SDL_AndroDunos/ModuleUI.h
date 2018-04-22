#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * user_interface = nullptr;

	SDL_Rect credits_rect;
	SDL_Rect life1_rect;
	SDL_Rect life2_rect;

	Animation gameover;
	Animation* animationGameover = nullptr;

	Animation press1p;
	Animation* animationPress1p = nullptr;

	Animation press2p;
	Animation* animationPress2p = nullptr;

	int font_score = -1;
	char score_text[10];
	int font_score2 = -1;
	char HighScore_text[13];
	int font_credits = -1;
	char credits_text[17];
	bool activate_credit = true;
	bool empty_credit = true;

	uint credit = 0;

	Uint32 score;
	uint high_score = 0;

};

#endif //__MODULEUI_H__
