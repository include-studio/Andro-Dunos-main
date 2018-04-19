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
	position.x -= 1;
}