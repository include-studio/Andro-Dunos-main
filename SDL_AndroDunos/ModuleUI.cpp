#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include <stdio.h>
#include "ModuleStageClear.h"
#include "ModuleStage1.h"
#include "ModuleGameOver.h"
#include "ModuleNeoGeo.h"
#include "ModuleViscoGames.h"
#include "ModuleMainMenu.h"

ModuleUI::ModuleUI() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start()
{
	LOG("Loading intro");

	user_interface = App->textures->Load("Assets/Sprites/user_interface.png");

	credits_rect.x = 0;
	credits_rect.y = 0;
	credits_rect.w = 45;//38 for credit
	credits_rect.h = 8;

	life1_rect.x = 46;
	life1_rect.y = 0;
	life1_rect.w = 7;
	life1_rect.h = 7;

	life2_rect.x = 54;
	life2_rect.y = 0;
	life2_rect.w = 7;
	life2_rect.h = 7;

	animationGameover = nullptr;

	gameover.PushBack({ 0,33,79,11 }); // x, y, w, h
	gameover.PushBack({ 80,33,79,11 });

	gameover.loop = true;
	gameover.speed = 0.0225f;

	animationPress1p = nullptr;

	press1p.PushBack({ 0,21,124,11 }); // x, y, w, h
	press1p.PushBack({ 125,21,124,11 });

	press1p.loop = true;
	press1p.speed = 0.0225f;

	animationPress2p = nullptr;

	press2p.PushBack({ 0,9,124,11 }); // x, y, w, h
	press2p.PushBack({ 125,9,124,11 });

	press2p.loop = true;
	press2p.speed = 0.0225f;

	animationInsertCoin = nullptr;

	insertCoin.PushBack({ 0,45,86,11 }); // x, y, w, h
	insertCoin.PushBack({ 87,45,86,11 });

	insertCoin.loop = true;
	insertCoin.speed = 0.0225f;
	
	font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	font_score2 = App->fonts->Load("Assets/Fonts/red_font_high_score.png", "HI-1234567890", 1);
	font_credits = App->fonts->Load("Assets/Fonts/credits.png", "0123456789", 1);

	credit_fx = App->audio->Loadfx("Assets/Audio/COIN_inserted.wav");

	credit = 0;
	score = 0;

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading user interface")

	App->textures->Unload(user_interface);
	App->audio->UnLoadFx(credit_fx);
	App->fonts->UnLoad(font_score);

	return true;
}
update_status ModuleUI::Update()
{
	//highscore logic
	if (App->player1->score > high_score) {
		high_score = App->player1->score;
	}

	if (score > high_score) {
		high_score = score;
	}

	if (App->stage1->IsEnabled() == true && App->gameover->IsEnabled() == false) {
		
		//score2
		sprintf_s(score_text, 10, "%7d", score);
		App->fonts->BlitText(210, 6, font_score, score_text);
		App->fonts->BlitText(190, 6, font_score, "P2");

		//highscore print
		sprintf_s(HighScore_text, 13, "%7d", high_score);
		App->fonts->BlitText(120, 7, font_score2, HighScore_text);
		App->fonts->BlitText(100, 7, font_score2, "HI-");
	}

	//final score in stage
	//if (App->stageclear->IsEnabled() == true && App->gameover->IsEnabled() == false) {
	//	sprintf_s(score_text, 10, "%7d", App->player1->score);
	//	App->fonts->BlitText(20, 100, font_score, score_text);
	//}

	if (App->neogeo->IsEnabled() == false) {
		
		if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
			if (credit < 99) {
				App->audio->PlayFx(credit_fx);
				credit++;
				empty_credit = false;
			}
			
		}

		sprintf_s(credits_text, 17, "%7d", credit);

		if (credit == 0) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, 230, 210, &credits_rect, 0.0f);
			App->fonts->BlitText(280, 210, font_credits, "00");
		}

		else if (credit == 1) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, 230, 210, &credits_rect, 0.0f);
			App->fonts->BlitText(280, 210, font_credits, "01");
		}

		else if (credit >= 2) {
			credits_rect.w = 45;
			App->render->Blit(user_interface, 230, 210, &credits_rect, 0.0f);
			if (credit < 10) {
				App->fonts->BlitText(280, 210, font_credits, "0");
				App->fonts->BlitText(240, 210, font_credits, credits_text);
			}
			else 
				App->fonts->BlitText(240, 210, font_credits, credits_text);
		}

		//Main Menu Credits
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN && App->mainmenu->IsEnabled() == true) {
			credit--;
		}
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN &&  App->mainmenu->IsEnabled() == true && credit >= 2) {
			credit -= 2;
		}

		//if players are dead
		
		/*if (App->player2->destroyed == true)
			activate_credit == false;*/


		if ((App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller1,SDL_CONTROLLER_BUTTON_A)) && activate_credit == false && App->mainmenu->IsEnabled() == false && empty_credit == false) {
			
			credit--;
			activate_credit = true;
			
			
		}
			
		if ((App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) && App->mainmenu->IsEnabled() == false && empty_credit == false &&  activate_credit == false ) {
			credit--;
			activate_credit = true;
		}

		
	}
	
	if (App->player1->IsEnabled() == true) {
		if (App->player1->hp == 7) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 50, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 60, 20, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 6) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 50, 20, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 5) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 20, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 4) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 20, &life1_rect, 0.0f);
		}

		if (App->player1->hp == 3) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 20, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 2) {
			App->render->Blit(user_interface, 10, 20, &life1_rect, 0.0f);
		}
	}

	if (App->player2->IsEnabled() == true) {
		if (App->player2->hp == 7) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 230, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 240, 20, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 6) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 230, 20, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 5) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 20, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 4) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 20, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 3) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 20, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 2) {
			App->render->Blit(user_interface, 190, 20, &life2_rect, 0.0f);
		}
	}

	if (App->player2->IsEnabled() == true && App->player1->IsEnabled() == true) {
		if (App->player1->hp == 0) {// && App->player2->hp > 0
			animationGameover = &gameover;
			SDL_Rect Rect_Gameover;
			Rect_Gameover = animationGameover->GetCurrentFrame();
			App->render->Blit(user_interface, 10, 20, &Rect_Gameover, 0.0f);
			gameover.loop = true;

			//COUNTDOWN CONTINUE

			/*animationPress1p = &press1p;
			SDL_Rect Rect_Press1p;
			Rect_Press1p = animationPress1p->GetCurrentFrame();
			App->render->Blit(user_interface, 10, 20, &Rect_Press1p, 0.0f);
			press1p.loop = true;*/	
		}

		if (App->player2->hp == 0 ) { //&& App->player1->hp > 0
			animationGameover = &gameover;
			SDL_Rect Rect_Gameover;
			Rect_Gameover = animationGameover->GetCurrentFrame();
			App->render->Blit(user_interface, 10, 20, &Rect_Gameover, 0.0f);
			gameover.loop = true;

			//COUNTDOWN CONTINUE

			//animationPress2p = &press2p;
			//SDL_Rect Rect_Press2p;
			//Rect_Press2p = animationPress2p->GetCurrentFrame();
			//App->render->Blit(user_interface, 190, 20, &Rect_Press2p, 0.0f);
			//press2p.loop = true;
			
		}
	}
	
	if (App->player2->IsEnabled() == false && App->player1->IsEnabled() == true) {

		//INSERT COIN
		if (credit <= 0) {
			animationInsertCoin = &insertCoin;
			SDL_Rect Rect_InsertCoin;
			Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
			App->render->Blit(user_interface, 190, 20, &Rect_InsertCoin, 0.0f);
			press2p.loop = true;
		}

		if (credit > 0) {
			animationPress2p = &press2p;
			SDL_Rect Rect_Press2p;
			Rect_Press2p = animationPress2p->GetCurrentFrame();
			App->render->Blit(user_interface, 171, 20, &Rect_Press2p, 0.0f);
			press2p.loop = true;
		}
	}

	return UPDATE_CONTINUE;
}
