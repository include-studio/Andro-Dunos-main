//#include "Globals.h"
//#include "Application.h"
//#include "ModuleTextures.h"
//#include "ModuleAudio.h"
//#include "ModuleInput.h"
//#include "ModuleRender.h"
//#include "SDL/include/SDL_timer.h"
//#include "ModuleFonts.h"
//#include "ModuleFadeToBlack.h"
//#include "ModuleUI.h"
//#include "ModulePlayer1.h"
//#include "ModuleEnemies.h"
//#include <stdio.h>
//#include "ModuleStageClear.h"

//
//ModuleUI::ModuleUI(){}
//
//ModuleUI::~ModuleUI(){}
//
//bool ModuleUI::Start()
//{
//	LOG("Loading intro");
//	font_score = App->fonts->Load("Assets/font_score.png", "1234567890P", 1);
//	//coins_font = = App->fonts->Load("Assets/coins_font.png", "1234567890P", 1);
//
//	return true;
//}
//
//update_status ModuleUI::Update()
//{
//
//	if (App->player1->score > top_score) {
//		top_score = App->player1->score;
//	}
//
//	sprintf_s(score_text, 10, "%7d", top_score);
//	App->fonts->BlitText(20, 20, font_score, score_text);
//
//	//if (App->stageclear->IsEnabled() == true) {
//	//}
//
//	/*sprintf_s(coins_text, 10, "%7d", coins);
//	App->fonts->BlitText(250, 210, coins_font, coins_text);*/
//
//	/*if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN) {
//	App->audio->Loadfx("");
//	coins++;
//	}*/
//
//	/*if (coins == 0) {
//		blit insertcoins
//	}*/
//
//	//if (App->player1->IsEnabled() == true) {
//	//	
//	//	if (App->player1->hp == 3) {
//	//		//blit 3 lives
//	//	}
//	//	if (App->player1->hp >= 2) {
//	//		//blit 2 lives
//	//	}
//	//	else {
//	//		//blit 1 live
//	//	}
//	//}
//
//	return UPDATE_CONTINUE;
//}