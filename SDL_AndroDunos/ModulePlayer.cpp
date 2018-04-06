#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleBackground.h"


ModulePlayer::ModulePlayer()
{
	flames_animation = nullptr;

	movVertical = 0;
	maxVertical = 14;

	position.x = SCREEN_WIDTH/2;
	position.y = SCREEN_HEIGHT/2;

	idle.PushBack({ 0,48,39,17 });
	idle.PushBack({ 42,48,39,17 });
	idle.PushBack({ 85,48,39,17 });

	up.PushBack({ 85,24,39,15 });
	up.PushBack({ 43,24,39,15 });
	up.PushBack({ 2,24,39,15 });
	up.PushBack({ 2,4,39,15 });
	up.PushBack({ 41,4,39,15 });
	up.PushBack({ 85,4,39,15 });
	
	up.speed = 0.5f;

	upidle.PushBack({ 85,24,39,15 });
	upidle.PushBack({ 43,24,39,15 });
	upidle.PushBack({ 2,24,39,15 });
	upidle.PushBack({ 0,48,39,17 });
	upidle.PushBack({ 42,48,39,17 });
	upidle.PushBack({ 85,48,39,17 });

	upidle.speed = 0.1f;
	
	down.PushBack({ 0,76,39,16 });
	down.PushBack({ 43,76,39,16 });
	down.PushBack({ 85,76,39,16 });
	down.PushBack({ 2,104,39,17 });
	down.PushBack({ 43,104,39,17 });
	down.PushBack({ 85,104,39,17 });

	down.speed = 0.5f;

	downidle.PushBack({ 0,76,39,16 });
	downidle.PushBack({ 43,76,39,16 });
	downidle.PushBack({ 85,76,39,16 });
	downidle.PushBack({ 0,48,39,17 });
	downidle.PushBack({ 42,48,39,17 });
	downidle.PushBack({ 85,48,39,17 });

	downidle.speed = 0.5f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/ships.png");
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Animation* current_animation = &idle;

	flames_animation = &idle;
	

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
		
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1) {
		position.x -= speed;

	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1) {
		flames_animation = &up;
		position.y -= speed;

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter.
		}
	}
	/*if (App->input->keyboard[SDL_SCANCODE_W] == 0) {//if up is 0, that animation resets to 0
		up.reset();
	}*/
	if (App->input->keyboard[SDL_SCANCODE_S] == 1) {
		flames_animation = &down;
		position.y += speed;

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter.
		}
	}
	/*if (App->input->keyboard[SDL_SCANCODE_S] == 0)
		down.reset();*/

	if (movVertical >= maxVertical)
	{
		flames_animation = &up;
		
	}

	else if (movVertical > (maxVertical / 2) && movVertical < maxVertical)
	{
		flames_animation = &upidle;
	}

	else if (movVertical <= (maxVertical / 2) && movVertical >= -(maxVertical / 2))
	{
		flames_animation = &idle;
	}

	else if (movVertical < -(maxVertical / 2) && movVertical > -maxVertical)
	{
		flames_animation = &downidle;
	}

	else if (movVertical <= -maxVertical)
	{
		flames_animation = &down;
	}


	switch (App->background->part_stage) {
	case 0:
		position.x++;
		break;
	case 1:
		position.y++;
		break;
	case 2:
		position.x++;
		break;
	case 3:
		position.x ++;
		position.y --;
		break;
	case 4: 
		position.x ++;
		break;
	case 5:
		position.x++;
		position.y++;
		break;
	case 6:
		position.x++;
		break;
	case 7:
		position.x++;
		position.y--;
		break;
	case 8:
		position.x++;
		break;
	case 9:
		position.x++;
		position.y++;
		break;
	case 10:
		position.x++;
		break;
	case 11:
		position.x--;
		break;
	case 12:
		position.x++;
		break;

	}

	// Draw everything --------------------------------------
	SDL_Rect flames;

	flames = flames_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - flames.h, &flames);
	
	return UPDATE_CONTINUE;
}

//cleanup?