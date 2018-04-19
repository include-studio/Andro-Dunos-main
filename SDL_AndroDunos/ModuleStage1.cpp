#include "Globals.h"
#include "Application.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStageClear.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

ModuleStage1::ModuleStage1()
{
	// ground1
	ground[0].x = 0;
	ground[0].y = 0;
	ground[0].w = 2048;
	ground[0].h = 224;

	//ground2
	ground[1].x = 0;
	ground[1].y = 224;
	ground[1].w = 2048;
	ground[1].h = 447;

	//ground3
	ground[2].x = 0;
	ground[2].y = 672;
	ground[2].w = 2048;
	ground[2].h = 447;

	//ground 4
	ground[3].x = 0;
	ground[3].y = 1119;
	ground[3].w = 2048;
	ground[3].h = 475;

	//ground 5
	ground[4].x = 0;
	ground[4].y = 1594;
	ground[4].w = 1113;
	ground[4].h = 226;

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

	part_stage = 0;

	App->render->camera.x = 0;
	App->render->camera.x = 0;

	stars_tx = App->textures->Load("assets/Stars.png");
	back_tx = App->textures->Load("assets/Background.png");
	ground_tx = App->textures->Load("assets/Ground.png");

	App->collision->AddCollider({ 0,195,1098,39 }, COLLIDER_WALL); //Initial Floor
	App->collision->AddCollider({ 1491,195,1480,39 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1098,204,393,20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 905,184,103,11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1560,189,103,6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2362,189,103,6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2601,184,103,11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2971,187,39,214 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2960,401,114,47 }, COLLIDER_WALL);
	
	App->collision->AddCollider({ 3204,187 ,45,108 }, COLLIDER_WALL); //Top
	App->collision->AddCollider({ 3218,295 ,15,10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3249,215 ,90,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3339,215 ,90,35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3429,190 ,635,45 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4064,190 ,17,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4064,160 ,62,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4126,130 ,30,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4156, 90 ,30,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4186, 70 ,600,40 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6286, 0, 30, 30 }, COLLIDER_WALL); //Top 2
	App->collision->AddCollider({ 6316, 30, 30, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6346, 60, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6396, 90, 40, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6426, 140, 40, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6466, 170, 40, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6506, 205, 650, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7156, 185, 45, 105 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7036, 240, 120, 20 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3074,430,1006,18 }, COLLIDER_WALL); //Downfall
	App->collision->AddCollider({ 3893,418,64,12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4080,421,29,29 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4109,389,30,58 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4139,351,81,89 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4183,325,20,26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4203,311,402,40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4605,331,15,30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4605,361,65,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4670,387,25,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4695,416,31,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4726,430,490,25 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5216,415,32,25 }, COLLIDER_WALL); //Rise
	App->collision->AddCollider({ 5248,385,27,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5275,357,50,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5325,307,35,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5360,277,30,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5390,247,53,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5443,209,770,55 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6213,247,53,55 }, COLLIDER_WALL);//Downfall
	App->collision->AddCollider({ 6266,277,30,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6296,307,35,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6331,357,50,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6381,385,27,55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6408,415,32,25 }, COLLIDER_WALL); 
	App->collision->AddCollider({ 6440,435,910,25 }, COLLIDER_WALL);


	App->collision->AddCollider({ 7350,415,90,25 }, COLLIDER_WALL);//Rise
	App->collision->AddCollider({ 7370,400,90,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7400,200,90,200 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7412,180,20,20 }, COLLIDER_WALL);

	App->collision->AddCollider({ 7490,200,1700,40 }, COLLIDER_WALL); // Final Floor
	App->collision->AddCollider({ 7780,190,105,10 }, COLLIDER_WALL); // End Crater 1
	App->collision->AddCollider({ 8410,190,105,10 }, COLLIDER_WALL); // End Crater 2
	App->collision->AddCollider({ 8650,190,105,10 }, COLLIDER_WALL); // End Crater 3



	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 300, 60); //WAVINGSHIP
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 315, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 326, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 338, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 435, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 445, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 456, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 468, 140);


	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 550, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 565, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 576, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 588, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 705, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 715, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 726, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 738, 140);

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
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1230, 87);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1265, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1285, 125);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1375, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1365, 65);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1345, 85);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1440, 87);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1465, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1485, 125);



	//App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET, 1038, 170);





	App->audio->Load("assets/Stage_1__The_Moon_Loop.ogg");
	
	App->player1->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	if (App->player2->insert2 == true) 
	{
		App->player2->Enable();
	}
	camera_limit.xi = 0;
	camera_limit.xf = SCREEN_WIDTH-39;//-player width
	camera_limit.yi = 0;
	camera_limit.yf = SCREEN_HEIGHT-17;//-player height

	return ret;
}

