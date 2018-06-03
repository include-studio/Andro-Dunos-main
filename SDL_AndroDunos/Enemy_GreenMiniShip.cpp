#include "Application.h"
#include "Enemy_GreenMiniShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "Globals.h"


Enemy_GreenMiniShip1::Enemy_GreenMiniShip1(int x, int y) : Enemy(x, y)				//1rst path UP to DOWN
{
	left.PushBack({ 0,165,16,16 });
	right.PushBack({ 16,165,16,16 });
	right.PushBack({ 16*2,165,16,16 });
	right.PushBack({ 16*3,165,16,16 });
	right.PushBack({ 16*4,165,16,16 });
	right.PushBack({ 16*5,165,16,16 });
	right_go.PushBack({ 16*6,165,16,16 });

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

	life = 1;
}

void Enemy_GreenMiniShip1::Move()
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
													
void Enemy_GreenMiniShip1::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
	
	
}

Enemy_GreenMiniShip2::Enemy_GreenMiniShip2(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	left.PushBack({ 0,165,16,16 });
	right.PushBack({ 16,165,16,16 });
	right.PushBack({ 16 * 2,165,16,16 });
	right.PushBack({ 16 * 3,165,16,16 });
	right.PushBack({ 16 * 4,165,16,16 });
	right.PushBack({ 16 * 5,165,16,16 });
	right_go.PushBack({ 16 * 6,165,16,16 });

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

	path.PushBack({ -2.0f, -0.3f }, 50, &left);
	path.PushBack({ +2.0f, -0.5f }, 20, &right);
	path.PushBack({ +3.0f, -1.3f }, 5000, &right_go);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_GreenMiniShip2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 
	if (current_time >= 1000 && shoot == false) {
		Shoot();
		shoot = true;
	}
}
void Enemy_GreenMiniShip2::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
}


//Green enemy 3th path



Enemy_GreenMiniShip3::Enemy_GreenMiniShip3(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	left.PushBack({ 0,165,16,16 });
	right.PushBack({ 16,165,16,16 });
	right.PushBack({ 16 * 2,165,16,16 });
	right.PushBack({ 16 * 3,165,16,16 });
	right.PushBack({ 16 * 4,165,16,16 });
	right.PushBack({ 16 * 5,165,16,16 });
	right_go.PushBack({ 16 * 6,165,16,16 });

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

	path.PushBack({ 0, 0 }, 120, &left);
	path.PushBack({ 0, -2.0f }, 70, &left);
	path.PushBack({ -2.0f, 0 }, 50, &left);
	path.PushBack({ +3.0f, 0 }, 10, &right);
	path.PushBack({ +4.0f, 0 }, 5000, &right_go);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_GreenMiniShip3::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 
	
}
