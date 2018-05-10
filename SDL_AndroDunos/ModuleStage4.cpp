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
#include "SDL/include/SDL.h"


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
	water.PushBack({ 1235,978,304,21 });
	water.PushBack({ 1235,1017,304,21 });
	water.PushBack({ 1235,1056,304,21 });
	water.PushBack({ 1235,1095,304,21 });
	water.PushBack({ 1235,1136,304,21 });
	water.loop = true;
	water.speed = 0.08f;

}

ModuleStage4::~ModuleStage4(){}

bool ModuleStage4::Start() {
	bool ret = true;
	//load textures
	back_tx = App->textures->Load("assets/Sprites/background4.png");
	ground_tx = App->textures->Load("assets/Sprites/ground4.png");

	//colliders
	App->collision->AddCollider({ 1000,215,125,100 }, COLLIDER_WALL4); //x y w h
	App->collision->AddCollider({ 1240,215,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1365,200,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1490,175,175,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1665,190,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1745,200,175,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1920,185,135,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2055,170,64,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2119,155,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2184,140,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2249,125,95,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2344,145,110,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2454,125,160,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2614,110,225,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2839,80,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2919,45,45,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2964,85,255,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3219,122,127,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3346,142,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3411,157,15,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3426,188,33,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3459,203,15,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3474,233,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3554,263,30,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3584,288,30,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3614,308,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3704,323,1530,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5234,313,275,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5509,288,25,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5534,268,50,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5584,328,225,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6065,328,508,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6573,308,130,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6703,298,20,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6723,278,20,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6743,285,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6833,265,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6958,250,62,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7020,280,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7100,310,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7180,290,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7270,270,100,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7370,205,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7435,160,285,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7720,200,210,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7930,235,500,100 }, COLLIDER_WALL4);


	App->collision->AddCollider({ 1645,-40,545,50 }, COLLIDER_WALL4); //Up
	App->collision->AddCollider({ 2190,-60,65,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2255,-110,295,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2550,-90,195,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2745,-130,100,50 }, COLLIDER_WALL4);

	App->collision->AddCollider({ 5585,90,50,50 }, COLLIDER_WALL4); //Up 2
	App->collision->AddCollider({ 5635,80,160,100 }, COLLIDER_WALL4);  
	App->collision->AddCollider({ 5795,95,210,50 }, COLLIDER_WALL4);

	App->collision->AddCollider({ 7070,90,20,50 }, COLLIDER_WALL4); //Up3
	App->collision->AddCollider({ 7090,80,222,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7312,20,35,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7347,-40,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7412,-65,145,100 }, COLLIDER_WALL4);


	//reset variables (camera position, players position...)
	App->render->camera.x = 0;
	App->render->camera.y = -100;
	stage = 0;
	//enemies

	App->powerup->AddPowerUp(App->powerup->one_up, 4285, 200, COLLIDER_ONE_UP);

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
	App->textures->Unload(ground_tx);
	
	return true;
}

update_status ModuleStage4::Update() {
	//input

	//logic
	App->player1->position.x++;
	for (int i = 0; i < 4; i++)
		App->render->Blit(back_tx, back.w*i, -50, NULL, BACKGROUND4SPEED);
	App->render->Blit(ground_tx, 1000, -97, &ground[0], GROUND4SPEED);
	App->render->Blit(ground_tx, 1000 + ground[0].w, 18, &ground[1], GROUND4SPEED);
	animation_water = &water;
	water_rect = animation_water->GetCurrentFrame();
	for (int i = 0; i < 5; i++)
		App->render->Blit(ground_tx, (1000 + ground[0].w + ground[1].w) + water_rect.w*i - 9, 316, &water_rect, GROUND4SPEED);
	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w, 52, &ground[2], GROUND4SPEED);
	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w + ground[2].w, 13, &ground[3], GROUND4SPEED);
	switch (stage) {
	case 0:				//scroll diagonal to y=43
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y += 1;

		if (App->render->camera.y >= -2*SCREEN_SIZE)
			stage++;;
		break;
	case 1:				//scroll horizontal
		App->render->camera.x += 1 * SCREEN_SIZE;

		if (App->render->camera.x >= 1960 * SCREEN_SIZE)
			stage++;;
		break;
	case 2:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y--;

		if (App->render->camera.y <= -97*SCREEN_SIZE)
			stage++;
		break;
	case 3:
		App->render->camera.x += 1 * SCREEN_SIZE;

		if (App->render->camera.x >= 3092 * SCREEN_SIZE)
			stage++;
		break;
	case 4:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y++;

		if (App->render->camera.y >= 113 * SCREEN_SIZE)
			stage++;
		break;
	case 5:
		App->render->camera.x += 1 * SCREEN_SIZE;

		if (App->render->camera.x >= 7200 * SCREEN_SIZE)
			stage++;
		break;
	case 6:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y--;

		if (App->render->camera.y <= 13 * SCREEN_SIZE)
			stage++;
		break;
	case 7:
		App->render->camera.x += 1 * SCREEN_SIZE;

		if (App->render->camera.x >= 7970 * SCREEN_SIZE)
			stage++;
		break;
	case 8:

		break;
	}


	return UPDATE_CONTINUE;
}