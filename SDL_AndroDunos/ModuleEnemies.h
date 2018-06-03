#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_WavingShip.h"
#include "Enemy_HorizontalRocket.h"
#include "Enemy_GreenMiniShip.h"
#include "Enemy_PowerUp.h"
#include "Enemy_MiniMiniBoss.h"
#include "Enemy_Column.h"
#include "Enemy_TinyRedShip.h"
#include "Enemy_BigShip.h"
#include "Enemy_TripleCanon.h"
#include "Enemy_VendingMachine.h"
#include "Enemy_FishShip.h"
#include "Enemy_LongShip.h"




#define MAX_ENEMIES 200

enum ENEMY_TYPES
{
	NO_TYPE,
	WAVINGSHIP,
	WAVINGSHIP2,
	HORIZONTALROCKET,
	HORIZONTALROCKET2,
	HORIZONTALROCKET3,
	POWERUP,
	MINIMINIBOSS,
	MINIGREEN1,
	MINIGREEN2,
	MINIGREEN3,
	COLUMN,
	TINYREDSHIP,
	TINYREDSHIP2,
	BIGSHIP,
	BIGSHIP2,
	BIGSHIP3,
	TRIPLECANON,
	TRIPLECANON2,
	VENDING,
	FISH,
	WATER,
	WATER2,
	LONG

};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	bool drop;

};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool drop = false);

	uint score = 0;

private:

	void SpawnEnemy(const EnemyInfo& info);

public:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
private:
	SDL_Texture* sprites;

	uint big_explosion_fx;
	uint enemy_hit_fx;
};

#endif // __ModuleEnemies_H__