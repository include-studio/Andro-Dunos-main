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
	
	if(ground.x == 3248-ground.w) {
		App->render->Blit(graphics, speed, mov, &background);
		App->render->Blit(graphics, background.w + speed, mov, &background);
		App->render->Blit(graphics, background.w * 2 + speed, mov, &background);
		App->render->Blit(graphics, 0, 0, &ground);
		ground.y++;
		mov--;
		if (ground.y == 542 - SCREEN_HEIGHT)
			ground.x++;
	}
	else{
		App->render->Blit(graphics, speed, 118, &background);
		App->render->Blit(graphics, background.w + speed, 118, &background);
		App->render->Blit(graphics, background.w * 2 + speed, 118, &background);
		App->render->Blit(graphics, 0, 0, &ground);
		ground.x++;
		speed -= 0.5f;
	}
	//mov
	
	
	if (speed <= -background.w) {
		speed = 0;
	}
	

	return UPDATE_CONTINUE;
}