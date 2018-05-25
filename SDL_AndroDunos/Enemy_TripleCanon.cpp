#include "Application.h"
#include "Enemy_TripleCanon.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "SDL/include/SDL.h"

#define PIXEL 30


Enemy_TripleCanon::Enemy_TripleCanon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113,PIXEL,PIXEL });
	fly.PushBack({ 243 ,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });


	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	
	init_time = SDL_GetTicks(); //Timer
	current_time = 0;

	/*hp = 6;*/
}

void Enemy_TripleCanon::Move()
{
	position.x--;

	current_time = SDL_GetTicks() - init_time; //Set time


	if (current_time >= 300 && shoot == false) {
		Shoot();
		shoot = true;
	}
	/*if (current_time <= 800) {
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
	}*/

	/*if (current_time > 800)
		position.x -= 0.25;*/
}

void Enemy_TripleCanon::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue_laser, position.x, position.y, COLLIDER_ENEMY_SHOT);

}

void Enemy_TripleCanon::OnCollision(Collider* collider) {
	
}