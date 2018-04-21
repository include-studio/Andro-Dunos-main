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
#include "ModuleNeoGeo.h"
#define MAX_W_ALPH 255 



ModuleInsertCoin::ModuleInsertCoin()
{
	//Insert Coin
	insert.PushBack({ 0,0,88,8 }); // x, y, w, h
	insert.PushBack({ 0,9,88,8 });

	insert.loop = true;
	insert.speed = 0.0225f;

	//White fade - Flash position
	white.x = 0;
	white.y = 0;
	white.w = SCREEN_WIDTH * SCREEN_SIZE;
	white.h = SCREEN_HEIGHT * SCREEN_SIZE;

	W_alph = MAX_W_ALPH;

	//White fade - Flash position
	black.x = 0;
	black.y = 0;
	black.w = SCREEN_WIDTH * SCREEN_SIZE;
	black.h = SCREEN_HEIGHT * SCREEN_SIZE;

	current_time = 0;
	init_time = 0;
	
}

ModuleInsertCoin::~ModuleInsertCoin()
{}

// Load assets
bool ModuleInsertCoin::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer	
	insert_tx = App->textures->Load("Assets/Sprites/insert_coin.png");

	current_time = 0;
	

	
	// play music null
	//App->audio->PlayMusic(6);

	return ret;
}

// Load assets
bool ModuleInsertCoin::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(insert_tx);
	current_time = 0;
	W_alph = 255;
	
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
	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, W_alph); //Flash White
	SDL_RenderFillRect(App->render->renderer, &black);
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, NULL);//Flash Black
	
	

	// make so pressing SPACE the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
		App->fade->FadeToBlack(this, App->neogeo, 0.5);
	if (App->input->keyboard[SDL_SCANCODE_C])
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}
	if (App->input->keyboard[SDL_SCANCODE_LCTRL])
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}

	//White fade - Flash 
	if (current_time >= 200) {
		if (W_alph > 0) {
			SDL_RenderFillRect(App->render->renderer, &white);
			W_alph --;
		}
	}
	//Fade to neogeo Completloop
	if (current_time >= 10000) {
		App->fade->FadeToBlack(this, App->neogeo, 1);
		current_time = 0;
	}

	return UPDATE_CONTINUE;
}