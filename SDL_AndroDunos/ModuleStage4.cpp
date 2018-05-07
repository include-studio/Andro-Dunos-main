#include "Globals.h"
#include "Application.h"
#include "ModuleStage4.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
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
#include "ModulePowerUp.h"

ModuleStage4::ModuleStage4() {
	//background
	back.x = 0;
	back.y = 0;
	back.w = 1024;
	back.h = 323;

	//ground
	ground[0].x = 0;
	ground[0].y = 0;
	ground[0].w = 2048;
	ground[0].h = 319;

	ground[1].x = 0;
	ground[1].y = 319;
	ground[1].w = 673;
	ground[1].h = 319;

	ground[2].x = 0;
	ground[2].y = 672;
	ground[2].w = 2048;
	ground[2].h = 285;

	ground[3].x = 0;
	ground[3].y = 1090;
	ground[3].w = 1113;
	ground[3].h = 324;

	//water
	water.x = 1235;
	water.y = 978;
	water.w = 304;
	water.h = 21;

}

ModuleStage4::~ModuleStage4(){}

bool ModuleStage4::Start() {
	bool ret = true;
	//load textures
	back_tx = App->textures->Load("assets/Sprites/background4.png");
	ground_tx = App->textures->Load("assets/Sprites/ground4.png");
	//colliders
	//reset variables (camera position, players position...)
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	stage = 0;
	//enemies
	//audio
	//enable modules
	App->player1->Enable();
	if (App->player2->insert2 == true)
	{
		App->player2->Enable();
	}

	return ret;
}

bool ModuleStage4::CleanUp() {
	//disable modules
	App->player1->Disable();
	App->player2->Disable();
	//unload textures
	App->textures->Unload(back_tx);

	return true;
}

update_status ModuleStage4::Update() {
	//input

	//logic
	/*switch (stage) {
	case 0:				//scroll diagonal to y=43
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y += 1;
		App->render->Blit(back_tx, 0, 0, NULL, BACKGROUND4SPEED);
		

		if (App->render->camera.y >= 43*SCREEN_SIZE)
			stage++;;
		break;
	case 1:				//scroll horizontal
		App->render->camera.x += 1 * SCREEN_SIZE;

		for (int i = 0; i < 3; i++)
			App->render->Blit(back_tx, back.w*i, 0, NULL, BACKGROUND4SPEED);
		App->render->Blit(ground_tx, 1000, -58, &ground[0], GROUND4SPEED);

		if (App->render->camera.x >= 1950 * SCREEN_SIZE)
			stage++;;
		break;
	case 2:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y--;

		for (int i = 0; i < 3; i++)
			App->render->Blit(back_tx, back.w*i, 0, NULL, BACKGROUND4SPEED);
		App->render->Blit(ground_tx, 1000, -52, &ground[0], GROUND4SPEED);

		if (App->render->camera.y <= -156)
			stage++;
		break;
	case 3:
		App->render->camera.x += 1 * SCREEN_SIZE;

		for (int i = 0; i < 3; i++)
			App->render->Blit(back_tx, back.w*i, 0, NULL, BACKGROUND4SPEED);
		App->render->Blit(ground_tx, 1000, -52, &ground[0], GROUND4SPEED);


	}*/
	
	//case 2 scroll diagonal up right
	//case 3 scroll horizontal
		//wall brakable
	//case 4 scroll diagonal down
	//case 5 scroll horizontal water + big boss
	//case 6 scroll diagonal up
	//case 7 scroll horizontal
	//case 8 scroll horizontal lower until stop
	//case 9 camera no move, final boss
		
	for (int i = 0; i < 5; i++)
		App->render->Blit(ground_tx, (1000 + ground[0].w + ground[1].w) + water.w*i-9, 318, &water, GROUND4SPEED);

	App->render->Blit(ground_tx, 1000, -95, &ground[0], GROUND4SPEED);
	App->render->Blit(ground_tx, 1000 + ground[0].w, 20, &ground[1], GROUND4SPEED);
	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w, 54, &ground[2], GROUND4SPEED);
	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w  + ground[2].w, 15, &ground[3], GROUND4SPEED);
	App->render->camera.x += 1 * SCREEN_SIZE;
	App->player1->position.x++;

	//draw everithing
	

	return UPDATE_CONTINUE;
}