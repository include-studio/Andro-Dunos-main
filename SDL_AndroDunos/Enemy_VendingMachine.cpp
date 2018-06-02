#include "Application.h"
#include "Enemy_VendingMachine.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"
#include "Globals.h"

#define PIXEL 32

Enemy_VendingMachine::Enemy_VendingMachine(int x, int y) : Enemy(x, y)                       //Zig Zag stage 4 to down
{
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 1,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,473,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,473 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,473 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,473 + PIXEL ,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL * 2 ,PIXEL,PIXEL });

	fly.PushBack({ PIXEL * 2,473 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,473 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473 + PIXEL ,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 2,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 1,473,PIXEL,PIXEL });
	fly.PushBack({ PIXEL * 0,473,PIXEL,PIXEL });

	animation = &fly;
	fly.speed = 0.16;

	fly.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 32, 15 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;

	init_time = SDL_GetTicks(); //Timer

	life = 8;
}


