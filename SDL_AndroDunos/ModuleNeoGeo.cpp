#include "Globals.h"
#include "Application.h"
#include "ModuleViscoGames.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNeoGeo.h"
#include "ModuleAudio.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

#define SNKWIDTH 72
#define NeoGeoWIDTH 227
#define MachineWIDTH 133
#define MAX_W_ALPH 255 

ModuleNeoGeo::ModuleNeoGeo()
{
	
	animationNeoGeo = nullptr;
	animationSNK = nullptr;
	animationMachine1 = nullptr;
	animationMachine2 = nullptr;

	NeoGeo.PushBack({ 0, 0, 227, 40 });
	NeoGeo.PushBack({ 0, 40, 227, 40 });
	NeoGeo.PushBack({ 0, 80, 227, 40 });
	NeoGeo.PushBack({ 0, 120, 227, 40 });
	NeoGeo.PushBack({ 0, 160, 227, 40 });
	NeoGeo.PushBack({ 0, 200, 227, 40 });
	NeoGeo.PushBack({ 0, 240, 227, 40 });
	NeoGeo.PushBack({ 0, 280, 227, 40 });
	NeoGeo.PushBack({ 0, 320, 227, 40 });
	NeoGeo.PushBack({ 0, 360, 227, 40 });
	NeoGeo.PushBack({ 0, 400, 227, 40 });
	NeoGeo.PushBack({ 0, 440, 227, 40 });
	NeoGeo.PushBack({ 0, 480, 227, 40 });
	NeoGeo.PushBack({ 0, 520, 227, 40 });
	NeoGeo.PushBack({ 0, 560, 227, 40 });
	NeoGeo.PushBack({ 0, 600, 227, 40 });
	NeoGeo.PushBack({ 0, 640, 227, 40 });
	NeoGeo.PushBack({ 0, 680, 227, 40 });
	NeoGeo.PushBack({ 0, 720, 227, 40 });
	NeoGeo.PushBack({ 0, 760, 227, 40 });
	NeoGeo.PushBack({ 0, 800, 227, 40 });
	NeoGeo.PushBack({ 0, 840, 227, 40 });
	NeoGeo.PushBack({ 0, 880, 227, 40 });
	NeoGeo.PushBack({ 0, 920, 227, 40 });
	NeoGeo.PushBack({ 0, 960, 227, 40 });
	NeoGeo.PushBack({ 0, 1000, 227, 40 });
	NeoGeo.PushBack({ 0, 1040, 227, 40 });
	NeoGeo.PushBack({ 0, 1080, 227, 40 });
	NeoGeo.PushBack({ 0, 1120, 227, 40 });
	NeoGeo.PushBack({ 0, 1160, 227, 40 });
	NeoGeo.PushBack({ 0, 1200, 227, 40 });
	NeoGeo.PushBack({ 0, 1240, 227, 40 });
	NeoGeo.PushBack({ 0, 1280, 227, 40 });
	NeoGeo.PushBack({ 0, 1320, 227, 40 });
	NeoGeo.PushBack({ 0, 1360, 227, 40 });
	NeoGeo.PushBack({ 0, 1400, 227, 40 });
	NeoGeo.PushBack({ 0, 1440, 227, 40 });
	NeoGeo.PushBack({ 0, 1480, 227, 40 });
	NeoGeo.PushBack({ 0, 1520, 227, 40 });
	NeoGeo.PushBack({ 0, 1560, 227, 40 });
	NeoGeo.PushBack({ 0, 1600, 227, 40 });
	NeoGeo.PushBack({ 0, 1640, 227, 40 });
	NeoGeo.PushBack({ 0, 1680, 227, 40 });
	NeoGeo.PushBack({ 0, 1720, 227, 40 });
	NeoGeo.PushBack({ 0, 1760, 227, 40 });
	NeoGeo.PushBack({ 0, 1800, 227, 40 });
	NeoGeo.PushBack({ 0, 1840, 227, 40 });

	NeoGeo.loop = false;

	NeoGeo.speed = 0.5f;

	SNK.PushBack({ 17,35,72,19 });
	SNK.PushBack({ 94,35,72,19 });
	SNK.PushBack({ 169,35,72,19 });

	SNK.PushBack({ 18,64,72,19 });
	SNK.PushBack({ 94,64,72,19 });
	SNK.PushBack({ 170,64,72,19 });
	
	SNK.PushBack({ 18,90,72,19 });
	SNK.PushBack({ 94,90,72,19 });
	SNK.PushBack({ 170,91,72,19 });

	SNK.PushBack({ 18,114,72,19 });
	SNK.PushBack({ 94,114,72,19 });
	SNK.PushBack({ 169,114,72,19 });

	SNK.PushBack({ 17,140,72,19 });
	SNK.PushBack({ 94,140,72,19 });
	SNK.PushBack({ 170,140,72,19 });

	SNK.PushBack({ 17,164,72,19 });
	SNK.PushBack({ 94,164,72,19 });
	SNK.PushBack({ 171,164,72,19 });

	SNK.loop = false;

	SNK.speed = 0.2f;

	Machine1.PushBack({ 0,0,7,14 });//MAX
	Machine1.PushBack({ 0,0,14,14 });

	Machine1.PushBack({ 0,0,19,14 });
	Machine1.PushBack({ 0,0,25,14 });

	Machine1.PushBack({ 0,0,30,14 });
	Machine1.PushBack({ 0,0,35,14 });

	Machine1.PushBack({ 0,0,49,14 });//330
	Machine1.PushBack({ 0,0,53,14 });

	Machine1.PushBack({ 0,0,58,14 });
	Machine1.PushBack({ 0,0,62,14 });

	Machine1.PushBack({ 0,0,68,14 });
	Machine1.PushBack({ 0,0,72,14 });

	Machine1.PushBack({ 0,0,83,14 });//MEGA
	Machine1.PushBack({ 0,0,90,14 });

	Machine1.PushBack({ 0,0,98,14 });
	Machine1.PushBack({ 0,0,101,14 });

	Machine1.PushBack({ 0,0,105,14 });
	Machine1.PushBack({ 0,0,110,14 });

	Machine1.PushBack({ 0,0,115,14 });
	Machine1.PushBack({ 0,0,121,14 });
	Machine1.PushBack({ 0,0,126,14 });

	Machine1.loop = false;

	Machine1.speed = 0.2f;

	Machine2.PushBack({ 0,17,0,13 });//PRO-
	Machine2.PushBack({ 0,17,4,13 });

	Machine2.PushBack({ 0,17,10,13 });
	Machine2.PushBack({ 0,17,14,13 });

	Machine2.PushBack({ 0,17,21,13 });
	Machine2.PushBack({ 0,17,26,13 });

	Machine2.PushBack({ 0,17,34,13 });
	Machine2.PushBack({ 0,17,39,13 });

	Machine2.PushBack({ 0,17,46,13 });//GEAR
	Machine2.PushBack({ 0,17,51,13 });

	Machine2.PushBack({ 0,17,58,13 });
	Machine2.PushBack({ 0,17,62,13 });

	Machine2.PushBack({ 0,17,67,13 });
	Machine2.PushBack({ 0,17,72,13 });

	Machine2.PushBack({ 0,17,79,13 });
	Machine2.PushBack({ 0,17,83,13 });

	Machine2.PushBack({ 0,17,93,13 });//SPEC
	Machine2.PushBack({ 0,17,98,13 });

	Machine2.PushBack({ 0,17,104,13 });
	Machine2.PushBack({ 0,17,108,13 });

	Machine2.PushBack({ 0,17,114,13 });
	Machine2.PushBack({ 0,17,118,13 });

	Machine2.PushBack({ 0,17,124,13 });
	Machine2.PushBack({ 0,17,129,13 });
	Machine2.PushBack({ 0,17,133,13 });

	Machine2.loop = false;

	Machine2.speed = 0.2f;

	copyright.x = 126;
	copyright.y = 0;
	copyright.w = 8;
	copyright.h = 8;

	//White fade - Flash position
	white.x = 0;
	white.y = 0;
	white.w = SCREEN_WIDTH * SCREEN_SIZE;
	white.h = SCREEN_HEIGHT * SCREEN_SIZE;

	W_alph = MAX_W_ALPH;

	//White fade - Flash position
	black.x = 0;
	black.y = 0;
	black.w = SCREEN_WIDTH * SCREEN_SIZE;
	black.h = SCREEN_HEIGHT * SCREEN_SIZE;
}

