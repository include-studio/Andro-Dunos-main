#include "Application.h"
#include "Enemy_FishShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "Globals.h"

#define PIXEL 16

Enemy_FishShip::Enemy_FishShip(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	up.PushBack({ 105,483,16,16 });
	
	trans.PushBack({ 105 + PIXEL,483,16,16 });
	trans.PushBack({ 105 + PIXEL * 2,483,16,16 });
	trans.PushBack({ 105 + PIXEL * 3,483,16,16 });

	down.PushBack({ 105 + PIXEL * 4,483,16,16 });


	

	up.loop = false;
	trans.loop = false;
	down.loop = false;

	

	//Path

	path.PushBack({ 0, 0 }, 120, &up);
	path.PushBack({ 0, -2.0f }, 70, &up);
	path.PushBack({ 0, -2.f }, 20, &trans);
	path.PushBack({ 0, 2.f }, 20, &trans);
	path.PushBack({ 0, 2 }, 100, &down);


	path.PushBack({ -10.0f, 0 }, 5000, &down);//getting out

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_FishShip::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 

}