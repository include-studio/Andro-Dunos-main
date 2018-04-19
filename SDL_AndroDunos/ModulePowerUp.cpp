#include "Globals.h"
#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"

ModulePowerUp::ModulePowerUp() {
	for (uint i = 0; i < MAX_ACTIVE_ITEM; ++i)
		active[i] = nullptr;

	//Bonus B
	BonusB.anim.PushBack({});
	BonusB.anim.speed = 0.9f;
	//1up

	//gun
}

ModulePowerUp::~ModulePowerUp() {}

bool ModulePowerUp::Start() {
	graphics = App->textures->Load("assets/power_up.png");

	return true;
}

bool ModulePowerUp::CleanUp() {
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_ITEM; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

/*update_status ModulePowerUp::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_ITEM; ++i)
	{
		Item* it = active[i];

		if (it == nullptr)
			continue;

		if (it->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here!
			}
		}
	}

	return UPDATE_CONTINUE;
}*/