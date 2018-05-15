#include "Application.h"
#include "Enemy_Column.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_Column::Enemy_Column(int x, int y) : Enemy(x, y)
{
	immobil.PushBack({ 157,109,41,81 });
	animation = &immobil;

	collider = App->collision->AddCollider({ 0, 0, 41, 81 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}