#ifndef _MODULEAUDIO_H
#define _MODULEAUDIO_H
#include "Module.h"

class ModuleAudio :public Module {
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp();
};
#endif // !_MODULEAUDIO_H
