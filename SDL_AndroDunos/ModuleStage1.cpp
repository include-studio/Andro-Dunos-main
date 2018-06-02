#include "Globals.h"
#include "Application.h"
#include "ModuleStage1.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModulePowerUp.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStageClear.h"
#include "ModuleGameOver.h"
#include "ModuleStage4.h"


ModuleStage1::ModuleStage1()
{
	

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
	for (int i = 0; i < 9; i++) {
		star[i].star.y = 0;
		star[i].star.w = 3;
		star[i].star.h = 3;
	}
	star[0].starposy = SCREEN_HEIGHT * 14 / 100; star[0].starposx = 269; star[0].speed = 2.0f; star[0].star.x = 0 ;
	star[1].starposy = SCREEN_HEIGHT * 18 / 100; star[1].starposx = 43;  star[1].speed = 0.9f; star[1].star.x = 15;
	star[2].starposy = SCREEN_HEIGHT * 20 / 100; star[2].starposx = 58;  star[2].speed = 0.9f; star[2].star.x = 18;
	star[3].starposy = SCREEN_HEIGHT * 21 / 100; star[3].starposx = 261; star[3].speed = 1.5f; star[3].star.x = 3;
	star[4].starposy = SCREEN_HEIGHT * 28 / 100; star[4].starposx = 54;  star[4].speed = 1.5f; star[4].star.x = 12;
	star[5].starposy = SCREEN_HEIGHT * 28 / 100; star[5].starposx = 274; star[5].speed = 0.9f; star[5].star.x = 15;
	star[6].starposy = SCREEN_HEIGHT * 42 / 100; star[6].starposx = 224; star[6].speed = 0.9f; star[6].star.x = 15;
	star[7].starposy = SCREEN_HEIGHT * 42 / 100; star[7].starposx = 45;  star[7].speed = 2.0f; star[7].star.x = 9;
	star[8].starposy = SCREEN_HEIGHT * 42 / 100; star[8].starposx = 81;  star[8].speed = 1.5f; star[8].star.x = 6;
	for(int i=0;i<9;i++)
		starpos[i] = star[i].starposx;

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

ModuleStage1::~ModuleStage1()
{}

// Load assets
bool ModuleStage1::Start()
{
	
	LOG("Loading stage1 assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.x = 0;

	stars_tx = App->textures->Load("assets/Sprites/Stars.png");
	back_tx = App->textures->Load("assets/Sprites/Background.png");

	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 400, 80); 
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 375, 50);

	
	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 370, 60); //WAVINGSHIP
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 385, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 396, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 408, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 435, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 445, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 456, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 468, 140);


	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 550, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 565, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 576, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 588, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 705, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 715, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 726, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 738, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 838, 90); // ENEMY_POWERUP
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 1738, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 2558, 90);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 935, 40); //HORIZONTALROCKET
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 915, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 936, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1035, 100); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1015, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1036, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1135, 40); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1115, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1136, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1285, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1265, 65);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1245, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1230, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1265, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1285, 125);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1375, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1365, 65);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1345, 85);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1440, 87);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1465, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1485, 125);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1703, SCREEN_HEIGHT/2); //MINI-MINIBOSS
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1753, (SCREEN_HEIGHT / 2) + 40, true);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1753, (SCREEN_HEIGHT / 2) - 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1803, (SCREEN_HEIGHT / 2) + 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1803, (SCREEN_HEIGHT / 2) - 40);




	App->audio->PlayMusic("assets/Audio/Stage_1__The_Moon_Loop.ogg");
	
	App->player1->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	App->powerup->Enable();
	App->stage1floor->Enable();

	if (App->player2->insert2 == true) 
	{
		App->player2->Enable();
	}

	return ret;
}

