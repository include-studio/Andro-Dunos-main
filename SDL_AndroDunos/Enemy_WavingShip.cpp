#include "Application.h"
#include "Enemy_WavingShip.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL.h"

#include "Globals.h"
#define PI 3.1415

Enemy_WavingShip2::Enemy_WavingShip2(int x, int y, bool _drop) : Enemy(x, y)
{
	fly.PushBack({ 0,  0, 22, 22 });
	fly.PushBack({ 22, 0, 22, 22 });
	fly.PushBack({ 44, 0, 22, 22 });
	fly.PushBack({ 66, 0, 22, 22 });
	fly.PushBack({ 88, 0, 22, 22 });
	fly.PushBack({ 110, 0, 22, 22 });

	fly.PushBack({ 0, 22, 22, 22 });
	fly.PushBack({ 22, 22, 22, 22 });
	fly.PushBack({ 44, 22, 22, 22 });
	fly.PushBack({ 66, 22, 22, 22 });
	fly.PushBack({ 88, 22, 22, 22 });

	fly.speed = 0.4f;

	animation = &fly;

	drop = _drop;

	collider = App->collision->AddCollider({ 0, 0, 22, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_WavingShip2::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 

	if (going_up)
	{
		if (wave > 1.0f)
		{
			going_up = false;
		}
		else
			wave += 0.03f;
	}
	else
	{
		if (wave <= -1.0f)
		{
			going_up = true;

		}
		else
			wave -= 0.03f;
	}

	if (current_time >= 2800) {
		position.y = original_y - int(40.f * sinf(wave+PI));
		position.x += 2;
	}
	else position.y = original_y + int(40.0f * sinf(wave));
	
}

void Enemy_WavingShip2::OnCollision(Collider* collider) {
	if (drop == true)
		App->powerup->AddPowerUp(App->powerup->bonus, position.x, position.y, COLLIDER_BONUS);
		
}




Enemy_WavingShip::Enemy_WavingShip(int x, int y, bool _drop) : Enemy(x, y)
{
	fly.PushBack({ 0,  0, 22, 22 });
	fly.PushBack({ 22, 0, 22, 22 });
	fly.PushBack({ 44, 0, 22, 22 });
	fly.PushBack({ 66, 0, 22, 22 });
	fly.PushBack({ 88, 0, 22, 22 });
	fly.PushBack({ 110, 0, 22, 22 });

	fly.PushBack({ 0, 22, 22, 22 });
	fly.PushBack({ 22, 22, 22, 22 });
	fly.PushBack({ 44, 22, 22, 22 });
	fly.PushBack({ 66, 22, 22, 22 });
	fly.PushBack({ 88, 22, 22, 22 });

	fly.speed = 0.2f;

	animation = &fly;

	drop = _drop;

	collider = App->collision->AddCollider({ 0, 0, 22, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_WavingShip::Move()
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

	position.y = original_y + int(25.0f * sinf(wave));
	position.x -= 1;
}

void Enemy_WavingShip::OnCollision(Collider* collider) {
	if (drop == true)
		App->powerup->AddPowerUp(App->powerup->bonus, position.x, position.y, COLLIDER_BONUS);

}