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

#include "SDL/include/SDL_timer.h"

ModulePowerUp::ModulePowerUp()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++) {
			bonus.anim.PushBack({ 16 * j,16 * i,16,16 });
			if (i == 2 && j == 4) break;
		}
	bonus.life = 5000000;
	bonus.speed.x = 1;
	bonus.anim.loop = false;
	bonus.anim.speed = 0.7f;
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

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}