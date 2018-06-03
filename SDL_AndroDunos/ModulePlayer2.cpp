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
	state = IDLE;

	for (int i = 0; i < 5; i++)
		ship[i].PushBack({ 100,i * 23,32,23 });

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			fire[i].PushBack({ j * 12,120 + i * 10,12,10 });
		}
		fire[i].speed = 0.8f;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			anim_ultimate[i].PushBack({ 100 + j * 32,i * 23,32,22 });
		}
		anim_ultimate[i].speed = 0.9f;
	}

	hp = 3;
	type_weapon = 1;
	powerup_s = 1;
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

	time_bomb = init_time = SDL_GetTicks(); //Timer

	if (powerup_u > 0)
		if (App->shield2->IsEnabled() == false) {
			App->shield2->Enable();
		}
	destroyed = false;
	dead = false;
	
	player_col = App->collision->AddCollider({ position.x + 14,position.y + 4,21, 13 }, COLLIDER_PLAYER, this);
	
	//font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	//score = 0;
	blink = true;
	
	god_mode_die = true;
	fx_laser1 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-1_(Main_Ships).wav");
	fx_laser2 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-2_(Main_Ships).wav");
	fx_laser3 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-3_(Main_Ships).wav");
	fx_laser4 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-4_(Main_Ships).wav");
	explosion_player = App->audio->Loadfx("Assets/Audio/Player_Death_Explosion.wav");
	type_change_fx = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");

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
			blink = true;
		}
		else {
			player_col->type = COLLIDER_NONE;
			god_mode = true;
		}
	}
	if (god_mode == true && god_mode_die == false) {
		if (blink)	blink = false;
		else blink = true;
	}
	//Respawn 

	if ((App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_DOWN) && dead == true && App->ui->credit > 0) { //Pressing 2
		
		hp = 3;
		App->ui->credit--;
		
		god_mode_die = true;
		blink = true;
		state = CLEAR;
		init_time = SDL_GetTicks();
		position.x = App->render->camera.x / 3;
		position.y = App->render->camera.y / 3 + 71;
		dead = false;
		

		
	}

	if (god_mode_die == true) {  //Winky winky
		if (current_time < 2500) {
			player_col->type = COLLIDER_DEAD;
			if (blink)
				blink = false;
			else blink = true;
			/*if (position.x <= App->render->camera.x / 3 + 44)
				position.x++;*/
		}

		else {
			if (god_mode == false)
				player_col->type = COLLIDER_PLAYER;
			blink = true;
			god_mode_die = false;
			hp_down = false;
			state = IDLE;
		}
	}

	//Dead
	if (hp <= 0)
	{
		LOG("Player2 Dead ---");
		dead = true;
		player_col->type = COLLIDER_NONE;
	
	}
	//Alive
	if (hp > 0 && god_mode_die == false && god_mode == false)
	{
		player_col->type = COLLIDER_PLAYER;
	}

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_REPEAT)
		charge = true;
	else charge = false;

	if ((App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_UP) && charged)
		Ultimate();

	//powerup+
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		if (powerup_s < MAX_POWERUP)
			powerup_s++;
		if (powerup_b < 5)
			powerup_b++;
		if (powerup_m < 5)
			powerup_m++;
	}
	if (powerup_u > 0)
		if (App->shield2->IsEnabled() == false) {
			App->shield2->Enable();
		}

	// input
	//controller input
	//change weapon
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_X] == KEY_STATE::KEY_DOWN) {
		App->audio->PlayFx(type_change_fx);
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
		Shoot();
		BombandMissile();
	}

	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN && hp != 7)
		hp++;

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_DOWN)
		if (hp > 0) {
			Shoot();
			if (time_bomb < SDL_GetTicks() - 1500) {
				BombandMissile();
				time_bomb = SDL_GetTicks();
			}
		}

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
	States();

	player_col->SetPos(position.x+3, position.y+4);

	if (position.x < App->render->camera.x / 3)
		position.x = App->render->camera.x / 3;
	if (position.x > App->render->camera.x / 3 + SCREEN_WIDTH - 40)
		position.x = App->render->camera.x / 3 + SCREEN_WIDTH - 40;
	if (position.y < App->render->camera.y / 3)
		position.y = App->render->camera.y / 3;
	if (position.y > App->render->camera.y / 3 + SCREEN_HEIGHT - 17)
		position.y = App->render->camera.y / 3 + SCREEN_HEIGHT - 17;

	// Draw everything --------------------------------------
	Animation *ship_state = ship;
	if (charged)
		ship_state = anim_ultimate;

	if (hp > 0) {														//Render Ship
		if (blink)
			App->render->Blit(graphics, position.x, position.y, &ship_state[current_anim].GetCurrentFrame());
		App->render->Blit(graphics, position.x - fire[current_anim].frames->w + 1, position.y + 5, &fire[current_anim].GetCurrentFrame());
	}

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
	App->audio->UnLoadFx(type_change_fx);
	App->audio->UnLoadFx(explosion_player);
	App->audio->UnLoadFx(fx_laser4);
	App->audio->UnLoadFx(fx_laser3);
	App->audio->UnLoadFx(fx_laser2);
	App->audio->UnLoadFx(fx_laser1);

	if (player_col != nullptr)
		player_col->to_delete = true;
	return true;
}

