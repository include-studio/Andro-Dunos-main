#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleStage1.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include <stdio.h>

ModulePlayer1::ModulePlayer1()
{
	state = IDLE;

	animationShip = nullptr;

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


	upidle.speed = 0.5f;
	
	down.PushBack({ 2,104,39,17 });
	down.PushBack({ 43,104,39,17 });
	down.PushBack({ 85,104,39,17 });


	down.speed = 0.5f;

	downidle.PushBack({ 0,76,39,16 });
	downidle.PushBack({ 43,76,39,16 });
	downidle.PushBack({ 85,76,39,16 });

	downidle.speed = 0.5f;
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/Sprites/ships.png");
	position.x = SCREEN_WIDTH / 3;
	position.y = SCREEN_HEIGHT / 3;

	destroyed = false;
	type_weapon = 1;
	player_col = App->collision->AddCollider({ position.x,position.y,39,17 }, COLLIDER_PLAYER, this);
	hp = 3;
	font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	score = 0;

	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()
{

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (god_mode == false) {

			player_col->type = COLLIDER_NONE;
			god_mode = true;
		}
		else if (god_mode == true) {
			
			god_mode = false;
			player_col->type = COLLIDER_PLAYER;
		}
	}

	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) {
		App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}

	//type 1
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type_weapon == 1) {
				App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
	}

	//type 2
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type_weapon == 2) {
		App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 11, COLLIDER_PLAYER_SHOT);
	}

	//type 3
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type_weapon == 3) {
		App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
	}

	//type 4
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type_weapon == 4) {
		App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
	}

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
	player_col->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	SDL_Rect ship;

	ship = animationShip->GetCurrentFrame();

	if (!destroyed && dead == false)
		App->render->Blit(graphics, position.x, position.y, &ship);
	
	sprintf_s(score_text, 10, "%7d", score);
	
	// Blit the text of the score in at the bottom of the screen	
	App->fonts->BlitText(30, 6, font_score, score_text);
	App->fonts->BlitText(10, 6, font_score, "P1");

	return UPDATE_CONTINUE;
}

bool ModulePlayer1::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->CleanUp();
	App->particles->CleanUp();
	App->fonts->UnLoad(font_score);

	if (player_col != nullptr)
		player_col->to_delete = true;

	return true;
}

void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == player_col && destroyed == false && App->fade->IsFading() == false && c2->type != COLLIDER_TYPE::COLLIDER_ITEM)
	{
		hp--;
		animationShip->reset();

		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);

		//it has to be big_explosion
		App->particles->AddParticle(App->particles->explosion_player1, position.x + 15, position.y - 2);

		//if (hp == 0) {
		//	
		//	dead = true;
		//}

		destroyed = true;
	}
}