#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleBackground.h"


ModulePlayer::ModulePlayer()
{
	state = IDLE;

	animationShip = nullptr;

	movVertical = 0;
	maxVertical = 14;

	position.x = SCREEN_WIDTH/2;
	position.y = SCREEN_HEIGHT/2;

	idle.PushBack({ 0,48,39,17 });
	idle.PushBack({ 42,48,39,17 });
	idle.PushBack({ 85,48,39,17 });


	up.PushBack({ 2,4,39,15 });
	up.PushBack({ 41,4,39,15 });
	up.PushBack({ 85,4,39,15 });
	
	up.speed = 0.5f;

	upidle.PushBack({ 85,24,39,15 });
	upidle.PushBack({ 43,24,39,15 });
	upidle.PushBack({ 2,24,39,15 });


	upidle.speed = 0.1f;
	
	down.PushBack({ 2,104,39,17 });
	down.PushBack({ 43,104,39,17 });
	down.PushBack({ 85,104,39,17 });


	down.speed = 0.5f;

	downidle.PushBack({ 0,76,39,16 });
	downidle.PushBack({ 43,76,39,16 });
	downidle.PushBack({ 85,76,39,16 });

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
	
	if (App->input->keyboard[SDL_SCANCODE_D])
		position.x += speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_A])
		position.x -= speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_W])
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (App->input->keyboard[SDL_SCANCODE_S])
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
	}


	if (!App->input->keyboard[SDL_SCANCODE_S] && !App->input->keyboard[SDL_SCANCODE_W])
	{
		if (state == DOWN)
			state = IDLE_DOWN;

		else if (state == UP)
			state = IDLE_UP;

		else if (state == IDLE_DOWN)
			counterReturn++;

		else if ( state == IDLE_UP)
			counterReturn2++;

		if (counterReturn > TIMERETURNIDDLE || counterReturn2 > TIMERETURNIDDLE)
		{
			counterReturn = 0;
			counterReturn2 = 0;
			state = IDLE;
		}

	}
		

	switch (state)
	{
	case DOWN:		
		animationShip = &down;
		break;
	case IDLE_DOWN:
		animationShip = &downidle;
		break;
	case IDLE:
		animationShip = &idle;

		if (counterMoved > 0 || counterMoved2 > 0)
		{
			counterMoved = 0;
			counterMoved2 = 0;
		}
		
		break;
	case IDLE_UP:
		animationShip = &upidle;
		break;
	case UP:
		animationShip = &up;
		break;
	}



	switch (App->background->part_stage) 
	{
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

	flames = animationShip->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - flames.h, &flames);
	
	return UPDATE_CONTINUE;
}

//cleanup?