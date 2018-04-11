#include "Globals.h"
#include "Application.h"
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


ModuleStage2::ModuleStage2() {
	ground.x = 0;
	ground.y = 773;
	ground.w = 2000;
	ground.h = 230;
	
	background.x = 47;
	background.y = 27;
	background.w = 410;
	background.h = 224;
}

ModuleStage2::~ModuleStage2(){}

bool ModuleStage2::Start() {
	LOG("Loading stage1 assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.x = 0;

	ground_tx = App->textures->Load("assets/Ground2.png");
	back_tx = App->textures->Load("assets/Background2.png");

	App->audio->PlayMusic(2);

	App->player1->Enable();
	
	if (App->player2->insert2 == true)
	{
		App->player2->Enable();
	}

	return ret;
}

update_status ModuleStage2::Update() {
	App->render->camera.x-=3;
	
	App->player1->position.x++;
	App->player2->position.x++;
	for (int i = 0; i < 20; i++)
		App->render->Blit(back_tx, background.w*i, 0, &background, 0.4f);
	App->render->Blit(ground_tx, 0, 0, &ground);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->stageclear, 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == 1)
	{
		App->fade->FadeToBlack(this, App->gameover, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleStage2::CleanUp() {
	App->textures->Unload(ground_tx);
	App->textures->Unload(back_tx);

	App->player1->Disable();
	App->player2->Disable();

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return true;
}