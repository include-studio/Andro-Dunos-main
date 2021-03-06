#include "Application.h"
#include "Enemy_MiniMiniBoss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL.h"
#include "ModuleStage1.h"
#include "ModuleStage4.h"



Enemy_MiniMiniBoss::Enemy_MiniMiniBoss(int x, int y, bool _drop) : Enemy(x, y)
{
	fly.PushBack({ 0,132,30,30 });
	fly.PushBack({ 31,132,30,30 });

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	drop = _drop;
	init_time = SDL_GetTicks(); //Timer
	current_time = 0;

	life = 5;
}

void Enemy_MiniMiniBoss::Move()
{
	position.x -= 1;

	current_time = SDL_GetTicks() - init_time; //Set time

	if (current_time <= 1000) {
		if (App->player1->position.y > (float)position.y)
			position.y += 1;

		if (App->player1->position.y < (float)position.y)
			position.y -= 0.25;
	}
	if (current_time >= 300 && shoot == false) {
		Shoot();
		shoot = true;
	}
	if (current_time >= 1500 && shoot2 == false) {
		Shoot();
		shoot2 = true;
	}
	
	if (current_time >= 1000 && current_time <= 1700)
		position.x += 1;
}

void Enemy_MiniMiniBoss::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);

}

void Enemy_MiniMiniBoss::OnCollision(Collider* collider) {

	if (App->stage4->IsEnabled()) {
		App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemy_blue_up, position.x, position.y, COLLIDER_ENEMY_SHOT); //Triple shot
		App->particles->AddParticle(App->particles->enemy_blue_down, position.x, position.y, COLLIDER_ENEMY_SHOT);
	}
	
	if (drop == true)
		App->powerup->AddPowerUp(App->powerup->bonus, position.x, position.y, COLLIDER_BONUS);
}