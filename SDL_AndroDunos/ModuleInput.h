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
	
	SDL_GameController *controller1 = nullptr;
	SDL_GameController *controller2 = nullptr;
	KEY_STATE keyboard[MAX_KEYS];
	KEY_STATE buttons1[SDL_CONTROLLER_BUTTON_MAX];
	KEY_STATE buttons2[SDL_CONTROLLER_BUTTON_MAX];
	SDL_GameControllerButton B[SDL_CONTROLLER_BUTTON_MAX];

};

#endif // __ModuleInput_H__