#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleBackground.h"


ModulePlayer2::ModulePlayer2()
{
	state = IDLE;

	animationShip = nullptr;

	movVertical = 0;
	maxVertical = 14;

	position.x = SCREEN_WIDTH / 3;
	position.y = SCREEN_HEIGHT *2/3;

	idle.PushBack({ 126,48,39,17 });
	idle.PushBack({ 169,48,39,17 });
	idle.PushBack({ 215,48,39,17 });


	up.PushBack({ 126,4,39,15 });
	up.PushBack({ 169,4,39,15 });
	up.PushBack({ 215,4,39,15 });

	up.speed = 0.5f;

	upidle.PushBack({ 126,24,39,15 });
	upidle.PushBack({ 169,24,39,15 });
	upidle.PushBack({ 215,24,39,15 });


	upidle.speed = 0.5f;

	down.PushBack({ 126,104,39,17 });
	down.PushBack({ 169,104,39,17 });
	down.PushBack({ 215,104,39,17 });


	down.speed = 0.5f;

	downidle.PushBack({ 126,76,39,16 });
	downidle.PushBack({ 169,76,39,16 });
	downidle.PushBack({ 215,76,39,16 });

	downidle.speed = 0.5f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/ships.png");
	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	if (App->input->keyboard[SDL_SCANCODE_L])
		position.x += speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_J])
		position.x -= speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_I])
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (App->input->keyboard[SDL_SCANCODE_K])
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
	}


	if (!App->input->keyboard[SDL_SCANCODE_K] && !App->input->keyboard[SDL_SCANCODE_I])
	{
		if (state == DOWN)
			state = IDLE_DOWN;

		else if (state == UP)
			state = IDLE_UP;

		else if (state == IDLE_DOWN)
			counterReturn++;

		else if (state == IDLE_UP)
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
		position.x++;
		position.y--;
		break;
	case 4:
		position.x++;
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
		position.y--;
		break;
	case 12:
		position.x++;
		break;
	case 13:
		position.x++;
		position.y--;
		break;
	}

	// Draw everything --------------------------------------
	SDL_Rect ship;

	ship = animationShip->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - ship.h, &ship);

	return UPDATE_CONTINUE;
}

//cleanup?