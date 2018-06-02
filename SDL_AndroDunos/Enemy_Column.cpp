#include "Application.h"
#include "Enemy_Column.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_Column::Enemy_Column(int x, int y) : Enemy(x, y)
{
	immobil.PushBack({ 357,119,64,128 });
	animation = &immobil;

	collider = App->collision->AddCollider({ 0,0,60,124 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies); //0,0,41,91

	original_y = y;

	life = 10;
}