#include "Application.h"
#include "Enemy_WavingShip.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "Globals.h"


Enemy_WavingShip::Enemy_WavingShip(int x, int y, bool _drop) : Enemy(x, y)
{
	fly.PushBack({ 0,  0, 22, 22 });
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

	drop = _drop;

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

	position.y = original_y + int(25.0f * sinf(wave));
	position.x -= 1;
}

void Enemy_WavingShip::OnCollision(Collider* collider) {
	if (drop == true)
		App->powerup->AddPowerUp(App->powerup->bonus, position.x, position.y, COLLIDER_BONUS);
		
}