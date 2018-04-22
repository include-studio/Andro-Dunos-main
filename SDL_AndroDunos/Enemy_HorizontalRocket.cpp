#include "Application.h"
#include "Enemy_HorizontalRocket.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_HorizontalRocket::Enemy_HorizontalRocket(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 30,50,30,30 }); 
	fly.PushBack({ 0,50,30,30 }); 
	fly.PushBack({ 90,50,30,30 }); 
	fly.PushBack({ 0,50,30,30 }); 
	fly.PushBack({ 30,50,30,30 }); 
	fly.PushBack({ 60,50,30,30 }); 

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 13 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_HorizontalRocket::Move()
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
	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 1;
}