#include "Application.h"
#include "Enemy_GreenMiniShip.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_GreenMiniShip::Enemy_GreenMiniShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,165,16,16 });
	fly.PushBack({ 16,165,16,16 });
	fly.PushBack({ 16*2,165,16,16 });
	fly.PushBack({ 16*3,165,16,16 });
	fly.PushBack({ 16*4,165,16,16 });
	fly.PushBack({ 16*5,165,16,16 });
	fly.PushBack({ 16*6,165,16,16 });


	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_GreenMiniShip::Move()
{


	position.x -= 1;
}