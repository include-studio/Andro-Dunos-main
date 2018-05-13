#include "Application.h"
#include "Enemy_GreenMiniShip.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_GreenMiniShip1::Enemy_GreenMiniShip1(int x, int y) : Enemy(x, y)				//1rst path UP to DOWN
{
	left.PushBack({ 0,165,16,16 });
	right.PushBack({ 16,165,16,16 });
	right.PushBack({ 16*2,165,16,16 });
	right.PushBack({ 16*3,165,16,16 });
	right.PushBack({ 16*4,165,16,16 });
	right.PushBack({ 16*5,165,16,16 });
	right.PushBack({ 16*6,165,16,16 });

	left.speed = 0.1f;
	right.speed = 0.1f;

	left.loop = false;
	right.loop = false;

	animation = &left;
	animation = &right;

	//Path

	path.PushBack({ -2.0f, +0.3f }, 50, &left);
	path.PushBack({ +2.0f, +0.5f }, 5000, &right);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_GreenMiniShip1::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}
																		
Enemy_GreenMiniShip2::Enemy_GreenMiniShip2(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	left.PushBack({ 0,165,16,16 });
	right.PushBack({ 16,165,16,16 });
	right.PushBack({ 16 * 2,165,16,16 });
	right.PushBack({ 16 * 3,165,16,16 });
	right.PushBack({ 16 * 4,165,16,16 });
	right.PushBack({ 16 * 5,165,16,16 });
	right.PushBack({ 16 * 6,165,16,16 });

	left.speed = 0.1f;
	right.speed = 0.1f;

	left.loop = false;
	right.loop = false;

	animation = &left;
	animation = &right;

	//Path

	path.PushBack({ -2.0f, -0.3f }, 50, &left);
	path.PushBack({ +2.0f, -0.5f }, 5000, &right);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_GreenMiniShip2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}