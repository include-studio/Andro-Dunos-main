#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleViscoGames.h"
#include "ModuleAudio.h"
#include "ModuleStage2.h"

#define StageClearWIDTH 304

ModuleStageClear::ModuleStageClear() {
	
	//rect new coord in new texture

	stage_clear.x = 0;
	stage_clear.y = 0;
	stage_clear.w = 304;
	stage_clear.h = 48;

	animationStageClear = nullptr;

	StageClear.PushBack({ 0, 0 ,304,48 });//stageclear
	StageClear.PushBack({ 0, 50 ,304,48 });
	StageClear.PushBack({ 0, 101 ,304,43 });
	StageClear.PushBack({ 0, 147 ,304,43 });
	StageClear.PushBack({ 0, 195 ,304,40 });
	StageClear.PushBack({ 0, 240 ,304,37 });
	StageClear.PushBack({ 0, 281 ,304,34 });
	StageClear.PushBack({ 0, 319 ,304,32 });
	StageClear.PushBack({ 0, 356 ,304,29 });
	StageClear.PushBack({ 0, 390 ,304,26 });
	StageClear.PushBack({ 0, 421 ,304,23 });
	StageClear.PushBack({ 0, 448 ,304,21 });
	StageClear.PushBack({ 0, 472 ,304,18 });
	StageClear.PushBack({ 0, 495 ,304,15 });
	StageClear.PushBack({ 0, 514 ,304,12 });
	StageClear.PushBack({ 0, 530 ,304,9 });
	StageClear.PushBack({ 0, 543 ,304,6});

	StageClear.PushBack({ 0, 556 ,304,2 });//clearbonus
	StageClear.PushBack({ 0, 563 ,304,2 });
	StageClear.PushBack({ 0, 571 ,304,5 });
	StageClear.PushBack({ 0, 583 ,304,7 });
	StageClear.PushBack({ 0, 598 ,304,9 });
	StageClear.PushBack({ 0, 614 ,304,11 });
	StageClear.PushBack({ 0, 634 ,304,12 });
	StageClear.PushBack({ 0, 654 ,304,13 });
	StageClear.PushBack({ 0, 675 ,304,15 });
	StageClear.PushBack({ 0, 697 ,304,16 });
	StageClear.PushBack({ 0, 720 ,304,18 });
	StageClear.PushBack({ 0, 744 ,304,20 });
	StageClear.PushBack({ 0, 771 ,304,22 });
	StageClear.PushBack({ 0, 802 ,304,24 });
	StageClear.PushBack({ 0, 833 ,304,26 });
	StageClear.PushBack({ 0, 865 ,304,26 });
	StageClear.PushBack({ 0, 898 ,304,28 });
	StageClear.PushBack({ 0, 934 ,304,28 });

	StageClear.loop = false;

	StageClear.speed = 0.5f;
}

ModuleStageClear::~ModuleStageClear(){}

bool ModuleStageClear::Start() {
	LOG("Loading StageClear textures");
	bool ret = true;

	stage_clear_tx = App->textures->Load("assets/StageClear.png");
	
	positionstage.x = SCREEN_WIDTH;
	positionstage.y = 100; //Position Y

	App->audio->PlayMusic(1, 1);

	return ret;
}

update_status ModuleStageClear::Update() {
	
	//animation after final state
	if (positionstage.x) {

		App->render->Blit(stage_clear_tx, positionstage.x, positionstage.y, &stage_clear);

		positionstage.x -= 4;

	}

	else if (positionstage.x == NULL && positionstage.y > 36) {

		App->render->Blit(stage_clear_tx, positionstage.x, positionstage.y, &stage_clear);

		positionstage.y -= 4;

	}

	else if (positionstage.y == 36) 
	{
		animationStageClear = &StageClear;

		SDL_Rect animation_StageClear;

		animation_StageClear = animationStageClear->GetCurrentFrame();

		App->render->Blit(stage_clear_tx, 0, 36, &animation_StageClear);
	}

	if (App->input->keyboard[SDL_SCANCODE_C])
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