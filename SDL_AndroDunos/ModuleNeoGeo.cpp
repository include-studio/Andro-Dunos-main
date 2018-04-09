#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNeoGeo.h"
#include "ModuleAudio.h"

ModuleNeoGeo::ModuleNeoGeo()
{
	animationNeoGeo = nullptr;
	
	//NeoGeo.PushBack({ 0,?,227,40 });
	


	NeoGeo.speed = 0.5f;

}

ModuleNeoGeo::~ModuleNeoGeo()
{}

// Load assets
bool ModuleNeoGeo::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	neogeo = App->textures->Load("Assets/neogeo.png");

	//App->audio->PlayMusic(0);

	return ret;
}

// Load assets
bool ModuleNeoGeo::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(neogeo);

	return true;
}

// Update: draw background
update_status ModuleNeoGeo::Update()
{
	// Draw everything --------------------------------------	
	animationNeoGeo = &NeoGeo;

	SDL_Rect animation;

	animation = animationNeoGeo->GetCurrentFrame();

	App->render->Blit(neogeo, 0, 0, &animation);

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}

	return UPDATE_CONTINUE;
}