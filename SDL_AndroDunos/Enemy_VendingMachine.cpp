#include "Application.h"
#include "Enemy_VendingMachine.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"
#include "Globals.h"
#include "ModulePowerUp.h"
#include "ModuleRender.h"

#define PIXEL 32

Enemy_VendingMachine::Enemy_VendingMachine(int x, int y, bool _drop) : Enemy(x, y)                       //Zig Zag stage 4 to down
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

	life = 4;

	drop = _drop;
}

void Enemy_VendingMachine::OnCollision(Collider* collider) {
	if (drop == true)
		App->powerup->AddPowerUp(App->powerup->bonus, position.x, position.y, COLLIDER_BONUS);

}


void Enemy_VendingMachine::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x , position.y + 15);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}