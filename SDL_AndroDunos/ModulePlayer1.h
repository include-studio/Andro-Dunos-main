#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define METERSMOVED 50
#define TIMERETURNIDDLE 10

struct SDL_Texture;
struct Collider;

class ModulePlayer1 : public Module
{
public:
	ModulePlayer1();
	~ModulePlayer1();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

public:

	PLAYER_STATE_MOVE state;
	int speedMoveShip = 2;
	Animation *animationShip;

	int counterMoved = 0;
	int counterMoved2 = 0;
	int counterReturn = 0;
	int counterReturn2 = 0;

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation upidle;
	Animation up;
	Animation downidle;
	Animation down;
	iPoint position;
	Collider* player_col = nullptr;

	bool destroyed = false;
	bool god_mode = false;
	int type_weapon = 0;
	uint hp;

	int font_score = 1;
	char score_text[10];
};
#endif