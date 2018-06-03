#include "Application.h"
#include "Enemy_LongShip.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"
#include "Globals.h"

#define PIXEL 24

Enemy_LongShip::Enemy_LongShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 330 + PIXEL * 0,266,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 1,266,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 2,266,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 3,266,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 4,266,PIXEL,PIXEL });

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 5 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 1;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_LongShip::Move()
{

	current_time = SDL_GetTicks() - init_time; //Set time

	if (current_time < 1000) position.x -= 1;
	else if (current_time >= 1000 && current_time <= 1400)
	{
		position.x += 2;
		position.y -= 1;
	}
	else position.x -= 4;
}


