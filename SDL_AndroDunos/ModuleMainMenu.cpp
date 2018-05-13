#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"
#include "ModuleUI.h"

ModuleMainMenu::ModuleMainMenu()
{
	// background
	logo_background.x = 0;
	logo_background.y = 0;
	logo_background.w = 320;
	logo_background.h = 224;

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

	
	//Press1P

	animationPress1P = nullptr;

	Press1P.PushBack({ 0,0,112,8 }); // x, y, w, h
	Press1P.PushBack({ 0,8,112,8 });

	Press1P.loop = true;
	Press1P.speed = 0.0225f;

	//Press2P

	animationPress2P = nullptr;

	Press2P.PushBack({ 0,0,160,8 }); // x, y, w, h
	Press2P.PushBack({ 0,8,160,8 });

	Press2P.loop = true;
	Press2P.speed = 0.0225f;

	//c1992
	c1992.x = 0;
	c1992.y = 0;
	c1992.w = 192;
	c1992.h = 24;

	//Num Counter

	animationNum_Count = nullptr;

	Num_Count.PushBack({ 0,0,17,8 }); // x, y, w, h
	Num_Count.PushBack({ 0,9,17,8 });
	Num_Count.PushBack({ 0,18,17,8 });
	Num_Count.PushBack({ 0,27,17,8 });
	Num_Count.PushBack({ 0,36,17,8 });
	Num_Count.PushBack({ 0,45,17,8 });
	Num_Count.PushBack({ 0,54,17,8 });
	Num_Count.PushBack({ 0,63,17,8 });
	Num_Count.PushBack({ 0,72,17,8 });
	Num_Count.PushBack({ 0,81,17,8 }); //10

	Num_Count.PushBack({ 20,0,17,8 }); // x, y, w, h
	Num_Count.PushBack({ 20,9,17,8 });
	Num_Count.PushBack({ 20,18,17,8 });
	Num_Count.PushBack({ 20,27,17,8 });
	Num_Count.PushBack({ 20,36,17,8 });
	Num_Count.PushBack({ 20,45,17,8 });
	Num_Count.PushBack({ 20,54,17,8 });
	Num_Count.PushBack({ 20,63,17,8 });
	Num_Count.PushBack({ 20,72,17,8 });
	Num_Count.PushBack({ 20,81,17,8 }); //20

	Num_Count.PushBack({ 40,0,17,8 }); // x, y, w, h
	Num_Count.PushBack({ 40,9,17,8 });
	Num_Count.PushBack({ 40,18,17,8 });
	Num_Count.PushBack({ 40,27,17,8 });
	Num_Count.PushBack({ 40,36,17,8 });
	Num_Count.PushBack({ 40,45,17,8 });
	Num_Count.PushBack({ 40,54,17,8 });
	Num_Count.PushBack({ 40,63,17,8 });
	Num_Count.PushBack({ 40,72,17,8 });
	Num_Count.PushBack({ 40,81,17,8 }); //30

	Num_Count.loop = false;
	
	Num_Count.speed = 0.016f;
}

ModuleMainMenu::~ModuleMainMenu()
{}

// Load assets
bool ModuleMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	credit = 0;

	logo_background_tx = App->textures->Load("assets/Sprites/logo_background.png");
	logo_andro_tx = App->textures->Load("assets/Sprites/logo.png");
	visco_games_tx = App->textures->Load("assets/Sprites/visco_games.png");
	press1P_tx = App->textures->Load("assets/Sprites/press_1p.png");
	press2P_tx = App->textures->Load("assets/Sprites/press_2p.png");
	c1992_tx = App->textures->Load("assets/Sprites/1992.png");
	num_count_tx = App->textures->Load("assets/Sprites/num_counter.png");

	return ret;
}

// Load assets
bool ModuleMainMenu::CleanUp()
{
	Num_Count.reset();
	Press1P.reset();
	Press2P.reset();

	LOG("Unloading MainMenu stage");
	App->textures->Unload(logo_andro_tx);
	App->textures->Unload(logo_background_tx);
	App->textures->Unload(visco_games_tx);
	App->textures->Unload(press1P_tx);
	App->textures->Unload(press2P_tx);
	App->textures->Unload(c1992_tx);
	App->textures->Unload(num_count_tx);

	return true;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{
	// Draw everything --------------------------------------	

	

	animationNum_Count = &Num_Count;
	SDL_Rect animation_Rect_Num_Count;
	animation_Rect_Num_Count = animationNum_Count->GetCurrentFrame();

	App->render->Blit(logo_background_tx, 0, 0, &logo_background); 
	App->render->Blit(logo_andro_tx, 42, 70, &title_rect); 
	App->render->Blit(logo_andro_tx, 27, 38, &logo_andro); 
	App->render->Blit(visco_games_tx, 64, 168, &visco_games); 
	
	App->render->Blit(c1992_tx, 48, 192, &c1992);
	App->render->Blit(num_count_tx, 160, 208, &animation_Rect_Num_Count);

	//Credit to P2

	if (App->ui->credit == 1) {
		animationPress1P = &Press1P;
		SDL_Rect animation_Rect_Press1P;
		animation_Rect_Press1P = animationPress1P->GetCurrentFrame();
		App->render->Blit(press1P_tx, 88, 152, &animation_Rect_Press1P);
		Press1P.loop = true;
	}

	if (App->ui->credit >= 2) {
			animationPress2P = &Press2P;
			SDL_Rect animation_Rect_Press2P;
			animation_Rect_Press2P = animationPress2P->GetCurrentFrame();
			App->render->Blit(press2P_tx, 68, 152, &animation_Rect_Press2P);
			Press1P.loop = false;
	}
	
	if (Num_Count.current_frame >= Num_Count.last_frame - 1) 
	{
			App->fade->FadeToBlack(this, App->stage1, 0.5);
			
	}

	if (App->input->keyboard[SDL_SCANCODE_1]||SDL_GameControllerGetButton(App->input->controller1,SDL_CONTROLLER_BUTTON_A))
	{
		App->player2->insert2 = false;
		App->fade->FadeToBlack(this, App->stage1, 0.5);
	}

	if ((App->input->keyboard[SDL_SCANCODE_2] || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) /*&& App->input->controller2 == nullptr*/)
	{
		if (App->ui->credit >= 2) {
			App->player2->insert2 = true;
			App->fade->FadeToBlack(this, App->stage1, 0.5);
		}
	}
	
	return UPDATE_CONTINUE;
}