bool ModuleStage1::CleanUp()
{
	LOG("Unloading players");
	App->player1->Disable();
	App->player2->Disable();
	

	LOG("Unloading stage1");
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	App->powerup->Disable();
	App->stage1floor->Disable();
	App->textures->Unload(stars_tx);
	App->textures->Unload(back_tx);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_2]==KEY_STATE::KEY_DOWN && App->ui->credit > 0) {
		if (!App->player2->IsEnabled()) {
			App->player2->Enable();
			App->player2->position.x = App->player1->position.x;
			App->player2->position.y = 2 * SCREEN_HEIGHT / 3;
			App->player2->insert2 = true;
			/*App->ui->credit--;*/
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F11])
		App->fade->FadeToBlack(this, App->stageclear, 0.5);
	if (App->input->keyboard[SDL_SCANCODE_F12])
		App->fade->FadeToBlack(this, App->gameover, 0.5);

	switch (App->stage1floor->part_stage) {
	case 0: //case 0: Start & PreDownfall
		//draw
		for (int i = 0; i < 12; i++)
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.382f);

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 20; j++)
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		App->render->Blit(back_tx, 800, 17, &planet1, 0.32f);

		break;

	case 1: //Downfall 
		if (App->render->camera.y >= (SCREEN_HEIGHT-1) * SCREEN_SIZE) {
			for (int i = 0; i < 9; i++)
				starpos[i] = star[i].starposx;//resets auxiliar variable star position
		}
		for (int i = 0; i < 9; i++) {
			starpos[i] -= star[i].speed/4;
			for (int j = 0; j < 20; j++)
				App->render->Blit(stars_tx, starpos[i] + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		}
		for (int i = 0; i < 12; i++) 
		{
			if (App->render->camera.y >= -130 * SCREEN_SIZE)
				App->render->Blit(back_tx, background.w*i, 123, &background, 0.40f);
		}
		break;

	case 2: //Post Downfall & Pre Diagonal rise  
		for (int i = 0; i < 20; i++)
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
		
		App->render->Blit(back_tx, 1500, 61, &rocks_entry, 0.40f);
		
		break;

	case 3: //Diagonal rise Up
		for (int i = 0; i < 50; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 4: //Post Diagonal rise Up & Diagonal rise Down  
		for (int i = 0; i < 12; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;
	
	case 5:  //Diagonal rise Down
		for (int i = 0; i < 12; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 6://Post Diagonal rise Down & Pre Diagonal rise Up
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 7://Diagonal rise Up
		for (int i = 0; i < 30; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 8://Post Diagonal rise Up & Pre Diagonal rise Down
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 9://Diagonal rise Down
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
			App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		}
		break;

	case 10://Post Diagonal Down & Pre Rise Up
		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		}
		break;

	case 11: //Rise Up
		for (int i = 0; i < 20; i++)
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);

		for (int i = 0; i < 9; i++) {
			
			for (int j = 0; j < 400; j++) {
				//starpos[i] -= star[i].speed / 4;
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
			}
		}
		break;

	case 12:// Post Rise Up & Pre Diagonal to Boss 
		for (int i = 0; i < 200; i++)
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);
		for (int i = 0; i < 9; i++)
			for (int j = 20; j < 100; j++)
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		App->render->Blit(back_tx, 2670, 17, &planet2, 0.32f);
		break;

	case 13://Diagonal to Boss
		if (App->render->camera.y <= -228) {
			for (int i = 0; i < 9; i++)
				starpos[i] = star[i].starposx;
		}

		for (int i = 0; i < 200; i++) 
			App->render->Blit(back_tx, background.w*i, 123, &background);
		for (int i = 0; i < 9; i++)
			for (int j = 20; j < 100; j++)
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		break;

	case 14: // Boss
		//App->render->camera.x -= 3;

		for (int i = 0; i < 200; i++) 
			App->render->Blit(back_tx, background.w*i, 123, &background);
		for (int i = 0; i < 9; i++){
			starpos[i] -= star[i].speed;
			for (int j = 20; j < 100; j++)
				App->render->Blit(stars_tx, starpos[i] + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		}
		for (int i = 150; i < 200; i++)
			App->fade->FadeToBlack(this, App->stageclear, 1);
		break;
	}

	if (App->input->keyboard[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->stage4, 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->stageclear, 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_F12] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->gameover, 1);
	}

	return UPDATE_CONTINUE;
}

