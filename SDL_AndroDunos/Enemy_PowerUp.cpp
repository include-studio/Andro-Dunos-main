#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleCollision.h"
#include "Globals.h"


Enemy_PowerUp::Enemy_PowerUp(int x, int y) : Enemy(x, y)
{
	/*fly.PushBack({ 0,  0, 22, 22 });
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

	animation = &fly;*/

	left.PushBack({ 153, 0, 26, 26 }); //left
	left.PushBack({ 179, 0, 26, 26 });

	transition1.PushBack({ 153, 0, 26, 26 }); //transition1
	left.PushBack({ 179, 0, 26, 26 });

	left_down.PushBack({ 153, 0, 26, 26 }); //left_down
	left.PushBack({ 179, 0, 26, 26 });

	transition2.PushBack({ 153, 0, 26, 26 }); //transition2
	left.PushBack({ 179, 0, 26, 26 });

	left_up.PushBack({ 153, 0, 26, 26 }); //left_up
	left.PushBack({ 179, 0, 26, 26 });

	transition3.PushBack({ 153, 0, 26, 26 }); //transition3
	left.PushBack({ 179, 0, 26, 26 });

	right.PushBack({ 153, 0, 26, 26 }); //right
	left.PushBack({ 179, 0, 26, 26 });

	transition4.PushBack({ 153, 0, 26, 26 }); //transition4
	left.PushBack({ 179, 0, 26, 26 });

	left.speed = 0.2f;
	transition1.speed = 0.2f;
	left_down.speed = 0.2f;
	transition2.speed = 0.2f;
	left_up.speed = 0.2f;
	transition3.speed = 0.2f;
	right.speed = 0.2f;
	transition4.speed = 0.2f;

	animation = &left;
	animation = &transition1;
	animation = &left_down;
	animation = &transition2;
	animation = &left_up;
	animation = &transition3;
	animation = &right;
	animation = &transition4;

	path.PushBack({ -0.0f, 0.0f }, 110, &left);
	path.PushBack({ 0.0f, 0.0f }, 100, &transition1);
	path.PushBack({ 0.0f, 0.0f }, 30, &left_down);
	path.PushBack({ 0.0f, 0.0f }, 15, &transition2);
	path.PushBack({ 0.0f, 0.0f }, 30, &left_up);
	path.PushBack({ 0.0f, 0.0f }, 35, &transition3);
	path.PushBack({ 0.0f, 0.0f }, 140, &right);
	path.PushBack({ 0.0f, 0.0f }, 35, &transition4);


	collider = App->collision->AddCollider({ 0, 0, 26, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_PowerUp::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}