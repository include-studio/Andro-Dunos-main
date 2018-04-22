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
#include "SDL/include/SDL.h"
#include "ModuleMainMenu.h"
#include "ModuleUI.h"
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

	//Grey_Square_GM
	Grey_Square.x = 2576;
	Grey_Square.y = 2768;
	Grey_Square.w = SCREEN_WIDTH;
	Grey_Square.h = 48;
}

ModuleGameOver::~ModuleGameOver()
{}

// Load assets
bool ModuleGameOver::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer

	gameover_tx = App->textures->Load("Assets/Sprites/gameover.png");

	App->audio->PlayMusic("assets/Audio/18_Game_Over.ogg");

	return ret;
}

// Load assets
bool ModuleGameOver::CleanUp()
{
	game_over.reset();
	LOG("Unloading MainMenu stage");
	App->textures->Unload(gameover_tx);

	return true;
}

// Update: draw background
update_status ModuleGameOver::Update()
{
	//Time
	current_time = SDL_GetTicks() - init_time;
	// Draw everything --------------------------------------	

	Animation_game_over = &game_over;

	Animation_Rect_game_over = Animation_game_over->GetCurrentFrame();
	if(current_time>=1550) //ms when Game Over grey bckgnd appears
		App->render->Blit(gameover_tx, 0, 74, &Grey_Square);
	App->render->Blit(gameover_tx, 24, -30, &Animation_Rect_game_over);

	if (current_time >= 3000) //ms when Game Over auido stop
		Mix_PauseMusic();
	if (current_time >= 3500) { //ms when Game Over auido stop
		if (App->ui->credit >0)
		App->fade->FadeToBlack(this, App->mainmenu, 0.5f);
		else if(App->ui->credit == 0) {
			App->fade->FadeToBlack(this, App->visco, 0.5f);
		}
	}
	
	

	// make so pressing C the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_C])
	{
		App->fade->FadeToBlack(this, App->mainmenu, 0.5f);
		Mix_PauseMusic();
	}
	
	return UPDATE_CONTINUE;
}