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

#include "SDL/include/SDL_timer.h"

ModulePowerUp::ModulePowerUp()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++) {
			bonus.anim.PushBack({ 16 * j,16 * i,16,16 });
			if (i == 2 && j == 4) break;
		}
	bonus.life = 5000000;
	bonus.anim.loop = false;
	bonus.anim.speed = 0.7f;
	bonus.speed.y = 1;
	bonus.speed.x = 0;
	bonus.n_collisions = 0;

	powerup_S.anim.PushBack({ 80,64,16,16 });
	powerup_S.life = 5000000;
	powerup_S.speed.y = -1;
	powerup_S.speed.x = 0;
	powerup_S.n_collisions = 0;
}

ModulePowerUp::~ModulePowerUp()
{}

// Load assets
bool ModulePowerUp::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/Sprites/power_up.png");

	return true;
}

// Unload assets
bool ModulePowerUp::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

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
			App->render->Blit(graphics, it->position.x, it->position.y, &(it->anim.GetCurrentFrame()));

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
				if (c1->type == COLLIDER_BONUS)
					App->player1->score += 100;
				if (c1->type == COLLIDER_POWER_S)
						App->player1->powerup++;
			}
			if (c2->callback == App->player2) {
				if (c1->type == COLLIDER_BONUS)
					App->player2->score += 100;
				if (c1->type == COLLIDER_POWER_S)
						App->player2->powerup++;
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
	if (screen_col == 0)
		if (position.x < App->stage1->camera_limit.xf + 16)
			screen_col++;

	if (screen_col > 0) {
		if (n_collisions < 6) {
			if (position.y <= App->stage1->camera_limit.yi || position.y >= App->stage1->camera_limit.yf) {
				if (speed.y == -1)speed.y = 1;
				else speed.y = -1;
				n_collisions++;
			}
			if (position.x > App->stage1->camera_limit.xf + 16 || position.x < App->stage1->camera_limit.xi) {
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