#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleBackground.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ModuleMainMenu::ModuleMainMenu()
{
	// background
	logo_background.x = 0;
	logo_background.y = 0;
	logo_background.w = 320;
	logo_background.h = 224;

	// blue title rectangle under the title
	title_rect.x = 9;
	title_rect.y = 162;
	title_rect.w = 208;
	title_rect.h = 44;

	// androletters
	logo_andro.x = 7;
	logo_andro.y = 47;
	logo_andro.w = 240;
	logo_andro.h = 112;

	// viscogameslogo
	visco_games.x = 40;
	visco_games.y = 116;
	visco_games.w = 167;
	visco_games.h = 15;

}

ModuleMainMenu::~ModuleMainMenu()
{}

// Load assets
bool ModuleMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	logo_background_tx = App->textures->Load("assets/logo_background.png");
	logo_andro_tx = App->textures->Load("assets/logo.png");
	visco_games_tx = App->textures->Load("assets/visco_games.png");

	return ret;
}

// Load assets
bool ModuleMainMenu::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(logo_andro_tx);
	App->textures->Unload(logo_background_tx);
	App->textures->Unload(visco_games_tx);

	return true;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(logo_background_tx, 0, 0, &logo_background); 
	App->render->Blit(logo_andro_tx, 52, 60, &title_rect); 
	App->render->Blit(logo_andro_tx, 36, 27, &logo_andro); 
	App->render->Blit(visco_games_tx, 75, 160, &visco_games); 

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->FadeToBlack->FadeToBlack(this, App->background, 0.5);
	}

	return UPDATE_CONTINUE;
}