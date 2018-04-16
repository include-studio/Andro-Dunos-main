#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleViscoGames.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleInsertCoin.h"


ModuleInsertCoin::ModuleInsertCoin()
{
	//Insert Coin
	insert.PushBack({ 0,0,88,8 }); // x, y, w, h
	insert.PushBack({ 0,9,88,8 });

	insert.loop = true;
	insert.speed = 0.0225f;
}

ModuleInsertCoin::~ModuleInsertCoin()
{}

// Load assets
bool ModuleInsertCoin::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer

	insert_tx = App->textures->Load("Assets/insert_coin.png");

	
	// play music null
	//App->audio->PlayMusic(6);

	return ret;
}

// Load assets
bool ModuleInsertCoin::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(insert_tx);

	//animation_transition = 0;

	return true;
}

// Update: draw background
update_status ModuleInsertCoin::Update()
{
	//Time
	current_time = SDL_GetTicks() - init_time;
	// Draw everything --------------------------------------	
	animationInsert = &insert;

	Insert_Rect = animationInsert->GetCurrentFrame();

	App->render->Blit(insert_tx, 104, 112, &Insert_Rect); 
	

	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_C])
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}

	return UPDATE_CONTINUE;
}