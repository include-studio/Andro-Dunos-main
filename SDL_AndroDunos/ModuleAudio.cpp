#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module() 
{
	for (int i = 0; i < MAX_BGMS; ++i)
		bgms[i] = nullptr;
	for (int i = 0; i < MAX_FXS; ++i)
		fxs[i] = nullptr;
}

ModuleAudio::~ModuleAudio() {

}
// Called before audio is available
bool ModuleAudio::Init()
{

	LOG("Init Audio library");
	bool ret = true;
	
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if (init != flags)
	{
		LOG("Could not initialize mixer lib. Mix_Init: %s", Mix_GetError());
		ret = true;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		LOG("Error Mix_OpenAudio: %s", Mix_GetError());
		ret = false;
	}

	LoadBgm("assets/Stage_1__The_Moon_Loop.ogg");
	LoadBgm("assets/06_Stage_Clear.ogg");
	LoadBgm("assets/07_Stage_2 -Mechanized-Unit-Loop.ogg");
	LoadFx("assets/01_Neo_Geo_Logo.ogg");
	Mix_PlayChannel(-1, fx, 0);
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

bool ModuleAudio::PlayMusic(int i, int j) {
	Mix_PlayMusic(bgms[i], j);
	return true;
}
// Called before quitting
bool ModuleAudio::CleanUp() {

	LOG("Freeing Audio library");

	for (int i = 0; i < MAX_BGMS; ++i) {
		if (bgms[i] != nullptr)
			Mix_FreeMusic(bgms[i]);
	}
	LOG("BGMS Cleaned");
	for (int i = 0; i < MAX_FXS; ++i) {
		if (fxs[i] != nullptr)
			Mix_FreeChunk(fxs[i]);
	}
	LOG("FXS Cleaned");
	SDL_CloseAudio();
	LOG("SDL_Audio closed");
	Mix_Quit();
	return true;
}

_Mix_Music *const ModuleAudio::LoadBgm(const char* path) {
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
				if (bgms[i] == nullptr) {
					bgms[i] = bgm;
					i = MAX_BGMS;
				}
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
				if (fxs[i] == nullptr) {
					fxs[i] = fx;
					i = MAX_FXS;
				}
			}
		}
	}
	return fx;
}