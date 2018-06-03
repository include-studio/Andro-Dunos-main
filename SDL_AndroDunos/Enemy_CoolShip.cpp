#include "Application.h"
#include "Enemy_MiniMiniBoss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL.h"
#include "ModuleStage1.h"
#include "ModuleStage4.h"

#define PIXEL 23
Enemy_CoolShip::Enemy_CoolShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 330 + PIXEL * 0,290,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 1,290,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 2,290,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 3,290,PIXEL,PIXEL });


	fly.PushBack({ 330 + PIXEL * 0,290 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 330 + PIXEL * 1,290 + PIXEL,PIXEL,PIXEL });

	fly.speed = 0.05f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 9 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 0.5;
	init_time = SDL_GetTicks(); //Timer
	current_time = 0;
}

void Enemy_CoolShip::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set time
	if (current_time >= 700 && shoot == false && App->stage4->IsEnabled()) {
		Shoot();
		shoot = true;
	}
	if (going_up)
	{
		if (wave > 10.0f)
			going_up = false;
		else
			wave += 0.07;
	}
	else
	{
		if (wave < -10.0f)
			going_up = true;
		else
			wave -= 0.07f;
	}
	position.y = int(float(original_y) + (10.0f * sinf(wave)));
	position.x -= 1;
}

void Enemy_CoolShip::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);

}