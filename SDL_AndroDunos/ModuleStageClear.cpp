#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleViscoGames.h"
#include "ModuleAudio.h"
#include "ModuleStage2.h"

//#define StageClearWIDTH 304

ModuleStageClear::ModuleStageClear() {
	
	//rect new coord in new texture

	stage_clear.x = 108;
	stage_clear.y = 232;
	stage_clear.w = 304;
	stage_clear.h = 48;

	/*animationStageClear = nullptr;

	StageClear.PushBack({ 108, 232 ,304,48 });

	StageClear.loop = false;

	StageClear.speed = 0.5f;*/
}

ModuleStageClear::~ModuleStageClear(){}

bool ModuleStageClear::Start() {
	LOG("Loading StageClear textures");
	bool ret = true;

	stage_clear_tx = App->textures->Load("assets/StageClear.png");
	
	positionstage.x = SCREEN_WIDTH;
	positionstage.y = 0;

	App->audio->PlayMusic(1, 1);

	return ret;
}

update_status ModuleStageClear::Update() {
	
	//initial state
	//App->render->Blit(stage_clear_tx, positionstage.x , positionstage.y + 100, &stage_clear); // 100 comes from a cross multiplication between emulator

	//positionstage.x = positionstage.x - 4;

	//middle state
	//App->render->Blit(stage_clear_tx, positionstage.x - SCREEN_WIDTH, positionstage.y + 100, &stage_clear); //

	//positionstage.y = positionstage.y - 4;

	//final state
	App->render->Blit(stage_clear_tx, positionstage.x - SCREEN_WIDTH, positionstage.y + 36, &stage_clear); //100 comes from a cross multiplication between emulator
	
	//animation after final state
	/*animationStageClear = &StageClear;

	SDL_Rect animationStageClear;

	animationStageClear = animationStageClear->GetCurrentFrame();

	App->render->Blit(stage_clear_tx, 8, 36, &animationStageClear);*/

	if (App->input->keyboard[SDL_SCANCODE_SPACE])
		switch (part_stageClear)
		{
		case 0:
			if (App->fade->FadeToBlack(this, App->stage2, 1))
				part_stageClear++;
			break;
		case 1:
			if (App->fade->FadeToBlack(this, App->visco, 1))
				part_stageClear = 0;
			break;
		}
		

	return UPDATE_CONTINUE;
}

bool ModuleStageClear::CleanUp() {

	LOG("Unloading MainMenu stage");

	App->textures->Unload(stage_clear_tx);

	return true;
}