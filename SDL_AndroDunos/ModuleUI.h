#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class ModuleUI : public Module
{
	int current_time1 = 0;
	int init_time1 = 0;
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
	SDL_Rect miniCoundown_rect;
	SDL_Rect gameover_rect;

	Animation miniContinueNum;
	Animation* animationMiniContinueNum = nullptr;

	Animation press1p;
	Animation* animationPress1p = nullptr;

	Animation press2p;
	Animation* animationPress2p = nullptr;

	Animation insertCoin;
	Animation* animationInsertCoin = nullptr;

	int font_score1 = 1;
	char score1_text[10];

	int font_score2 = -1;
	char score2_text[10];

	int font_highscore = -1;
	char HighScore_text[13];

	int font_credits = -1;
	char credits_text[17];

	bool activate_credit = true;
	bool empty_credit = true;
	bool credit_on = true;

	bool game_over_time = true;


	uint credit = 0;
	uint credit_fx;

	uint score1 = 0;
	uint score2 = 0;
	uint high_score = 0;

	
};

#endif //__MODULEUI_H__
