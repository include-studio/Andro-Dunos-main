#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleViscoGames.h"
#include "ModuleAudio.h"

ModuleViscoGames::ModuleViscoGames()
{

	Visco.x = 32;
	Visco.y = 88;
	Visco.w = 189;
	Visco.h = 39 ;

	Games.x = 15;
	Games.y = 128;
	Games.w = 223;
	Games.h = 39;
}

ModuleViscoGames::~ModuleViscoGames()
{}

// Load assets
bool ModuleViscoGames::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	visco = App->textures->Load("Assets/visco_games_intro.png");

	positionvisco.x = SCREEN_WIDTH / 2;
	positionvisco.y = SCREEN_HEIGHT / 2;

	positiongames.x = SCREEN_WIDTH / 2;
	positiongames.y = SCREEN_HEIGHT / 2;


	return ret;
}

// Load assets
bool ModuleViscoGames::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(visco);

	animation_transition = 0;

	return true;
}

// Update: draw background
update_status ModuleViscoGames::Update()
{
	// Draw everything --------------------------------------	
	
	//320x224 visco has to go up and games has to go down before they get to the middle

	//animation_transition = 0;

	/*if (time == 0) {
		for (time = 0; time < 1; time++) {
			App->render->Blit(visco, positionvisco.x - Visco.w / 2, positionvisco.y = SCREEN_HEIGHT, &Visco,1.0f);
			App->render->Blit(visco, positiongames.x - Games.w / 2, positiongames.y = 0 - Games.h, &Games,1.0f);

			positiongames.y = +4;
			positionvisco.y = -4;

			time++;
		}
		for (time = 1; time < 2; time++) {
			App->render->Blit(visco, positionvisco.x-Visco.w/2, positionvisco.y-Visco.h, &Visco);
			App->render->Blit(visco, positiongames.x-Games.w/2, positiongames.y, &Games);

			positiongames.x = positiongames.x + 4;
			positionvisco.x = positionvisco.x - 4;

			time++;
		}
		for (time = 2; time < 3; time++) {
			time++;
		}
	}*/

	App->render->Blit(visco, positionvisco.x - Visco.w / 2, positionvisco.y * 2, &Visco);
	App->render->Blit(visco, positiongames.x - Games.w / 2, positiongames.y * 1 - SCREEN_HEIGHT / 2, &Games);

	positiongames.y = positiongames.y + 3;
	positionvisco.y = positionvisco.y - 2;

	/*App->render->Blit(visco, positionvisco.x-Visco.w/2, positionvisco.y-Visco.h, &Visco);
	App->render->Blit(visco, positiongames.x-Games.w/2, positiongames.y, &Games);

	positiongames.x = positiongames.x + 4;
	positionvisco.x = positionvisco.x - 4;*/
	
	/*switch (animation_transition) {
	case 0: { //Start to middle

		App->render->Blit(visco, positionvisco.x - Visco.w / 2, positionvisco.y * 2, &Visco);
		App->render->Blit(visco, positiongames.x - Games.w / 2, positiongames.y * 1 - SCREEN_HEIGHT / 2, &Games);

		for (int i = 0; i < 12; i++) {
			
			positiongames.y = positiongames.y + 3;
			positionvisco.y = positionvisco.y - 2;
		}
		break;
	}
	case 1: { //Middle to sides
		for (int i = 0; i < 12; i++) {
			App->render->Blit(visco, positionvisco.x - Visco.w / 2, positionvisco.y - Visco.h, &Visco);
			App->render->Blit(visco, positiongames.x - Games.w / 2, positiongames.y, &Games);

			positiongames.x = positiongames.x + 4;
			positionvisco.x = positionvisco.x - 4;
		}
		break;
	}

	case 2: {//End
		break;
	}
	}*/

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}

	return UPDATE_CONTINUE;
}