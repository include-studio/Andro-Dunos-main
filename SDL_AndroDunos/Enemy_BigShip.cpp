#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "Enemy_BigShip.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"

#include "ModuleRender.h"

#define PIXEL 116


Enemy_BigShip::Enemy_BigShip(int x, int y) : Enemy(x, y)
{
	
	fly.PushBack({ 0, 222, PIXEL, PIXEL });
	fly.PushBack({ PIXEL, 222, PIXEL, PIXEL });

	fly.speed = 0.3f;
	fly.loop = true;
	

	path.PushBack({ -1.0f, 0.0f }, 40, &fly);//Important

	collider = App->collision->AddCollider({ 10, 10, 90, 90 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_BigShip::Move()
{
	position.x++;
	position = original_pos + path.GetCurrentSpeed(&animation);
	
}
void Enemy_BigShip::Shoot() {

	App->particles->AddParticle(App->particles->enemy_blue, position.x, position.y, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->enemy_blue_up, position.x, position.y, COLLIDER_ENEMY_SHOT); //Triple shot
	App->particles->AddParticle(App->particles->enemy_blue_down, position.x, position.y, COLLIDER_ENEMY_SHOT);
}
void Enemy_BigShip::OnCollision(Collider* c1) {

	
}

void Enemy_BigShip::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x + 4, position.y + 6);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}