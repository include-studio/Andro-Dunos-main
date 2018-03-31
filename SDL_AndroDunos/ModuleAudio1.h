#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_audio.h"

#define MAX_BGMS 50
#define MAX_FXS 50

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

	_Mix_Music* const LoadBgm(const char* path);
	Mix_Chunk* const LoadFx(const char* path);

public:
	_Mix_Music *bgms[MAX_BGMS];
	_Mix_Music *bgm;
	Mix_Chunk *fxs[MAX_FXS];
	Mix_Chunk *fx;
};

#endif //__ModuleRenderer_H__
