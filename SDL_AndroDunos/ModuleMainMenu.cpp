#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleStage1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

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

	//c1992
	c1992.x = 0;
	c1992.y = 0;
	c1992.w = 192;
	c1992.h = 24;


}

ModuleMainMenu::~ModuleMainMenu()
{}

// Load assets
bool ModuleMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	logo_background_tx = App->textures->Load("assets/logo_background.png");
	logo_andro_tx = App->textures->Load("assets/logo.png");
	visco_games_tx = App->textures->Load("assets/visco_games.png");
	press1P_tx = App->textures->Load("assets/press_1p.png");
	c1992_tx = App->textures->Load("assets/1992.png");

	return ret;
}

// Load assets
bool ModuleMainMenu::CleanUp()
{
	LOG("Unloading MainMenu stage");
	App->textures->Unload(logo_andro_tx);
	App->textures->Unload(logo_background_tx);
	App->textures->Unload(visco_games_tx);
	App->textures->Unload(press1P_tx);
	App->textures->Unload(c1992_tx);

	return true;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{
	// Draw everything --------------------------------------	
	animationPress1P = &Press1P;

	SDL_Rect animation_Rect_Press1P;

	animation_Rect_Press1P = animationPress1P->GetCurrentFrame();

	App->render->Blit(logo_background_tx, 0, 0, &logo_background); 
	App->render->Blit(logo_andro_tx, 42, 70, &title_rect); 
	App->render->Blit(logo_andro_tx, 27, 38, &logo_andro); 
	App->render->Blit(visco_games_tx, 64, 168, &visco_games); 
	App->render->Blit(press1P_tx, 88, 152, &animation_Rect_Press1P); 
	App->render->Blit(c1992_tx, 47, 190, &c1992);


	// make so pressing SPACE the background is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->stage1, 0.5);
	}

	return UPDATE_CONTINUE;
}