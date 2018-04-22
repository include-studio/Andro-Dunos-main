#include "Application.h"
#include "Enemy_MiniMiniBoss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"


Enemy_MiniMiniBoss::Enemy_MiniMiniBoss(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,132,30,30 });
	fly.PushBack({ 31,132,30,30 });

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	init_time = SDL_GetTicks(); //Timer
	current_time = 0;

	hp = 6;
}

void Enemy_MiniMiniBoss::Move()
{
	position.x += 0.7;

	current_time = SDL_GetTicks() - init_time;

	if (current_time <= 800) {
		if (App->player1->position.y > (float)position.y)
			position.y += 1;

		if (App->player1->position.y < (float)position.y)
			position.y -= 0.25;
	}
	if (current_time >= 800 && shoot == false) {
		Shoot();
		shoot = true;
	}
	
	if (current_time > 800)
		position.x -= 0.25;
}

void Enemy_MiniMiniBoss::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
}

/*void Enemy_MiniMiniBoss::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT)
		hp--;
	if (hp < 0)
		App->enemies->OnCollision(this->collider,collider);
}*/