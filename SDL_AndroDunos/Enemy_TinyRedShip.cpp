#include "Application.h"
#include "Enemy_TinyRedShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "Globals.h"
#define PIXEL 16

Enemy_TinyRedShip::Enemy_TinyRedShip(int x, int y) : Enemy(x, y)				//1rst path UP to DOWN
{
	left.PushBack({ PIXEL * 0,188,PIXEL,PIXEL });
	left.PushBack({ PIXEL * 1,188,PIXEL,PIXEL });
	left.PushBack({ PIXEL * 2,188,PIXEL,PIXEL });
	right.PushBack({ PIXEL * 3,188,PIXEL,PIXEL });
	right.PushBack({ PIXEL * 4,188,PIXEL,PIXEL });
	right.PushBack({ PIXEL * 5,188,PIXEL,PIXEL });

	right.PushBack({ PIXEL * 0,188 + PIXEL,PIXEL,PIXEL });
	right.PushBack({ PIXEL * 1,188 + PIXEL,PIXEL,PIXEL });
	right_go.PushBack({ PIXEL * 2,188 + PIXEL,PIXEL,PIXEL });
	right_go.PushBack({ PIXEL * 3,188 + PIXEL,PIXEL,PIXEL });
	right_go.PushBack({ PIXEL * 4,188 + PIXEL,PIXEL,PIXEL });
	right_go.PushBack({ PIXEL * 5,188 + PIXEL,PIXEL,PIXEL });

	left.speed = 0.1f;
	right.speed = 0.1f;
	right_go.speed = 0.1f;

	left.loop = false;
	right.loop = false;
	right_go.loop = false;

	animation = &left;
	animation = &right;
	animation = &right_go;

	//Path

	path.PushBack({ -2.0f, +0.3f }, 50, &left);
	path.PushBack({ +2.0f, +0.5f }, 20, &right);
	path.PushBack({ +3.0f, +1.3f }, 5000, &right_go);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	init_time = SDL_GetTicks(); //Timer
}

void Enemy_TinyRedShip::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 
	if (current_time >= 1000 && shoot == false) {
		Shoot();
		shoot = true;

	}


	/*wave -= 0.05f;
	position.y = original_pos.y - int(25.0f * sinf(wave));
	*/


	position.x -= 1;
}

void Enemy_TinyRedShip::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
}
