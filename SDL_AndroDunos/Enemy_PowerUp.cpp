#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleCollision.h"
#include "Globals.h"



Enemy_PowerUp::Enemy_PowerUp(int x, int y) : Enemy(x, y)
{

	left.PushBack({ 153, 0, 26, 26 }); //left
	left.PushBack({ 179, 0, 26, 26 });

	transition1.PushBack({ 205, 0, 26, 26 }); //transition1
	
	left_down.PushBack({ 231, 0, 26, 26 }); //left_down
	left_down.PushBack({ 257, 0, 26, 26 });

	transition2.PushBack({ 283, 0, 26, 26 }); //transition2
	transition2.PushBack({ 309, 0, 26, 26 });
	transition2.PushBack({ 335, 0, 26, 26 });

	left_up.PushBack({ 361, 0, 26, 26 }); //left_up
	left_up.PushBack({ 387, 0, 26, 26 });

	transition3.PushBack({ 413, 0, 26, 26 }); //transition3
	transition3.PushBack({ 439, 0, 26, 26 });
	transition3.PushBack({ 153, 26, 26, 26 });
	transition3.PushBack({ 179, 26, 26, 26 });
	transition3.PushBack({ 205, 26, 26, 26 });
	transition3.PushBack({ 231, 26, 26, 26 });
	transition3.PushBack({ 257, 26, 26, 26 });
	transition3.PushBack({ 283, 26, 26, 26 });
	transition3.PushBack({ 309, 26, 26, 26 });
	transition3.PushBack({ 335, 26, 26, 26 });
	transition3.PushBack({ 361, 26, 26, 26 });
	transition3.PushBack({ 387, 26, 26, 26 });
	transition3.PushBack({ 413, 26, 26, 26 });
	transition3.PushBack({ 439, 26, 26, 26 });
	transition3.PushBack({ 153, 52, 26, 26 });

	right.PushBack({ 179, 52, 26, 26 }); //right
	right.PushBack({ 205, 52, 26, 26 });

	transition4.PushBack({ 231, 52, 26, 26 }); //transition4
	transition4.PushBack({ 257, 52, 26, 26 });
	transition4.PushBack({ 283, 52, 26, 26 });
	transition4.PushBack({ 309, 52, 26, 26 });
	transition4.PushBack({ 335, 52, 26, 26 });
	transition4.PushBack({ 361, 52, 26, 26 });
	transition4.PushBack({ 387, 52, 26, 26 });
	transition4.PushBack({ 413, 52, 26, 26 });
	transition4.PushBack({ 439, 52, 26, 26 });
	transition4.PushBack({ 153, 78, 26, 26 });
	transition4.PushBack({ 179, 78, 26, 26 });
	transition4.PushBack({ 205, 78, 26, 26 });
	transition4.PushBack({ 231, 78, 26, 26 });
	transition4.PushBack({ 257, 78, 26, 26 });
	transition4.PushBack({ 283, 78, 26, 26 });

	left.speed = 0.2f;
	transition1.speed = 0.2f;
	left_down.speed = 0.2f;
	transition2.speed = 0.2f;
	left_up.speed = 0.2f;
	transition3.speed = 0.2f;
	right.speed = 0.2f;
	transition4.speed = 0.05f;

	animation = &left;
	animation = &transition1;
	animation = &left_down;
	animation = &transition2;
	animation = &left_up;
	animation = &transition3;
	animation = &right;
	animation = &transition4;


	path.PushBack({ -1.0f, 0.0f }, 40, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 15, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 15, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 15, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 10, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 15, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 500, &left); // you're no longer welcome here.





	

	


	collider = App->collision->AddCollider({ 0, 0, 26, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_PowerUp::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	part_power_up = 1;
}