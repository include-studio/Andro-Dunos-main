#include "Globals.h"
#include "Application.h"
#include "ModuleStage1.h"
#include "ModuleTextures.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"


ModuleStage1Floor::ModuleStage1Floor() {
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
}
ModuleStage1Floor::~ModuleStage1Floor() {}

bool ModuleStage1Floor::Start() {

	part_stage = 0;

	ground_tx = App->textures->Load("assets/Sprites/Ground.png");

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

	//-----------------------------------------
	//-----------------------------------------
	//Enamble modules
	App->collision->Enable();



	return true;
}

update_status ModuleStage1Floor::Update() {


	switch (part_stage) {
	case 0: //case 0: Start & PreDownfall
			//logic
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 2945 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}
		//draw
		break;

	case 1: //Downfall 
		App->render->camera.y += 3;
		App->player1->position.y++;
		App->player2->position.y++;
		if (App->render->camera.y >= (SCREEN_HEIGHT - 1) * SCREEN_SIZE) {
			part_stage++;
			break;

	case 2: //Post Downfall & Pre Diagonal rise  
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 4000 * SCREEN_SIZE)
			part_stage++;
		break;

	case 3: //Diagonal rise Up
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		if (App->render->camera.y <= 294)
			part_stage++;
		break;

	case 4: //Post Diagonal rise Up & Diagonal rise Down  
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 4538 * SCREEN_SIZE)
			part_stage++;
		break;

	case 5:  //Diagonal rise Down
		App->render->camera.x += 3;
		App->render->camera.y += 3;
		App->player1->position.x++;
		App->player1->position.y++;
		App->player2->position.x++;
		App->player2->position.y++;
		if (App->render->camera.y >= (SCREEN_HEIGHT - 1) * SCREEN_SIZE)
			part_stage++;
		break;

	case 6://Post Diagonal rise Down & Pre Diagonal rise Up
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;

		if (App->render->camera.x >= 5040 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}
		break;

	case 7://Diagonal rise Up
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		if (App->render->camera.y <= 0)
			part_stage++;
		break;

	case 8://Post Diagonal rise Up & Pre Diagonal rise Down
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 6020 * SCREEN_SIZE)
			part_stage++;
		break;

	case 9://Diagonal rise Down
		App->render->camera.x += 3;
		App->render->camera.y += 3;
		App->player1->position.x++;
		App->player1->position.y++;
		App->player2->position.x++;
		App->player2->position.y++;
		if (App->render->camera.y >= (SCREEN_HEIGHT - 1) * SCREEN_SIZE)
			part_stage++;
		break;

	case 10://Post Diagonal Down & Pre Rise Up
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 7156 * SCREEN_SIZE) {
			part_stage++;
			ground_cont++;
		}
		break;

	case 11: //Rise Up
		App->render->camera.y -= 3;
		App->player1->position.y--;
		App->player2->position.y--;
		if (App->render->camera.y <= 0)
			part_stage++;
		break;

	case 12:// Post Rise Up & Pre Diagonal to Boss 
		App->render->camera.x += 3;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 26241)
			part_stage++;
		break;

	case 13://Diagonal to Boss
		App->render->camera.x += 3;
		App->render->camera.y -= 3;
		App->player1->position.x++;
		App->player1->position.y--;
		App->player2->position.x++;
		App->player2->position.y--;
		if (App->render->camera.y <= -228) {
			part_stage++;
		}
		break;

	case 14: // Boss
			 //App->render->camera.x -= 3;
		break;
		}
	}
	for (int i = ground_cont; i < ground_cont + 2; i++)
		App->render->Blit(ground_tx, ground[0].w*i, 0, &ground[i]);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleStage1Floor::CleanUp() {

	App->textures->Unload(ground_tx);

	ground_cont = 0;

	return true;
}
