#include "Application.h"
#include "Enemy_WavingShip.h"
#include "ModuleCollision.h"

Enemy_WavingShip::Enemy_WavingShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,22,22 });
	fly.PushBack({ 22, 0, 22, 22 });
	fly.PushBack({ 44, 0, 22, 22 });
	fly.PushBack({ 66, 0, 22, 22 });
	fly.PushBack({ 88, 0, 22, 22 });
	fly.PushBack({ 110, 0, 22, 22 });

	fly.PushBack({ 0, 22, 22, 22 });
	fly.PushBack({ 22, 22, 22, 22 });
	fly.PushBack({ 44, 22, 22, 22 });
	fly.PushBack({ 66, 22, 22, 22 });
	fly.PushBack({ 88, 22, 22, 22 });

	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_WavingShip::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
}