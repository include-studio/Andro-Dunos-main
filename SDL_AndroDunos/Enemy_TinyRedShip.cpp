#include "Application.h"
#include "Enemy_TinyRedShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "Globals.h"
#define PIXEL 16

Enemy_TinyRedShip::Enemy_TinyRedShip(int x, int y) : Enemy(x, y)				//1rst path UP to DOWN
{
	fly.PushBack({ PIXEL * 0,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 3,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 4,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 5,188,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 3,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 4,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 5,188 + PIXEL,PIXEL,PIXEL });

	fly.speed = 0.2f;
	fly.loop = true;
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer

	life = 1;
}

void Enemy_TinyRedShip::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 

	if ( current_time <= 1300) {
		position.y = original_pos.y + int(20.0f * sinf(wave));
		wave -= 0.04f;
		position.x -= 1;
	}
	else position.y += 1;

}

Enemy_TinyRedShip2::Enemy_TinyRedShip2(int x, int y) : Enemy(x, y)				//path DOWN to UP
{
	fly.PushBack({ PIXEL * 0,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 3,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 4,188,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 5,188,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 3,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 4,188 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 5,188 + PIXEL,PIXEL,PIXEL });

	fly.speed = 0.2f;
	fly.loop = true;
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_TinyRedShip2::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 

	if (current_time <= 1300) {
		position.y = original_pos.y + int(20.0f * sinf(-wave));
		wave -= 0.04f;
		position.x -= 1;
	}
	else position.y -= 1;
}
