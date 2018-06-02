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
	
	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 370, 60); //WAVINGSHIP
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 383, 60); 
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 396, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 409, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 470, 140); 
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 483, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 496, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 509, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 570, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 583, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 596, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 609, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 670, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 683, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 696, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 709, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 838, 90); // ENEMY_POWERUP

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1030, 40); //HORIZONTALROCKET
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1015, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1030, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1100, 100); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1085, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1100, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1170, 40); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1155, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1170, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1270, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1255, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1225, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1240, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1255, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1270, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1355, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1340, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1370, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1410, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1425, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1440, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::VENDING, 1370, 175); //VENDING

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1383, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1382, 230);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1381, 260);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1380, 290);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 1600, 90); //POWERUP 2

	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1703, SCREEN_HEIGHT/2); //MINI-MINIBOSS
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1753, (SCREEN_HEIGHT / 2) + 40, true);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1753, (SCREEN_HEIGHT / 2) - 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1803, (SCREEN_HEIGHT / 2) + 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1803, (SCREEN_HEIGHT / 2) - 40);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 2270, 120); //TINY RED SHIP
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 2310, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 2350, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 2390, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 2340, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 2380, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 2420, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 2460, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 2558, 90); //POWER UP 3

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 3900, 330); //POWER UP 4 underground

	App->enemies->AddEnemy(ENEMY_TYPES::VENDING, 5500, 185); //VENDING underground

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 5513, 212);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 5512, 242);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 5511, 272);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 5510, 302);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 6080, 160); //TINY RED SHIP underground
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 6120, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 6160, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 6200, 160); 

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 6250, 110); //POWER UP 5

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6900, 300); //HORITZONTAL ROCKET ZIGZAG
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6915, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6930, 300);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 7000, 400);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 7015, 400);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 7030, 400);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 7100, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 7115, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 7130, 300);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 7540, 50);  //TINY RED SHIP SURFACE
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 7580, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 7620, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 7660, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7970, 120); //TINY RED SHIP
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 8010, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 8050, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 8090, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 8040, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 8080, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 8120, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 8160, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8300, 60); //HORITZONTAL ROCKET ZIGZAG
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8315, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8330, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8400, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8415, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8430, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8500, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8515, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8530, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8600, 60); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8615, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8630, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8600, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8615, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8630, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8800, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8815, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 8830, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8800, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8815, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 8830, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 9000, 90); //POWER UP 5

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

