#include "Application.h"
#include "Enemy_Boss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleStage4.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStageClear.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include <time.h>


Enemy_Boss::Enemy_Boss(int x, int y) :Enemy(x, y) {
	anim.PushBack({ 0,743,187,89 });
	//anim.PushBack({ 187,743,187,89 });
	anim.speed = 0.8f;
	anim.loop = true;

	collider = App->collision->AddCollider({ 0, 0, 150, 50 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	fire = new Fire_Gun(position.x,position.y);

	path.PushBack({ 0,0 }, 0, &anim);
	/*path.PushBack({ -1.0f,NULL }, 150, &anim);
	path.PushBack({ 0.8f,NULL }, 150, &anim);
	*/
	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
	
	life = 50;
}

void Enemy_Boss::Move() {

	time = SDL_GetTicks()-init_time;
	//cont time to shoot
	if (time >= 3000) {
		fire->Shoot();
		init_time = SDL_GetTicks();
	}

	position = original_pos + path.GetCurrentSpeed(&animation);

}



void Enemy_Boss::Dispend() {
	/*for (int i = 0; i < 4; i++)
		App->enemies->AddEnemy(BOSS_DISP, position.x, position.y);*/

}


void Enemy_Boss::Draw(SDL_Texture* sprites) {
	if (collider != nullptr)
		collider->SetPos(position.x + 7, position.y+15);

	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
	App->render->Blit(sprites, position.x, position.y, &(fire->anim.GetCurrentFrame()));
}



void Enemy_Boss::OnCollision(Collider *c1 ) {
	//create destroyed
	App->enemies->AddEnemy(ENEMY_TYPES::BOSSDES, position.x, position.y+35);

	//delete firegun
	delete fire;
	fire = nullptr;

	//pieces destroyed

}

Fire_Gun::Fire_Gun(int x, int y) {
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 8; i++) {
			anim.PushBack({ i * 62,1131 + j * 68,62,68 });
			if (i == 5 && j == 1)
				break;
		}
	for (int j = 1; j >= 0; j--) {
		for (int i = 7; i >= 0; i--) {
			if (j == 1 && i == 7)
				i = 5;
			anim.PushBack({ i * 62,1131 + j * 68,62,68 });
		}
	}
	anim.speed = 0.2f;
	pos.x = x;
	pos.y = y;
}


void Fire_Gun::Shoot() {
	//Position();
	for (int n = 0; n < 20; n++) {
		int random = (rand()%20)+25;
		App->particles->AddParticle(App->particles->boss_fire, pos.x+random, pos.y + random, COLLIDER_ENEMY_SHOT);
	}
}

Enemy_Boss_Destroyed::Enemy_Boss_Destroyed(int x, int y) :Enemy(x, y) {
	anim.PushBack({ 0,960,187,60 });
	//anim.PushBack({ 187,960,187,60 });

	collider = App->collision->AddCollider({ 0, 0, 75, 100 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	path.PushBack({ 0,0 }, 0, &anim);
	/*path.PushBack({ -1.0f,NULL }, 150, &anim);
	path.PushBack({ 0.8f,NULL }, 150, &anim);
	*/

	tower = new Tower(position.x, position.y);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer

	life = 80;
}


void Enemy_Boss_Destroyed::Move() {

	time = SDL_GetTicks() - init_time;
	//cont time to shoot
	if (time >= 3000) {
		tower->Shoot();
		init_time = SDL_GetTicks();
	}

	position = original_pos + path.GetCurrentSpeed(&animation);

}

void Enemy_Boss_Destroyed::Draw(SDL_Texture* sprites) {
	if (collider != nullptr)
		collider->SetPos(position.x + 100, position.y -50);
	
	App->render->Blit(sprites, position.x + 100, position.y - 60, &tower->anim.GetCurrentFrame());
	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));

}

void Enemy_Boss_Destroyed::OnCollision(Collider *c1) {
	App->fade->FadeToBlack(App->stage4, App->stageclear, 0.5f);

	delete tower;
	tower = nullptr;
}

Tower::Tower(int x, int y) {

	anim.PushBack({ 0,1020,64,110 });

	pos.x = x;
	pos.y = y;

}

void Tower::Shoot() {
	App->particles->AddParticle(App->particles->boss_bomb1, pos.x + 125, pos.y-75, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->boss_bomb1, pos.x + 100, pos.y - 75, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->boss_bomb1, pos.x + 75, pos.y - 75, COLLIDER_ENEMY_SHOT);

	App->particles->AddParticle(App->particles->boss_bomb2, pos.x+(rand()%178-105), App->render->camera.y / SCREEN_SIZE - 50, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->boss_bomb2, pos.x+(rand() % 178 - 105), App->render->camera.y / SCREEN_SIZE - 75, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->boss_bomb2, pos.x+ (rand() % 178 - 105), App->render->camera.y / SCREEN_SIZE - 50, COLLIDER_ENEMY_SHOT);
}