#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define METERSMOVED 50
#define TIMERETURNIDDLE 10
#define MAX_POWERUP 4

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

	void Shoot();
	void States();

	void OnCollision(Collider*, Collider*);

public:

	PLAYER_STATE_MOVE state;
	int speedMoveShip = 2;

	iPoint position;

	uint score = 0;

	int hp;
	int powerup = 1;
	int type_weapon = 0;
	int part_stagePlayer = 0;

	bool god_mode = false;

private:

	int counterMoved = 0;
	int counterMoved2 = 0;
	int counterReturn = 0;
	int counterReturn2 = 0;

	SDL_Texture* graphics = nullptr;
	Animation ship[5];
	Animation anim_ultimate[5];
	Animation fire[5];
	int current_anim;

	Collider* player_col = nullptr;

	uint fx_laser1, fx_laser2, fx_laser3, fx_laser4, explosion_player, type_change;

	bool ultimate=false;
	bool destroyed = false;
	bool dead = false;
	bool god_mode_die = false;

	int current_time = 0;
	int init_time = 0;

	int font_score = 1;
	char score_text[10];
	
};
#endif