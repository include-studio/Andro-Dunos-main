#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 0;
	ground.y = 95;
	ground.w = SCREEN_WIDTH;
	ground.h = SCREEN_HEIGHT ;

	// Background / sky
	background.x = 0;
	background.y = 459;
	background.w = 251;
	background.h = 85;

	//stars

	//planets
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Background1.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	App->render->Blit(graphics, 0, 0, &ground);

	return UPDATE_CONTINUE;
}