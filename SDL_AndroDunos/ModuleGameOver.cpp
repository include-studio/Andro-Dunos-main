#include "Globals.h"
#include "Application.h"
#include "ModuleViscoGames.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "Animation.h"
#define GMSIZE 256



ModuleGameOver::ModuleGameOver()
{
	//Animation Game Over
	Animation_game_over = nullptr;

	for(xGM = 0; xGM <= 10 && loopGM == true; xGM++)
	{
		for(yGM = 0; yGM <= 10 && loopGM == true; yGM++)
		{
			game_over.PushBack({ GMSIZE * xGM,GMSIZE * yGM,GMSIZE,GMSIZE });//x * NUM ROW , y * NUM COLUMN, w, h

			if(xGM == 10 && yGM == 4)
				loopGM = false;
		}
	}
	game_over.loop = false;
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

	App->audio->PlayMusic(4, 1);

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

	App->render->Blit(gameover_tx, 24, -30, &Animation_Rect_game_over); 

	// make so pressing SPACE the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
	}

	return UPDATE_CONTINUE;
}