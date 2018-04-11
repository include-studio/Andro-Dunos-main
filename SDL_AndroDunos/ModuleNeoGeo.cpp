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
#define NeoGeoWIDTH 227



ModuleNeoGeo::ModuleNeoGeo()
{
	animationNeoGeo = nullptr;
	animationSNK = nullptr;

	NeoGeo.PushBack({ 0,1415,14,40 });
	NeoGeo.PushBack({ 0,1371,28,40 });
	NeoGeo.PushBack({ 0,1328,42,40 });
	NeoGeo.PushBack({ 0,1285,56,40 });
	NeoGeo.PushBack({ 0,1243,71,40 });
	NeoGeo.PushBack({ 0,1200,85,40 });
	NeoGeo.PushBack({ 0,1158,99,40 });
	NeoGeo.PushBack({ 0,1115,113,40 });
	NeoGeo.PushBack({ 0,1072,127,40 });
	NeoGeo.PushBack({ 0,1030,141,40 });
	NeoGeo.PushBack({ 0,987,156,40 });
	NeoGeo.PushBack({ 0,955,170,40 });
	NeoGeo.PushBack({ 0,899,185,40 });
	NeoGeo.PushBack({ 0,855,199,40 });
	NeoGeo.PushBack({ 0,810,213,40 });
	NeoGeo.PushBack({ 0,767,223,40 });
	NeoGeo.PushBack({ 0,725,223,38 });
	NeoGeo.PushBack({ 0,686,223,35 });
	NeoGeo.PushBack({ 0,650,223,32 });
	NeoGeo.PushBack({ 0,617,223,30 });
	NeoGeo.PushBack({ 0,587,223,28 });
	NeoGeo.PushBack({ 0,559,223,25 });
	NeoGeo.PushBack({ 0,531,223,22 });
	NeoGeo.PushBack({ 0,508,223,20 });
	NeoGeo.PushBack({ 0,484,223,18 });
	NeoGeo.PushBack({ 0,466,223,15 });
	NeoGeo.PushBack({ 0,451,223,12 });
	NeoGeo.PushBack({ 0,438,223,10 });
	NeoGeo.PushBack({ 0,425,223,8 });
	NeoGeo.PushBack({ 0,414,223,5 });
	NeoGeo.PushBack({ 0,408,221,2 });
	NeoGeo.PushBack({ 0,401,221,2 });
	NeoGeo.PushBack({ 0,393,224,5 });
	NeoGeo.PushBack({ 0,381,224,8 });
	NeoGeo.PushBack({ 0,365,224,10 });
	NeoGeo.PushBack({ 0,348,224,12 });
	NeoGeo.PushBack({ 0,330,227,15 });
	NeoGeo.PushBack({ 0,310,227,18 });
	NeoGeo.PushBack({ 0,286,227,20 });
	NeoGeo.PushBack({ 0,262,227,22 });
	NeoGeo.PushBack({ 0,235,227,25 });
	NeoGeo.PushBack({ 0,203,227,28 });
	NeoGeo.PushBack({ 0,168,227,30 });
	NeoGeo.PushBack({ 0,129,227,32 });
	NeoGeo.PushBack({ 0,88,227,35 });
	NeoGeo.PushBack({ 0,44,227,38 });
	NeoGeo.PushBack({ 0,0,227,40 });

	NeoGeo.loop = false;

	NeoGeo.speed = 0.5f;

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

	neogeo = App->textures->Load("Assets/neogeo.png");

	snk = App->textures->Load("Assets/snk_animation.png");
	
	App->audio->PlayMusic(3,1);

	return ret;
}

// Load assets
bool ModuleNeoGeo::CleanUp()
{
	LOG("Unloading MainMenu stage");

	App->textures->Unload(neogeo);
	App->textures->Unload(snk);

	return true;
}

// Update: draw background
update_status ModuleNeoGeo::Update()
{
	// Draw everything --------------------------------------	
	animationNeoGeo = &NeoGeo;
	animationSNK = &SNK;

	SDL_Rect animationNeo;

	animationNeo = animationNeoGeo->GetCurrentFrame();

	SDL_Rect animation_SNK;

	animation_SNK = animationSNK->GetCurrentFrame();

	App->render->Blit(neogeo, SCREEN_WIDTH / 2 - NeoGeoWIDTH/2, 52, &animationNeo); //52 comes from a Cross-multiplication between the emulator and the resolution
	App->render->Blit(snk, SCREEN_WIDTH / 2 - SNK.frames[0].w / 2, 161, &animation_SNK); //161 comes from a Cross-multiplication between the emulator and the resolution

	//need to start snk when animation neogeo finishes

	/*if (animationNeo == NeoGeo.frames[47]) {
		App->render->Blit(snk, SCREEN_WIDTH / 2 - SNK.frames[0].w / 2, 161, &animation_SNK);
	}*/
	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
	}

	return UPDATE_CONTINUE;
}