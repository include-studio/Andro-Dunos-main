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
#include "ModuleStage4.h"
#include "ModuleGameOver.h"
#include "ModuleNeoGeo.h"
#include "ModuleViscoGames.h"
#include "ModuleMainMenu.h"

#define SCREEN_MIDDLE 160 //For andro dunos' developers this is the middle (not 152)
#define SCORES_HEIGHT 7
#define WEAPONS_HEIGHT 17
#define HP_HEIGHT 25
#define CREDITS_HEIGHT 208
#define CREDITS_X 224
#define DEAD_UI_X 26

ModuleUI::ModuleUI() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start()
{
	LOG("Loading UI");
	

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

	miniCoundown_rect.x = 0;
	miniCoundown_rect.y = 57;
	miniCoundown_rect.w = 67;
	miniCoundown_rect.h = 11;

	gameover_rect.x = 0;
	gameover_rect.y = 33;
	gameover_rect.w = 79;
	gameover_rect.h = 11;

	normal1.x = 130;
	normal1.y = 174;
	normal1.w = 31;
	normal1.h = 7;

	reverse.x = 130;
	reverse.y = 185;
	reverse.w = 31;
	reverse.h = 7;

	laser3.x = 130;
	laser3.y = 208;
	laser3.w = 31;
	laser3.h = 7;

	way.x = 130;
	way.y = 196;
	way.w = 31;
	way.h = 7;

	fintrel.x = 130;
	fintrel.y = 219;
	fintrel.w = 31;
	fintrel.h = 7;

	hawk.x = 130;
	hawk.y = 230;
	hawk.w = 31;
	hawk.h = 7;

	normal3.x = 163;
	normal3.y = 219;
	normal3.w = 31;
	normal3.h = 7;

	laser4.x = 130;
	laser4.y = 241;
	laser4.w = 31;
	laser4.h = 7;

	homing.x = 163;
	homing.y = 230;
	homing.w = 31;
	homing.h = 7;

	rolling.x = 163;
	rolling.y = 174;
	rolling.w = 31;
	rolling.h = 7;

	side.x = 163;
	side.y = 185;
	side.w = 31;
	side.h = 7;

	front.x = 163;
	front.y = 208;
	front.w = 31;
	front.h = 7;

	rear.x = 163;
	rear.y = 196;
	rear.w = 31;
	rear.h = 7;

	animationMiniContinueNum = nullptr;

	miniContinueNum.PushBack({ 86,69,9,11 }); // x, y, w, h
	miniContinueNum.PushBack({ 76,69,9,11 });
	miniContinueNum.PushBack({ 66,69,9,11 });
	miniContinueNum.PushBack({ 56,69,9,11 });
	miniContinueNum.PushBack({ 46,69,9,11 }); //5 
	miniContinueNum.PushBack({ 36,69,9,11 });
	miniContinueNum.PushBack({ 26,69,9,11 });
	miniContinueNum.PushBack({ 16,69,9,11 });
	miniContinueNum.PushBack({ 10,69,5,11 });
	miniContinueNum.PushBack({ 0,69,9,11 }); //0

	miniContinueNum.loop = false;
	miniContinueNum.speed = 0.0225f;

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

	animationUltimateBar = nullptr;

	for(int i=0;i<3;i++)
		for (int j = 0; j < 29; j++) {
			ultimateBar.PushBack({ i * 64,81 + j * 7,64,7 });
			if (i == 2 && j > 8)
				break;
		}

	ultimateBar.loop = false;
	ultimateBar.speed = 0.5f;

	animationUltimateCharged = nullptr;

	for (int i = 0; i < 3; i++)
		ultimateCharged.PushBack({ 128,144 + i * 7,64,7 });

	ultimateCharged.loop = true;
	ultimateCharged.speed = 0.9f;
	
	font_score1 = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	font_score2 = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	font_highscore = App->fonts->Load("Assets/Fonts/red_font_high_score.png", "HI-1234567890", 1);
	font_credits = App->fonts->Load("Assets/Fonts/credits.png", "0123456789", 1);

	credit_fx = App->audio->Loadfx("Assets/Audio/COIN_inserted.wav");

	credit = 0;
	score1 = 0;
	score2 = 0;

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading user interface")

	App->textures->Unload(user_interface);
	App->audio->UnLoadFx(credit_fx);
	App->fonts->UnLoad(font_score1);
	App->fonts->UnLoad(font_score2);
	App->fonts->UnLoad(font_highscore);
	App->fonts->UnLoad(font_credits);
	credit_on = true;
	return true;
}
update_status ModuleUI::Update()
{
	//highscore logic
	if (score1 > high_score) {
		high_score = score1; //App->player1->score
	}

	if (score2 > high_score) {
		high_score = score2;
	}

	//scores
	if (App->stage1->IsEnabled() == true && App->gameover->IsEnabled() == false) {
		//score1
		sprintf_s(score1_text, 10, "%7d", score1);
		App->fonts->BlitText(35, SCORES_HEIGHT, font_score1, score1_text);
		App->fonts->BlitText(10, SCORES_HEIGHT, font_score1, "P1");

		//score2
		sprintf_s(score2_text, 10, "%7d", score2);
		App->fonts->BlitText(SCREEN_MIDDLE + 73, SCORES_HEIGHT, font_score2, score2_text);
		App->fonts->BlitText(SCREEN_MIDDLE + 48, SCORES_HEIGHT, font_score2, "P2");

		//highscore print
		sprintf_s(HighScore_text, 13, "%7d", high_score);
		App->fonts->BlitText(125, SCORES_HEIGHT + 1, font_highscore, HighScore_text);
		App->fonts->BlitText(104, SCORES_HEIGHT + 1, font_highscore, "HI-");
	}

	if (App->stage4->IsEnabled() == true && App->gameover->IsEnabled() == false) {
		//score1
		sprintf_s(score1_text, 10, "%7d", score1);
		App->fonts->BlitText(35, SCORES_HEIGHT, font_score1, score1_text);
		App->fonts->BlitText(10, SCORES_HEIGHT, font_score1, "P1");

		//score2
		sprintf_s(score2_text, 10, "%7d", score2);
		App->fonts->BlitText(SCREEN_MIDDLE + 73, SCORES_HEIGHT, font_score2, score2_text);
		App->fonts->BlitText(SCREEN_MIDDLE + 48, SCORES_HEIGHT, font_score2, "P2");

		//highscore print
		sprintf_s(HighScore_text, 13, "%7d", high_score);
		App->fonts->BlitText(125, SCORES_HEIGHT + 1, font_highscore, HighScore_text);
		App->fonts->BlitText(104, SCORES_HEIGHT + 1, font_highscore, "HI-");
	}

	//final score in stage
	/*if (App->stageclear->IsEnabled() == true && App->gameover->IsEnabled() == false) {
		sprintf_s(score_text, 10, "%7d", App->player1->score);
		App->fonts->BlitText(20, 100, font_score, score_text);
	}*/

	//credits
	if (App->neogeo->IsEnabled() == false) {

		if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN || App->input->buttons1[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_STATE::KEY_DOWN || App->input->buttons2[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_STATE::KEY_DOWN) {
			if (credit < 99) {
				App->audio->PlayFx(credit_fx);
				credit++;
				empty_credit = false;
			}
			
		}

		sprintf_s(credits_text, 17, "%7d", credit);

		if (credit == 0) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, CREDITS_X, CREDITS_HEIGHT, &credits_rect, 0.0f);
			App->fonts->BlitText(272, CREDITS_HEIGHT, font_credits, "00"); //280
		}

		else if (credit == 1) {
			credits_rect.w = 38;
			App->render->Blit(user_interface, CREDITS_X, CREDITS_HEIGHT, &credits_rect, 0.0f);
			App->fonts->BlitText(272, CREDITS_HEIGHT, font_credits, "01"); //280
		}

		else if (credit >= 2) {
			credits_rect.w = 45;
			App->render->Blit(user_interface, CREDITS_X, CREDITS_HEIGHT, &credits_rect, 0.0f);
			if (credit < 10) {
				App->fonts->BlitText(272, CREDITS_HEIGHT, font_credits, "0"); //280
				App->fonts->BlitText(232, CREDITS_HEIGHT, font_credits, credits_text); //240
			}
			else 
				App->fonts->BlitText(232, CREDITS_HEIGHT, font_credits, credits_text); //240
		}

		//Main Menu Credits
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN && App->mainmenu->IsEnabled() == true && credit_on == true) {
			credit--;
			credit_on = false;

		}
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN &&  App->mainmenu->IsEnabled() == true && credit >= 2 && credit_on == true) {
			credit -= 2;
			credit_on = false;

		}

		//if players are dead
		
		/*if (App->player2->destroyed == true)
			activate_credit == false;*/


		/*if ((App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller1,SDL_CONTROLLER_BUTTON_A)) && activate_credit == false && App->mainmenu->IsEnabled() == false && empty_credit == false) {
			
			credit--;
			activate_credit = true;
			
			
		}
			
		if ((App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->controller2, SDL_CONTROLLER_BUTTON_A)) && App->mainmenu->IsEnabled() == false && empty_credit == false &&  activate_credit == false ) {
			credit--;
			activate_credit = true;
		}*/

		
	}
	
	//hp
	if (App->player1->IsEnabled() == true) {
		if (App->player1->hp == 7) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 24, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 32, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 48, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 56, HP_HEIGHT, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 6) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 24, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 32, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 48, HP_HEIGHT, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 5) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 24, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 32, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, HP_HEIGHT, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 4) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 24, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 32, HP_HEIGHT, &life1_rect, 0.0f);
		}

		if (App->player1->hp == 3) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 24, HP_HEIGHT, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 2) {
			App->render->Blit(user_interface, 16, HP_HEIGHT, &life1_rect, 0.0f);
		}
	}

	if (App->player2->IsEnabled() == true) {
		if (App->player2->hp == 7) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 24, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 32, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 48, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 56, HP_HEIGHT, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 6) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 24, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 32, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 48, HP_HEIGHT, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 5) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 24, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 32, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, HP_HEIGHT, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 4) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 24, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 32, HP_HEIGHT, &life2_rect, 0.0f);
		}

		if (App->player2->hp == 3) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 24, HP_HEIGHT, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 2) {
			App->render->Blit(user_interface, SCREEN_MIDDLE + 16, HP_HEIGHT, &life2_rect, 0.0f);
		}
	}

	//weapon type UI
	if (App->player1->IsEnabled() == true && App->player1->hp > 0) {
		switch (App->player1->type_weapon)
		{
		case 1:
			App->render->Blit(user_interface, 8, WEAPONS_HEIGHT, &normal1, 0.0f);
			App->render->Blit(user_interface, 40, WEAPONS_HEIGHT, &fintrel, 0.0f);
			App->render->Blit(user_interface, 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, 104, WEAPONS_HEIGHT, &rolling, 0.0f);
			break;
		case 2:
			App->render->Blit(user_interface, 8, WEAPONS_HEIGHT, &reverse, 0.0f);
			App->render->Blit(user_interface, 40, WEAPONS_HEIGHT, &hawk, 0.0f);
			App->render->Blit(user_interface, 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, 104, WEAPONS_HEIGHT, &side, 0.0f);
			break;
		case 3:
			App->render->Blit(user_interface, 8, WEAPONS_HEIGHT, &laser3, 0.0f);
			App->render->Blit(user_interface, 40, WEAPONS_HEIGHT, &normal3, 0.0f);
			App->render->Blit(user_interface, 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, 104, WEAPONS_HEIGHT, &front, 0.0f);
			break;
		case 4:
			App->render->Blit(user_interface, 8, WEAPONS_HEIGHT, &way, 0.0f);
			App->render->Blit(user_interface, 40, WEAPONS_HEIGHT, &laser4, 0.0f);
			App->render->Blit(user_interface, 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, 104, WEAPONS_HEIGHT, &rear, 0.0f);
			break;
		}
	}

	if (App->player2->IsEnabled() == true && App->player2->hp > 0) {
		switch (App->player2->type_weapon)
		{
		case 1:
			App->render->Blit(user_interface, SCREEN_MIDDLE + 8, WEAPONS_HEIGHT, &normal1, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, WEAPONS_HEIGHT, &fintrel, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 104, WEAPONS_HEIGHT, &rolling, 0.0f);
			break;
		case 2:
			App->render->Blit(user_interface, SCREEN_MIDDLE + 8, WEAPONS_HEIGHT, &reverse, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, WEAPONS_HEIGHT, &hawk, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 104, WEAPONS_HEIGHT, &side, 0.0f);
			break;
		case 3:
			App->render->Blit(user_interface, SCREEN_MIDDLE + 8, WEAPONS_HEIGHT, &laser3, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, WEAPONS_HEIGHT, &normal3, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 104, WEAPONS_HEIGHT, &front, 0.0f);
			break;
		case 4:
			App->render->Blit(user_interface, SCREEN_MIDDLE + 8, WEAPONS_HEIGHT, &way, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 40, WEAPONS_HEIGHT, &laser4, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 72, WEAPONS_HEIGHT, &homing, 0.0f);
			App->render->Blit(user_interface, SCREEN_MIDDLE + 104, WEAPONS_HEIGHT, &rear, 0.0f);
			break;
		}
	}

	//ultimate bar
	if (App->player1->ultimate1 == true) {
		animationUltimateBar = &ultimateBar;
		SDL_Rect Rect_ultimateBar;
		Rect_ultimateBar = animationUltimateBar->GetCurrentFrame();
		App->render->Blit(user_interface, 72, HP_HEIGHT, &Rect_ultimateBar, 0.0f);
		ultimateBar.loop = false;

		if (ultimateBar.current_frame >= ultimateBar.last_frame - 1) {

			animationUltimateCharged = &ultimateCharged;
			SDL_Rect Rect_UltimateCharged;
			Rect_UltimateCharged = animationUltimateCharged->GetCurrentFrame();
			App->render->Blit(user_interface, 72, HP_HEIGHT, &Rect_UltimateCharged, 0.0f);

		}

		//if () {
		//	ultimateBar.reset();
		//	ultimateCharged.reset();
		//}
	}

	if (App->player2->ultimate2 == true) {
		animationUltimateBar = &ultimateBar;
		SDL_Rect Rect_ultimateBar;
		Rect_ultimateBar = animationUltimateBar->GetCurrentFrame();
		App->render->Blit(user_interface, SCREEN_MIDDLE + 72, HP_HEIGHT, &Rect_ultimateBar, 0.0f);
		ultimateBar.loop = false;

		if (ultimateBar.current_frame >= ultimateBar.last_frame - 1) {

			animationUltimateCharged = &ultimateCharged;
			SDL_Rect Rect_UltimateCharged;
			Rect_UltimateCharged = animationUltimateCharged->GetCurrentFrame();
			App->render->Blit(user_interface, SCREEN_MIDDLE + 72, HP_HEIGHT, &Rect_UltimateCharged, 0.0f);

		}

		//if () {
		//	ultimateBar.reset();
		//	ultimateCharged.reset();
		//}
	}

	//gameover/countdown/gameover/insert or press
	if (App->player2->IsEnabled() == true && App->player1->IsEnabled() == true) {
		if (App->player1->hp <= 0) {// && App->player2->hp > 0
			//Time
			if (game_over_time == true) {
				init_time1 = SDL_GetTicks();
				game_over_time = false;
			}

			current_time1 = SDL_GetTicks() - init_time1;
			
			//gameover longer
			if (current_time1 <= 2000 ){
				App->render->Blit(user_interface, DEAD_UI_X, WEAPONS_HEIGHT, &gameover_rect, 0.0f);
			}
			//countdown
			if (current_time1 > 2000 && current_time1 <= 9000) {
				//word
				App->render->Blit(user_interface, DEAD_UI_X, WEAPONS_HEIGHT, &miniCoundown_rect, 0.0f);
				//numbers
				animationMiniContinueNum = &miniContinueNum;
				SDL_Rect Rect_miniContinueNum;
				Rect_miniContinueNum = animationMiniContinueNum->GetCurrentFrame();
				App->render->Blit(user_interface, 104, WEAPONS_HEIGHT, &Rect_miniContinueNum, 0.0f);
				miniContinueNum.loop = false;
			}
			//gameover shorter when countdown finishes
			if (current_time1 > 9000 && current_time1 <= 10000)
			{
				App->render->Blit(user_interface, DEAD_UI_X, WEAPONS_HEIGHT, &gameover_rect, 0.0f);
			}
			//insert or press depending on credits
			if (current_time1 >= 10000) {
				//no credits == insert
				if (credit <= 0) {
					animationInsertCoin = &insertCoin;
					SDL_Rect Rect_InsertCoin;
					Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
					App->render->Blit(user_interface, DEAD_UI_X, WEAPONS_HEIGHT, &Rect_InsertCoin, 0.0f);
					insertCoin.loop = true;
				}
				//yes credits == press
				if (credit > 0) {
					animationPress1p = &press1p;
					SDL_Rect Rect_Press1p;
					Rect_Press1p = animationPress1p->GetCurrentFrame();
					App->render->Blit(user_interface, 9, WEAPONS_HEIGHT, &Rect_Press1p, 0.0f);
					press1p.loop = true;				
				}
			}
		}

		if (App->player2->hp <= 0 ) { //&& App->player1->hp > 0
			
									  //Time
			if (game_over_time == true) {
				init_time1 = SDL_GetTicks();
				game_over_time = false;
			}

			current_time1 = SDL_GetTicks() - init_time1;

			//gameover longer
			if (current_time1 <= 2000) {
				App->render->Blit(user_interface, SCREEN_MIDDLE + DEAD_UI_X, WEAPONS_HEIGHT, &gameover_rect, 0.0f);
			}
			//countdown
			if (current_time1 > 2000 && current_time1 <= 9000) {
				//word
				App->render->Blit(user_interface, SCREEN_MIDDLE + DEAD_UI_X, WEAPONS_HEIGHT, &miniCoundown_rect, 0.0f);
				//numbers
				animationMiniContinueNum = &miniContinueNum;
				SDL_Rect Rect_miniContinueNum;
				Rect_miniContinueNum = animationMiniContinueNum->GetCurrentFrame();
				App->render->Blit(user_interface, SCREEN_MIDDLE + 104, WEAPONS_HEIGHT, &Rect_miniContinueNum, 0.0f);
				miniContinueNum.loop = false;
			}
			//gameover shorter when countdown finishes
			if (current_time1 > 9000 && current_time1 <= 10000)
			{
				App->render->Blit(user_interface, SCREEN_MIDDLE + DEAD_UI_X, WEAPONS_HEIGHT, &gameover_rect, 0.0f);
			}
			//insert or press depending on credits
			if (current_time1 >= 10000) {
				//no credits == insert
				if (credit <= 0) {
					animationInsertCoin = &insertCoin;
					SDL_Rect Rect_InsertCoin;
					Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
					App->render->Blit(user_interface, SCREEN_MIDDLE + DEAD_UI_X, WEAPONS_HEIGHT, &Rect_InsertCoin, 0.0f);
					insertCoin.loop = true;
				}
				//yes credits == press
				if (credit > 0) {
					animationPress2p = &press2p;
					SDL_Rect Rect_Press2p;
					Rect_Press2p = animationPress2p->GetCurrentFrame();
					App->render->Blit(user_interface, SCREEN_MIDDLE + 9, WEAPONS_HEIGHT, &Rect_Press2p, 0.0f);
					press2p.loop = true;
				}
			}
		}
	}
	
	if (App->player2->IsEnabled() == false && App->player1->IsEnabled() == true) {

		//no credits == insert
		if (credit <= 0) {
			animationInsertCoin = &insertCoin;
			SDL_Rect Rect_InsertCoin;
			Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
			App->render->Blit(user_interface, SCREEN_MIDDLE + DEAD_UI_X, WEAPONS_HEIGHT, &Rect_InsertCoin, 0.0f);
			insertCoin.loop = true;
		}
		//yes credits == press
		if (credit > 0) {
			animationPress2p = &press2p;
			SDL_Rect Rect_Press2p;
			Rect_Press2p = animationPress2p->GetCurrentFrame();
			App->render->Blit(user_interface, SCREEN_MIDDLE + 9, WEAPONS_HEIGHT, &Rect_Press2p, 0.0f);
			press2p.loop = true;
		}
	}

	return UPDATE_CONTINUE;
}
