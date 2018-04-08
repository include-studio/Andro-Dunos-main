#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_BGMS 5
#define MAX_FXS 30

struct _Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();
	bool PlayMusic(int);

	_Mix_Music* const LoadBgm(const char* path);
	Mix_Chunk* const LoadFx(const char* path);

public:
	_Mix_Music *bgms[MAX_BGMS];
	Mix_Music *bgm = nullptr;
	Mix_Chunk *fxs[MAX_FXS];
	Mix_Chunk *fx = nullptr;
};

#endif //__ModuleRenderer_H__
