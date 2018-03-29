#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
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

	down.PushBack({ 0,76,39,16 });
	down.PushBack({ 43,76,39,16 });
	down.PushBack({ 85,76,39,16 });
	down.PushBack({ 85,104,39,17 });
	down.PushBack({ 43,104,39,17 });
	down.PushBack({ 2,104,39,17 });
	down.speed = 0.5f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ships.png");
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1) {
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1) {
		current_animation = &up;
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 0) //if up is 0, that animation resets to 0
		up.reset();

	if (App->input->keyboard[SDL_SCANCODE_S] == 1) {
		current_animation = &down;
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 0)
		down.reset();

	
	// Draw everything --------------------------------------
	SDL_Rect ship;
	if (current_animation == &up || current_animation == &down) {	//only animation up and down have end animation
		ship = current_animation->end_animation();						//this check if the the animation is at its last frame, then return the rect of last frame or use GetCurrentFrame() (see it in Animation.h)
	}
	else ship = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - ship.h, &ship);
	
	return UPDATE_CONTINUE;
}