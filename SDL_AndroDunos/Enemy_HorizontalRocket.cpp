#include "Application.h"
#include "Enemy_HorizontalRocket.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"
#include "Globals.h"


Enemy_HorizontalRocket::Enemy_HorizontalRocket(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 30,50,30,30 }); 
	fly.PushBack({ 0,50,30,30 }); 
	fly.PushBack({ 90,50,30,30 }); 
	fly.PushBack({ 0,50,30,30 }); 
	fly.PushBack({ 30,50,30,30 }); 
	fly.PushBack({ 60,50,30,30 }); 

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 13 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 1;
}

void Enemy_HorizontalRocket::Move()
{

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}
	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 1;
}






Enemy_HorizontalRocket2::Enemy_HorizontalRocket2(int x, int y) : Enemy(x, y)                       //Zig Zag stage 4 to down
{
	fly.PushBack({ 30,50,30,30 });

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 13 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_HorizontalRocket2::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set time

	if (current_time <= 500) position.x -= 2;
	else if (current_time >= 500 && current_time <= 750)
	{
		position.x += 3;
		position.y += 2;
	}
	else position.x -= 3;

}






Enemy_HorizontalRocket3::Enemy_HorizontalRocket3(int x, int y) : Enemy(x, y)             //Zig Zag stage 4 to up
{
	fly.PushBack({ 30,50,30,30 });

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 13 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_HorizontalRocket3::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set time

	if (current_time <= 500) position.x -= 2;
	else if (current_time >= 500 && current_time <= 750)
	{
		position.x += 3;
		position.y -= 2;
	}
	else position.x -= 3;
	
}