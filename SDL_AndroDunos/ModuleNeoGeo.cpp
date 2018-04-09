#include "Globals.h"
#include "Application.h"
#include "ModuleViscoGames.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNeoGeo.h"
#include "ModuleAudio.h"
#include "Animation.h"

#define SNKWIDTH 72


ModuleNeoGeo::ModuleNeoGeo()
{
	//animationNeoGeo = nullptr;
	animationSNK = nullptr;

	//NeoGeo.PushBack({ 0,?,227,40 });
	
	//NeoGeo.speed = 0.5f;

	SNK.PushBack({ 17,35,72,19 });
	SNK.PushBack({ 94,35,72,19 });
	SNK.PushBack({ 169,35,72,19 });

	SNK.PushBack({ 18,64,72,19 });
	SNK.PushBack({ 94,64,72,19 });
	SNK.PushBack({ 170,64,72,19 });
	
	SNK.PushBack({ 18,90,72,19 });
	SNK.PushBack({ 94,90,72,19 });
	SNK.PushBack({ 170,91,72,19 });

	SNK.PushBack({ 18,114,72,19 });
	SNK.PushBack({ 94,114,72,19 });
	SNK.PushBack({ 169,114,72,19 });


	SNK.PushBack({ 17,140,72,19 });
	SNK.PushBack({ 94,140,72,19 });
	SNK.PushBack({ 170,140,72,19 });

	SNK.PushBack({ 17,164,72,19 });
	SNK.PushBack({ 94,164,72,19 });
	SNK.PushBack({ 171,164,72,19 });

	SNK.loop = false;

	SNK.speed = 0.2f;

}

ModuleNeoGeo::~ModuleNeoGeo()
{}

// Load assets
bool ModuleNeoGeo::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	//neogeo = App->textures->Load("Assets/neogeo.png");

	snk = App->textures->Load("Assets/snk_animation.png");
		
	App->audio->PlayMusic(3);

	return ret;
}

// Load assets
bool ModuleNeoGeo::CleanUp()
{
	LOG("Unloading MainMenu stage");

	//App->textures->Unload(neogeo);
	App->textures->Unload(snk);

	return true;
}

// Update: draw background
update_status ModuleNeoGeo::Update()
{
	// Draw everything --------------------------------------	
	//animationNeoGeo = &NeoGeo;
	animationSNK = &SNK;

	//SDL_Rect animationNeo;

	//animationNeo = animationNeoGeo->GetCurrentFrame();

	SDL_Rect animation_SNK;

	animation_SNK = animationSNK->GetCurrentFrame();

	//App->render->Blit(neogeo, 0, 0, &animationNeo);
	App->render->Blit(snk, SCREEN_WIDTH/2 - SNK.frames[0].w /2, 161, &animation_SNK); //161 comes from a Cross-multiplication between the emulator and the resolution

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
	}

	return UPDATE_CONTINUE;
}