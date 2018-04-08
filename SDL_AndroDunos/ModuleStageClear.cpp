#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleAudio.h"

ModuleStageClear::ModuleStageClear() {
	stage_clear.x = 108;
	stage_clear.y = 232;
	stage_clear.w = 304;
	stage_clear.h = 48;
}

ModuleStageClear::~ModuleStageClear(){}

bool ModuleStageClear::Start() {
	LOG("Loading StageClear textures");
	stage_clear_tx = App->textures->Load("assets/StageClear.png");
	//audio
	App->audio->PlayMusic(1, 1);
	return true;
}

update_status ModuleStageClear::Update() {
	App->render->Blit(stage_clear_tx, 10, 50, &stage_clear);

	if (App->input->keyboard[SDL_SCANCODE_SPACE])
		App->fade->FadeToBlack(this, App->mainmenu, 1);

	return UPDATE_CONTINUE;
}

bool ModuleStageClear::CleanUp() {
	App->textures->Unload(stage_clear_tx);
	return true;
}