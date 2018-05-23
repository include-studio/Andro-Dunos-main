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

	ultimateBar.PushBack({ 0,81,64,6 }); // x, y, w, h
	ultimateBar.PushBack({ 0,88,64,6 });
	ultimateBar.PushBack({ 0,95,64,6 });
	ultimateBar.PushBack({ 0,102,64,6 });
	ultimateBar.PushBack({ 0,109,64,6 });
	ultimateBar.PushBack({ 0,116,64,6 });
	ultimateBar.PushBack({ 0,123,64,6 });
	ultimateBar.PushBack({ 0,130,64,6 });
	ultimateBar.PushBack({ 0,137,64,6 });
	ultimateBar.PushBack({ 0,144,64,6 });
	ultimateBar.PushBack({ 0,151,64,6 });
	ultimateBar.PushBack({ 0,158,64,6 });
	ultimateBar.PushBack({ 0,165,64,6 });
	ultimateBar.PushBack({ 0,172,64,6 });
	ultimateBar.PushBack({ 0,179,64,6 });
	ultimateBar.PushBack({ 0,186,64,6 });
	ultimateBar.PushBack({ 0,193,64,6 });
	ultimateBar.PushBack({ 0,200,64,6 });
	ultimateBar.PushBack({ 0,207,64,6 });
	ultimateBar.PushBack({ 0,214,64,6 });
	ultimateBar.PushBack({ 0,221,64,6 });
	ultimateBar.PushBack({ 0,228,64,6 });
	ultimateBar.PushBack({ 0,235,64,6 });
	ultimateBar.PushBack({ 0,242,64,6 });
	ultimateBar.PushBack({ 0,249,64,6 });
	ultimateBar.PushBack({ 0,256,64,6 });
	ultimateBar.PushBack({ 0,263,64,6 });
	ultimateBar.PushBack({ 0,270,64,6 });
	ultimateBar.PushBack({ 0,277,64,6 });
	ultimateBar.PushBack({ 68,82,64,6 }); // x, y, w, h
	ultimateBar.PushBack({ 68,89,64,6 });
	ultimateBar.PushBack({ 68,96,64,6 });
	ultimateBar.PushBack({ 68,103,64,6 });
	ultimateBar.PushBack({ 68,110,64,6 });
	ultimateBar.PushBack({ 68,117,64,6 });
	ultimateBar.PushBack({ 68,124,64,6 });
	ultimateBar.PushBack({ 68,131,64,6 });
	ultimateBar.PushBack({ 68,138,64,6 });
	ultimateBar.PushBack({ 68,145,64,6 });
	ultimateBar.PushBack({ 68,152,64,6 });
	ultimateBar.PushBack({ 68,159,64,6 });
	ultimateBar.PushBack({ 68,166,64,6 });
	ultimateBar.PushBack({ 68,173,64,6 });
	ultimateBar.PushBack({ 68,180,64,6 });
	ultimateBar.PushBack({ 68,187,64,6 });
	ultimateBar.PushBack({ 68,194,64,6 });
	ultimateBar.PushBack({ 68,201,64,6 });
	ultimateBar.PushBack({ 68,208,64,6 });
	ultimateBar.PushBack({ 68,215,64,6 });
	ultimateBar.PushBack({ 68,222,64,6 });
	ultimateBar.PushBack({ 68,229,64,6 });
	ultimateBar.PushBack({ 68,236,64,6 });
	ultimateBar.PushBack({ 68,243,64,6 });
	ultimateBar.PushBack({ 68,250,64,6 });
	ultimateBar.PushBack({ 68,257,64,6 });
	ultimateBar.PushBack({ 68,264,64,6 });
	ultimateBar.PushBack({ 68,271,64,6 });
	ultimateBar.PushBack({ 68,278,64,6 });
	ultimateBar.PushBack({ 136,82,64,6 }); // x, y, w, h
	ultimateBar.PushBack({ 136,89,64,6 });
	ultimateBar.PushBack({ 136,96,64,6 });
	ultimateBar.PushBack({ 136,103,64,6 });
	ultimateBar.PushBack({ 136,110,64,6 });

	ultimateBar.loop = false;
	ultimateBar.speed = 1.0f;

	animationUltimateCharged = nullptr;

	//ultimateCharged.PushBack({ 136,117,64,6 });
	////ultimateCharged.PushBack({ 136,128,64,4 }); 
	////ultimateCharged.PushBack({ 136,137,64,1 });
	ultimateCharged.PushBack({ 136,142,64,5 }); // x, y, w, h
	ultimateCharged.PushBack({ 136,150,64,7 });
	ultimateCharged.PushBack({ 136,161,64,7 });
	ultimateCharged.PushBack({ 136,170,64,7 });
	ultimateCharged.PushBack({ 136,180,64,7 });

	ultimateCharged.loop = true;
	ultimateCharged.speed = 1.0f;
	
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
		App->fonts->BlitText(30, 6, font_score1, score1_text);
		App->fonts->BlitText(10, 6, font_score1, "P1");

		//score2
		sprintf_s(score2_text, 10, "%7d", score2);
		App->fonts->BlitText(210, 6, font_score2, score2_text);
		App->fonts->BlitText(190, 6, font_score2, "P2");

		//highscore print
		sprintf_s(HighScore_text, 13, "%7d", high_score);
		App->fonts->BlitText(120, 7, font_highscore, HighScore_text);
		App->fonts->BlitText(100, 7, font_highscore, "HI-");
	}

	if (App->stage4->IsEnabled() == true && App->gameover->IsEnabled() == false) {
		//score1
		sprintf_s(score1_text, 10, "%7d", score1);
		App->fonts->BlitText(30, 6, font_score1, score1_text);
		App->fonts->BlitText(10, 6, font_score1, "P1");

		//score2
		sprintf_s(score2_text, 10, "%7d", score2);
		App->fonts->BlitText(210, 6, font_score2, score2_text);
		App->fonts->BlitText(190, 6, font_score2, "P2");

		//highscore print
		sprintf_s(HighScore_text, 13, "%7d", high_score);
		App->fonts->BlitText(120, 7, font_highscore, HighScore_text);
		App->fonts->BlitText(100, 7, font_highscore, "HI-");
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
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 50, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 60, 22, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 6) {
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 50, 22, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 5) {
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 40, 22, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 4) {
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 30, 22, &life1_rect, 0.0f);
		}

		if (App->player1->hp == 3) {
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
			App->render->Blit(user_interface, 20, 22, &life1_rect, 0.0f);
		}
		if (App->player1->hp == 2) {
			App->render->Blit(user_interface, 10, 22, &life1_rect, 0.0f);
		}
	}

	if (App->player2->IsEnabled() == true) {
		if (App->player2->hp == 7) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 230, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 240, 22, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 6) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 230, 22, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 5) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 220, 22, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 4) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 210, 22, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 3) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
			App->render->Blit(user_interface, 200, 22, &life2_rect, 0.0f);
		}
		if (App->player2->hp == 2) {
			App->render->Blit(user_interface, 190, 22, &life2_rect, 0.0f);
		}
	}

	//ultimate bar
	if (App->player1->ultimate1 == true) {
		animationUltimateBar = &ultimateBar;
		SDL_Rect Rect_ultimateBar;
		Rect_ultimateBar = animationUltimateBar->GetCurrentFrame();
		App->render->Blit(user_interface, 80, 22, &Rect_ultimateBar, 0.0f);
		ultimateBar.loop = false;

		if (ultimateBar.current_frame >= ultimateBar.last_frame - 1) {

			animationUltimateCharged = &ultimateCharged;
			SDL_Rect Rect_UltimateCharged;
			Rect_UltimateCharged = animationUltimateCharged->GetCurrentFrame();
			App->render->Blit(user_interface, 80, 22, &Rect_UltimateCharged, 0.0f); 

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
		App->render->Blit(user_interface, 230, 22, &Rect_ultimateBar, 0.0f);
		ultimateBar.loop = false;

		if (ultimateBar.current_frame >= ultimateBar.last_frame - 1) {

			animationUltimateCharged = &ultimateCharged;
			SDL_Rect Rect_UltimateCharged;
			Rect_UltimateCharged = animationUltimateCharged->GetCurrentFrame();
			App->render->Blit(user_interface, 230, 22, &Rect_UltimateCharged, 0.0f);

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
				App->render->Blit(user_interface, 10, 20, &gameover_rect, 0.0f);
			}
			//countdown
			if (current_time1 > 2000 && current_time1 <= 9000) {
				//word
				App->render->Blit(user_interface, 10, 20, &miniCoundown_rect, 0.0f);
				//numbers
				animationMiniContinueNum = &miniContinueNum;
				SDL_Rect Rect_miniContinueNum;
				Rect_miniContinueNum = animationMiniContinueNum->GetCurrentFrame();
				App->render->Blit(user_interface, 190, 20, &Rect_miniContinueNum, 0.0f);
				miniContinueNum.loop = false;
			}
			//gameover shorter when countdown finishes
			if (current_time1 > 9000 && current_time1 <= 10000)
			{
				App->render->Blit(user_interface, 10, 20, &gameover_rect, 0.0f);
			}
			//insert or press depending on credits
			if (current_time1 >= 10000) {
				//no credits == insert
				if (credit <= 0) {
					animationInsertCoin = &insertCoin;
					SDL_Rect Rect_InsertCoin;
					Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
					App->render->Blit(user_interface, 10, 20, &Rect_InsertCoin, 0.0f);
					insertCoin.loop = true;
				}
				//yes credits == press
				if (credit > 0) {
					animationPress1p = &press1p;
					SDL_Rect Rect_Press1p;
					Rect_Press1p = animationPress1p->GetCurrentFrame();
					App->render->Blit(user_interface, 10, 20, &Rect_Press1p, 0.0f);
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
				App->render->Blit(user_interface, 190, 20, &gameover_rect, 0.0f);
			}
			//countdown
			if (current_time1 > 2000 && current_time1 <= 9000) {
				//word
				App->render->Blit(user_interface, 10, 20, &miniCoundown_rect, 0.0f);
				//numbers
				animationMiniContinueNum = &miniContinueNum;
				SDL_Rect Rect_miniContinueNum;
				Rect_miniContinueNum = animationMiniContinueNum->GetCurrentFrame();
				App->render->Blit(user_interface, 280, 20, &Rect_miniContinueNum, 0.0f);
				miniContinueNum.loop = false;
			}
			//gameover shorter when countdown finishes
			if (current_time1 > 9000 && current_time1 <= 10000)
			{
				App->render->Blit(user_interface, 190, 20, &gameover_rect, 0.0f);
			}
			//insert or press depending on credits
			if (current_time1 >= 10000) {
				//no credits == insert
				if (credit <= 0) {
					animationInsertCoin = &insertCoin;
					SDL_Rect Rect_InsertCoin;
					Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
					App->render->Blit(user_interface, 190, 20, &Rect_InsertCoin, 0.0f);
					insertCoin.loop = true;
				}
				//yes credits == press
				if (credit > 0) {
					animationPress2p = &press2p;
					SDL_Rect Rect_Press2p;
					Rect_Press2p = animationPress2p->GetCurrentFrame();
					App->render->Blit(user_interface, 171, 20, &Rect_Press2p, 0.0f);
					press2p.loop = true;
				}
			}
		}
	}
	
	if (App->player2->IsEnabled() == false && App->player1->IsEnabled() == true) {

		//insert
		if (credit <= 0) {
			animationInsertCoin = &insertCoin;
			SDL_Rect Rect_InsertCoin;
			Rect_InsertCoin = animationInsertCoin->GetCurrentFrame();
			App->render->Blit(user_interface, 190, 20, &Rect_InsertCoin, 0.0f);
			insertCoin.loop = true;
		}
		//press
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
