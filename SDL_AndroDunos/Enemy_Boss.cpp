#include "Application.h"
#include "Enemy_Boss.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"


Enemy_Boss::Enemy_Boss(int x, int y) :Enemy(x, y) {
	anim.PushBack({ 0,743,187,89 });
	anim.PushBack({ 187,743,187,89 });
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
	
	life = 80;
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
	for (int i = 0; i < 4; i++)
		App->enemies->AddEnemy(BOSS_DISP, position.x, position.y);

}


void Enemy_Boss::Draw(SDL_Texture* sprites) {
	if (collider != nullptr)
		collider->SetPos(position.x + 7, position.y + 33);

	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
	App->render->Blit(sprites, position.x, position.y, &(fire->anim.GetCurrentFrame()));
}
void Enemy_Boss::OnCollision(Collider *c1 ) {
	//create destroyed
	//App->enemies->AddEnemy(ENEMY_TYPES::BOSSDES, position.x, position.y);

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

void Fire_Gun::Position() {
	
}
void Fire_Gun::Shoot() {
	int delay = 0;
	//Position();
	for (int n = 0; n < 20; n++) {
		App->particles->AddParticle(App->particles->boss_fire, pos.x+delay/20, pos.y+delay/20, COLLIDER_ENEMY_SHOT, delay);
		delay += 100;
	}
}