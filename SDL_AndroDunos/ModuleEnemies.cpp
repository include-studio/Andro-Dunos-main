#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_WavingShip.h"
#include "ModulePlayer1.h"
#include "Enemy_HorizontalRocket.h"
#include "Enemy_GreenMiniShip.h"
#include "Enemy_PowerUp.h"
#include "ModulePowerUp.h"
#include "ModulePlayer2.h"
#include "Enemy_MiniMiniBoss.h"
#include "Enemy_Column.h"
#include "Enemy_TinyRedShip.h"
#include "Enemy_BigShip.h"
#include "Enemy_TripleCanon.h"
#include "Enemy_VendingMachine.h"
#include "Enemy_FishShip.h"
#include "Enemy_LongShip.h"
#include "Enemy_CoolShip.h"
#include "Enemy_Boss4.h"

#include "ModuleAudio.h"

#define SPAWN_MARGIN 200

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Assets/Sprites/enemies.png");

	big_explosion_fx = App->audio->Loadfx("Assets/Audio/Enemy_Medium_EXPLOSION.wav");
	enemy_hit_fx = App->audio->Loadfx("Assets/Audio/Enemy_WHITE_SPRITE_Hit.wav");
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
			/*if (queue[i].x > App->render->camera.x)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}*/
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	App->audio->UnLoadFx(big_explosion_fx);
	App->audio->UnLoadFx(enemy_hit_fx);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		queue[i].type = NO_TYPE;
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, bool drop)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].drop = drop;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		
		case ENEMY_TYPES::WAVINGSHIP:
			enemies[i] = new Enemy_WavingShip(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::WAVINGSHIP2:
			enemies[i] = new Enemy_WavingShip2(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::HORIZONTALROCKET:
			enemies[i] = new Enemy_HorizontalRocket(info.x, info.y);
			break;
		case ENEMY_TYPES::HORIZONTALROCKET2:
			enemies[i] = new Enemy_HorizontalRocket2(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::HORIZONTALROCKET3:
			enemies[i] = new Enemy_HorizontalRocket3(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::POWERUP:
			enemies[i] = new Enemy_PowerUp(info.x, info.y);
			break;
		case ENEMY_TYPES::MINIMINIBOSS:
			enemies[i] = new Enemy_MiniMiniBoss(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::MINIGREEN1:
			enemies[i] = new Enemy_GreenMiniShip1(info.x, info.y);
			break;
		case ENEMY_TYPES::MINIGREEN2:
			enemies[i] = new Enemy_GreenMiniShip2(info.x, info.y);
			break;
		case ENEMY_TYPES::MINIGREEN3:
			enemies[i] = new Enemy_GreenMiniShip3(info.x, info.y);
			break;
		case ENEMY_TYPES::COLUMN:
			enemies[i] = new Enemy_Column(info.x, info.y);
			break;
		case ENEMY_TYPES::TINYREDSHIP:
			enemies[i] = new Enemy_TinyRedShip(info.x, info.y);
			break;
		case ENEMY_TYPES::TINYREDSHIP2:
			enemies[i] = new Enemy_TinyRedShip2(info.x, info.y);
			break;
		case ENEMY_TYPES::BIGSHIP:
			enemies[i] = new Enemy_BigShip(info.x, info.y, info.type, info.drop);
			break;
		case ENEMY_TYPES::BIGSHIP2:
			enemies[i] = new Enemy_BigShip2(info.x, info.y, info.type);
			break;
		case ENEMY_TYPES::BIGSHIP3:
			enemies[i] = new Enemy_BigShip3(info.x, info.y, info.type);
			break;
		case ENEMY_TYPES::TRIPLECANON:
			enemies[i] = new Enemy_TripleCanon(info.x, info.y);
			break;
		case ENEMY_TYPES::TRIPLECANON2:
			enemies[i] = new Enemy_TripleCanon2(info.x, info.y);
			break;
		case ENEMY_TYPES::VENDING:
			enemies[i] = new Enemy_VendingMachine(info.x, info.y, info.drop);
			break;
		case ENEMY_TYPES::FISH:
			enemies[i] = new Enemy_FishShip(info.x, info.y);
			break;
		case ENEMY_TYPES::WATER:
			enemies[i] = new Enemy_Water(info.x, info.y);
			break;
		case ENEMY_TYPES::WATER2:
			enemies[i] = new Enemy_Water2(info.x, info.y);
			break;
		case ENEMY_TYPES::LONG:
			enemies[i] = new Enemy_LongShip(info.x, info.y);
			break;
		case ENEMY_TYPES::COOL:
			enemies[i] = new Enemy_CoolShip(info.x, info.y);
			break;
		//case ENEMY_TYPES::BOSS4:
		//	enemies[i] = new Enemy_Boss4(info.x, info.y, info.type);
		//	break;
		//case ENEMY_TYPES::BOSS4_HEAD:
		//	enemies[i] = new Enemy_Boss4Head(info.x, info.y, info.type);
		//	break;
		//case ENEMY_TYPES::BOSS4_LIFT:
		//	enemies[i] = new Enemy_Boss4Lift(info.x, info.y, info.type);
		//	break;
		//case ENEMY_TYPES::BOSS4_ENEMY:
		//	enemies[i] = new Enemy_Boss4Enemy(info.x, info.y,info.type);
		//	break;
		//case ENEMY_TYPES::BOSS4_ARM:
		//	enemies[i] = new Enemy_Boss4Arm(info.x, info.y,info.type);
		//	break;
		}
		
	}	
}


void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (enemies[i]->life > 0) {
				enemies[i]->life -= 0.5f;
				if (App->player1->type_weapon == 3)
					enemies[i]->life --;
				if (App->player2->type_weapon == 3)
					enemies[i]->life --;
				App->audio->PlayFx(enemy_hit_fx);
				break;
			}
			else {
				App->audio->PlayFx(big_explosion_fx);

				App->particles->AddParticle(App->particles->ring_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->big_explosion, enemies[i]->position.x + 15, enemies[i]->position.y + 5, COLLIDER_NONE, 150);
				App->particles->AddParticle(App->particles->ring_explosion, enemies[i]->position.x + 15, enemies[i]->position.y + 15, COLLIDER_NONE, 250);
				App->particles->AddParticle(App->particles->mini_explosion, enemies[i]->position.x, enemies[i]->position.y - 5, COLLIDER_NONE, 350);
				enemies[i]->OnCollision(c1);

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}