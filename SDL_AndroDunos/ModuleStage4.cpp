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

	//water

}

ModuleStage4::~ModuleStage4(){}

bool ModuleStage4::Start() {
	bool ret = true;
	//load textures
	back_tx = App->textures->Load("assets/Sprites/background4.png");
	//colliders
	//reset variables (camera position, players position...)
	App->render->camera.x = 0;
	App->render->camera.y = 43*SCREEN_SIZE;
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
	//case 0 scroll diagonal to y=43
	//case 1 scroll horizontal
	App->render->camera.x += 1*SCREEN_SIZE;
	//case 2 scroll diagonal up right
	//case 3 scroll horizontal
		//wall brakable
	//case 4 scroll diagonal down
	//case 5 scroll horizontal water + big boss
	//case 6 scroll diagonal up
	//case 7 scroll horizontal
	//case 8 scroll horizontal lower until stop
	//case 9 camera no move, final boss
		

	App->player1->position.x++;

	//draw everithing
	for (int i = 0; i < 20; i++)
		App->render->Blit(back_tx, back.w*i, 0, NULL, 0.382f);

	return UPDATE_CONTINUE;
}