void ModulePlayer2::OnCollision(Collider* col1, Collider* col2) 
{
	if (col1 == player_col && dead == false && App->fade->IsFading() == false && hp_down == false && col2->type != COLLIDER_TYPE::COLLIDER_BONUS && col2->type != COLLIDER_TYPE::COLLIDER_POWERUP && col2->type != COLLIDER_TYPE::COLLIDER_ONE_UP)
	{
		App->audio->PlayFx(explosion_player);
		hp--;
		hp_down = true;
		//animationShip->reset();
		App->particles->AddParticle(App->particles->explosion_player1, position.x + 15, position.y - 2);



		if (hp <= 0 && App->player1->hp <= 0) {
			if (App->stage1->IsEnabled())
				App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
			else if (App->stage4->IsEnabled())
				App->fade->FadeToBlack((Module*)App->stage4, (Module*)App->gameover);
		}



		else { //Respawn

			if (powerup_s > 1)
				powerup_s--;
			god_mode_die = true;
			state = CLEAR;
			init_time = SDL_GetTicks();
			position.x = App->render->camera.x / 3;
			position.y = App->render->camera.y / 3 + 127;
		}
		
	}
}

void ModulePlayer2::States() {
	switch (state)
	{
	case DOWN:
		current_anim = 4;
		break;
	case IDLE_DOWN:
		current_anim = 3;
		break;
	case IDLE:
		current_anim = 2;

		if (counterMoved > 0 || counterMoved2 > 0)
		{
			counterMoved = 0;
			counterMoved2 = 0;
		}

		break;
	case IDLE_UP:
		current_anim = 1;
		break;
	case UP:
		current_anim = 0;
		break;
	case CLEAR:
		//animationShip = &clear;
		break;
	}
}

