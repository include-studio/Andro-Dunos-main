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
#define PI 3.14

Enemy_TripleCanon::Enemy_TripleCanon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113,PIXEL,PIXEL });
	fly.PushBack({ 243 ,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 ,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });

	fly.speed = 0.1f;
	animation = &fly;
	


	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	original_pos.x = x;
	original_pos.y = y;
	
	init_time = SDL_GetTicks(); //Timer
	current_time = 0;

	life = 5;
}

void Enemy_TripleCanon::Move()
{
	

	current_time = SDL_GetTicks() - init_time; //Set time


	if (current_time >= 1800 && shoot1 == false) {
		Shoot();
		shoot1 = true;
		shoot2= false;
	}
	if (current_time >= 2000 && shoot2 == false) {
		Shoot();
		shoot2 = true;
		shoot3 = false;
	}
	if (current_time >= 2200 && shoot3 == false) {
		Shoot();
		shoot3 = true;
	}
	if (current_time <= 1000) {
		original_x-= 2;
		position.x = original_x + int(50.0f * cosf(rotation));
		position.y = original_y + int(50.0f * sinf(rotation));
	
	}
	if (current_time > 1000 && current_time < 4000) {
		original_x++;
		position.x = original_x + int(50.0f * cosf(rotation));
		position.y = original_y + int(50.0f * sinf(rotation));
	
	}
	if (current_time > 4000) {
		position.x+=3;
	}
	rotation += 0.045f;
}

void Enemy_TripleCanon::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue_laser, position.x, position.y, COLLIDER_ENEMY_SHOT);

}

void Enemy_TripleCanon::OnCollision(Collider* collider) {
	
}


// Triple canon 2


Enemy_TripleCanon2::Enemy_TripleCanon2(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113,PIXEL,PIXEL });
	fly.PushBack({ 243 ,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 ,113 + PIXEL,PIXEL,PIXEL });
	fly.PushBack({ 243 + PIXEL,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });
	fly.PushBack({ 243,113,PIXEL,PIXEL });

	fly.speed = 0.1f;
	animation = &fly;



	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	original_pos.x = x;
	original_pos.y = y;

	init_time = SDL_GetTicks(); //Timer
	current_time = 0;

	/*hp = 6;*/
}

void Enemy_TripleCanon2::Move()
{


	current_time = SDL_GetTicks() - init_time; //Set time


	if (current_time >= 1800 && shoot1 == false) {
		Shoot();
		shoot1 = true;
		shoot2 = false;
	}
	if (current_time >= 2000 && shoot2 == false) {
		Shoot();
		shoot2 = true;
		shoot3 = false;
	}
	if (current_time >= 2200 && shoot3 == false) {
		Shoot();
		shoot3 = true;
	}
	if (current_time <= 1000) {
		original_x -= 2;
		position.x = original_x + int(50.0f * sinf(rotation));
		position.y = original_y + int(50.0f * cosf(rotation));
		/*position.y+=4;*/

	}
	if (current_time > 1000 && current_time < 4700) {
		original_x++;
		position.x = original_x + int(50.0f * sinf(rotation));
		position.y = original_y + int(50.0f * cosf(rotation));
		/*position.y+=4;*/

	}
	if (current_time > 4700) {
		position.x += 3;
	}
	rotation += 0.045f;
}

void Enemy_TripleCanon2::Shoot()
{
	App->particles->AddParticle(App->particles->enemy_blue_laser, position.x, position.y, COLLIDER_ENEMY_SHOT);

}

void Enemy_TripleCanon2::OnCollision(Collider* collider) {

}