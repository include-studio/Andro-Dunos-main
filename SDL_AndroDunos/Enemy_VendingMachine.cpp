#include "Application.h"
#include "Enemy_VendingMachine.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"
#include "Globals.h"

#define PIXEL 32

Enemy_VendingMachine::Enemy_VendingMachine(int x, int y) : Enemy(x, y)                       //Zig Zag stage 4 to down
{
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });


	fly.PushBack({ PIXEL * 1,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,433,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,433 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,433 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,433 + PIXEL ,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL * 2 ,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 2,433 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,433 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,433,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,433,PIXEL,PIXEL });

	animation = &fly;
	fly.speed = 0.12;

	fly.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 32, 15 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;

	init_time = SDL_GetTicks(); //Timer

	life = 8;
}

void Enemy_VendingMachine::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set time

	if (current_time >= 500 && current_time <= 750)
	{
		
	}
	

}

