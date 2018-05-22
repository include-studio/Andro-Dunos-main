#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "Enemy_BigShip.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "ModuleRender.h"

#define PIXEL 116


Enemy_BigShip::Enemy_BigShip(int x, int y) : Enemy(x, y)
{
	
	fly.PushBack({ 0, 222, PIXEL, PIXEL });
	fly.PushBack({ PIXEL, 222, PIXEL, PIXEL });

	fly.speed = 0.2f;
	fly.loop = true;
	

	path.PushBack({ -1.0f, 0.0f }, 60, &fly);//Important
	path.PushBack({ +1.0f, 0.0f }, 4000, &fly);//Important

	collider = App->collision->AddCollider({ 10, 10, 90, 90 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_BigShip::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 
	//Blue Bullet
	if (current_time >= 2000 && shoot1 == true) {    
		Shoot();
		shoot1 = false;
		shoot1_sub = true;
	}
	if (current_time >= 2500 && shoot1_sub == true) {
		Shoot();
		shoot1_sub = false;
		shoot2 = true;
	}
	if (current_time >= 12000 && shoot2 == true) {
		Shoot();
		
		shoot2 = false;
		shoot3 = true;
	}
	if (current_time >= 16000 && shoot3 == true) {
		Shoot();

		shoot3 = false;
		shoot3_sub = true;
	}
	if (current_time >= 16500 && shoot3_sub == true) {
		Shoot();

		shoot3_sub = false;
		shoot4 = true;
	}
	if (current_time >= 21000 && shoot4 == true) {
		Shoot();
		shoot4 = false;
	}

	//Yellow Laser
	if (current_time >= 3000 && yellow1 == true) {
		Shoot_yellow();

		yellow1 = false;
		yellow1_sub = true;
	}
	if (current_time >= 3500 && yellow1_sub == true) {
		Shoot_yellow();

		yellow1_sub = false;
		yellow2 = true;
	}
	if (current_time >= 8000 && yellow2 == true) {
		Shoot_yellow();

		yellow2 = false;
		yellow2_sub = true;
	}
	if (current_time >= 8500 && yellow2_sub == true) {
		Shoot_yellow();

		yellow2_sub = false;
		yellow3 = true;
	}
	if (current_time >= 12000 && yellow3 == true) {
		Shoot_yellow();

		yellow3 = false;
		yellow3_sub = true;
	}
	if (current_time >= 12500 && yellow3_sub == true) {
		Shoot_yellow();

		yellow3_sub = false;
		yellow4 = true;
	}
	if (current_time >= 17000 && yellow4 == true) {
		Shoot_yellow();

		yellow4 = false;
		yellow4_sub = true;
	}
	if (current_time >= 17500 && yellow4_sub == true) {
		Shoot_yellow();

		yellow4_sub = false;
		
	}
	




	
	position = original_pos + path.GetCurrentSpeed(&animation);
	//2, 12, 16, 21
	//3, 8, 12, 17
}
void Enemy_BigShip::Shoot() {
	
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y + 52, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->enemy_blue_up, position.x, position.y + 52, COLLIDER_ENEMY_SHOT); //Triple shot
	App->particles->AddParticle(App->particles->enemy_blue_down, position.x, position.y + 52, COLLIDER_ENEMY_SHOT);
	

}
void Enemy_BigShip::Shoot_yellow() {

	App->particles->AddParticle(App->particles->enemy_yellow_laser, position.x + 77, position.y, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->enemy_yellow_laser, position.x + 77, position.y + 105, COLLIDER_ENEMY_SHOT);

}
void Enemy_BigShip::OnCollision(Collider* c1) {

	
}

void Enemy_BigShip::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x + 4, position.y + 6);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}