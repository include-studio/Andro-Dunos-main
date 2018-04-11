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

	

	for(x = 0; x <= 10 && loop == true; x++)
	{
		for(y = 0; y <= 10 && loop == true; y++)
		{
			game_over.PushBack({ GMSIZE * x,GMSIZE * y,GMSIZE,GMSIZE });

			if(x == 10 && y == 4)
				loop = false;
			
				
			
		}
	}

	//game_over.PushBack({ GMSIZE * 0,GMSIZE * 0,GMSIZE,GMSIZE }); //x * NUM ROW , y * NUM COLUMN, w, h
	//game_over.PushBack({ 0,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ 0,GMSIZE * 10,GMSIZE,GMSIZE }); //11

	//game_over.PushBack({ GMSIZE,GMSIZE * 0,GMSIZE,GMSIZE }); 
	//game_over.PushBack({ GMSIZE,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE,GMSIZE * 10,GMSIZE,GMSIZE }); //22

	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 2,GMSIZE * 10,GMSIZE,GMSIZE }); //33

	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 3,GMSIZE * 10,GMSIZE,GMSIZE }); //44

	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 4,GMSIZE * 10,GMSIZE,GMSIZE }); //55

	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 5,GMSIZE * 10,GMSIZE,GMSIZE }); //66

	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 6,GMSIZE * 10,GMSIZE,GMSIZE }); //77

	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 7,GMSIZE * 10,GMSIZE,GMSIZE }); //88

	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 8,GMSIZE * 10,GMSIZE,GMSIZE }); //99

	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 4,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 5,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 6,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 7,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 8,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 9,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 9,GMSIZE * 10,GMSIZE,GMSIZE }); //110

	//game_over.PushBack({ GMSIZE * 10,GMSIZE * 0,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 10,GMSIZE * 1,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 10,GMSIZE * 2,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 10,GMSIZE * 3,GMSIZE,GMSIZE });
	//game_over.PushBack({ GMSIZE * 10,GMSIZE * 4,GMSIZE,GMSIZE }); //115
	
	
	
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