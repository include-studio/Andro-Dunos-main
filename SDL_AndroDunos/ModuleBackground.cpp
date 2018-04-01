#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 0;
	ground.y = 95;
	ground.w = SCREEN_WIDTH;
	ground.h = SCREEN_HEIGHT ;
	

	// Background / sky
	background.x = 0;
	background.y = 459;
	background.w = 251;
	background.h = 85;

	//rocks
	rocks.x = 252;
	rocks.y = 319;
	rocks.w = 64;
	rocks.h = 224;

	//stars

	//planets
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Background1.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	switch (part_stage) {
		case 0: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(graphics, background.w*i + speed, mov_planet, &background);
			}
			App->render->Blit(graphics, 0, 0, &ground);
			ground.x++;
			speed -= 0.5f;
			if (ground.x == 3248 - ground.w)
				part_stage++;
			break;
		}
		case 1: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(graphics, background.w*i + speed, mov_planet, &background);
			}
			App->render->Blit(graphics, 0, 0, &ground);
			ground.y++;
			mov_planet--;
			if (ground.y == 542 - SCREEN_HEIGHT) {
				part_stage++;
				speed = 0;
			}
			break;
		}
		case 2: {
			for (int i = SCREEN_WIDTH/rocks.w; i < 20; i++) {
				App->render->Blit(graphics, rocks.w*i + speed, mov_rocks, &rocks);
			}
			App->render->Blit(graphics, 0, 0, &ground);
			ground.x++;
			speed -= 0.5f;
			if (ground.x == 3248 - ground.w)
				
			break;
		}
	}

	return UPDATE_CONTINUE;
}