#include "Globals.h"
#include "Application.h"
#include "ModuleViscoGames.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"

ModuleGameOver::ModuleGameOver()
{
	//Game Over
	game_over.x = 0;
	game_over.y = 0;
	game_over.h = 48;
	game_over.w = 256;

}

ModuleGameOver::~ModuleGameOver()
{}

// Load assets
bool ModuleGameOver::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	gameover_tx = App->textures->Load("Assets/gameover.png");

	//App->audio->PlayMusic(0);

	return ret;
}

// Load assets
bool ModuleGameOver::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(gameover_tx);

	return true;
}

// Update: draw background
update_status ModuleGameOver::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(gameover_tx, 40, 70, &game_over); 

	// make so pressing SPACE the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
	}

	return UPDATE_CONTINUE;
}