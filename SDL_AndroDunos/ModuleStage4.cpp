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

	App->collision->AddCollider({ 1000,215,125,100 }, COLLIDER_WALL); //x y w h
	App->collision->AddCollider({ 1240,215,125,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1365,200,125,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1490,175,175,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1665,190,80,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1745,200,175,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1920,185,135,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2055,170,64,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2119,155,65,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2184,140,65,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2249,125,95,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2344,145,110,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2454,125,160,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2614,110,225,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2839,80,80,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2919,45,45,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2964,85,255,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3219,122,127,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3346,142,65,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3411,157,15,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3426,188,33,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3459,203,15,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3474,233,80,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3554,263,30,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3584,288,30,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3614,308,90,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3704,323,1530,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5234,313,275,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5509,288,25,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5534,268,50,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5584,328,225,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6065,328,508,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6573,308,130,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6703,298,20,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6723,278,20,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6743,285,90,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6833,265,125,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6958,250,62,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7020,280,80,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7100,310,80,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7180,290,90,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7270,270,100,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7370,205,65,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7435,160,285,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7720,200,210,100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7930,235,500,100 }, COLLIDER_WALL);









	//reset variables (camera position, players position...)
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	stage = 0;
	//enemies

	//audio
	App->audio->PlayMusic("assets/Audio/11_Stage_4 -Caven-Loop.ogg");

	//enable modules
	App->player1->Enable();
	App->particles->Enable();
	App->collision->Enable();
	/*App->enemies->Enable();*/
	App->powerup->Enable();

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