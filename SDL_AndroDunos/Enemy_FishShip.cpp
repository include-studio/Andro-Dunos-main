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


	trans.speed = 0.07;
	down.speed = 1;
	up.loop = false;
	trans.loop = false;
	down.loop = false;

	

	//Path

	path.PushBack({ 0, 0 }, 120, &up);
	path.PushBack({ 1, -2.0f }, 70, &up);

	path.PushBack({ 1, -1.f }, 20, &trans);
	path.PushBack({ 1, -0.5f }, 30, &trans);
	//path.PushBack({ 0, 0.5f }, 0, &trans);
	path.PushBack({ 1, 0.5f }, 20, &down);
	path.PushBack({ 1, 1 }, 20, &down);
	path.PushBack({ 1, 2 }, 100, &down);


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






//
//
//Enemy_Water::Enemy_Water(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
//{
//	up.PushBack({ 105,483,16,16 });
//
//	trans.PushBack({ 105 + PIXEL,483,16,16 });
//	trans.PushBack({ 105 + PIXEL * 2,483,16,16 });
//	trans.PushBack({ 105 + PIXEL * 3,483,16,16 });
//
//	down.PushBack({ 105 + PIXEL * 4,483,16,16 });
//
//
//	trans.speed = 0.07;
//	down.speed = 1;
//	up.loop = false;
//	trans.loop = false;
//	down.loop = false;
//
//
//
//	//Path
//
//	path.PushBack({ 0, 0 }, 120, &up);
//	path.PushBack({ 1, -2.0f }, 70, &up);
//
//	path.PushBack({ 1, -1.f }, 20, &trans);
//	path.PushBack({ 1, -0.5f }, 30, &trans);
//	//path.PushBack({ 0, 0.5f }, 0, &trans);
//	path.PushBack({ 1, 0.5f }, 20, &down);
//	path.PushBack({ 1, 1 }, 20, &down);
//	path.PushBack({ 1, 2 }, 100, &down);
//
//
//	path.PushBack({ -10.0f, 0 }, 5000, &down);//getting out
//
//	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
//
//	original_pos.x = x;
//	original_pos.y = y;
//	init_time = SDL_GetTicks(); //Timer
//}
//
//void Enemy_Water::Move()
//{
//	position = original_pos + path.GetCurrentSpeed(&animation);
//	current_time = SDL_GetTicks() - init_time; //Set Time 
//
//}