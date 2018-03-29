#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio() {

}

//Destructor
ModuleAudio::~ModuleAudio() {}

//Initialization
bool ModuleAudio::Init() {
	bool ret = true;
	int init;
	init = Mix_Init(MIX_INIT_OGG);
	return ret;
}

update_status ModuleAudio::Update() {
	return update_status::UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp() {
	bool ret = true;
	SDL_Quit();
	return ret;
}