void ModulePlayer2::BombandMissile() {
	switch (type_weapon) {
	case 1:
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_1, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_1, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			break;
		}
		break;
	case 2:
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	case 3:
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	case 4:
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);

			break;
		case 2:	//more damage ?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:	//more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	}
	switch (powerup_m) {
	case 1:
		App->particles->AddParticle(App->particles->missile, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 2:
		App->particles->AddParticle(App->particles->missile, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 3:
		App->particles->AddParticle(App->particles->missile2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 4:
		App->particles->AddParticle(App->particles->missile2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 5:
		App->particles->AddParticle(App->particles->missile2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 6:
		App->particles->AddParticle(App->particles->missile2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	case 7:
		App->particles->AddParticle(App->particles->missile2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		break;
	}
}
void ModulePlayer2::Shoot() {
	switch (type_weapon) {
	case 1:
		App->audio->PlayFx(fx_laser1);
		switch (powerup_s) {
		case 1:
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 33, position.y + 16, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_1_base, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 38, position.y + 9, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5:
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y - 1, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 42, position.y + 7, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 42, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y + 23, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 6:
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y - 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 42, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 42, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_2_fat, position.x + 33, position.y + 27, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 7:
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 33, position.y - 8, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 42, position.y + 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 42, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_1_6, position.x + 33, position.y + 25, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_1, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_1_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB);
			App->particles->AddParticle(App->particles->bomb_1_1, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			App->particles->AddParticle(App->particles->bomb_1_2, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2, BOMB_DELAY);
			break;
		}
		break;
	case 2:
		App->audio->PlayFx(fx_laser2);

		switch (powerup_s) {
		case 1:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_back, position.x, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_back, position.x, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_back, position.x, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonaluthin, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonaldthin, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonaluthin, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonaldthin, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_4, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonalu, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonald, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_4, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 6:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 47, position.y + 9, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 18, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonalu, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonald, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_4, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 7:
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_7_fat, position.x + 47, position.y + 9, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_1_front, position.x + 38, position.y + 20, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonalu, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_3_diagonald, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_2_4, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_2_1, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_2, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_2_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	case 3:
		App->audio->PlayFx(fx_laser3);

		switch (powerup_s) {
		case 1:
			App->particles->AddParticle(App->particles->laser_3_1_0, position.x + 20, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser_3_2_diagonalupfront, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_2_diagonaldownfront, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser_3_2_diagonalupfront, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_2_diagonaldownfront, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_3_diagonalupback, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_3_diagonaldownback, position.x + 5, position.y + 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser_3_4_diagonalupfront, position.x + 5, position.y + 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_4_diagonaldownfront, position.x + 5, position.y + 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_4_diagonaldownback, position.x + 5, position.y + 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_4_diagonalupback, position.x + 5, position.y + 2, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5:
			App->particles->AddParticle(App->particles->laser_3_5_diagonalupfront, position.x - 3, position.y - 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_5_diagonaldownfront, position.x - 3, position.y - 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_5_diagonaldownback, position.x - 3, position.y - 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_5_diagonalupback, position.x - 3, position.y - 5, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 6:
			App->particles->AddParticle(App->particles->laser_3_6_diagonalupfront, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_6_diagonaldownfront, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_6_diagonaldownback, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_6_diagonalupback, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 7:
			App->particles->AddParticle(App->particles->laser_3_7_diagonalupfront, position.x - 13, position.y - 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_7_diagonaldownfront, position.x - 13, position.y - 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_7_diagonaldownback, position.x - 13, position.y - 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_3_7_diagonalupback, position.x - 13, position.y - 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage
			App->particles->AddParticle(App->particles->bomb_3_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_3, position.x + 10, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_3_4, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	case 4:
		App->audio->PlayFx(fx_laser4);

		switch (powerup_s) {
		case 1:
			App->particles->AddParticle(App->particles->laser_4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_1_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser_4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_1_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_2_0, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser_4_4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_4_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_3_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser_4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_1_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5:
			App->particles->AddParticle(App->particles->laser_4_4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_5_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_5_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 6:
			App->particles->AddParticle(App->particles->laser_4_4_1, position.x + 18, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_4_2, position.x + 18, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_5_1, position.x + 28, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_5_2, position.x + 28, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_6, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 7:
			App->particles->AddParticle(App->particles->laser_4_5_1, position.x + 28, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_5_2, position.x + 28, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_7_1, position.x + 18, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_7_2, position.x + 18, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->laser_4_6, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		switch (powerup_b) {
		case 1:
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);

			break;
		case 2:	//more damage ?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 3: //more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 4:	//more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		case 5: //more damage?
			App->particles->AddParticle(App->particles->bomb_4_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_2, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_3, position.x, position.y + 15, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			App->particles->AddParticle(App->particles->bomb_4_4, position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
			break;
		}
		break;
	}
}

void ModulePlayer2::Ultimate() {
	switch (type_weapon) {
	case 1:

		break;
	case 2:
		for (int i = 0; i < 7; i++)
			App->particles->AddParticle(App->particles->ultimate2[i], position.x, position.y, COLLIDER_PLAYER_SHOT, 0, OWNER_PLAYER2);
		for (int i = 0; i < 7; i++)
			App->particles->AddParticle(App->particles->ultimate2[i], position.x, position.y, COLLIDER_PLAYER, 1000, OWNER_PLAYER2);
		break;
	case 3:

		break;
	case 4:

		break;
	}
}