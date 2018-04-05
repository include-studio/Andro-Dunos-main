#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 9305;
	ground.h = 543;
	

	// Background / sky
	background.x = 0;
	background.y = 139;
	background.w = 251;
	background.h = 85;

	//rocks
	//rocks.x = 252;
	//rocks.y = 319;
	//rocks.w = 64;
	//rocks.h = 224;

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
	back_tx = App->textures->Load("assets/Background.png");
	ground_tx = App->textures->Load("assets/Ground.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	switch (part_stage) {
		case 0: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(back_tx, background.w*i, 118, &background, 0.8f);
			}
			App->render->Blit(ground_tx, 0, -94, &ground,2);
			App->render->camera.x--;
			break;
		}
		case 1: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(back_tx, background.w*i, 0, &background);
			}
			App->render->Blit(ground_tx, 0, 0, &ground);
			ground.y++;
			if (ground.y == 542 - SCREEN_HEIGHT) {
				part_stage++;
			}
			break;
		}
		case 2: {
			for (int i = SCREEN_WIDTH/rocks.w; i < 20; i++) {
				App->render->Blit(back_tx, rocks.w*i, 0, &rocks);
			}
			App->render->Blit(ground_tx, 0, 0, &ground);
			ground.x++;
			if (ground.x == 3248 - ground.w)
				
			break;
		}
	}

	return UPDATE_CONTINUE;
}