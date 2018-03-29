#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module(){
}

ModuleAudio::~ModuleAudio() {

}
//Init Audio
bool ModuleAudio::Init() {
	LOG("Init Audio library");
	bool ret = true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		LOG("Error: %s", Mix_GetError());
		ret = false;
	}
	return ret;
}
//CleanUp Audio
bool ModuleAudio::CleanUp() {

	LOG("Freeing Audio library");

	if (bgm != nullptr) {
		Mix_FreeMusic(bgm);
	}

	Mix_Quit();
	SDL_CloseAudio();
	return true;
}

//Load new audio
//Mix_Music