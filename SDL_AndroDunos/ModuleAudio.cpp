#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() { };
ModuleAudio::~ModuleAudio() { };

bool ModuleAudio::Start()
{
	LOG("Init Audio library");
	bool ret = true;

	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load support for the PNG image format
	int audioflags = MIX_INIT_OGG;

	int initted = Mix_Init(audioflags);

	if ((initted) != audioflags)
	{
		LOG("Could not initialize Audio lib. MIX_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}
	
	return ret;
}

bool ModuleAudio::CleanUp() {

	LOG("Freeing Audio library");
	
	if(music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	//p2List_item<Mix_Chunk*>* item;

	for (uint i = 0; i < MAX_FX; i++)
	{
		Mix_FreeChunk(fx[i]);
	}

	//fx.clear();
	Mix_CloseAudio();


	//Mix_FreeMusic(music);
	//Mix_FreeChunk(fx);
	//music = NULL;
	//fx = NULL;

	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

//void ModuleAudio::Load(const char* path) {
//	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
//	LOG("Initing %s", path);
//	music = Mix_LoadMUS(path);
//	Mix_PlayMusic(music, -1);
//	Mix_VolumeMusic(volume_music); //Set up Volume Music
//
//}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	//if (music != NULL)
	//{
	//	if (fade_time > 0.0f)
	//	{
	//		Mix_FadeOutMusic((int)(fade_time * 1000.0f));
	//	}
	//	else
	//	{
	//		Mix_HaltMusic();
	//	}
	//	if (music != nullptr)
	//		Mix_FreeMusic(music);
	//}

	music = Mix_LoadMUS(path);

	Mix_VolumeMusic(volume_music);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}


unsigned int ModuleAudio::Loadfx(const char* path) {

	//LOG("Initing %s", path);
	//fx = Mix_LoadWAV(path);
	//Mix_PlayChannel(-1, fx, 0);

	//for (int i = 0; i < MAX_FX; i++) {
	//	Mix_VolumeChunk(fx[i], volume_fx); //Set up Volume Fx
	//}

	unsigned int ret = 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else {
		if (last_fx == MAX_FX)
			last_fx = 0;
		fx[last_fx] = chunk;
		ret = last_fx++;
	}
	
	return ret;

}

// Play WAV
bool ModuleAudio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}

bool ModuleAudio::UnLoadFx(unsigned int id)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		fx[id] = nullptr;
		Mix_FreeChunk(fx[id]);
		ret = true;
	}

	return ret;
}

//ModuleAudio::ModuleAudio() : Module()
//{
//	for (int i = 0; i < MAX_BGMS; ++i)
//		bgms[i] = { nullptr };
//	for (int i = 0; i < MAX_FXS; ++i)
//		fxs[i] = { nullptr };
//}
//
//ModuleAudio::~ModuleAudio() {
//
//}
//// Called before audio is available
//bool ModuleAudio::Init()
//{
//
//	LOG("Init Audio library");
//	bool ret = true;
//
//
//	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
//	{
//		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
//		ret = false;
//	}
//
//	//load support for the OGG format
//	int flags = MIX_INIT_OGG;
//	int init = Mix_Init(flags);
//
//	if (init != flags)
//	{
//		LOG("Could not initialize mixer lib. Mix_Init: %s", Mix_GetError());
//		ret = false;
//	}
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//		LOG("Error Mix_OpenAudio: %s", Mix_GetError());
//		ret = false;
//	}
//	
//	/*Mix_PlayChannel(-1, fx, 0);*/
//	return ret;
//}
//
//
//void ModuleAudio::PlayMusic(const char* path, int j) {
//	bgm = Mix_LoadMUS(path);
//	for (int i = 0; i < MAX_BGMS; i++) {
//		if (bgms[i] == bgm) {
//			Mix_PlayMusic(bgms[i], j);
//			bgm = nullptr;
//		}
//	}
//	if(bgm!=nullptr)
//	Mix_PlayMusic(LoadBgm(path), j);
//}
//
//// Called before quitting
//bool ModuleAudio::CleanUp() {
//
//	LOG("Freeing Audio library");
//
//	for (int i = 0; i < MAX_BGMS; ++i) {
//		if (bgms[i] != nullptr)
//			Mix_FreeMusic(bgms[i]);
//	}
//	LOG("BGMS Cleaned");
//	for (int i = 0; i < MAX_FXS; ++i) {
//		if (fxs[i] != nullptr)
//			Mix_FreeChunk(fxs[i]);
//	}
//	LOG("FXS Cleaned");
//	SDL_CloseAudio();
//	LOG("SDL_Audio closed");
//	Mix_Quit();
//	return true;
//}
//
//_Mix_Music *const ModuleAudio::LoadBgm(const char* path) {
//	bgm = Mix_LoadMUS(path);
//	if (!bgm) {
//		LOG("Mix_LoadMUS: %s", Mix_GetError());
//	}
//	else {
//		if (bgms[MAX_BGMS - 1] != nullptr) {
//			LOG("BGMS aren't empty");
//		}
//		else {
//			for (int i = 0; i < MAX_BGMS; ++i) {
//				if (bgms[i] == nullptr) {
//					bgms[i] = bgm;
//					i = MAX_BGMS;
//				}
//			}
//		}
//	}
//	return bgm;
//
//}
//
////Load new fx from file path
//Mix_Chunk *const ModuleAudio::LoadFx(const char* path) {
//	fx = Mix_LoadWAV(path);
//	if (!fx) {
//		LOG("Mix_LoadWAV: %s", Mix_GetError());
//	}
//	else {
//		if (fxs[MAX_FXS - 1] != nullptr) {
//			LOG("FXS aren't empty");
//		}
//		else {
//			for (int i = 0; i < MAX_FXS; ++i) {
//				if (fxs[i] == nullptr) {
//					fxs[i] = fx;
//					i = MAX_FXS;
//				}
//			}
//		}
//	}
//	return fx;
//}
