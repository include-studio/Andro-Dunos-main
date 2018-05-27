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
	
	//left, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Right, Left, Up-Right, Down, Up-Left, Right, Up-Right, Down, Up-Left, Up-Right, Down, Up-Left, Up-Right, Down, Right, Left, 

	path.PushBack({ -1.0f, 0.0f }, 85, &fly); //left
	path.PushBack({ +2.5f, -0.4f }, 45, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.4f }, 70, &fly); //Down
	path.PushBack({ -1.0f, -0.4f }, 50, &fly); //Up-Left
	path.PushBack({ +3.0f, -1.0f }, 45, &fly); // Up-Right
	path.PushBack({ +1.0f, +2.0f }, 40, &fly); // Down
	path.PushBack({  0.0f, -0.5f }, 60, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 20, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 35, &fly); //Left
	path.PushBack({ +2.5f, -0.5f }, 35, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 40, &fly); // Down
	path.PushBack({ 0.0f, -0.5f }, 40, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ +2.5f, -1.0f }, 30, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 60, &fly); // Down
	path.PushBack({  0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 80, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.5f }, 90, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left


	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 2000, &fly); //Left


	
	//path.PushBack({ +1.0f, 0.0f }, 4000, &fly); //IDLE

	collider = App->collision->AddCollider({ 0, 0, 100, 55 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer

	life = 50;
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
	//2, 12, 16, 21 Seconds Blue
	//3, 8, 12, 17 Seconds Yellow
}
void Enemy_BigShip::Shoot() {
	
	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y + 52, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->enemy_blue_up, position.x, position.y + 52, COLLIDER_ENEMY_SHOT); //Triple shot
	App->particles->AddParticle(App->particles->enemy_blue_down, position.x, position.y + 52, COLLIDER_ENEMY_SHOT);
	

}
void Enemy_BigShip::Shoot_yellow() {

	App->particles->AddParticle(App->particles->enemy_yellow_laser, position.x + 70, position.y, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->enemy_yellow_laser, position.x + 70, position.y + 105, COLLIDER_ENEMY_SHOT);

}
//void Enemy_BigShip::OnCollision(Collider* c1) {
//
//	
//}

void Enemy_BigShip::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x + 7, position.y + 33);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}












//Wing1



Enemy_BigShip2::Enemy_BigShip2(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 0, 222 + PIXEL, PIXEL, PIXEL });
	animation = &fly;
	fly.speed = 0.2f;
	fly.loop = true;

	path.PushBack({ -1.0f, 0.0f }, 85, &fly); //left
	path.PushBack({ +2.5f, -0.4f }, 45, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.4f }, 70, &fly); //Down
	path.PushBack({ -1.0f, -0.4f }, 50, &fly); //Up-Left
	path.PushBack({ +3.0f, -1.0f }, 45, &fly); // Up-Right
	path.PushBack({ +1.0f, +2.0f }, 40, &fly); // Down
	path.PushBack({ 0.0f, -0.5f }, 60, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 20, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 35, &fly); //Left
	path.PushBack({ +2.5f, -0.5f }, 35, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 40, &fly); // Down
	path.PushBack({ 0.0f, -0.5f }, 40, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ +2.5f, -1.0f }, 30, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 60, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 80, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.5f }, 90, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 2000, &fly); //Left

	//path.PushBack({ +1.0f, 0.0f }, 4000, &fly); //IDLE

	collider = App->collision->AddCollider({ 0, 0, 50, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	

	init_time = SDL_GetTicks(); //Timer
}

void Enemy_BigShip2::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 
	
	//Open Wings
	
	if (current_time >= 1700 && current_time <= 1816) { //Time Wing Up/Down = 116 //Double
		WingUp();
	}
	if (current_time >= 3000 && current_time <= 3116) {
		WingDown();
	}

	if (current_time >= 6700 && current_time <= 6816) {  //Knock Out
		WingUp();
	}
	if (current_time >= 7800 && current_time <= 7916) { 
		WingDown();
	}

	if (current_time >= 11700 && current_time <= 11816) { //One
		WingUp();
	}
	if (current_time >= 12400 && current_time <= 12516) {
		WingDown();
	}

	if (current_time >= 15700 && current_time <= 15816) { //Double
		WingUp();
	}
	if (current_time >= 17000 && current_time <= 17116) {
		WingDown();
	}

	if (current_time >= 20700 && current_time <= 20816) {
		WingUp();
	}
	if (current_time >= 21400 && current_time <= 21516) {
		WingDown();
	}
	position = original_pos + path.GetCurrentSpeed(&animation);

}

//void Enemy_BigShip::OnCollision(Collider* c1) {
//
//	
//}

void Enemy_BigShip2::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y + 33);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}























//Wing2


Enemy_BigShip3::Enemy_BigShip3(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ PIXEL, 222 + PIXEL, PIXEL, PIXEL });
	animation = &fly;
	fly.speed = 0.2f;
	fly.loop = true;

	path.PushBack({ -1.0f, 0.0f }, 85, &fly); //left
	path.PushBack({ +2.5f, -0.4f }, 45, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.4f }, 70, &fly); //Down
	path.PushBack({ -1.0f, -0.4f }, 50, &fly); //Up-Left
	path.PushBack({ +3.0f, -1.0f }, 45, &fly); // Up-Right
	path.PushBack({ +1.0f, +2.0f }, 40, &fly); // Down
	path.PushBack({ 0.0f, -0.5f }, 60, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 20, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 35, &fly); //Left
	path.PushBack({ +2.5f, -0.5f }, 35, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 40, &fly); // Down
	path.PushBack({ 0.0f, -0.5f }, 40, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ +2.5f, -1.0f }, 30, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 60, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +1.0f }, 80, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.0f, -0.4f }, 80, &fly); //Up-Right
	path.PushBack({ +1.0f, +0.5f }, 90, &fly); // Down
	path.PushBack({ 0.0f, -0.4f }, 80, &fly); //Up-Left
	path.PushBack({ +2.5f, 0.0f }, 70, &fly); //Right
	path.PushBack({ -2.0f, 0.0f }, 2000, &fly); //Left

	//path.PushBack({ +1.0f, 0.0f }, 4000, &fly); //IDLE

	collider = App->collision->AddCollider({ 0, 0, 50, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_BigShip3::Move()
{
	current_time = SDL_GetTicks() - init_time; //Set Time 

	if (current_time >= 1700 && current_time <= 1816) { //Time Wing Up/Down = 116 //Double
		WingDown();
	}
	if (current_time >= 3000 && current_time <= 3116) {
		WingUp();
	}

	if (current_time >= 6700 && current_time <= 6816) {  //Knock Out
		WingDown();
	}
	if (current_time >= 7800 && current_time <= 7916) {
		WingUp();
	}

	if (current_time >= 11700 && current_time <= 11816) { //One
		WingDown();
	}
	if (current_time >= 12400 && current_time <= 12516) {
		WingUp();
	}

	if (current_time >= 15700 && current_time <= 15816) { //Double
		WingDown();
	}
	if (current_time >= 17000 && current_time <= 17116) {
		WingUp();
	}

	if (current_time >= 20700 && current_time <= 20816) {
		WingDown();
	}
	if (current_time >= 21400 && current_time <= 21516) {
		WingUp();
	}

	position = original_pos + path.GetCurrentSpeed(&animation);
	//2, 12, 16, 21 Seconds Blue
	//3, 8, 12, 17 Seconds Yellow
}

//void Enemy_BigShip::OnCollision(Collider* c1) {
//
//	
//}

void Enemy_BigShip3::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y + 60);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}