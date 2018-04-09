#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleStage2.h"

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
		switch (part_stageClear)
		{
		case 0:
			if (App->fade->FadeToBlack(this, App->stage2, 1))
				part_stageClear++;
			break;
		case 1:
			if (App->fade->FadeToBlack(this, App->mainmenu, 1))
				part_stageClear = 0;
			break;
		}
		

	return UPDATE_CONTINUE;
}

bool ModuleStageClear::CleanUp() {
	App->textures->Unload(stage_clear_tx);
	return true;
}