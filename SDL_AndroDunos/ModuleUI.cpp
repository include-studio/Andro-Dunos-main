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

ModuleUI::ModuleUI() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start()
{
	LOG("Loading intro");

	user_interface = App->textures->Load("Assets/Fonts/user_interface.png");

	credits_rect.x = 0;
	credits_rect.y = 0;
	credits_rect.w = 45;//38 for credit
	credits_rect.h = 8;




	//font_score = App->fonts->Load("Assets/font_score.png", "1234567890P", 1); //not needed for the moment
	font_score2 = App->fonts->Load("Assets/Fonts/red_font_high_score.png", "HI-1234567890", 1);
	font_credits = App->fonts->Load("Assets/Fonts/credits.png", "0123456789", 1);

	credit = 0;

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading user interface")

	App->textures->Unload(user_interface);

	return true;
}
update_status ModuleUI::Update()
{

	//highscore
	if (App->player1->score > high_score) {
		high_score = App->player1->score;
	}
	if (App->stage1->IsEnabled() == true && App->gameover->IsEnabled() == false) {
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
		
		if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN) {
			App->audio->Loadfx("Assets/Audio/COIN_inserted.wav");
			credit++;
		}

		sprintf_s(credits_text, 17, "%7d", credit);

		if (credit == 0) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, 230, 200, &credits_rect, 0.0f);
			App->fonts->BlitText(280, 200, font_credits, "00");
		}

		else if (credit == 1) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, 230, 200, &credits_rect, 0.0f);
			App->fonts->BlitText(280, 200, font_credits, "01");
		}

		else if (credit >= 2) {
			credits_rect.w = 45;
			App->render->Blit(user_interface, 230, 200, &credits_rect, 0.0f);
			if (credit < 10) {
				App->fonts->BlitText(280, 200, font_credits, "0");
				App->fonts->BlitText(240, 200, font_credits, credits_text);
			}
			else 
				App->fonts->BlitText(240, 200, font_credits, credits_text);
		}

		//need (&& players are dead)
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
			credit -= 2;
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
			credit --;
	}
	

	//if (App->player1->IsEnabled() == true) {
	//	
	//	if (App->player1->hp == 3) {
	//		//blit 3 lives
	//	}
	//	if (App->player1->hp >= 2) {
	//		//blit 2 lives
	//	}
	//	else {
	//		//blit 1 live
	//	}
	//}

	return UPDATE_CONTINUE;
}
