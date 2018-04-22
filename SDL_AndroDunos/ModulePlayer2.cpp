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
#include "ModulePlayer1.h"
#include "ModuleFonts.h"
#include <stdio.h>
#include "Animation.h"
#include "ModuleUI.h"


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
	graphics = App->textures->Load("assets/Sprites/ships.png");
	position.x = SCREEN_WIDTH / 3;
	position.y = SCREEN_HEIGHT * 2 / 3;

	//destroyed = false;
	type_weapon = 1;
	player2_col = App->collision->AddCollider({ position.x,position.y,39, 17 }, COLLIDER_PLAYER, this);
	hp = 3;
	font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	score = 0;

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	if (god_mode != App->player1->god_mode) {
		if (god_mode) {
			player2_col->type = COLLIDER_PLAYER;
			god_mode = false;
		}
		else {
			player2_col->type = COLLIDER_NONE;
			god_mode = true;
		}
	}

	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
		powerup++;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		switch (type_weapon) {
		case 1:
			switch (powerup) {
			case 1:
				App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT,0,OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 16, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 3:
				App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 4:
				App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 9, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			default:			//in case that the power up is higher than gun power up, the default switch set power up to the last case
				powerup = 4;
				break;
			}
			break;
		case 2:
			switch (powerup) {
			case 1:
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 2:
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 3:
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 4:
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser2_3, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			default:
				powerup = 4;
				break;
			}
			break;
		case 3:
			switch (powerup) {
			case 1:
				App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 2:
				App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 3:
				App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_3, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_4, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 4:
				App->particles->AddParticle(App->particles->laser3_5, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_6, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_7, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser3_8, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			default:
				powerup = 4;
				break;
			}
			break;
		case 4:
			switch (powerup) {
			case 1:
				App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 2:
				App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 3:
				App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_2_1, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_3_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			case 4:
				App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				App->particles->AddParticle(App->particles->laser4_2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
				break;
			default:
				powerup = 4;
				break;
			}
			break;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT])
		position.x += speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_LEFT])
		position.x -= speedMoveShip;

	if (App->input->keyboard[SDL_SCANCODE_UP])
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN])
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
	}

	if (!App->input->keyboard[SDL_SCANCODE_DOWN] && !App->input->keyboard[SDL_SCANCODE_UP])
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

	//if (!destroyed ) //&& dead == false
		App->render->Blit(graphics, position.x, position.y, &ship);

	sprintf_s(score_text, 10, "%7d", score);

	// Blit the text of the score in at the bottom of the screen	
	App->fonts->BlitText(210, 6, font_score, score_text);
	App->fonts->BlitText(190, 6, font_score, "P2");

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->CleanUp();
	App->particles->CleanUp();
	App->fonts->UnLoad(font_score);

	if (player2_col != nullptr)
		player2_col->to_delete = true;
	return true;
}

//void ModulePlayer2::OnCollision(Collider* col1, Collider* col2)
//{
//	animationShip->reset();
//
//	App->particles->AddParticle(App->particles->explosion_player2, position.x + 15, position.y - 2);
//
//	state = DEAD;
//	
//}
void ModulePlayer2::OnCollision(Collider* col1, Collider* col2) 
{
	if (col1 == player2_col  && App->fade->IsFading() == false && col2->type != COLLIDER_TYPE::COLLIDER_BONUS && col2->type != COLLIDER_TYPE::COLLIDER_POWER_S) //&& destroyed == false
	{

		destroyed = true;

		hp--;

		animationShip->reset();
		if (hp <= 0)
			state = DEAD;
		else position.x -= SCREEN_WIDTH;

		App->particles->AddParticle(App->particles->explosion_player2, position.x + 15, position.y - 2);
	
		
	}
}