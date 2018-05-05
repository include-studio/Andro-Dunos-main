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
#include "ModuleSubMainMenu.h"

ModuleSubMainMenu::ModuleSubMainMenu()
{
	//Insert Coin
	insert.PushBack({ 0,0,88,8 }); // x, y, w, h
	insert.PushBack({ 0,9,88,8 });

	insert.loop = true;
	insert.speed = 0.0225f;

	//Background //Provisional
	sub_background.x = 0;
	sub_background.y = 0;
	sub_background.w = 320;
	sub_background.h = 224;

	// blue title rectangle under the title
	title_rect.x = 9;
	title_rect.y = 162;
	title_rect.w = 208;
	title_rect.h = 44;

	// androletters
	logo_andro.x = 7;
	logo_andro.y = 47;
	logo_andro.w = 240;
	logo_andro.h = 112;

	// viscogameslogo
	visco_games.x = 40;
	visco_games.y = 116;
	visco_games.w = 167;
	visco_games.h = 15;

	//c1992
	c1992.x = 0;
	c1992.y = 0;
	c1992.w = 192;
	c1992.h = 24;

	
}

ModuleSubMainMenu::~ModuleSubMainMenu()
{}

// Load assets
bool ModuleSubMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer	
	sub_background_tx = App->textures->Load("assets/Sprites/sub_background.png"); //Provisional
	insert_tx = App->textures->Load("Assets/Sprites/insert_coin.png");
	logo_andro_tx = App->textures->Load("assets/Sprites/logo.png");
	visco_games_tx = App->textures->Load("assets/Sprites/visco_games.png");
	c1992_tx = App->textures->Load("assets/Sprites/1992.png");
	current_time = 0;


	App->audio->PlayMusic("assets/Audio/02_Title.ogg");

	return ret;
}

// Load assets
bool ModuleSubMainMenu::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(insert_tx);
	App->textures->Unload(sub_background_tx); //Provisional
	App->textures->Unload(logo_andro_tx);
	App->textures->Unload(visco_games_tx);
	App->textures->Unload(c1992_tx);
	current_time = 0;

	//animation_transition = 0;

	return true;
}

// Update: draw background
update_status ModuleSubMainMenu::Update()
{
	//Time
	current_time = SDL_GetTicks() - init_time;
	// Draw everything --------------------------------------	
	animationInsert = &insert;
	Insert_Rect = animationInsert->GetCurrentFrame();

	App->render->Blit(sub_background_tx, 0, 0, &sub_background); //Provisional
	App->render->Blit(insert_tx, 104, 152, &Insert_Rect);
	App->render->Blit(logo_andro_tx, 42, 70, &title_rect);
	App->render->Blit(logo_andro_tx, 27, 38, &logo_andro);
	App->render->Blit(visco_games_tx, 64, 168, &visco_games);
	App->render->Blit(c1992_tx, 48, 192, &c1992);

																 // make so pressing SPACE the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE]|| SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) {
		Mix_PauseMusic();
		App->fade->FadeToBlack(this, App->neogeo, 0.5);
	}
		

	if (App->input->keyboard[SDL_SCANCODE_C]) {
		Mix_PauseMusic();
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}
		
	
	if (App->input->keyboard[SDL_SCANCODE_LCTRL]) {
		Mix_PauseMusic();
		App->fade->FadeToBlack(this, App->mainmenu, 0.5);
	}
		

	
	//Fade to neogeo Completloop
	if (current_time >= 4000)
		Mix_PauseMusic();
	if (current_time >= 4000) {
		App->fade->FadeToBlack(this, App->neogeo, 1);
		current_time = 0;
		Mix_PauseMusic();
	}

	return UPDATE_CONTINUE;
}