#include "Application.h"
#include "Enemy_MiniMiniBoss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModulePlayer1.h"


Enemy_MiniMiniBoss::Enemy_MiniMiniBoss(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 30,50,30,30 });
	fly.PushBack({ 0,50,30,30 });

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 13 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_MiniMiniBoss::Move()
{
	position.x -= 1;
}

void Enemy_MiniMiniBoss::Shoot()
{
	if(fly.loop == true )
		App->particles->AddParticle(App->particles->laser1, position.x, position.y, COLLIDER_ENEMY_SHOT);
}