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
	rocks.x = 252;
	rocks.y = 0;
	rocks.w = 64;
	rocks.h = 224;

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
	planet.x = 0;
	planet.y = 0;
	planet.w = 106;
	planet.h = 106;
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
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	switch (part_stage) {
		case 0: { 
			for (int i = 0; i < 20; i++) {
				App->render->Blit(back_tx, background.w*i, 123, &background,0.42f);
				
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 15, 31, &star1, 2.0f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 15, 46, &star2, 1.0f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 97, &star3, 0.5f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 60, 97, &star4, 2.0f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 100, 63, &star5, 1.0f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) - 13, 63, &star6, 0.5f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) +50, 41, &star7, 0.5f);
				App->render->Blit(stars_tx, (SCREEN_WIDTH*i) + 50, 87, &star6, 1.0f);
<<<<<<< HEAD
			}	
=======
			}
			App->render->Blit(ground_tx, 0, -94, &ground);
			App->render->Blit(back_tx, 650, 20, &planet, 0.2f);
>>>>>>> 9ae9bfb3a13f4a8dc9e12a35088f6682d7b0428a
			App->render->camera.x-=3;
			if (App->render->camera.x <= -2929*SCREEN_SIZE)
				part_stage++;
			break;
		}
		case 1: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);
			}			
			App->render->camera.y -= 3;
			if (App->render->camera.y <= -SCREEN_HEIGHT*SCREEN_SIZE)
				part_stage++;
			break;
		}
		case 2: {
			for (int i = 0; i < 20; i++) {
				App->render->Blit(back_tx, 3250*SCREEN_SIZE + rocks.w*i, 220, &rocks,0.42f);
			}
			App->render->camera.x -= 3;

			if (App->render->camera.x <= -3910 * SCREEN_SIZE)
				part_stage++;
			break;
		}
		case 3: {
			for (int i = 0; i < 50 ; i++) {
				App->render->Blit(back_tx, 3000 + SCREEN_WIDTH + rocks.w*i, 220, &rocks,0.42f);
			}
			App->render->camera.x -= 3;
			App->render->camera.y += 3;
			if (App->render->camera.y >= -294)
				part_stage++;
			break;
		}
		case 4: {
			for (int i = 0; i < 70; i++) {
				App->render->Blit(back_tx, 3000 + SCREEN_WIDTH + rocks.w*i, 220, &rocks, 0.42f);
			}
			App->render->camera.x -= 3;
			if (App->render->camera.x <= -4538*SCREEN_SIZE)
				part_stage++;
			break;
		}
		case 5:
			App->render->camera.x -= 3;
			App->render->camera.y -= 3;
			if (App->render->camera.y <= -SCREEN_HEIGHT*SCREEN_SIZE)
				part_stage++;
			break;
		case 6:
			App->render->camera.x -= 3;
			if (App->render->camera.x <= -5040*SCREEN_SIZE)
				part_stage++;
			break;
		case 7:
			App->render->camera.x -= 3;
			App->render->camera.y += 3;
			if (App->render->camera.y >= 0)
				part_stage++;
			break;
		case 8:
			App->render->camera.x -= 3;
			if (App->render->camera.x <= -6020*SCREEN_SIZE)
				part_stage++;
			break;
		case 9:
			App->render->camera.x -= 3;
			App->render->camera.y -= 3;
			if (App->render->camera.y <= -SCREEN_HEIGHT*SCREEN_SIZE)
				part_stage++;
			break;
		case 10:
			App->render->camera.x -= 3;
			if (App->render->camera.x <= -7136 * SCREEN_SIZE)
				part_stage++;
			break;
		case 11:
			App->render->camera.y += 3;
			if (App->render->camera.y >= 0)
				part_stage++;
			break;
		case 12:
			for (int i = 0; i < 20; i++) {
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
			break;
	}
	App->render->Blit(ground_tx, 0, -94, &ground);
	return UPDATE_CONTINUE;
}