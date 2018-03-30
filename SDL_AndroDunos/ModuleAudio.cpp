#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module(){
	//Initialize all ModuleAudio pointers to nullptr
	for (int i = 0; i < MAX_BGMS; ++i) {
		bgms[i] = nullptr;
	}
	bgm = nullptr;

	for (int i = 0; i < MAX_FXS; ++i) {
		fxs[i] = nullptr;
	}
	fx = nullptr;

}

ModuleAudio::~ModuleAudio() {

}
// Called before audio is available
bool ModuleAudio::Init() {

	LOG("Init Audio library");
	bool ret = true;
	Mix_Init(MIX_INIT_OGG);
	

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		LOG("Error: %s", Mix_GetError());
		ret = false;
	}

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags) {

		LOG("Could not initialize mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}
	return ret;
}

update_status ModuleAudio::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAudio::Update()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAudio::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp() {

	LOG("Freeing Audio library");

	if (bgm != nullptr) {
		Mix_FreeMusic(bgm);
	}

	for (int i = 0; i < MAX_BGMS; ++i) {
		Mix_FreeMusic(bgms[i]);
	}
	for (int i = 0; i < MAX_FXS; ++i) {
		Mix_FreeChunk(fxs[i]);
	}


	Mix_Quit();
	SDL_CloseAudio();
	return true;
}



Mix_Music *const ModuleAudio::LoadBgm(const char* path) {
	bgm = Mix_LoadMUS(path);
	if (!bgm) {
		LOG("Mix_LoadMUS: %s", Mix_GetError());
	}
	else {
		if (bgms[MAX_BGMS - 1] != nullptr) {
			LOG("BGMS aren't empty");
		}
		else {
			for (int i = 0; i < MAX_BGMS; ++i) {
				if (bgms[i] == nullptr)
					bgms[i] = bgm;
			}
		}
	}
	return bgm;
}

//Load new fx from file path
Mix_Chunk *const ModuleAudio::LoadFx(const char* path) {
	fx = Mix_LoadWAV(path);
	if (!fx) {
		LOG("Mix_LoadWAV: %s", Mix_GetError());
	}
	else {
		if (fxs[MAX_FXS - 1] != nullptr) {
			LOG("FXS aren't empty");
		}
		else {
			for (int i = 0; i < MAX_FXS; ++i) {
				if (fxs[i] == nullptr)
					fxs[i] = fx;
			}
		}
	}
	return fx;
}