#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_events.h"

#define MAX_KEYS 300

typedef unsigned char Uint8;

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	SDL_Event e;
	
	SDL_GameController *controller = NULL;
	KEY_STATE keyboard[MAX_KEYS];
};

#endif // __ModuleInput_H__