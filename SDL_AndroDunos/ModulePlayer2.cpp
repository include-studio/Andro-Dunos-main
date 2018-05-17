#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleStage4.h"

#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer1.h"
#include "ModuleFonts.h"
#include "ModuleShieldPlayer2.h"
#include <stdio.h>
#include "Animation.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"


ModulePlayer2::ModulePlayer2()
{
	state = CLEAR;

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

	clear.PushBack({ 126,48,39,17 });
	clear.PushBack({ 0,0,10,20 });

	clear.speed = 0.4f;

	hp = 3;
	type_weapon = 1;
	powerup = 1;
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
	position.x = 0;
	position.y = SCREEN_HEIGHT * 2 / 3;

	init_time = SDL_GetTicks(); //Timer

	destroyed = false;
	dead = false;
	
	player_col = App->collision->AddCollider({ position.x + 14,position.y + 4,21, 13 }, COLLIDER_PLAYER, this);
	
	//font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	//score = 0;
	
	god_mode_die = true;
	laser1 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-1_(Main_Ships).wav");
	laser2 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-2_(Main_Ships).wav");
	laser3 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-3_(Main_Ships).wav");
	laser4 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-4_(Main_Ships).wav");
	explosion_player = App->audio->Loadfx("Assets/Audio/Player_Death_Explosion.wav");
	type_change = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	current_time = SDL_GetTicks() - init_time;

	if (god_mode != App->player1->god_mode) {
		if (god_mode) {
			player_col->type = COLLIDER_PLAYER;
			god_mode = false;
		}
		else {
			player_col->type = COLLIDER_NONE;
			god_mode = true;
		}
	}
	//Respawn 

	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_DOWN && dead == true && App->ui->credit > 0) { //Pressing 2
		hp = 3;
		App->ui->credit--;
		god_mode_die = true;
		state = CLEAR;
		init_time = SDL_GetTicks();
		position.x = App->render->camera.x / 3;
		position.y = App->render->camera.y / 3 + 71;
		dead = false;
	}

	if (god_mode_die == true) {  //Winky winky
		if (current_time < 2500) {
			player_col->type = COLLIDER_DEAD;
			//if (position.x <= App->render->camera.x / 3 + 44)
			//	position.x++;
		}

		else if (god_mode == false) {
			player_col->type = COLLIDER_PLAYER;
			god_mode_die = false;
			state = IDLE;
		}
	}

	//Dead
	if (hp <= 0)
	{
		dead = true;
		player_col->type = COLLIDER_NONE;
	
	}
	//Alive
	if (hp > 0 && god_mode_die == false && god_mode == false)
	{
		player_col->type = COLLIDER_PLAYER;
	}

	//powerup+
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
		powerup++;
	if (powerup > 4)
		powerup = 4;

	// input
	//controller input
	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_X] == KEY_STATE::KEY_DOWN) {
		App->audio->PlayFx(type_change);
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}

	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN && hp != 7)
		hp++;

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_DOWN)
		if (hp>0) Shoot();

	if (SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTX) > 6000)
		position.x += speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTX) < -6000)
		position.x -= speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) < -6000)
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) > 6000)
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
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

	if ((!App->input->keyboard[SDL_SCANCODE_DOWN] && !App->input->keyboard[SDL_SCANCODE_UP]) && (SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) < 6000 && SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) > -6000))
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
	//States
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
	case CLEAR:
		animationShip = &clear;
	}

	player_col->SetPos(position.x+14, position.y+4);

	if (position.x < App->render->camera.x / 3)
		position.x = App->render->camera.x / 3;
	if (position.x > App->render->camera.x / 3 + SCREEN_WIDTH - 40)
		position.x = App->render->camera.x / 3 + SCREEN_WIDTH - 40;
	if (position.y < App->render->camera.y / 3)
		position.y = App->render->camera.y / 3;
	if (position.y > App->render->camera.y / 3 + SCREEN_HEIGHT - 17)
		position.y = App->render->camera.y / 3 + SCREEN_HEIGHT - 17;

	// Draw everything --------------------------------------
	SDL_Rect ship;

	ship = animationShip->GetCurrentFrame();

	if (hp > 0)	       												//Render Ship
		App->render->Blit(graphics, position.x, position.y, &ship);

	//sprintf_s(score_text, 10, "%7d", score);

	//// Blit the text of the score in at the bottom of the screen	
	//App->fonts->BlitText(210, 6, font_score, score_text);
	//App->fonts->BlitText(190, 6, font_score, "P2");

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->Disable();
	App->particles->Disable();
	App->shield2->Disable();
	//App->fonts->UnLoad(font_score);
	App->audio->UnLoadFx(type_change);
	App->audio->UnLoadFx(explosion_player);
	App->audio->UnLoadFx(laser4);
	App->audio->UnLoadFx(laser3);
	App->audio->UnLoadFx(laser2);
	App->audio->UnLoadFx(laser1);

	if (player_col != nullptr)
		player_col->to_delete = true;
	return true;
}

void ModulePlayer2::OnCollision(Collider* col1, Collider* col2) 
{
	if (col1 == player_col && dead == false && App->fade->IsFading() == false && col2->type != COLLIDER_TYPE::COLLIDER_BONUS && col2->type != COLLIDER_TYPE::COLLIDER_POWER_S && col2->type != COLLIDER_TYPE::COLLIDER_ONE_UP)
	{
		App->audio->PlayFx(explosion_player);
		hp--;
		animationShip->reset();
		App->particles->AddParticle(App->particles->explosion_player1, position.x + 15, position.y - 2);


		if (hp <= 0) {
			if (App->player1->hp <= 0) 
			{


				if (App->stage1->IsEnabled())
					App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
				else if (App->stage4->IsEnabled())
					App->fade->FadeToBlack((Module*)App->stage4, (Module*)App->gameover);
				/*switch (App->player1->part_stagePlayer = 1)
				{
				case 0:
					App->player1->part_stagePlayer= 1;
					App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
					break;
				case 1:
					App->player1->part_stagePlayer = 0;
					App->fade->FadeToBlack((Module*)App->stage4, (Module*)App->gameover);
					break;
				}*/
			
			}
			
		}

		else { //Respawn

			god_mode_die = true;
			state = CLEAR;
			init_time = SDL_GetTicks();
			position.x = App->render->camera.x / 3;
			position.y = App->render->camera.y / 3 + 127;
		}
	}
}

void ModulePlayer2::Shoot() {
	switch (type_weapon) {
	case 1:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 16, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser1);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser1);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 9, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser1);
			break;
		}
		break;
	case 2:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser2_3, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser2);
			break;
		}
		break;
	case 3:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser3);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser3);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_3, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_4, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser3);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser3_5, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_6, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_7, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser3_8, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser3);
			break;
		}
		break;
	case 4:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser4);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser4);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_3_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser4);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->audio->PlayFx(laser4);
			break;
		}
		break;
	}
}