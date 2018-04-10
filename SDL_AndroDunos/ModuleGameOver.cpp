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











	//TRY 1
	//game_over.PushBack({ 0,0,256,7 }); //x, y, w, h
	//game_over.PushBack({ 0,9,256,11 });
	//game_over.PushBack({ 0,22,256,37-22 });
	//game_over.PushBack({ 0,39,256,58-39 });
	//game_over.PushBack({ 0,60,256,83-60 });
	//game_over.PushBack({ 0,85,256,110-85 });
	//game_over.PushBack({ 0,112,256,139-112 });
	//game_over.PushBack({ 0,141,256,170-141 });
	//game_over.PushBack({ 0,172,256,204-172 });
	//game_over.PushBack({ 0,206,256,236-206 }); //10

	//game_over.PushBack({ 0,240,256,270-240 });
	//game_over.PushBack({ 0,272,256,300-272 });
	//game_over.PushBack({ 0,302,256,328-302 });
	//game_over.PushBack({ 0,330,256,352-330 });
	//game_over.PushBack({ 0,354,256,370-354 }); //15
	//game_over.PushBack({ 0,372,256,384-372 });
	//game_over.PushBack({ 0,386,256,409-386 });
	//game_over.PushBack({ 0,411,256,436-411 });
	//game_over.PushBack({ 0,440,256,475-440});
	//game_over.PushBack({ 0,477,256,522-477}); //20

	//game_over.PushBack({ 0,524,256,579- 524 });
	//game_over.PushBack({ 0,581,256,647- 581 });
	//game_over.PushBack({ 0,649,256,724- 649 });
	//game_over.PushBack({ 0,726,256,809- 726 });
	//game_over.PushBack({ 0,811,256,907- 811 });
	//game_over.PushBack({ 0,909,256,1015- 909 });
	//game_over.PushBack({ 0,1017,256,1131- 1017 });
	//game_over.PushBack({ 0,1133,256,1257- 1133 });
	//game_over.PushBack({ 0,1259,256,1391- 1259 });
	//game_over.PushBack({ 0,1393,256,1531- 1393 }); //30

	//game_over.PushBack({ 0,1533,256,1679- 1533 });
	//game_over.PushBack({ 0,1681,256,1831- 1681 });
	//game_over.PushBack({ 0,1833,256,1988- 1833 });
	//game_over.PushBack({ 0,1990,256,2147- 1990 });
	//game_over.PushBack({ 0,2149,256,2306- 2149 }); //35
	//game_over.PushBack({ 256,2308,256, });
	//game_over.PushBack({ 256,1393,256,19 });
	//game_over.PushBack({ 256,1393,256,19 });
	//game_over.PushBack({ 256,1393,256,19 });
	//game_over.PushBack({ 256,1393,256,19 }); //40
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