
#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

//#define MAX_BGMS 5
//#define MAX_FXS 30

class ModuleAudio :public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Start();
	bool CleanUp();
	Mix_Music *music;
	Mix_Chunk*fx;
	
	void Load(const char* path);
	void Loadfx(const char* path);

	int volume_fx = 20;
	int volume_music = 10;


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

#endif //__ModuleRenderer_H__
