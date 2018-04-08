#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleMainMenu.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"

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
	rocks_entry.x = 317;
	rocks_entry.y = 0;
	rocks_entry.w = 64;
	rocks_entry.h = 384;
	rocks.x = 252;
	rocks.y = 0;
	rocks.w = 64;
	rocks.h = 384;
	rocks_escape.x = 382;
	rocks_escape.y = 0;
	rocks_escape.w = 64;
	rocks_escape.h = 384;
	
	//stars
	star1.x = 5;
	star1.y = 3;
	star1.w = 3;
	star1.h = 3;
	star2.x = 5;
	star2.y = 8;
	star2.w = 3;
	star2.h = 3;
	star3.x = 5;
	star3.y = 13;
	star3.w = 3;
	star3.h = 3;
	star4.x = 5;
	star4.y = 18;
	star4.w = 3;
	star4.h = 3;
	star5.x = 5;
	star5.y = 23;
	star5.w = 2;
	star5.h = 2;
	star6.x = 5;
	star6.y = 26;
	star6.w = 2;
	star6.h = 2;
	star7.x = 5;
	star7.y = 29;
	star7.w = 17;
	star7.h = 6;
	//planets
	planet1.x = 0;
	planet1.y = 0;
	planet1.w = 106;
	planet1.h = 106;
	planet2.x = 115;
	planet2.y = 0;
	planet2.w = 62;
	planet2.h = 62;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	
	LOG("Loading background assets");
	bool ret = true;

	stars_tx = App->textures->Load("assets/Stars.png");
	back_tx = App->textures->Load("assets/Background.png");
	ground_tx = App->textures->Load("assets/Ground.png");
	
	App->player1->Enable();
	App->player2->Enable();
	//if (current_step == fade_step) App->player->CleanUp();

	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	switch (part_stage) {
	case 0: { //case 0: Start & PreDownfall
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.40f);

			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 41, &star7, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);

			App->render->Blit(ground_tx, 0, -94, &ground);
			App->render->Blit(back_tx, 800, 17, &planet1, 0.32f);

		}
		App->render->camera.x -= 3;
		if (App->render->camera.x <= -2929 * SCREEN_SIZE)
			part_stage++;
		break;
	}
	case 1: { //Start 
		for (int i = 0; i < 70; i++) {
			if (App->render->camera.y >= -130 * SCREEN_SIZE) {
				App->render->Blit(back_tx, background.w*i, 123, &background, 0.40f);
			}
			//Blit Stars, "(SCREEN_WIDTH*i) + 15" Means position.x, "15" is the initial star position.
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 5.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 41, &star7, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);
			App->render->camera.x -= 3;
		}
		App->render->camera.y -= 3;
		if (App->render->camera.y <= -SCREEN_HEIGHT * SCREEN_SIZE)
			part_stage++;
		break;
	}
	case 2: { //Post Downfall & Pre Diagonal rise  
		for (int i = 0; i < 20; i++)
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
		App->render->Blit(back_tx, 1500, 61, &rocks_entry, 0.40f);
		App->render->camera.x -= 3;

		if (App->render->camera.x <= -4000 * SCREEN_SIZE)
			part_stage++;
		break;
	}
	case 3: {//Diagonal rise Up
		for (int i = 0; i < 50; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->camera.x -= 3;
		App->render->camera.y += 3;
		if (App->render->camera.y >= -294)
			part_stage++;
		break;
	}
	case 4: {//Post Diagonal rise Up & Diagonal rise Down  
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->camera.x -= 3;
		if (App->render->camera.x <= -4538 * SCREEN_SIZE)
			part_stage++;
		break;
	}
	case 5: { //Diagonal rise Down
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->camera.x -= 3;
		App->render->camera.y -= 3;
		if (App->render->camera.y <= -SCREEN_HEIGHT * SCREEN_SIZE)
			part_stage++;
		break;
	}
	case 6://Post Diagonal rise Down & Pre Diagonal rise Up
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->camera.x -= 3;
		if (App->render->camera.x <= -5040 * SCREEN_SIZE)
			part_stage++;
		break;
	case 7://Diagonal rise Up
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->camera.x -= 3;
		App->render->camera.y += 3;
		if (App->render->camera.y >= 0)
			part_stage++;
		break;
	case 8://Post Diagonal rise Up & Pre Diagonal rise Down
		App->render->camera.x -= 3;
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		if (App->render->camera.x <= -6020 * SCREEN_SIZE)
			part_stage++;
		break;
	case 9://Diagonal rise Down
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		App->render->camera.x -= 3;
		App->render->camera.y -= 3;
		if (App->render->camera.y <= -SCREEN_HEIGHT * SCREEN_SIZE)
			part_stage++;
		break;
	case 10://Post Diagonal Down & Pre Rise Up
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			
			
		}
		App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		App->render->camera.x -= 3;
	
	
		if (App->render->camera.x <= -7156 * SCREEN_SIZE)
			part_stage++;
		break;
	case 11: //Rise Up
		for (int i = 0; i < 200; i++) {
			
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 41, &star7, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);
		}

		App->render->Blit(ground_tx, 0, -94, &ground);
		App->render->camera.y += 3;
		if (App->render->camera.y >= 0)
			part_stage++;
		break;
	case 12:
		for (int i = 0; i < 200; i++) {
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);

			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 41, &star7, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);
		}
		App->render->Blit(back_tx, 2670, 17, &planet2, 0.32f);
		App->render->camera.x -= 3;
		if (App->render->camera.x <= -26241)
			part_stage++;
		break;
	case 13:
		for (int i = 0; i < 70; i++) {
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 41, &star7, 0.5f);
			App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);
		}
		App->render->camera.x -= 3;
		App->render->camera.y += 3;
		if (App->render->camera.y >= 828)
			part_stage++;
		break;
	case 14:
		//only stars and boss, no mov of camera
		break;
	}
	App->render->Blit(ground_tx, 0, -94, &ground);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->FadeToBlack->FadeToBlack(App->background, App->mainmenu, 1);
	}

	return UPDATE_CONTINUE;
}

bool ModuleBackground::CleanUp()
{
	LOG("Unloading players");
	App->player1->Disable();
	App->player2->Disable();

	LOG("Unloading stage1");
	App->textures->Unload(stars_tx);
	App->textures->Unload(back_tx);
	App->textures->Unload(ground_tx);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return true;
}