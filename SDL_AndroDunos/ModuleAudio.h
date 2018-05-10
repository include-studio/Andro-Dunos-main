#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 50

class ModuleAudio :public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Start();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	bool PlayFx(unsigned int id, int repeat = 0);
	unsigned int Loadfx(const char* path);
	bool UnLoadFx(unsigned int id);
	

private:

	
	Mix_Chunk* fx[MAX_FX];

	uint last_fx = 1;

	int volume_fx = 20;
	int volume_music = 10;
public:
	Mix_Music * music;
	Mix_Music* stage4;
};

//typedef struct _Mix_Music Mix_Music;
//struct Mix_Chunk;
//
//class ModuleAudio : public Module
//{
//public:
//	ModuleAudio();
//	~ModuleAudio();
//
//	bool Init();
//	bool CleanUp();
//
//	void PlayMusic(const char* path, int = -1);
//
//	Mix_Music* const LoadBgm(const char* path);
//	Mix_Chunk* const LoadFx(const char* path);
//
//public:
//	Mix_Music * bgms[MAX_BGMS];
//	Mix_Music *bgm = nullptr;
//	Mix_Chunk *fxs[MAX_FXS];
//	Mix_Chunk *fx = nullptr;
//	
//
//};

#endif //__ModuleAudio_H__
