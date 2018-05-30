#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleStage1.h"
#include "ModuleUI.h"
#include "ModuleShieldPlayer1.h"
#include "ModuleShieldPlayer2.h"

#include "SDL/include/SDL_timer.h"

ModulePowerUp::ModulePowerUp()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++) {
			bonus.anim.PushBack({ 16 * j,16 * i,16,16 });
			if (i == 2 && j == 4) break;
		}

	bonus.life = 50000;
	bonus.anim.speed = 0.5f;
	bonus.speed.y = 1;
	bonus.speed.x = 0;
	bonus.n_collisions = 0;
	bonus.anim.frame = 14;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (j == 0)
				powerup.anim.PushBack({ 112,48,16,16 });//closed
			else if (j == 5)
				powerup.anim.PushBack({ 112,64,16,16 });//white
			else
				powerup.anim.PushBack({ j * 16,64 + i * 16,16,16 });
		}
		for (int j = 3; j > 0; j--)
			powerup.anim.PushBack({ j * 16,64 + i * 16,16,16 });
	}
	powerup.anim.speed = 0.1f;
	powerup.life = 50000;
	powerup.speed.y = -1;
	powerup.speed.x = 0;
	powerup.n_collisions = 0;

	one_up.anim.PushBack({ 16 * 5,  16 * 2, 16, 16 });
	one_up.anim.PushBack({ 16 * 6, 16 * 2, 16, 16 });
	one_up.anim.PushBack({ 16 * 7, 16 * 2, 16, 16 });
	one_up.anim.PushBack({ 16 * 0, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 1, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 2, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 3, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 4, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 5, 16 * 3, 16, 16 });
	one_up.anim.PushBack({ 16 * 6, 16 * 3, 16, 16 });

	one_up.life = 50000;
	one_up.anim.speed = 0.25f;
	one_up.speed.y = 0;
	one_up.speed.x = 0;
	one_up.n_collisions = 8;
	one_up.screen_col = -1;
}

ModulePowerUp::~ModulePowerUp()
{}

// Load assets
bool ModulePowerUp::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/Sprites/power_up.png");

	powerup_fx = App->audio->Loadfx("Assets/Audio/Power_Up_Picked.wav");

	bonus_fx = App->audio->Loadfx("Assets/Audio/Bonus_Pickup.wav");

	one_up_fx = App->audio->Loadfx("Assets/Audio/Extra_Life_Pick_Up.wav");

	return true;
}

// Unload assets
bool ModulePowerUp::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	App->audio->UnLoadFx(powerup_fx);
	App->audio->UnLoadFx(bonus_fx);
	App->audio->UnLoadFx(one_up_fx);

	for (uint i = 0; i < MAX_ACTIVE_ITEMS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModulePowerUp::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS; ++i)
	{
		Item* it = active[i];

		if (it == nullptr)
			continue;

		if (it->Update() == false)
		{
			delete it;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= it->born)
		{
			App->render->Blit(graphics, it->position.x, it->position.y, &(it->anim.GetCurrentFrame(it->anim.frame)));

			if (it->fx_played == false)
			{
				it->fx_played = true;
				// Play particle fx here!
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePowerUp::AddPowerUp(const Item& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS; ++i)
	{
		if (active[i] == nullptr)
		{
			Item* it = new Item(particle);
			it->born = SDL_GetTicks() + delay;
			it->position.x = x;
			it->position.y = y;
			if (collider_type != COLLIDER_NONE)
				it->collider = App->collision->AddCollider(it->anim.GetCurrentFrame(), collider_type, this);
			active[i] = it;
			break;
		}
	}
}
void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c2->callback == App->player1) {
				if (c1->type == COLLIDER_BONUS) {
					App->ui->score1 += 100;
					App->audio->PlayFx(bonus_fx);
				}
				if (c1->type == COLLIDER_POWERUP) {
					App->player1->powerup++; 
					App->audio->PlayFx(powerup_fx);
					if (App->shield1->IsEnabled() == false)
						App->shield1->Enable();
				}
				if (c1->type == COLLIDER_ONE_UP) {
					App->audio->PlayFx(one_up_fx);
					if (App->player1->hp != 7) {
						App->player1->hp++;
					}
				}
			}
			if (c2->callback == App->player2) {
				if (c1->type == COLLIDER_BONUS) {
					App->ui->score2 += 100;
					App->audio->PlayFx(bonus_fx);
				}
				if (c1->type == COLLIDER_POWERUP) {
					App->player2->powerup++;
					App->audio->PlayFx(powerup_fx);
					if (App->shield2->IsEnabled() == false)
						App->shield2->Enable();
				}
				if (c1->type == COLLIDER_ONE_UP) {
					App->audio->PlayFx(one_up_fx);
					if (App->player2->hp != 7) {
						App->player2->hp++;
					}
				}
			}
			delete active[i];
			active[i] = nullptr;
			break;
		}

	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Item::Item()
{
	position.SetToZero();
	speed.SetToZero();
}

Item::Item(const Item& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Item::~Item()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Item::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;			

	if (collider->type == COLLIDER_BONUS && anim.speed != 0.2f && anim.current_frame > 11)
 		anim.speed = 0.2f;

	if (this->collider->type == COLLIDER_POWERUP) {
		if (anim.isInFrame(3) || anim.isInFrame(7) || anim.isInFrame(13) ||
			anim.isInFrame(17) || anim.isInFrame(23) || anim.isInFrame(27) ||
			anim.isInFrame(33) || anim.isInFrame(37)) {
			if (anim.speed != 0.005f)
				anim.speed = 0.005f;
		}
		else
			if (anim.speed != 0.3f)
				anim.speed = 0.3f;
		if (anim.isBetween(0, 9))
			poweruptype = S;
	}
			
	if (this->collider->type != COLLIDER_ONE_UP)
		if (!screen_col)
			if (position.x < App->render->camera.x / 3 + SCREEN_WIDTH - this->anim.frames->w)
				screen_col = true;

	if (screen_col) {
		if (n_collisions < 6) {
			if (position.y <= App->render->camera.y / 3 || position.y >= App->render->camera.y / 3 + SCREEN_HEIGHT - this->anim.frames->h) {
				if (speed.y == -1)speed.y = 1;
				else speed.y = -1;
				n_collisions++;
			}
			if (position.x > App->render->camera.x / 3 + SCREEN_WIDTH - this->anim.frames->w || position.x < App->render->camera.x / 3) {
				if (speed.x == 2) {
					speed.x = 0;
					n_collisions++;
				}
				else if (speed.x == 0)
					speed.x = 2;
			}
		}
	}

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}