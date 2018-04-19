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
	/*bool CleanUp(); //textures*/

public:

	int font_score = -1;
	char score_text[10];
	int font_score2 = -1;
	char coins_text[10];

	uint coins = 0;

	Uint32 score;
	uint high_score = 0;

};

#endif //__MODULEUI_H__
