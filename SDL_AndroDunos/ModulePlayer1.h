#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define METERSMOVED 50
#define TIMERETURNIDDLE 10
#define MAX_POWERUP 7

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
	void BombandMissile();
	void Ultimate();
	void States();

	void OnCollision(Collider*, Collider*);

public:

	PLAYER_STATE_MOVE state;
	int speedMoveShip = 2;

	iPoint position;

	uint score = 0;

	int hp;
	int powerup_s = 1;
	int powerup_b = 0;
	int powerup_m = 0;
	int powerup_u = 0;
	int type_weapon = 0;
	int part_stagePlayer = 0;

	bool god_mode = false;
	bool charge = false;
	bool charged = false;
	bool hp_down = false;

public:
	uint ultimate_charged_fx;

private:

	int time_bomb = 0;
	int counterMoved = 0;
	int counterMoved2 = 0;
	int counterReturn = 0;
	int counterReturn2 = 0;

	SDL_Texture* graphics = nullptr;
	Animation ship[5];
	Animation anim_ultimate[5];
	Animation fire[5];
	int current_anim;
	bool blink;

	Collider* player_col = nullptr;

	uint fx_laser1, fx_laser2, fx_laser3, fx_laser4, explosion_player, type_change_fx, ultimate_charge_fx;

	bool destroyed = false;
	bool dead = false;
	bool god_mode_die = false;

	int current_time = 0;
	int init_time = 0;
	
};
#endif