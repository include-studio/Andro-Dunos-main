#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleStage4.h"


#include "ModuleShieldPlayer1.h"
#include "SDL/include/SDL.h"
#include <stdio.h>

ModulePlayer1::ModulePlayer1()
{
	state = CLEAR;

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

	clear.PushBack({ 0,48,39,17 });
	clear.PushBack({ 0,0,10,20 });

	clear.speed = 0.4f;
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	init_time = SDL_GetTicks(); //Timer

	graphics = App->textures->Load("assets/Sprites/ships.png");
	position.x = 0;
	position.y = SCREEN_HEIGHT / 3;

	destroyed = false;
	dead = false;
	type_weapon = 1;
	powerup = 1;
	player_col = App->collision->AddCollider({ position.x+14,position.y+4,21,13 }, COLLIDER_PLAYER, this);
	hp = 3;
	font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	score = 0;
	god_mode_die = true;
	laser1 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-1_(Main_Ships).wav");
	laser2 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-2_(Main_Ships).wav");
	laser3 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-3_(Main_Ships).wav");
	laser4 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-4_(Main_Ships).wav");
	explosion_player = App->audio->Loadfx("Assets/Audio/Player_Death_Explosion.wav");
	type_change = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");

	return ret;
}

bool ModulePlayer1::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->Disable();
	App->particles->Disable();
	App->shield1->Disable();
	App->fonts->UnLoad(font_score);
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

// Update: draw background
update_status ModulePlayer1::Update()
{
	current_time = SDL_GetTicks() - init_time;

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

	//Respawn 

	if ((App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A)) && dead == true && App->ui->credit > 0) { //Pressing 1
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
			/*if (position.x <= App->render->camera.x / 3 + 44)
				position.x++;*/
		}
		
		else if(god_mode == false) {
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
	if (!SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A))
		stillpressed_a = false;

	if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) && !stillpressed_a) {
		shoot = true;
		stillpressed_a = true;
	}
	if (!SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_X))
		stillpressed_x = false;

	if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_X) && !stillpressed_x) {
		change = true;
		stillpressed_x = true;
	}
		//change weapon
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN || change) {
		change = false;
		App->audio->PlayFx(type_change);
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN && hp!=7)
		hp++;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || shoot) {
		if(hp>0) Shoot();
	}
		
		
	
	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTX) > 6000)
		position.x += speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTX) < -6000)
		position.x -= speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) < -6000)
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) > 6000)
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
	}
	// W A S D 
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
	//End WASD
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
	//Satates
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
		break;
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

	if (hp > 0)														//Render Ship
		App->render->Blit(graphics, position.x, position.y, &ship);
	
	sprintf_s(score_text, 10, "%7d", score);
	
	// Blit the text of the score in at the bottom of the screen	
	App->fonts->BlitText(30, 6, font_score, score_text);
	App->fonts->BlitText(10, 6, font_score, "P1");

	return UPDATE_CONTINUE;
}


void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == player_col && dead == false && App->fade->IsFading() == false && c2->type != COLLIDER_TYPE::COLLIDER_BONUS && c2->type != COLLIDER_TYPE::COLLIDER_POWER_S && c2->type != COLLIDER_TYPE::COLLIDER_ONE_UP)
	{
		App->audio->PlayFx(explosion_player);
		hp--;
		animationShip->reset();
		App->particles->AddParticle(App->particles->explosion_player1, position.x + 15, position.y - 2);

		if (hp <= 0) {
			if (App->player2->hp <= 0 || App->player2->IsEnabled() == false) 
			{
				
				if (App->stage1->IsEnabled())
					App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
				else if(App->stage4->IsEnabled())
					App->fade->FadeToBlack((Module*)App->stage4, (Module*)App->gameover);

				/*switch (part_stagePlayer)
				{
				case 0:
					part_stagePlayer = 1;
					App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
					break;
				case 1:
					part_stagePlayer = 0;
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
			position.y = App->render->camera.y / 3 +71;
		}
	}
}

void ModulePlayer1::Shoot() {
	shoot = false;

	switch (type_weapon) {
	case 1:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 16, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 9, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		}
		break;
	case 2:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_3, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		}
		break;
	case 3:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_3, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_4, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser3_5, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_6, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_7, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_8, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		}
		break;
	case 4:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_3_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		}
		break;
	}
}