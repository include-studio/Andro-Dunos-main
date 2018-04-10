#include "Globals.h"
#include "Application.h"
#include "ModuleViscoGames.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
//#include "ModulePlayer1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "Animation.h"



ModuleGameOver::ModuleGameOver()
{
	//Animation Game Over
	Animation_game_over = nullptr;

	
	game_over.PushBack({ 0,0,256,7 }); //x, y, w, h
	game_over.PushBack({ 0,9,256,11 });
	game_over.PushBack({ 0,22,256,37-22 });
	game_over.PushBack({ 0,39,256,58-39 });
	game_over.PushBack({ 0,60,256,83-60 });
	game_over.PushBack({ 0,85,256,110-85 });
	game_over.PushBack({ 0,112,256,139-112 });
	game_over.PushBack({ 0,141,256,170-141 });
	game_over.PushBack({ 0,172,256,204-172 });
	game_over.PushBack({ 0,206,256,236-206 }); //10

	game_over.PushBack({ 0,240,256,270-240 });
	game_over.PushBack({ 0,272,256,300-272 });
	game_over.PushBack({ 0,302,256,328-302 });
	game_over.PushBack({ 0,330,256,352-330 });
	game_over.PushBack({ 0,354,256,370-354 }); //15
	//game_over.PushBack({ 0,372,256,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });

	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 }); //20

	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 });
	//game_over.PushBack({ 0,0,72,19 }); //30

	game_over.loop = true;
	game_over.speed = 0.9f;
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

	Animation_game_over = &game_over;

	SDL_Rect Animation_Rect_game_over;

	Animation_Rect_game_over = Animation_game_over->GetCurrentFrame();

	App->render->Blit(gameover_tx, 24, 76, &Animation_Rect_game_over); 

	// make so pressing SPACE the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
	}

	return UPDATE_CONTINUE;
}