bool ModuleStage1::CleanUp()
{
	LOG("Unloading players");
	App->player1->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();

	LOG("Unloading stage1");
	App->textures->Unload(stars_tx);
	App->textures->Unload(back_tx);
	App->textures->Unload(ground_tx);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	ground_cont = 0;
	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_2]==KEY_STATE::KEY_DOWN) {
		switch (App->player2->IsEnabled()) {
		case true:
			App->player2->Disable();
			break;
		case false:
			App->player2->Enable();
			App->player2->position.x = App->player1->position.x;
			App->player2->position.y = 2 * SCREEN_HEIGHT / 3;
			break;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_X])
		App->fade->FadeToBlack(this, App->stageclear, 0.5);
	if (App->input->keyboard[SDL_SCANCODE_C])
		App->fade->FadeToBlack(this, App->gameover, 0.5);
	switch (part_stage) {
	case 0: //case 0: Start & PreDownfall
		//logic
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 2945 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}
		//draw
		for (int i = 0; i < 12; i++)
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.382f);

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 20; j++)
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		App->render->Blit(back_tx, 800, 17, &planet1, 0.32f);

		break;

	case 1: //Downfall 
		App->render->camera.y += 3;
		App->player1->position.y++;
		App->player2->position.y++;
		camera_limit.yi++;
		camera_limit.yf++;
		if (App->render->camera.y >= (SCREEN_HEIGHT-1) * SCREEN_SIZE) {
			part_stage++;
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
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 4000 * SCREEN_SIZE)
			part_stage++;

		for (int i = 0; i < 20; i++)
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
		
		App->render->Blit(back_tx, 1500, 61, &rocks_entry, 0.40f);
		
		break;

	case 3: //Diagonal rise Up
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		camera_limit.xi++;
		camera_limit.xf++;
		camera_limit.yi--;
		camera_limit.yf--;
		if (App->render->camera.y <= 294)
			part_stage++;

		for (int i = 0; i < 50; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 4: //Post Diagonal rise Up & Diagonal rise Down  
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 4538 * SCREEN_SIZE)
			part_stage++;

		for (int i = 0; i < 12; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;
	
	case 5:  //Diagonal rise Down
		App->render->camera.x += 3;
		App->render->camera.y += 3;
		App->player1->position.x++;
		App->player1->position.y++;
		App->player2->position.x++;
		App->player2->position.y++;
		camera_limit.xi++;
		camera_limit.xf++;
		camera_limit.yi++;
		camera_limit.yf++;
		if (App->render->camera.y >= (SCREEN_HEIGHT-1) * SCREEN_SIZE)
			part_stage++;

		for (int i = 0; i < 12; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 6://Post Diagonal rise Down & Pre Diagonal rise Up
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 5040 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}

		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 7://Diagonal rise Up
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		camera_limit.xi++;
		camera_limit.xf++;
		camera_limit.yi--;
		camera_limit.yf--;
		if (App->render->camera.y <= 0)
			part_stage++;

		for (int i = 0; i < 30; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 8://Post Diagonal rise Up & Pre Diagonal rise Down
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 6020 * SCREEN_SIZE)
			part_stage++;

		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
		}
		break;

	case 9://Diagonal rise Down
		App->render->camera.x += 3;
		App->render->camera.y += 3;
		App->player1->position.x++;
		App->player1->position.y++;
		App->player2->position.x++;
		App->player2->position.y++;
		camera_limit.xi++;
		camera_limit.xf++;
		camera_limit.yi++;
		camera_limit.yf++;
		if (App->render->camera.y >= (SCREEN_HEIGHT - 1) * SCREEN_SIZE)
			part_stage++;

		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 1500 + (rocks.w*i), -131, &rocks, 0.40f);
			App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		}
		break;

	case 10://Post Diagonal Down & Pre Rise Up
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 7156 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}

		for (int i = 0; i < 20; i++) {
			App->render->Blit(back_tx, 1500 + (rocks.w*i), 61, &rocks, 0.40f);
			App->render->Blit(back_tx, 2715 + rocks.w, 61, &rocks_escape, 0.40f);
		}
		break;

	case 11: //Rise Up
		App->render->camera.y -= 3;
		App->player1->position.y--;
		App->player2->position.y--;
		camera_limit.yi--;
		camera_limit.yf--;
		if (App->render->camera.y <= 0)
			part_stage++;

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
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		camera_limit.xi++;
		camera_limit.xf++;
		if (App->render->camera.x >= 26241)
			part_stage++;

		for (int i = 0; i < 200; i++)
			App->render->Blit(back_tx, background.w*i, 123, &background, 0.42f);
		for (int i = 0; i < 9; i++)
			for (int j = 20; j < 100; j++)
				App->render->Blit(stars_tx, star[i].starposx + SCREEN_WIDTH * j, star[i].starposy, &star[i].star, star[i].speed);
		App->render->Blit(back_tx, 2670, 17, &planet2, 0.32f);
		break;

	case 13://Diagonal to Boss
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		camera_limit.xi++;
		camera_limit.xf++;
		camera_limit.yi--;
		camera_limit.yf--;
		if (App->render->camera.y <= -228) {
			part_stage++;
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
	for (int i = ground_cont; i < ground_cont+2; i++)
		App->render->Blit(ground_tx, ground[0].w*i, 0, &ground[i]);
	
	if (App->player1->position.x < camera_limit.xi)
		App->player1->position.x = camera_limit.xi;
	if (App->player1->position.x > camera_limit.xf)
		App->player1->position.x = camera_limit.xf;
	if (App->player1->position.y < camera_limit.yi)
		App->player1->position.y = camera_limit.yi;
	if (App->player1->position.y > camera_limit.yf)
		App->player1->position.y = camera_limit.yf;

	if (App->player2->position.x < camera_limit.xi)
		App->player2->position.x = camera_limit.xi;
	if (App->player2->position.x > camera_limit.xf)
		App->player2->position.x = camera_limit.xf;
	if (App->player2->position.y < camera_limit.yi)
		App->player2->position.y = camera_limit.yi;
	if (App->player2->position.y > camera_limit.yf)
		App->player2->position.y = camera_limit.yf;


	if (App->input->keyboard[SDL_SCANCODE_C] == 1)
	{
		App->fade->FadeToBlack(this, App->stageclear, 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == 1)
	{
		App->fade->FadeToBlack(this, App->gameover, 1);
	}

	return UPDATE_CONTINUE;
}

