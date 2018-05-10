#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleViscoGames.h"
#include "ModuleAudio.h"
#include "ModuleMainMenu.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleUI.h"
#include "ModuleStage4.h"

#include "SDL/include/SDL.h"


#define StageClearWIDTH 304

ModuleStageClear::ModuleStageClear() {
	
	//Animation StageClear

	stage_clear.x = 0;
	stage_clear.y = 0;
	stage_clear.w = 304;
	stage_clear.h = 48;

	animationStageClear = nullptr;

	StageClear.PushBack({ 0, 0, 304, 48 });
	StageClear.PushBack({ 0, 48, 304, 48 });
	StageClear.PushBack({ 0, 96, 304, 48 });
	StageClear.PushBack({ 0, 144, 304, 48 });
	StageClear.PushBack({ 0, 192, 304, 48 });
	StageClear.PushBack({ 0, 240, 304, 48 });
	StageClear.PushBack({ 0, 288, 304, 48 });
	StageClear.PushBack({ 0, 336, 304, 48 });
	StageClear.PushBack({ 0, 384, 304, 48 });
	StageClear.PushBack({ 0, 432, 304, 48 });
	StageClear.PushBack({ 0, 480, 304, 48 });
	StageClear.PushBack({ 0, 528, 304, 48 });
	StageClear.PushBack({ 0, 576, 304, 48 });
	StageClear.PushBack({ 0, 624, 304, 48 });
	StageClear.PushBack({ 0, 672, 304, 48 });
	StageClear.PushBack({ 0, 720, 304, 48 });
	StageClear.PushBack({ 0, 768, 304, 48 });
	StageClear.PushBack({ 0, 816, 304, 48 });
	StageClear.PushBack({ 0, 864, 304, 48 });
	StageClear.PushBack({ 0, 912, 304, 48 });
	StageClear.PushBack({ 0, 960, 304, 48 });
	StageClear.PushBack({ 0, 1008, 304, 48 });
	StageClear.PushBack({ 0, 1056, 304, 48 });
	StageClear.PushBack({ 0, 1104, 304, 48 });
	StageClear.PushBack({ 0, 1152, 304, 48 });
	StageClear.PushBack({ 0, 1200, 304, 48 });
	StageClear.PushBack({ 0, 1248, 304, 48 });
	StageClear.PushBack({ 0, 1296, 304, 48 });
	StageClear.PushBack({ 0, 1344, 304, 48 });
	StageClear.PushBack({ 0, 1392, 304, 48 });
	StageClear.PushBack({ 0, 1440, 304, 48 });
	StageClear.PushBack({ 0, 1488, 304, 48 });
	StageClear.PushBack({ 0, 1536, 304, 48 });
	StageClear.PushBack({ 0, 1584, 304, 48 });
	StageClear.PushBack({ 0, 1632, 304, 48 });

	StageClear.loop = false;

	StageClear.speed = 0.5f;

	//Blue Rect 
	small_blue.x = 0;
	small_blue.y = 0;
	small_blue.w = 124;
	small_blue.h = 75;

	//Blue Rect  2
	small_blue2.x = 125;
	small_blue2.y = 0;
	small_blue2.w = 124;
	small_blue2.h = 75;
}

ModuleStageClear::~ModuleStageClear(){}

bool ModuleStageClear::Start() {
	LOG("Loading StageClear textures");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer
	stage_clear_tx = App->textures->Load("assets/Sprites/StageClear.png");
	small_blue_tx = App->textures->Load("assets/Sprites/clear_bonus_small_screen.png");
	
	positionstage.x = SCREEN_WIDTH;
	positionstage.y = 100; 

	position_small_blue.x = 24;
	position_small_blue.y = SCREEN_HEIGHT;

	App->audio->PlayMusic("assets/Audio/06_Stage_Clear.ogg");
	

	return ret;
}

update_status ModuleStageClear::Update() {
	

	//Time
	current_time = SDL_GetTicks() - init_time;

	if (current_time >= 4500) {
		Mix_PauseMusic();
	}

	//Blit: Blue small screen 
	App->render->Blit(small_blue_tx, position_small_blue.x, position_small_blue.y , &small_blue);
	
	if (App->player2->insert2 == true)
	{
		App->render->Blit(small_blue_tx, position_small_blue.x + 128, position_small_blue.y, &small_blue2);
	}

	//Animation after final state
	if (positionstage.x) {

		App->render->Blit(stage_clear_tx, positionstage.x, positionstage.y, &stage_clear);

		positionstage.x -= 8;

	}

	else if (positionstage.x == NULL && positionstage.y > 36) {

		App->render->Blit(stage_clear_tx, positionstage.x, positionstage.y, &stage_clear);

		positionstage.y -= 3;

	}

	else if (positionstage.y <= 36) 
	{
		animationStageClear = &StageClear;

		SDL_Rect animation_StageClear;

		animation_StageClear = animationStageClear->GetCurrentFrame();

		App->render->Blit(stage_clear_tx, 0, 36, &animation_StageClear);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) {
		switch (part_stageClear)
		{
		case 0:
			App->fade->FadeToBlack(this, App->stage4, 1);
			part_stageClear=1;
			break;
		case 1:
			App->fade->FadeToBlack(this, App->stage1, 1);
			part_stageClear=0;
			break;
			/*if (App->ui->credit == 0) {
				App->fade->FadeToBlack(this, App->visco, 1);
				Mix_PauseMusic();
			}

			else if (App->ui->credit > 0) {
				App->fade->FadeToBlack(this, App->mainmenu, 1);
				Mix_PauseMusic();
			}*/
		}
	}

	if (position_small_blue.y > 83 && current_time >= 2000)
		position_small_blue.y -= 5;
	
	

	return UPDATE_CONTINUE;
}

bool ModuleStageClear::CleanUp() {

	LOG("Unloading MainMenu stage");
	App->textures->Unload(stage_clear_tx);
	App->textures->Unload(small_blue_tx);

	StageClear.reset();

	return true;
}