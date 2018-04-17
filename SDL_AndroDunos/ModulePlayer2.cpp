#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"


ModulePlayer2::ModulePlayer2()
{
	state = IDLE;

	animationShip = nullptr;

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
	bool insert2 = false;
	graphics = App->textures->Load("assets/ships.png");
	position.x = SCREEN_WIDTH / 3;
	position.y = SCREEN_HEIGHT * 2 / 3;

	destroyed = false;
	type_weapon = 1;
	player2_col = App->collision->AddCollider({ position.x,position.y,39, 17 }, COLLIDER_PLAYER, this);
	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		if (god_mode == false) {

			player2_col->type = COLLIDER_NONE;
			god_mode = true;
		}
		else if (god_mode == true) {

			god_mode = false;
			player2_col->type = COLLIDER_PLAYER;
		}
	}

	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->audio->Loadfx("Assets/Laser_Shot_Type_CHANGE.wav");
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}

	//type 1
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN && type_weapon == 1) {
		App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y - 12, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y - 4, COLLIDER_PLAYER_SHOT);
	}

	//type 2
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN && type_weapon == 2) {
		App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y - 4, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser2_2, position.x, position.y - 4, COLLIDER_PLAYER_SHOT);
	}

	//type 3
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN && type_weapon == 3) {
		App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y -4, COLLIDER_PLAYER_SHOT);
	}

	//type 4
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN && type_weapon == 4) {
		App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y -4, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y -4, COLLIDER_PLAYER_SHOT);
	}

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

	player2_col->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	SDL_Rect ship;

	ship = animationShip->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y, &ship);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->CleanUp();
	App->particles->CleanUp();

	if (player2_col != nullptr)
		player2_col->to_delete = true;
	return true;
}

void ModulePlayer2::OnCollision(Collider* col1, Collider* col2) 
{
	if (col1 == player2_col && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->stage2, (Module*)App->gameover);

		App->particles->AddParticle(App->particles->mini_explosion, position.x, position.y, COLLIDER_NONE, 150);
		App->particles->AddParticle(App->particles->mini_explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
		App->particles->AddParticle(App->particles->mini_explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
		App->particles->AddParticle(App->particles->mini_explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);

		destroyed = true;
	}
}