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

	// play music null
	//App->audio->PlayMusic(6);

	return ret;
}

// Load assets
bool ModuleViscoGames::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(visco);

	//animation_transition = 0;

	return true;
}

// Update: draw background
update_status ModuleViscoGames::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(visco, positionvisco.x - Visco.w / 2, positionvisco.y * 2, &Visco);
	App->render->Blit(visco, positiongames.x - Games.w / 2, positiongames.y * 1 - SCREEN_HEIGHT / 2, &Games);

	if (positiongames.y <= SCREEN_HEIGHT) {
		positiongames.y += 3;
		positionvisco.y -= 2;
	}

	if (positiongames.y >= SCREEN_HEIGHT) {
		positiongames.x += 4;
		positionvisco.x -= 4;
	}

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}

	return UPDATE_CONTINUE;
}