ModuleNeoGeo::~ModuleNeoGeo()
{}

// Load assets
bool ModuleNeoGeo::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	init_time = SDL_GetTicks(); //Timer


	neogeo = App->textures->Load("Assets/neogeo.png");
	snk = App->textures->Load("Assets/snk_animation.png");
	machine = App->textures->Load("Assets/snk_intro_font.png");
	
	
	App->audio->Load("assets/01_Neo_Geo_Logo.ogg");

	return ret;
}

// Load assets
bool ModuleNeoGeo::CleanUp()
{
	LOG("Unloading MainMenu stage");

	App->textures->Unload(neogeo);
	App->textures->Unload(snk);
	App->textures->Unload(machine);

	return true;
}

// Update: draw background
update_status ModuleNeoGeo::Update()
{
	//Pause Music
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		if (music_pasued == false) {

			Mix_PauseMusic();
			music_pasued = true;
		}
		else if (music_pasued == true) {
			Mix_ResumeMusic();
			music_pasued = false;

		}
	}
	//Time
	current_time = SDL_GetTicks() - init_time;

	// Draw everything --------------------------------------	
	animationNeoGeo = &NeoGeo;
	
	SDL_Rect animation_Neo;

	animation_Neo = animationNeoGeo->GetCurrentFrame();

	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, W_alph); //Flash White
	SDL_RenderFillRect(App->render->renderer, &black);
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, NULL);//Flash Black
	App->render->Blit(neogeo, SCREEN_WIDTH / 2 - NeoGeoWIDTH / 2, 52, &animation_Neo); //52 comes from a Cross-multiplication between the emulator and the resolution


	//Start snk when animation neogeo finishes
	if (NeoGeo.current_frame >= NeoGeo.last_frame - 1) {

		animationMachine1 = &Machine1;
		SDL_Rect animation_Machine1;
		animation_Machine1 = animationMachine1->GetCurrentFrame();
		App->render->Blit(machine, SCREEN_WIDTH / 2 - MachineWIDTH / 2 , 113, &animation_Machine1); //113 comes from a Cross-multiplication between the emulator and the resolution

	}


	if (Machine1.current_frame >= Machine1.last_frame - 1) {

		animationMachine2 = &Machine2;
		SDL_Rect animation_Machine2;
		animation_Machine2 = animationMachine2->GetCurrentFrame();
		App->render->Blit(machine, SCREEN_WIDTH / 2 - MachineWIDTH / 2 , 130, &animation_Machine2); //130 comes from a Cross-multiplication between the emulator and the resolution

	}

	if (Machine2.current_frame >= Machine2.last_frame - 1) {

		animationSNK = &SNK;
		SDL_Rect animation_SNK;
		animation_SNK = animationSNK->GetCurrentFrame();
		App->render->Blit(snk, SCREEN_WIDTH / 2 - SNKWIDTH / 2, 161, &animation_SNK); //161 comes from a Cross-multiplication between the emulator and the resolution
	}

	if (SNK.current_frame >= SNK.last_frame - 1) {

		App->render->Blit(machine, 272, 57, &copyright); //272 and 57 comes from a Cross-multiplication between the emulator and the resolution
	}

	// Make so pressing C the background is loaded
	if (App->input->keyboard[SDL_SCANCODE_C])
	{
		App->fade->FadeToBlack(this, App->visco, 0.5);
		Mix_PauseMusic();
		current_time = 0;
	}

	//White fade - Flash 
	if(current_time >= 200){
		if (W_alph > 0) {
			SDL_RenderFillRect(App->render->renderer, &white);
			W_alph -= 3;
		}
	}

	//Neogeo Pause Audio & go to Viscogames
	if (current_time >= 7000) {
		App->fade->FadeToBlack(this, App->visco, 0.5);
		Mix_PauseMusic();
		current_time = 0;
	}
	
	return UPDATE_CONTINUE;
}




